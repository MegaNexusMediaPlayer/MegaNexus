// vfs.meganexus (MegaNexus Usenet) - Copyright (c) 2024-2026 MegaNexusMediaPlayer
// SPDX-License-Identifier: GPL-3.0-or-later - see LICENSE.txt. Built with Kodi's add-on headers
// (GPL-2.0-or-later) and OpenSSL (Apache-2.0, LICENSE-OpenSSL.txt).
//
// The Usenet reader of vfs.meganexus (8.0): Kodi reads a film straight from Usenet
// through this code - no Python, no local HTTP server in between. MegaNexus' Python
// side reads the NZB, finds the film (also inside stored RAR volumes) and writes a
// plan: the servers and, for each piece of the film, its articles. This file only
// fetches, decodes (yEnc) and hands out bytes, on as many cores as there are
// connections.
#pragma once

#include <atomic>
#include <condition_variable>
#include <cstdint>
#include <deque>
#include <functional>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <queue>
#include <set>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

namespace mnx
{

struct Server
{
  bool ssl = true;
  std::string host;
  int port = 563;
  int connections = 8;
  std::string user;
  std::string password;
};

struct Extent
{
  uint64_t start = 0;   // where this piece begins in the film
  uint64_t offset = 0;  // where it begins in its NZB file
  uint64_t length = 0;
  uint64_t part = 0;    // an article's size in that file (the last may be shorter)
  std::vector<std::string> ids;
};

struct Plan
{
  uint64_t size = 0;
  std::string name;
  int keep = 64;   // decoded articles kept
  int ahead = 40;  // articles read ahead of the player
  std::vector<Server> servers;
  std::vector<Extent> extents;
};

// "meganexus-plan 1" text file (see plan_format in usenet_vfs.py); error says why not
bool LoadPlan(const std::string& path, Plan& plan, std::string& error);
bool ParsePlan(const std::string& text, Plan& plan, std::string& error);

struct Article
{
  uint64_t begin = 0;  // 0-based offset of the data in its NZB file
  std::vector<uint8_t> data;
  bool missing = false;
};

// One yEnc article body as the server sent it (dot-stuffed lines, CRLF); false if not yEnc
bool YencDecode(const uint8_t* body, size_t size, Article& out);

using LogFunction = std::function<void(const std::string&)>;

class Fetcher
{
public:
  Fetcher(const Plan& plan, LogFunction log);
  ~Fetcher();

  // The article, waiting at most `wait` seconds (nullptr: too slow, or cancelled/closed).
  // priority 0 = the player needs it now; higher = later.
  std::shared_ptr<const Article> Get(const std::string& id,
                                     int priority,
                                     double wait,
                                     const std::atomic<bool>* cancel);
  void Want(const std::string& id, int priority);  // read ahead, no wait
  int DropAhead();                                  // the player stopped: queued read-ahead goes
  void Close();
  bool Closed() const { return m_closed; }

private:
  struct Task
  {
    int priority;
    uint64_t seq;
    std::string id;
    bool operator<(const Task& other) const
    {
      return priority != other.priority ? priority > other.priority : seq > other.seq;
    }
  };

  void Queue(size_t server, int priority, const std::string& id);
  void Work(size_t server);
  void Finish(const std::string& id, std::shared_ptr<Article> article);
  void Report(size_t bytes, double network, double processing);

  Plan m_plan;
  LogFunction m_log;
  std::mutex m_mutex;
  std::condition_variable m_work;
  std::condition_variable m_done;
  std::vector<std::priority_queue<Task>> m_queues;
  std::vector<bool> m_started;
  std::vector<bool> m_dead;
  std::vector<int> m_alive;
  std::unordered_map<std::string, int> m_pending;  // id -> soonest priority asked
  std::set<std::string> m_taken;                   // being read on a connection
  std::unordered_map<std::string, std::shared_ptr<Article>> m_cache;
  std::list<std::string> m_order;                  // oldest first
  std::vector<std::thread> m_threads;
  uint64_t m_seq = 0;
  std::atomic<bool> m_closed{false};
  // the speed line in the log
  uint64_t m_bytes = 0;
  int m_articles = 0;
  double m_network = 0, m_processing = 0;
  double m_reported = 0;
  int m_missing = 0;
};

class Stream
{
public:
  Stream(std::shared_ptr<const Plan> plan, std::shared_ptr<Fetcher> fetcher);
  int64_t Read(uint8_t* buffer, size_t size);
  int64_t Seek(int64_t position, int whence);
  int64_t Position() const { return m_position; }
  int64_t Length() const { return static_cast<int64_t>(m_plan->size); }
  void Cancel() { m_cancel = true; }
  // MegaNexus' Stop (OSD button, Back) leaves this file: a wait for an article ends at once
  void SetLeaving(const std::string& path);

private:
  bool Locate(uint64_t position, size_t& extent, uint64_t& offset) const;
  void Ahead(uint64_t position);
  std::shared_ptr<const Article> Wait(const std::string& id, double wait);
  bool Leaving();

  std::shared_ptr<const Plan> m_plan;
  std::shared_ptr<Fetcher> m_fetcher;
  uint64_t m_position = 0;
  std::atomic<bool> m_cancel{false};
  std::string m_leaving;
  int64_t m_opened = 0;  // wall-clock second this stream opened: older "leaving" marks are not for it
};

double Now();  // monotonic seconds
void SetCaFile(const std::string& path);  // Kodi's certificates (special://xbmc/system/certs)

}  // namespace mnx
