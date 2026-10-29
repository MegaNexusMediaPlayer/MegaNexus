// vfs.meganexus (MegaNexus Usenet) - Copyright (c) 2024-2026 MegaNexusMediaPlayer
// SPDX-License-Identifier: GPL-3.0-or-later - see LICENSE.txt. Built with Kodi's add-on headers
// (GPL-2.0-or-later) and OpenSSL (Apache-2.0, LICENSE-OpenSSL.txt).

#include "usenet.h"

#include <algorithm>
#include <cctype>
#include <chrono>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <ctime>

#include <sys/stat.h>

#include <openssl/err.h>
#include <openssl/ssl.h>
#include <openssl/x509v3.h>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
using socket_t = SOCKET;
#define CLOSESOCKET closesocket
#else
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
using socket_t = int;
#define INVALID_SOCKET (-1)
#define CLOSESOCKET close
#endif

namespace mnx
{

namespace
{
constexpr int PIPELINE = 2;            // BODY requests sent before the answers are read
constexpr int TIMEOUT = 30;            // s a server may be silent
constexpr double REPORT_EVERY = 30.0;  // s between speed lines in the log
constexpr uint64_t START_BYTES = 16ull << 20;
constexpr double WAIT_START = 30.0;    // s an article of the film's start may take
constexpr double WAIT_PLAY = 12.0;     // later: then a gap, not a stall
constexpr size_t kMaxBuffer = 64u << 20;  // 7.0.59: a connection's buffer never grows past this

std::string g_caFile;
std::once_flag g_sslOnce;
SSL_CTX* g_ctx = nullptr;

struct NntpError : std::runtime_error
{
  using std::runtime_error::runtime_error;
};
struct Missing : NntpError
{
  Missing() : NntpError("missing") {}
};
struct TooMany : NntpError
{
  TooMany() : NntpError("too many connections") {}
};
struct AuthError : NntpError
{
  explicit AuthError(const std::string& what) : NntpError(what) {}
};

bool IsTooMany(int code, const std::string& line)
{
  std::string low(line);
  std::transform(low.begin(), low.end(), low.begin(), ::tolower);
  // as usenet_nntp._too_many: "too many connections" is not a wrong login
  if (code != 400 && code != 481 && code != 482 && code != 502)
    return false;
  for (const char* word : {"too many", "connection", "limit", "session", "max"})
  {
    if (low.find(word) != std::string::npos)
      return true;
  }
  return false;
}

SSL_CTX* Context()
{
  std::call_once(g_sslOnce, [] {
    g_ctx = SSL_CTX_new(TLS_client_method());
    if (!g_ctx)
      return;
    SSL_CTX_set_verify(g_ctx, SSL_VERIFY_PEER, nullptr);
    if (g_caFile.empty() || SSL_CTX_load_verify_locations(g_ctx, g_caFile.c_str(), nullptr) != 1)
      SSL_CTX_set_default_verify_paths(g_ctx);
  });
  return g_ctx;
}

class Connection
{
public:
  explicit Connection(const Server& server)
  {
#ifdef _WIN32
    static std::once_flag winsock;
    std::call_once(winsock, [] {
      WSADATA data;
      WSAStartup(MAKEWORD(2, 2), &data);
    });
#endif
    addrinfo hints{};
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    addrinfo* found = nullptr;
    if (getaddrinfo(server.host.c_str(), std::to_string(server.port).c_str(), &hints, &found) != 0 || !found)
      throw NntpError("address not found");
    for (addrinfo* a = found; a; a = a->ai_next)
    {
      m_fd = socket(a->ai_family, a->ai_socktype, a->ai_protocol);
      if (m_fd == INVALID_SOCKET)
        continue;
      Timeouts();
      if (connect(m_fd, a->ai_addr, static_cast<int>(a->ai_addrlen)) == 0)
        break;
      CLOSESOCKET(m_fd);
      m_fd = INVALID_SOCKET;
    }
    freeaddrinfo(found);
    if (m_fd == INVALID_SOCKET)
      throw NntpError("no connection");
    int one = 1;
    setsockopt(m_fd, IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<const char*>(&one), sizeof(one));
    int big = 4 << 20;
    setsockopt(m_fd, SOL_SOCKET, SO_RCVBUF, reinterpret_cast<const char*>(&big), sizeof(big));
    if (server.ssl)
    {
      SSL_CTX* ctx = Context();
      if (!ctx || !(m_ssl = SSL_new(ctx)))
        throw NntpError("no SSL");
      SSL_set_fd(m_ssl, static_cast<int>(m_fd));
      SSL_set_tlsext_host_name(m_ssl, server.host.c_str());
      SSL_set1_host(m_ssl, server.host.c_str());
      if (SSL_connect(m_ssl) != 1)
        throw NntpError("SSL handshake failed");
    }
    std::string line;
    int code = Status(line);
    if (code != 200 && code != 201)
    {
      if (IsTooMany(code, line))
        throw TooMany();
      throw NntpError("greeting " + std::to_string(code));
    }
    if (!server.user.empty())
    {
      Send("AUTHINFO USER " + server.user + "\r\n");
      code = Status(line);
      if (code == 381)
      {
        Send("AUTHINFO PASS " + server.password + "\r\n");
        code = Status(line);
      }
      if (code != 281)
      {
        if (IsTooMany(code, line))
          throw TooMany();
        throw AuthError("login refused (" + std::to_string(code) + ")");
      }
    }
  }

