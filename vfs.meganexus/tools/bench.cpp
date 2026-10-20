// vfs.meganexus (MegaNexus Usenet) - Copyright (c) 2024-2026 MegaNexusMediaPlayer
// SPDX-License-Identifier: GPL-3.0-or-later - see LICENSE.txt. Built with Kodi's add-on headers
// (GPL-2.0-or-later) and OpenSSL (Apache-2.0, LICENSE-OpenSSL.txt).
//
// Reads a film through the Usenet reader as Kodi would (no Kodi): speed, and how fast a
// read waiting for an article ends when the player leaves.
//   bench <plan> <seconds> [check-file]   - check-file: the film's bytes, compared
#include "../src/usenet.h"

#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>

int main(int argc, char** argv)
{
  if (argc < 3)
  {
    std::cerr << "bench <plan> <seconds> [check-file]\n";
    return 2;
  }
  mnx::Plan plan;
  std::string error;
  if (!mnx::LoadPlan(argv[1], plan, error))
  {
    std::cerr << "plan: " << error << "\n";
    return 2;
  }
  double seconds = atof(argv[2]);
  std::ifstream check;
  if (argc > 3)
    check.open(argv[3], std::ios::binary);
  auto shared = std::make_shared<mnx::Plan>(plan);
  auto fetcher = std::make_shared<mnx::Fetcher>(plan, [](const std::string& line) { std::cout << "  " << line << "\n"; });
  mnx::Stream stream(shared, fetcher);
  std::vector<uint8_t> buffer(1 << 20), expected(1 << 20);
  double began = mnx::Now();
  uint64_t total = 0;
  while (mnx::Now() - began < seconds)
  {
    int64_t n = stream.Read(buffer.data(), buffer.size());
    if (n <= 0)
      break;
    if (check.is_open())
    {
      check.read(reinterpret_cast<char*>(expected.data()), n);
      if (check.gcount() != n || memcmp(expected.data(), buffer.data(), static_cast<size_t>(n)) != 0)
      {
        std::cerr << "WRONG BYTES at " << total << "\n";
        return 1;
      }
    }
    total += static_cast<uint64_t>(n);
  }
  double took = mnx::Now() - began;
  printf("read %.0f MB in %.1f s = %.0f Mbit/s%s\n", total / 1e6, took, total * 8 / took / 1e6,
         check.is_open() ? " (bytes checked)" : "");
  // the player leaves while a read waits: how long until it returns
  stream.Seek(static_cast<int64_t>(plan.size / 2), SEEK_SET);
  fetcher->DropAhead();
  std::thread stopper([&] { std::this_thread::sleep_for(std::chrono::milliseconds(200)); stream.Cancel(); });
  double t = mnx::Now();
  stream.Read(buffer.data(), buffer.size());
  stopper.join();
  printf("a read cancelled by Stop returned after %.2f s\n", mnx::Now() - t);
  t = mnx::Now();
  fetcher->Close();
  fetcher.reset();
  printf("connections closed in %.2f s\n", mnx::Now() - t);
  return 0;
}
