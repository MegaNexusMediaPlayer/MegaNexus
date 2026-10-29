# vfs.meganexus (MegaNexus Usenet) - Copyright (c) 2024-2026 MegaNexusMediaPlayer
# SPDX-License-Identifier: GPL-3.0-or-later - see LICENSE.txt. Built with Kodi's add-on headers
# (GPL-2.0-or-later) and OpenSSL (Apache-2.0, LICENSE-OpenSSL.txt).
cmake_minimum_required(VERSION 3.16)
project(vfs.meganexus CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()
set(KODI_DEVKIT "" CACHE PATH "xbmc/addons/kodi-dev-kit/include of the Kodi version built for")
option(MNX_TOOLS "the bench tool" ON)
find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)

add_library(mnxusenet STATIC src/usenet.cpp src/images.cpp)
set_target_properties(mnxusenet PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_link_libraries(mnxusenet PUBLIC OpenSSL::SSL OpenSSL::Crypto Threads::Threads)

if(MNX_TOOLS)
  add_executable(mnx-bench tools/bench.cpp)
  target_link_libraries(mnx-bench mnxusenet)
  add_executable(mnx-images-test tools/images_test.cpp)
  target_link_libraries(mnx-images-test mnxusenet)
endif()

if(KODI_DEVKIT)
  add_library(vfs.meganexus SHARED src/addon.cpp)
  target_include_directories(vfs.meganexus PRIVATE ${KODI_DEVKIT})
  target_compile_definitions(vfs.meganexus PRIVATE BUILD_KODI_ADDON
      ADDON_GLOBAL_VERSION_MAIN_USED ADDON_GLOBAL_VERSION_GENERAL_USED
      ADDON_GLOBAL_VERSION_FILESYSTEM_USED ADDON_INSTANCE_VERSION_VFS_USED)
  target_link_libraries(vfs.meganexus PRIVATE mnxusenet)
  set_target_properties(vfs.meganexus PROPERTIES PREFIX "" CXX_VISIBILITY_PRESET hidden)
  if(NOT ANDROID AND NOT MSVC)
    # one file that runs on any system of its kind: the C++ runtime inside, no symbols
    target_link_options(vfs.meganexus PRIVATE -static-libstdc++ -static-libgcc -s)
  elseif(ANDROID)
    target_link_options(vfs.meganexus PRIVATE -s)
  endif()
  if(WIN32)
    target_link_libraries(vfs.meganexus PRIVATE ws2_32 crypt32)
    target_link_options(vfs.meganexus PRIVATE -static)   # no MinGW runtime DLLs beside it
  endif()
endif()