  ~Connection()
  {
    try
    {
      Send("QUIT\r\n");
    }
    catch (...)
    {
    }
    if (m_ssl)
    {
      SSL_shutdown(m_ssl);
      SSL_free(m_ssl);
    }
    if (m_fd != INVALID_SOCKET)
      CLOSESOCKET(m_fd);
  }

  void Send(const std::string& text)
  {
    size_t done = 0;
    while (done < text.size())
    {
      int n = m_ssl ? SSL_write(m_ssl, text.data() + done, static_cast<int>(text.size() - done))
                    : static_cast<int>(send(m_fd, text.data() + done, text.size() - done, 0));
      if (n <= 0)
        throw NntpError("send failed");
      done += static_cast<size_t>(n);
    }
  }

  // The answer to a BODY sent before: the raw body (dot-stuffed lines), valid until the next read
  std::pair<const uint8_t*, size_t> Body()
  {
    std::string line;
    int code = Status(line);
    if (code == 420 || code == 423 || code == 430)
      throw Missing();
    if (code != 222)
      throw NntpError("BODY " + std::to_string(code));
    if (Filled() >= 3 && memcmp(Head(), ".\r\n", 3) == 0)
    {
      m_head += 3;
      return {Head(), 0};
    }
    size_t scanned = 0;
    static const char END[] = "\r\n.\r\n";
    while (true)
    {
      size_t from = scanned > 4 ? scanned - 4 : 0;
      if (Filled() > from)
      {
        const uint8_t* at = Find(Head() + from, Filled() - from, END, 5);
        if (at)
        {
          size_t length = static_cast<size_t>(at - Head()) + 2;
          const uint8_t* body = Head();
          m_head += length + 3;
          return {body, length};
        }
      }
      scanned = Filled();
      Receive();
    }
  }

private:
  void Timeouts()
  {
#ifdef _WIN32
    DWORD ms = TIMEOUT * 1000;
    setsockopt(m_fd, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&ms), sizeof(ms));
    setsockopt(m_fd, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<const char*>(&ms), sizeof(ms));
#else
    timeval tv{TIMEOUT, 0};
    setsockopt(m_fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    setsockopt(m_fd, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));
#endif
  }

  static const uint8_t* Find(const uint8_t* hay, size_t size, const char* needle, size_t length)
  {
    const uint8_t* end = hay + size;
    const uint8_t* at = hay;
    while (at + length <= end)
    {
      at = static_cast<const uint8_t*>(memchr(at, needle[0], static_cast<size_t>(end - at)));
      if (!at || at + length > end)
        return nullptr;
      if (memcmp(at, needle, length) == 0)
        return at;
      ++at;
    }
    return nullptr;
  }

  const uint8_t* Head() const { return m_buffer.data() + m_head; }
  size_t Filled() const { return m_tail - m_head; }

