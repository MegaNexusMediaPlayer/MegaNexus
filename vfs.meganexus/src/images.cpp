// vfs.meganexus (MegaNexus Usenet) - Copyright (c) 2024-2026 MegaNexusMediaPlayer
// SPDX-License-Identifier: GPL-3.0-or-later - see LICENSE.txt. Built with Kodi's add-on headers
// (GPL-2.0-or-later) and OpenSSL (Apache-2.0, LICENSE-OpenSSL.txt).

#include "images.h"

#include <chrono>

namespace mnx
{
namespace
{
constexpr double FAILED_FOR = 600.0;      // s a picture that could not be fetched is not asked again
constexpr size_t QUEUE_MAX = 4000;        // pictures waiting to be fetched ahead

double Clock()
{
  using namespace std::chrono;
  return duration<double>(steady_clock::now().time_since_epoch()).count();
}
}  // namespace

std::string Base64UrlDecode(const std::string& text)
{
  static const std::string alphabet =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";
  std::string out;
  int value = 0, bits = -8;
  for (char c : text)
  {
    if (c == '=')
      break;
    size_t index = alphabet.find(c);
    if (index == std::string::npos)
      return "";
    value = (value << 6) + static_cast<int>(index);
    bits += 6;
    if (bits >= 0)
    {
      out.push_back(static_cast<char>((value >> bits) & 0xFF));
      bits -= 8;
    }
  }
  return out;
}

std::string PictureAddress(const std::string& path)
{
  std::string name = path;
  size_t slash = name.find_last_of('/');
  if (slash != std::string::npos)
    name = name.substr(slash + 1);
  size_t dot = name.find('.');
  if (dot != std::string::npos)
    name = name.substr(0, dot);
  std::string address = Base64UrlDecode(name);
  if (address.compare(0, 8, "https://") != 0 && address.compare(0, 7, "http://") != 0)
    return "";
  for (char c : address)
  {
    if (static_cast<unsigned char>(c) < 0x21 || c == '|')  // no options or spaces smuggled in
      return "";
  }
  return address;
}

bool LooksLikePicture(const std::string& data)
{
  auto starts = [&data](const char* magic, size_t size) {
    return data.size() >= size && data.compare(0, size, magic, size) == 0;
  };
  return starts("\xFF\xD8\xFF", 3) || starts("\x89PNG", 4) || starts("GIF8", 4) || starts("BM", 2) ||
         (starts("RIFF", 4) && data.size() >= 12 && data.compare(8, 4, "WEBP") == 0);
}

Pictures::Pictures(Fetch fetch, size_t budget, int workers, Logger log)
  : m_fetch(std::move(fetch)), m_budget(budget), m_log(std::move(log))
{
  for (int i = 0; i < workers; ++i)
    m_workers.emplace_back(&Pictures::Work, this);
}

Pictures::~Pictures()
{
  {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_stop = true;
  }
  m_wake.notify_all();
  m_done.notify_all();
  for (auto& worker : m_workers)
    worker.join();
}

void Pictures::Ahead(const std::string& address)
{
  std::lock_guard<std::mutex> lock(m_mutex);
  auto found = m_entries.find(address);
  if (found != m_entries.end())
  {
    if (found->second.kind != Kind::Failed || Clock() - found->second.failed_at < FAILED_FOR)
      return;
    m_entries.erase(found);
  }
  if (m_queue.size() >= QUEUE_MAX)
    return;
  m_entries[address] = Entry{};
  m_queue.push_back(address);
  m_wake.notify_one();
}

std::shared_ptr<const std::string> Pictures::Get(const std::string& address, double wait_seconds)
{
  std::unique_lock<std::mutex> lock(m_mutex);
  auto found = m_entries.find(address);
  if (found != m_entries.end() && found->second.kind == Kind::Failed &&
      Clock() - found->second.failed_at >= FAILED_FOR)
  {
    m_entries.erase(found);
    found = m_entries.end();
  }
  if (found == m_entries.end() || (found->second.kind == Kind::Pending && !found->second.started))
  {
    // not asked ahead, or still waiting in the queue: fetched right here (Kodi's own loading
    // thread) - never behind a long queue
    Entry& entry = m_entries[address];
    entry.started = true;
    lock.unlock();
    Load(address);
    lock.lock();
    found = m_entries.find(address);
  }
  double until = Clock() + wait_seconds;
  while (!m_stop && found != m_entries.end() && found->second.kind == Kind::Pending)
  {
    if (Clock() >= until)
      return nullptr;
    m_done.wait_for(lock, std::chrono::milliseconds(100));
    found = m_entries.find(address);
  }
  if (found == m_entries.end() || found->second.kind != Kind::Ready)
    return nullptr;
  Touch(address, found->second);
  return found->second.data;
}

int Pictures::State(const std::string& address)
{
  std::lock_guard<std::mutex> lock(m_mutex);
  auto found = m_entries.find(address);
  if (found == m_entries.end())
    return 0;
  if (found->second.kind == Kind::Ready)
    return 1;
  if (found->second.kind == Kind::Failed && Clock() - found->second.failed_at < FAILED_FOR)
    return -1;
  return 0;
}

size_t Pictures::Bytes()
{
  std::lock_guard<std::mutex> lock(m_mutex);
  return m_bytes;
}

size_t Pictures::Count()
{
  std::lock_guard<std::mutex> lock(m_mutex);
  return m_recent.size();
}

void Pictures::Work()
{
  while (true)
  {
    std::string address;
    {
      std::unique_lock<std::mutex> lock(m_mutex);
      m_wake.wait(lock, [this] { return m_stop || !m_queue.empty(); });
      if (m_stop)
        return;
      address = m_queue.front();
      m_queue.pop_front();
      auto found = m_entries.find(address);
      if (found == m_entries.end() || found->second.kind != Kind::Pending || found->second.started)
        continue;  // taken by Kodi already, or gone
      found->second.started = true;
    }
    Load(address);
  }
}

void Pictures::Load(const std::string& address)
{
  std::string data;
  bool good = false;
  try
  {
    good = m_fetch(address, data) && LooksLikePicture(data);
  }
  catch (...)
  {
    good = false;
  }
  {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto found = m_entries.find(address);
    if (found == m_entries.end())
      found = m_entries.emplace(address, Entry{}).first;
    if (found->second.kind == Kind::Pending)
    {
      if (good)
      {
        found->second.kind = Kind::Ready;
        found->second.data = std::make_shared<const std::string>(std::move(data));
        m_bytes += found->second.data->size();
        Touch(address, found->second);
        Trim();
      }
      else
      {
        found->second.kind = Kind::Failed;
        found->second.failed_at = Clock();
      }
    }
  }
  m_done.notify_all();
}

void Pictures::Touch(const std::string& address, Entry& entry)
{
  if (entry.ordered)
    m_recent.erase(entry.order);
  m_recent.push_front(address);
  entry.order = m_recent.begin();
  entry.ordered = true;
}

void Pictures::Trim()
{
  // the least recently used go first; one Kodi is reading keeps its bytes (shared)
  while (m_bytes > m_budget && m_recent.size() > 1)
  {
    std::string oldest = m_recent.back();
    m_recent.pop_back();
    auto found = m_entries.find(oldest);
    if (found != m_entries.end())
    {
      if (found->second.data)
        m_bytes -= found->second.data->size();
      m_entries.erase(found);
    }
  }
}

}  // namespace mnx
