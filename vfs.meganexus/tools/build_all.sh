#!/bin/bash
# vfs.meganexus (MegaNexus Usenet) - Copyright (c) 2024-2026 MegaNexusMediaPlayer
# SPDX-License-Identifier: GPL-3.0-or-later - see LICENSE.txt. Built with Kodi's add-on headers
# (GPL-2.0-or-later) and OpenSSL (Apache-2.0, LICENSE-OpenSSL.txt).
# vfs.meganexus for every system, inside Docker (debian bookworm: glibc 2.36, so the Linux
# builds run on CoreELEC / LibreELEC / older desktops). OpenSSL is built in, statically.
#   build_all.sh <cache dir> <out dir> <version> [targets...]
# targets: android-armv7 android-aarch64 linux-armv7 linux-aarch64 linux-x86_64 windows-x86_64
set -e
CACHE=$(realpath "$1"); OUT=$(realpath -m "$2"); VERSION=$3; shift 3
TARGETS=${@:-android-armv7 android-aarch64 linux-armv7 linux-aarch64 linux-x86_64 windows-x86_64}
SRC=$(cd "$(dirname "$0")/.." && pwd)
DEVKITS=$(realpath "$SRC/../../kodi-devkit")
mkdir -p "$OUT"
docker build -q -t mnx-vfs-build - <<'DOCKER' >/dev/null
FROM debian:bookworm
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential cmake perl unzip python3 file ca-certificates \
    g++-arm-linux-gnueabihf g++-aarch64-linux-gnu g++-mingw-w64-x86-64 && rm -rf /var/lib/apt/lists/*
DOCKER
docker run --rm -u "$(id -u):$(id -g)" -v "$CACHE:/cache" -v "$SRC:/src:ro" -v "$OUT:/out" -v "$DEVKITS:/devkits:ro" \
  -e VERSION="$VERSION" -e TARGETS="$TARGETS" mnx-vfs-build bash -ec '
cd /cache
[ -d ndk ] || { unzip -q android-ndk-r27c-linux.zip && mv android-ndk-r27c ndk; }
NDK=/cache/ndk; API=21
for T in $TARGETS; do
  case $T in
    android-armv7)   OSSL=android-arm;   ABI=armeabi-v7a; CC=;;
    android-aarch64) OSSL=android-arm64; ABI=arm64-v8a;  CC=;;
    linux-armv7)     OSSL=linux-armv4;   CROSS=arm-linux-gnueabihf-;;
    linux-aarch64)   OSSL=linux-aarch64; CROSS=aarch64-linux-gnu-;;
    linux-x86_64)    OSSL=linux-x86_64;  CROSS=;;
    windows-x86_64)  OSSL=mingw64;       CROSS=x86_64-w64-mingw32-;;
  esac
  SSL=/cache/openssl-$T
  if [ ! -f $SSL/lib/libssl.a ] && [ ! -f $SSL/lib64/libssl.a ]; then
    rm -rf /tmp/ossl && mkdir /tmp/ossl && tar xzf /cache/openssl-3.0.15.tar.gz -C /tmp/ossl --strip-components=1
    cd /tmp/ossl
    if [[ $T == android-* ]]; then
      export ANDROID_NDK_ROOT=$NDK PATH=$NDK/toolchains/llvm/prebuilt/linux-x86_64/bin:$PATH
      ./Configure $OSSL -D__ANDROID_API__=$API no-shared no-tests -fPIC --prefix=$SSL >/dev/null
    else
      ./Configure $OSSL ${CROSS:+--cross-compile-prefix=$CROSS} no-shared no-tests -fPIC --prefix=$SSL >/dev/null
    fi
    make -j$(nproc) >/dev/null 2>&1 && make install_sw >/dev/null
    cd /cache
  fi
  [ -d $SSL/lib64 ] && LIB=$SSL/lib64 || LIB=$SSL/lib
  for KODI in 21.3-Omega 22.0rc1-Piers; do
    B=/tmp/build-$T-$KODI; rm -rf $B
    ARGS="-DKODI_DEVKIT=/devkits/$KODI/xbmc/addons/kodi-dev-kit/include -DMNX_TOOLS=OFF -DOPENSSL_USE_STATIC_LIBS=TRUE -DOPENSSL_ROOT_DIR=$SSL -DOPENSSL_INCLUDE_DIR=$SSL/include -DOPENSSL_SSL_LIBRARY=$LIB/libssl.a -DOPENSSL_CRYPTO_LIBRARY=$LIB/libcrypto.a"
    if [[ $T == android-* ]]; then
      cmake -S /src -B $B -DCMAKE_TOOLCHAIN_FILE=$NDK/build/cmake/android.toolchain.cmake -DANDROID_ABI=$ABI -DANDROID_PLATFORM=android-$API -DANDROID_STL=c++_static $ARGS >/dev/null
    elif [ -n "$CROSS" ]; then
      SYS=Linux; [[ $T == windows-* ]] && SYS=Windows
      SUFFIX=; [[ $T == windows-* ]] && SUFFIX=-posix   # std::thread needs the posix threads build
      cmake -S /src -B $B -DCMAKE_SYSTEM_NAME=$SYS -DCMAKE_C_COMPILER=${CROSS}gcc$SUFFIX -DCMAKE_CXX_COMPILER=${CROSS}g++$SUFFIX -DCMAKE_FIND_ROOT_PATH_MODE_LIBRARY=BOTH -DCMAKE_FIND_ROOT_PATH_MODE_INCLUDE=BOTH $ARGS >/dev/null
    else
      cmake -S /src -B $B $ARGS >/dev/null
    fi
    cmake --build $B -j$(nproc) --target vfs.meganexus >/dev/null
    LIBFILE=$(ls $B/vfs.meganexus.so $B/vfs.meganexus.dll 2>/dev/null | head -1)
    [[ $T == windows-* ]] && [ -f $B/libvfs.meganexus.dll ] && LIBFILE=$B/libvfs.meganexus.dll
    DEST=/out/$KODI/vfs.meganexus+$T
    rm -rf $DEST && mkdir -p $DEST
    python3 /src/tools/make_addon.py /devkits/$KODI/xbmc/addons/kodi-dev-kit/include $LIBFILE $T $DEST $VERSION >/dev/null
    echo "$KODI $T: $(file -b $LIBFILE | cut -c1-60) $(stat -c %s $LIBFILE) bytes"
  done
done
'