  void Receive()
  {
    if (m_head > 0 && (m_head == m_tail || m_head > m_buffer.size() / 2))
    {
      memmove(m_buffer.data(), m_buffer.data() + m_head, m_tail - m_head);
      m_tail -= m_head;
      m_head = 0;
    }
    if (m_buffer.size() - m_tail < (256u << 10))
    {
      // 7.0.59: an article is under a few MB - a server sending endless broken data closes the
      // connection (a new one opens) instead of filling the memory
      if (m_buffer.size() >= kMaxBuffer)
        throw NntpError("too much data without an end");
      m_buffer.resize(std::min(kMaxBuffer, std::max<size_t>(m_buffer.size() * 2, 2u << 20)));
    }
    int n = m_ssl ? SSL_read(m_ssl, m_buffer.data() + m_tail, static_cast<int>(m_buffer.size() - m_tail))
                  : static_cast<int>(recv(m_fd, reinterpret_cast<char*>(m_buffer.data() + m_tail),
                                          m_buffer.size() - m_tail, 0));
    if (n <= 0)
      throw NntpError("connection closed");
    m_tail += static_cast<size_t>(n);
  }

  int Status(std::string& line)
  {
    while (true)
    {
      const uint8_t* at = Filled() ? Find(Head(), Filled(), "\r\n", 2) : nullptr;
      if (at)
      {
        line.assign(reinterpret_cast<const char*>(Head()), static_cast<size_t>(at - Head()));
        m_head += line.size() + 2;
        if (line.size() < 3 || !isdigit(static_cast<unsigned char>(line[0])))
          throw NntpError("bad reply");
        return std::stoi(line.substr(0, 3));
      }
      Receive();
    }
  }

  socket_t m_fd = INVALID_SOCKET;
  SSL* m_ssl = nullptr;
  std::vector<uint8_t> m_buffer;
  size_t m_head = 0, m_tail = 0;
};

std::string FromHex(const std::string& hex)
{
  std::string out;
  for (size_t i = 0; i + 1 < hex.size(); i += 2)
    out.push_back(static_cast<char>(std::stoi(hex.substr(i, 2), nullptr, 16)));
  return out;
}

uint64_t Field(const char* line, const char* end, const char* name)
{
  size_t length = strlen(name);
  for (const char* at = line; at + length <= end; ++at)
  {
    if ((at == line || at[-1] == ' ') && memcmp(at, name, length) == 0)
      return strtoull(at + length, nullptr, 10);
  }
  return 0;
}
}  // namespace

void SetCaFile(const std::string& path)
{
  g_caFile = path;
}

double Now()
{
  using namespace std::chrono;
  return duration<double>(steady_clock::now().time_since_epoch()).count();
}

// --- the plan -----------------------------------------------------------------------

bool ParsePlan(const std::string& text, Plan& plan, std::string& error)
{
  std::istringstream in(text);
  std::string line;
  if (!std::getline(in, line) || line.rfind("meganexus-plan 1", 0) != 0)
  {
    error = "not a plan";
    return false;
  }
  Extent* extent = nullptr;
  size_t ids = 0;
  uint64_t start = 0;
  while (std::getline(in, line))
  {
    if (!line.empty() && line.back() == '\r')
      line.pop_back();
    if (line.empty())
      continue;
    if (extent && ids > 0)
    {
      extent->ids.push_back(line);
      --ids;
      continue;
    }
    std::istringstream fields(line);
    std::string kind;
    fields >> kind;
    if (kind == "size")
      fields >> plan.size;
    else if (kind == "name")
    {
      std::string hex;
      fields >> hex;
      plan.name = FromHex(hex);
    }
    else if (kind == "keep")
      fields >> plan.keep;
    else if (kind == "ahead")
      fields >> plan.ahead;
    else if (kind == "server")
    {
      Server server;
      int ssl = 1;
      std::string user, password;
      fields >> ssl >> server.host >> server.port >> server.connections >> user >> password;
      server.ssl = ssl != 0;
      server.user = user == "-" ? "" : FromHex(user);
      server.password = password == "-" ? "" : FromHex(password);
      server.connections = std::max(1, std::min(50, server.connections));
      plan.servers.push_back(server);
    }
    else if (kind == "extent")
    {
      plan.extents.emplace_back();
      extent = &plan.extents.back();
      fields >> extent->offset >> extent->length >> extent->part >> ids;
      extent->start = start;
      start += extent->length;
      extent->ids.reserve(ids);
    }
  }
  if (plan.servers.empty() || plan.extents.empty() || ids != 0)
  {
    error = "incomplete plan";
    return false;
  }
  for (const Extent& e : plan.extents)
  {
    if (e.ids.empty() || !e.part)
    {
      error = "empty piece";
      return false;
    }
  }
  if (!plan.size || plan.size > start)
    plan.size = start;
  plan.keep = std::max(8, plan.keep);
  plan.ahead = std::max(1, std::min(plan.keep - 4, plan.ahead));
  return true;
}

