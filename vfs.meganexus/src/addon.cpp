// vfs.meganexus (MegaNexus Usenet) - Copyright (c) 2024-2026 MegaNexusMediaPlayer
// SPDX-License-Identifier: GPL-3.0-or-later - see LICENSE.txt. Built with Kodi's add-on headers
// (GPL-2.0-or-later) and OpenSSL (Apache-2.0, LICENSE-OpenSSL.txt).
//
// vfs.meganexus: Kodi opens mnxusenet://<token>/<name> through this add-on and reads the
// film straight from Usenet (usenet.cpp). MegaNexus writes the plan first:
// addon_data/plugin.video.meganexus/usenet/<token>.plan.

#include "usenet.h"

#include <kodi/AddonBase.h>
#include <kodi/Filesystem.h>
#include <kodi/addon-instance/VFS.h>

#include <cctype>
#include <cstdio>

#include <sys/stat.h>

namespace
{
constexpr double IDLE = 60.0;  // s a film's connections stay after it closed (a seek reopens it)
const char* FOLDER = "special://profile/addon_data/plugin.video.meganexus/usenet/";

struct Source
{
  std::shared_ptr<const mnx::Plan> plan;
  std::shared_ptr<mnx::Fetcher> fetcher;
  int handles = 0;
  double closed = 0;
};

struct Handle
{
  std::string token;
  std::unique_ptr<mnx::Stream> stream;
};

std::mutex g_mutex;
std::map<std::string, Source> g_sources;
std::thread g_reaper;
std::atomic<bool> g_stop{false};
std::string g_folder;

void Log(const std::string& text)
{
  kodi::Log(ADDON_LOG_INFO, "[MegaNexus] Usenet (native): %s", text.c_str());
}

bool ValidToken(const std::string& token)
{
  if (token.empty() || token.size() > 64)
    return false;
  for (char c : token)
  {
    if (!isxdigit(static_cast<unsigned char>(c)))
      return false;
  }
  return true;
}

// Kodi looks for files beside a film (film.edl, film.srt, ...): only the film itself is here
bool IsFilm(const kodi::addon::VFSUrl& url, const std::string& name)
{
  std::string file = url.GetFilename();
  size_t slash = file.find_last_of('/');
  if (slash != std::string::npos)
    file = file.substr(slash + 1);
  return !file.empty() && file == name;
}

std::string Folder()
{
  if (g_folder.empty())
    g_folder = kodi::vfs::TranslateSpecialProtocol(FOLDER);
  return g_folder;
}

void Reap()
{
  while (!g_stop)
  {
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::vector<std::shared_ptr<mnx::Fetcher>> gone;
    {
      std::lock_guard<std::mutex> lock(g_mutex);
      for (auto it = g_sources.begin(); it != g_sources.end();)
      {
        if (!it->second.handles && mnx::Now() - it->second.closed > IDLE)
        {
          gone.push_back(it->second.fetcher);
          it = g_sources.erase(it);
        }
        else
          ++it;
      }
    }
    for (auto& fetcher : gone)
      fetcher->Close();  // joined as the last reference goes, outside the lock
  }
}
}  // namespace

class CUsenetVFS : public kodi::addon::CInstanceVFS
{
public:
  explicit CUsenetVFS(const kodi::addon::IInstanceInfo& instance) : CInstanceVFS(instance) {}

  kodi::addon::VFSFileHandle Open(const kodi::addon::VFSUrl& url) override
  {
    std::string token = url.GetHostname();
    if (!ValidToken(token))
      return nullptr;
    std::shared_ptr<const mnx::Plan> plan;
    std::shared_ptr<mnx::Fetcher> fetcher;
    {
      std::lock_guard<std::mutex> lock(g_mutex);
      auto found = g_sources.find(token);
      if (found != g_sources.end())
      {
        ++found->second.handles;
        plan = found->second.plan;
        fetcher = found->second.fetcher;
      }
    }
    if (!plan)
    {
      auto loaded = std::make_shared<mnx::Plan>();
      std::string error;
      if (!mnx::LoadPlan(Folder() + token + ".plan", *loaded, error))
      {
        Log("can not open the film: " + error);
        return nullptr;
      }
      plan = loaded;
      fetcher = std::make_shared<mnx::Fetcher>(*loaded, Log);
      std::lock_guard<std::mutex> lock(g_mutex);
      auto found = g_sources.find(token);
      if (found != g_sources.end())  // opened twice at once: one source
      {
        plan = found->second.plan;
        fetcher->Close();
        fetcher = found->second.fetcher;
        ++found->second.handles;
      }
      else
      {
        g_sources[token] = Source{plan, fetcher, 1, 0};
        char text[160];
        snprintf(text, sizeof(text), "film %.2f GB, %zu pieces, %zu servers, keep %d, ahead %d",
                 plan->size / 1e9, plan->extents.size(), plan->servers.size(), plan->keep, plan->ahead);
        Log(text);
      }
    }
    if (!IsFilm(url, plan->name))
    {
      std::lock_guard<std::mutex> lock(g_mutex);
      auto found = g_sources.find(token);
      if (found != g_sources.end() && --found->second.handles <= 0)
      {
        found->second.handles = 0;
        found->second.closed = mnx::Now();
      }
      return nullptr;
    }
    auto* handle = new Handle{token, std::make_unique<mnx::Stream>(plan, fetcher)};
    handle->stream->SetLeaving(Folder() + "leaving");
    return handle;
  }

