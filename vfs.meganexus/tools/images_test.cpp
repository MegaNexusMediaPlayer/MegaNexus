// vfs.meganexus (MegaNexus Usenet) - Copyright (c) 2024-2026 MegaNexusMediaPlayer
// SPDX-License-Identifier: GPL-3.0-or-later - see LICENSE.txt. Built with Kodi's add-on headers
// (GPL-2.0-or-later) and OpenSSL (Apache-2.0, LICENSE-OpenSSL.txt).
// The picture cache without Kodi: a fake slow internet, many pictures at once.
#include "../src/images.h"

#include <atomic>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <thread>

static int failures = 0;
#define CHECK(cond) do { if (!(cond)) { std::printf("FAIL line %d: %s\n", __LINE__, #cond); ++failures; } } while (0)

static double Now()
{
  using namespace std::chrono;
  return duration<double>(steady_clock::now().time_since_epoch()).count();
}

int main()
{
  // base64url of https://image.tmdb.org/t/p/w500/a.jpg
  CHECK(mnx::PictureAddress("aHR0cHM6Ly9pbWFnZS50bWRiLm9yZy90L3AvdzUwMC9hLmpwZw.jpg") == "https://image.tmdb.org/t/p/w500/a.jpg");
  CHECK(mnx::PictureAddress("/aHR0cHM6Ly9pbWFnZS50bWRiLm9yZy90L3AvdzUwMC9hLmpwZw.jpg") == "https://image.tmdb.org/t/p/w500/a.jpg");
  CHECK(mnx::PictureAddress("ZmlsZTovLy9ldGMvcGFzc3dk.jpg").empty());              // file:///etc/passwd
  CHECK(mnx::PictureAddress("aHR0cHM6Ly94L3l8VXNlci1BZ2VudD14.jpg").empty());      // https://x/y|User-Agent=x
  CHECK(mnx::LooksLikePicture(std::string("\xFF\xD8\xFF\xE0", 4)));
  CHECK(mnx::LooksLikePicture("RIFF1234WEBPVP8 "));
  CHECK(!mnx::LooksLikePicture("<html>"));

  std::atomic<int> fetched{0}, at_once{0}, most{0};
  auto fetch = [&](const std::string& address, std::string& data) {
    int now = ++at_once;
    int seen = most.load();
    while (now > seen && !most.compare_exchange_weak(seen, now)) {}
    std::this_thread::sleep_for(std::chrono::milliseconds(50));   // a slow internet
    --at_once;
    ++fetched;
    if (address.find("broken") != std::string::npos)
      return false;
    data = std::string("\xFF\xD8\xFF", 3) + std::string(10000, 'x');
    return true;
  };
  {
    mnx::Pictures pictures(fetch, 1000000, 12, [](const std::string&) {});
    double start = Now();
    for (int i = 0; i < 240; ++i)
      pictures.Ahead("https://img/" + std::to_string(i));
    auto first = pictures.Get("https://img/239");            // at the end of the queue: fetched at once
    CHECK(first && first->size() == 10003);
    CHECK(Now() - start < 1.0);
    while (pictures.State("https://img/238") == 0 && Now() - start < 10)
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    double took = Now() - start;
    std::printf("240 pictures on 12 connections: %.2f s, %d at once at most\n", took, most.load());
    CHECK(took < 2.0);                                         // 240 x 50 ms one by one would be 12 s
    CHECK(most.load() >= 10);
    CHECK(pictures.Bytes() <= 1000000);                        // within the budget
    CHECK(pictures.Count() * 10003 <= 1000000);
    CHECK(!pictures.Get("https://img/broken"));
    CHECK(pictures.State("https://img/broken") == -1);
    int before = fetched;
    CHECK(!pictures.Get("https://img/broken"));               // not asked again for a while
    CHECK(fetched == before);
  }
  std::printf(failures ? "%d FAILED\n" : "all good\n", failures);
  return failures ? 1 : 0;
}