bool LoadPlan(const std::string& path, Plan& plan, std::string& error)
{
  std::ifstream file(path, std::ios::binary);
  if (!file)
  {
    error = "no plan";
    return false;
  }
  std::stringstream text;
  text << file.rdbuf();
  return ParsePlan(text.str(), plan, error);
}

// --- yEnc --------------------------------------------------------------------------

bool YencDecode(const uint8_t* body, size_t size, Article& out)
{
  const char* text = reinterpret_cast<const char*>(body);
  const char* end = text + size;
  const char* begin = nullptr;
  for (const char* at = text; at + 8 <= end; ++at)
  {
    at = static_cast<const char*>(memchr(at, '=', static_cast<size_t>(end - at)));
    if (!at || at + 8 > end)
      break;
    if (memcmp(at, "=ybegin ", 8) == 0)
    {
      begin = at;
      break;
    }
  }
  if (!begin)
    return false;
  const char* eol = static_cast<const char*>(memchr(begin, '\n', static_cast<size_t>(end - begin)));
  if (!eol)
    return false;
  out.begin = 0;
  const char* data = eol + 1;
  if (data + 7 <= end && memcmp(data, "=ypart ", 7) == 0)
  {
    const char* partEnd = static_cast<const char*>(memchr(data, '\n', static_cast<size_t>(end - data)));
    if (!partEnd)
      return false;
    uint64_t first = Field(data, partEnd, "begin=");
    out.begin = first ? first - 1 : 0;
    data = partEnd + 1;
  }
  // the data ends at the "=yend" line
  const char* stop = end;
  for (const char* at = end - 1; at > data; --at)
  {
    if (*at == '\n' && at + 6 <= end && memcmp(at + 1, "=yend", 5) == 0)
    {
      stop = at + 1;
      break;
    }
  }
  out.data.resize(static_cast<size_t>(stop - data));
  uint8_t* o = out.data.data();
  const uint8_t* p = reinterpret_cast<const uint8_t*>(data);
  const uint8_t* q = reinterpret_cast<const uint8_t*>(stop);
  bool lineStart = true;
  while (p < q)
  {
    uint8_t c = *p++;
    if (c == '\r' || c == '\n')
    {
      lineStart = true;
      continue;
    }
    if (lineStart && c == '.' && p < q && *p == '.')
    {
      lineStart = false;  // NNTP dot-stuffing: ".." at a line start is "."
      continue;
    }
    lineStart = false;
    if (c == '=')
    {
      if (p >= q || *p == '\r' || *p == '\n')
        continue;  // a cut-off escape
      c = static_cast<uint8_t>(*p++ - 64);
    }
    *o++ = static_cast<uint8_t>(c - 42);
  }
  out.data.resize(static_cast<size_t>(o - out.data.data()));
  return true;
}

// --- articles ----------------------------------------------------------------------

Fetcher::Fetcher(const Plan& plan, LogFunction log)
  : m_plan(plan), m_log(std::move(log)), m_queues(plan.servers.size()),
    m_started(plan.servers.size(), false), m_dead(plan.servers.size(), false),
    m_alive(plan.servers.size(), 0), m_reported(Now())
{
}

Fetcher::~Fetcher()
{
  Close();
  for (std::thread& thread : m_threads)
  {
    if (thread.joinable())
      thread.join();
  }
}

void Fetcher::Close()
{
  m_closed = true;
  m_work.notify_all();
  m_done.notify_all();
}