  bool Close(kodi::addon::VFSFileHandle context) override
  {
    auto* handle = static_cast<Handle*>(context);
    if (!handle)
      return false;
    handle->stream->Cancel();
    {
      std::lock_guard<std::mutex> lock(g_mutex);
      auto found = g_sources.find(handle->token);
      if (found != g_sources.end() && --found->second.handles <= 0)
      {
        found->second.handles = 0;
        found->second.closed = mnx::Now();
        int dropped = found->second.fetcher->DropAhead();
        if (dropped)
          Log("player stopped - " + std::to_string(dropped) + " articles read ahead not fetched");
      }
    }
    delete handle;
    return true;
  }

  ssize_t Read(kodi::addon::VFSFileHandle context, uint8_t* buffer, size_t size) override
  {
    auto* handle = static_cast<Handle*>(context);
    return handle ? static_cast<ssize_t>(handle->stream->Read(buffer, size)) : -1;
  }

  int64_t Seek(kodi::addon::VFSFileHandle context, int64_t position, int whence) override
  {
    auto* handle = static_cast<Handle*>(context);
    return handle ? handle->stream->Seek(position, whence) : -1;
  }

  int64_t GetLength(kodi::addon::VFSFileHandle context) override
  {
    auto* handle = static_cast<Handle*>(context);
    return handle ? handle->stream->Length() : 0;
  }

  int64_t GetPosition(kodi::addon::VFSFileHandle context) override
  {
    auto* handle = static_cast<Handle*>(context);
    return handle ? handle->stream->Position() : 0;
  }

  int GetChunkSize(kodi::addon::VFSFileHandle context) override { return 0; }

  bool IoControlGetSeekPossible(kodi::addon::VFSFileHandle context) override { return true; }

  int Stat(const kodi::addon::VFSUrl& url, kodi::vfs::FileStatus& buffer) override
  {
    // Kodi asks when it closes the film (the date for its library): answered from the plan
    std::string token = url.GetHostname();
    if (!ValidToken(token))
      return -1;
    uint64_t size = 0;
    std::string name;
    {
      std::lock_guard<std::mutex> lock(g_mutex);
      auto found = g_sources.find(token);
      if (found != g_sources.end())
      {
        size = found->second.plan->size;
        name = found->second.plan->name;
      }
    }
    std::string path = Folder() + token + ".plan";
    struct stat info{};
    if (stat(path.c_str(), &info) != 0)
      return -1;
    if (!size)
    {
      mnx::Plan plan;
      std::string error;
      if (!mnx::LoadPlan(path, plan, error))
        return -1;
      size = plan.size;
      name = plan.name;
    }
    if (!IsFilm(url, name))
      return -1;
    buffer.SetSize(size);
    buffer.SetModificationTime(info.st_mtime);
    buffer.SetAccessTime(info.st_mtime);
    buffer.SetStatusTime(info.st_mtime);
    buffer.SetIsDirectory(false);
    buffer.SetIsRegular(true);
    return 0;
  }

  bool Exists(const kodi::addon::VFSUrl& url) override
  {
    kodi::vfs::FileStatus status;
    return Stat(url, status) == 0;
  }

  bool DirectoryExists(const kodi::addon::VFSUrl& url) override { return false; }
};

class CMegaNexusVFS : public kodi::addon::CAddonBase
{
public:
  CMegaNexusVFS()
  {
    mnx::SetCaFile(kodi::vfs::TranslateSpecialProtocol("special://xbmc/system/certs/cacert.pem"));
    g_stop = false;
    g_reaper = std::thread(Reap);
  }

  ~CMegaNexusVFS() override
  {
    g_stop = true;
    if (g_reaper.joinable())
      g_reaper.join();
    std::lock_guard<std::mutex> lock(g_mutex);
    for (auto& source : g_sources)
      source.second.fetcher->Close();
    g_sources.clear();
  }

  ADDON_STATUS CreateInstance(const kodi::addon::IInstanceInfo& instance,
                              KODI_ADDON_INSTANCE_HDL& hdl) override
  {
    if (instance.IsType(ADDON_INSTANCE_VFS))
    {
      hdl = new CUsenetVFS(instance);
      return ADDON_STATUS_OK;
    }
    return ADDON_STATUS_UNKNOWN;
  }
};

ADDONCREATOR(CMegaNexusVFS)
