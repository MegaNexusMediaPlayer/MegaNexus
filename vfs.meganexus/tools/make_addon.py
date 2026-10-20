# vfs.meganexus (MegaNexus Usenet) - Copyright (c) 2024-2026 MegaNexusMediaPlayer
# SPDX-License-Identifier: GPL-3.0-or-later - see LICENSE.txt. Built with Kodi's add-on headers
# (GPL-2.0-or-later) and OpenSSL (Apache-2.0, LICENSE-OpenSSL.txt).
"""vfs.meganexus/<platform>/ ready to zip: addon.xml (the Kodi API versions from the dev kit
built against) and the library.  make_addon.py <devkit include dir> <library> <platform> <out dir> <version>"""
import os, re, shutil, sys

USED = (('ADDON_GLOBAL_VERSION_MAIN', 'kodi.binary.global.main'),
        ('ADDON_GLOBAL_VERSION_GENERAL', 'kodi.binary.global.general'),
        ('ADDON_GLOBAL_VERSION_FILESYSTEM', 'kodi.binary.global.filesystem'),
        ('ADDON_INSTANCE_VERSION_VFS', 'kodi.binary.instance.vfs'))
OS = {'linux': 'linux', 'android': 'android', 'windows': 'windows', 'osx': 'osx'}


def main(devkit, library, platform, out, version):
    text = open(os.path.join(devkit, 'kodi', 'versions.h'), encoding='utf-8').read()
    value = lambda name: re.search(r'#define %s\s+"([^"]+)"' % name, text).group(1)
    requires = ''.join('\n    <import addon="%s" minversion="%s" version="%s"/>' % (xml_id, value(base + '_MIN'), value(base))
                       for base, xml_id in USED)
    here = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    template = open(os.path.join(here, 'addon.xml.in'), encoding='utf-8').read()
    name = os.path.basename(library)
    folder = os.path.join(out, 'vfs.meganexus')
    os.makedirs(folder, exist_ok=True)
    xml = (template.replace('@VERSION@', version).replace('@REQUIRES@', requires)
           .replace('@LIBRARY_OS@', OS[platform.split('-')[0]]).replace('@LIBRARY@', name).replace('@PLATFORM@', platform))
    open(os.path.join(folder, 'addon.xml'), 'w', encoding='utf-8').write(xml)
    shutil.copy2(library, os.path.join(folder, name))
    for notice in ('LICENSE.txt', 'LICENSE-OpenSSL.txt'):   # GPL-3.0-or-later; OpenSSL built in
        shutil.copy2(os.path.join(here, notice), os.path.join(folder, notice))
    print(folder)


if __name__ == '__main__':
    main(*sys.argv[1:6])
