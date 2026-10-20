# Upstream acknowledgements

MegaNexus itself is under the [MegaNexus License](LICENSE.md). These parts keep their own licenses:

- [python-qrcode](https://github.com/lincolnloop/python-qrcode) in `plugin.video.meganexus/resources/lib/qrcode`: BSD license, see its `LICENSE` file.
- Noto Sans (SIL Open Font License): the text of the built-in collection covers, drawn by `review/make_collection_covers.py`.
- Google Sans, Fraunces and Oxanium (SIL Open Font License 1.1, no reserved names): reduced, renamed static instances in `skin.meganexus/fonts/ambient` (`review/make_ambient_fonts.py`), used by the MegaNexus Ambient screensaver widgets and the weather / clock corner of the MegaNexus screens; copyrights in `skin.meganexus/fonts/ambient/OFL.txt`.
- Noto Sans and Noto Emoji (SIL Open Font License 1.1): merged, reduced and renamed as MegaNexus Chat (`skin.meganexus/fonts/ambient/MNChat.ttf`, `review/make_chat_font.py`) for Watch Party messages with emoji; copyrights in `skin.meganexus/fonts/ambient/OFL.txt`.
- **vfs.meganexus** (the fast Usenet player, `vfs.meganexus/`) is free software under the **GNU General Public License v3.0 or later** (`vfs.meganexus/LICENSE.txt`) - unlike the rest of MegaNexus. It is built with Kodi's add-on headers (GPL-2.0-or-later) and includes OpenSSL 3 (Apache License 2.0, `vfs.meganexus/LICENSE-OpenSSL.txt`). Its complete source is in this repository's `vfs.meganexus` folder.
- Stream badge sets in `plugin.video.meganexus/resources/badges/sets`: MegaNexus rules that link to badge pictures hosted by their authors (not bundled; each set names its source in `sets.json`; Nebula's pictures: MIT, danielsdian/ColorfulAndConcise).
- [TRaSH Guides](https://github.com/TRaSH-Guides/Guides) release group tiers in `plugin.video.meganexus/resources/release_groups.json` (made by `review/make_release_groups.py`): MIT License, Copyright (c) 2021 TRaSH, see `plugin.video.meganexus/resources/licenses/TRaSH-Guides-LICENSE.txt`.
- TMDB's logo (`script.meganexus/resources/media/meganexus_tmdb_short.png`, from themoviedb.org/about/logos-attribution) credits TMDB as the source of the Trending now on TMDB titles, as TMDB's attribution rules require. MegaNexus is not endorsed or certified by TMDB.
- Subtitle flag icons in `skin.meganexus/media/windows/subtitles/flags`: MIT (GoSquared). Home images in `skin.meganexus/extras/home-images`: CC0.
- [Kodi 21.3 Estuary](https://github.com/xbmc/xbmc/tree/21.3-Omega/addons/skin.estuary): the skin foundation, standard dialogs, fonts and OSD. Code and artwork have the licenses described in `skin.meganexus/LICENSE.txt`.

The four component directories contain the detailed notices. Third-party Python code and skin assets retain their individual headers and license files. Do not remove them when redistributing or contributing.

This community project is independent of Nuvio, Kodi/Team Kodi, Simkl and the metadata/stream providers it can connect to. Collection labels identify categories and do not grant subscriptions or playback rights.

## Font handling in 6.0.10

This candidate references the Unicode font installed with Kodi through `special://xbmc/media/Fonts/arial.ttf`; it does not redistribute font binaries. Historic upstream font credits remain as attribution. Actual glyph coverage depends on the installed Kodi build.