void Fetcher::Queue(size_t server, int priority, const std::string& id)
{
  // m_mutex held
  while (server < m_queues.size() && m_dead[server])
    ++server;
  if (server >= m_queues.size())
  {
    auto article = std::make_shared<Article>();
    article->missing = true;
    m_pending.erase(id);
    m_cache[id] = article;
    m_order.push_back(id);
    ++m_missing;
    m_done.notify_all();
    return;
  }
  m_queues[server].push(Task{priority, m_seq++, id});
  if (!m_started[server])
  {
    m_started[server] = true;
    for (int n = 0; n < m_plan.servers[server].connections; ++n)
    {
      ++m_alive[server];
      m_threads.emplace_back(&Fetcher::Work, this, server);
    }
  }
  m_work.notify_one();
}

void Fetcher::Want(const std::string& id, int priority)
{
  std::lock_guard<std::mutex> lock(m_mutex);
  if (m_closed || m_cache.count(id) || m_taken.count(id))
    return;
  auto pending = m_pending.find(id);
  // asked again as the player nears it: queued again only when clearly sooner
  if (pending != m_pending.end() &&
      (priority >= pending->second || (priority > 0 && priority > pending->second / 2)))
    return;
  m_pending[id] = priority;
  Queue(0, priority, id);
}

std::shared_ptr<const Article> Fetcher::Get(const std::string& id,
                                            int priority,
                                            double wait,
                                            const std::atomic<bool>* cancel)
{
  Want(id, priority);
  double until = Now() + wait;
  std::unique_lock<std::mutex> lock(m_mutex);
  while (true)
  {
    auto found = m_cache.find(id);
    if (found != m_cache.end())
      return found->second;
    if (m_closed || (cancel && *cancel))
      return nullptr;
    double left = until - Now();
    if (left <= 0)
      return nullptr;
    m_done.wait_for(lock, std::chrono::duration<double>(std::min(left, 0.1)));
  }
}

int Fetcher::DropAhead()
{
  std::lock_guard<std::mutex> lock(m_mutex);
  int dropped = 0;
  for (auto& queue : m_queues)
  {
    std::priority_queue<Task> kept;
    while (!queue.empty())
    {
      Task task = queue.top();
      queue.pop();
      if (task.priority > 0 && !m_taken.count(task.id) && !m_cache.count(task.id))
      {
        if (m_pending.erase(task.id))
          ++dropped;
        continue;
      }
      kept.push(task);
    }
    queue.swap(kept);
  }
  return dropped;
}

void Fetcher::Finish(const std::string& id, std::shared_ptr<Article> article)
{
  // m_mutex held
  m_taken.erase(id);
  m_pending.erase(id);
  if (article->missing)
    ++m_missing;
  if (!m_cache.count(id))
    m_order.push_back(id);
  m_cache[id] = std::move(article);
  while (m_cache.size() > static_cast<size_t>(m_plan.keep) && !m_order.empty())
  {
    m_cache.erase(m_order.front());
    m_order.pop_front();
  }
  m_done.notify_all();
}

void Fetcher::Report(size_t bytes, double network, double processing)
{
  std::string line;
  {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_bytes += bytes;
    ++m_articles;
    m_network += network;
    m_processing += processing;
    double now = Now();
    if (now - m_reported < REPORT_EVERY)
      return;
    double took = now - m_reported;
    double spent = std::max(1e-9, m_network + m_processing);
    size_t waiting = 0;
    int alive = 0;
    for (size_t s = 0; s < m_queues.size(); ++s)
    {
      waiting += m_queues[s].size();
      alive += m_alive[s];
    }
    char text[256];
    snprintf(text, sizeof(text),
             "%.1f Mbit/s, %d articles in %.0f s, %d connections, network %d %% / processing %d %%, "
             "%zu waiting, %d missing so far",
             m_bytes * 8 / took / 1e6, m_articles, took, alive,
             static_cast<int>(m_network / spent * 100 + .5),
             static_cast<int>(m_processing / spent * 100 + .5), waiting, m_missing);
    line = text;
    m_reported = now;
    m_bytes = 0;
    m_articles = 0;
    m_network = m_processing = 0;
  }
  if (m_log)
    m_log(line);
}

