// vfs.meganexus (MegaNexus Usenet) - Copyright (c) 2024-2026 MegaNexusMediaPlayer
// SPDX-License-Identifier: GPL-3.0-or-later - see LICENSE.txt. Built with Kodi's add-on headers
// (GPL-2.0-or-later) and OpenSSL (Apache-2.0, LICENSE-OpenSSL.txt).
//
// Pictures for MegaNexus (8.1.0): Kodi opens mnxart://i/<base64url of the picture's address>.<ext>
// through this add-on. The pictures are fetched ahead on several connections (asked by MegaNexus
// with mnxart://p/...) and kept in memory up to a budget, so Kodi gets each one at once - no
// picture passes through Python. Kodi keeps its own copy on disk under the mnxart address.

#pragma once

#include <condition_variable>
#include <cstdint>
#include <deque>
#include <functional>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

namespace mnx
{

std::string Base64UrlDecode(const std::string& text);
// the picture's address in an mnxart path ("<base64url>.<ext>"), or "" when it is not one
std::string PictureAddress(const std::string& path);
// a picture's first bytes say it is one Kodi can draw (JPEG, PNG, WebP, GIF, BMP)
bool LooksLikePicture(const std::string& data);

class Pictures
{
public:
  using Fetch = std::function<bool(const std::string& address, std::string& data)>;
  using Logger = std::function<void(const std::string&)>;

  Pictures(Fetch fetch, size_t budget, int workers, Logger log);
  ~Pictures();

  // fetched in the background (MegaNexus asks for what comes next)
  void Ahead(const std::string& address);
  // the picture now: from memory, after a fetch under way, or fetched here; null when it can not be
  std::shared_ptr<const std::string> Get(const std::string& address, double wait_seconds = 15.0);
  // the state of one: 1 in memory, -1 failed lately, 0 unknown or under way
  int State(const std::string& address);
  size_t Bytes();
  size_t Count();

private:
  enum class Kind { Pending, Ready, Failed };
  struct Entry
  {
    Kind kind = Kind::Pending;
    bool started = false;              // a fetch is under way (a worker's or Kodi's own)
    std::shared_ptr<const std::string> data;
    double failed_at = 0;
    std::list<std::string>::iterator order;
    bool ordered = false;
  };

  void Work();
  void Load(const std::string& address);
  void Touch(const std::string& address, Entry& entry);
  void Trim();

  Fetch m_fetch;
  size_t m_budget;
  Logger m_log;
  std::mutex m_mutex;
  std::condition_variable m_wake;   // a worker: something to fetch
  std::condition_variable m_done;   // Get: a fetch ended
  std::deque<std::string> m_queue;
  std::map<std::string, Entry> m_entries;
  std::list<std::string> m_recent;  // ready ones, most recent first
  size_t m_bytes = 0;
  bool m_stop = false;
  std::vector<std::thread> m_workers;
};

}  // namespace mnx