void Fetcher::Work(size_t server)
{
  std::unique_ptr<Connection> connection;
  int failures = 0;
  Article decoded;
  while (!m_closed)
  {
    std::vector<Task> batch;
    {
      std::unique_lock<std::mutex> lock(m_mutex);
      m_work.wait_for(lock, std::chrono::seconds(2),
                      [&] { return m_closed || !m_queues[server].empty(); });
      if (m_closed)
        break;
      while (!m_queues[server].empty() && static_cast<int>(batch.size()) < PIPELINE)
      {
        Task task = m_queues[server].top();
        m_queues[server].pop();
        // a copy asked again sooner, or one already read: once only
        if (m_cache.count(task.id) || m_taken.count(task.id) || !m_pending.count(task.id))
          continue;
        m_taken.insert(task.id);
        batch.push_back(task);
      }
    }
    if (batch.empty())
      continue;
    size_t done = 0;
    try
    {
      if (!connection)
        connection = std::make_unique<Connection>(m_plan.servers[server]);
      for (const Task& task : batch)
        connection->Send("BODY <" + task.id + ">\r\n");
      for (; done < batch.size(); ++done)
      {
        const Task& task = batch[done];
        double began = Now();
        std::pair<const uint8_t*, size_t> body;
        try
        {
          body = connection->Body();
        }
        catch (const Missing&)
        {
          std::lock_guard<std::mutex> lock(m_mutex);
          m_taken.erase(task.id);
          Queue(server + 1, task.priority, task.id);  // the next server, if any
          continue;
        }
        double got = Now();
        auto article = std::make_shared<Article>();
        if (!YencDecode(body.first, body.second, *article))
          article->missing = true;
        failures = 0;
        size_t bytes = article->data.size();
        {
          std::lock_guard<std::mutex> lock(m_mutex);
          Finish(task.id, std::move(article));
        }
        Report(bytes, got - began, Now() - got);
      }
    }
    catch (const TooMany&)
    {
      connection.reset();
      bool last;
      {
        std::lock_guard<std::mutex> lock(m_mutex);
        for (size_t n = done; n < batch.size(); ++n)
        {
          m_taken.erase(batch[n].id);
          m_queues[server].push(batch[n]);
        }
        last = m_alive[server] <= 1;
        if (!last)
          --m_alive[server];
      }
      m_work.notify_all();
      if (!last)
        return;  // the provider allows fewer: this connection goes, the others read on
      std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    catch (const AuthError& error)
    {
      if (m_log)
        m_log(std::string("server ") + std::to_string(server + 1) + ": " + error.what());
      std::lock_guard<std::mutex> lock(m_mutex);
      m_dead[server] = true;
      for (size_t n = done; n < batch.size(); ++n)
      {
        m_taken.erase(batch[n].id);
        Queue(server + 1, batch[n].priority, batch[n].id);
      }
      while (!m_queues[server].empty())
      {
        Task task = m_queues[server].top();
        m_queues[server].pop();
        if (m_pending.count(task.id) && !m_taken.count(task.id))
          Queue(server + 1, task.priority, task.id);
      }
      --m_alive[server];
      return;
    }
    catch (const std::exception& error)
    {
      connection.reset();
      ++failures;
      bool next = failures >= 3;
      if (next && m_log)
        m_log(std::string("server ") + std::to_string(server + 1) + ": " + error.what());
      {
        std::lock_guard<std::mutex> lock(m_mutex);
        for (size_t n = done; n < batch.size(); ++n)
        {
          m_taken.erase(batch[n].id);
          if (next)
            Queue(server + 1, batch[n].priority, batch[n].id);
          else
            m_queues[server].push(batch[n]);
        }
      }
      m_work.notify_all();
      if (next)
      {
        failures = 0;
        std::this_thread::sleep_for(std::chrono::seconds(1));
      }
    }
  }
  std::lock_guard<std::mutex> lock(m_mutex);
  --m_alive[server];
}

// --- the film ------------------------------------------------------------------------

Stream::Stream(std::shared_ptr<const Plan> plan, std::shared_ptr<Fetcher> fetcher)
  : m_plan(std::move(plan)), m_fetcher(std::move(fetcher))
{
}

bool Stream::Locate(uint64_t position, size_t& extent, uint64_t& offset) const
{
  for (size_t e = 0; e < m_plan->extents.size(); ++e)
  {
    const Extent& x = m_plan->extents[e];
    if (position < x.start + x.length)
    {
      extent = e;
      offset = x.offset + (position - x.start);
      return true;
    }
  }
  return false;
}

void Stream::Ahead(uint64_t position)
{
  size_t extent;
  uint64_t offset;
  if (!Locate(position, extent, offset))
    return;
  uint64_t step = std::max<uint64_t>(m_plan->extents[extent].part, 256u << 10);
  for (int n = 1; n <= m_plan->ahead; ++n)
  {
    if (!Locate(position + n * step, extent, offset))
      break;
    const Extent& x = m_plan->extents[extent];
    size_t index = static_cast<size_t>(std::min<uint64_t>(offset / x.part, x.ids.size() - 1));
    m_fetcher->Want(x.ids[index], n);
  }
}

int64_t Stream::Read(uint8_t* buffer, size_t size)
{
  if (m_position >= m_plan->size || size == 0)
    return 0;
  size_t extent;
  uint64_t offset;
  if (!Locate(m_position, extent, offset))
    return 0;
  const Extent& x = m_plan->extents[extent];
  size_t index = static_cast<size_t>(std::min<uint64_t>(offset / x.part, x.ids.size() - 1));
  Ahead(m_position);
  double wait = m_position < START_BYTES ? WAIT_START : WAIT_PLAY;
  std::shared_ptr<const Article> article;
  uint64_t begin = 0;
  const uint8_t* data = nullptr;
  size_t length = 0;
  std::vector<uint8_t> zeros;
  for (int attempt = 0; attempt < 4; ++attempt)  // parts of another size: find the right one
  {
    article = Wait(x.ids[index], wait);
    if (m_cancel || m_fetcher->Closed())
      return -1;  // Kodi is closing the film: nothing more is waited for
    if (!article || article->missing || article->data.empty())
    {
      zeros.assign(static_cast<size_t>(x.part), 0);  // a gap, the film goes on
      begin = index * x.part;
      data = zeros.data();
      length = zeros.size();
    }
    else
    {
      begin = article->begin;
      data = article->data.data();
      length = article->data.size();
    }
    if (offset < begin && index > 0)
      index = static_cast<size_t>(index - 1 - std::min<uint64_t>(index - 1, (begin - offset) / x.part));
    else if (offset >= begin + length && index + 1 < x.ids.size())
      index = static_cast<size_t>(std::min<uint64_t>(x.ids.size() - 1,
                                                     index + 1 + (offset - begin - length) / x.part));
    else
      break;
  }
  if (offset < begin || offset >= begin + length)
    return 0;
  uint64_t skip = offset - begin;
  uint64_t give = std::min<uint64_t>({length - skip, size, x.start + x.length - m_position,
                                      m_plan->size - m_position});
  memcpy(buffer, data + skip, static_cast<size_t>(give));
  m_position += give;
  return static_cast<int64_t>(give);
}

void Stream::SetLeaving(const std::string& path)
{
  m_leaving = path;
  m_opened = static_cast<int64_t>(time(nullptr));
}

bool Stream::Leaving()
{
  if (m_leaving.empty())
    return false;
  struct stat info{};
  if (stat(m_leaving.c_str(), &info) != 0)
    return false;
  if (static_cast<int64_t>(info.st_mtime) + 1 < m_opened)
    return false;  // a Stop of an earlier film
  m_cancel = true;
  return true;
}

std::shared_ptr<const Article> Stream::Wait(const std::string& id, double wait)
{
  // in slices: Kodi waits for this read before it can close the film, so a Stop is looked for
  double until = Now() + wait;
  while (true)
  {
    double left = until - Now();
    auto article = m_fetcher->Get(id, 0, std::max(0.0, std::min(left, 0.25)), &m_cancel);
    if (article || m_cancel || m_fetcher->Closed() || left <= 0.25 || Leaving())
      return article;
  }
}

int64_t Stream::Seek(int64_t position, int whence)
{
  int64_t target;
  switch (whence)
  {
    case SEEK_SET:
      target = position;
      break;
    case SEEK_CUR:
      target = static_cast<int64_t>(m_position) + position;
      break;
    case SEEK_END:
      target = static_cast<int64_t>(m_plan->size) + position;
      break;
    default:
      return -1;
  }
  if (target < 0 || target > static_cast<int64_t>(m_plan->size))
    return -1;
  m_position = static_cast<uint64_t>(target);
  return target;
}

}  // namespace mnx
