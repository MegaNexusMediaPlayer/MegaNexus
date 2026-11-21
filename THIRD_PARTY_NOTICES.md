# Third-party notices

MegaNexus is under the [MegaNexus License](LICENSE.md). These parts keep their
own licenses; their notices must stay with them.

## Code

- **python-qrcode** (`plugin.video.meganexus/resources/lib/qrcode`) - BSD License,
  Copyright (c) 2011, Lincoln Loop. See the `LICENSE` file in that folder.
- **Kodi Estuary** - the base of `skin.meganexus`: code GPL-2.0, artwork
  CC BY-SA 4.0 (`skin.meganexus/LICENSE.txt`).
- **vfs.meganexus** - MegaNexus' Usenet player, GPL-3.0-or-later
  (`vfs.meganexus/LICENSE.txt`). Built with Kodi's add-on headers
  (GPL-2.0-or-later) and **OpenSSL 3** (Apache License 2.0,
  `vfs.meganexus/LICENSE-OpenSSL.txt`). Its complete source is in the
  `vfs.meganexus` folder.

## Fonts

- **Google Sans, Fraunces, Oxanium** (SIL Open Font License 1.1, no reserved
  names) - reduced and renamed static instances in `skin.meganexus/fonts/ambient`.
- **Noto Sans, Noto Emoji** (SIL Open Font License 1.1) - merged and renamed as
  MegaNexus Chat (`skin.meganexus/fonts/ambient/MNChat.ttf`) for Watch Party
  messages.
- Copyrights of the fonts above: `skin.meganexus/fonts/ambient/OFL.txt`.
- **Anton** (SIL Open Font License 1.1, Copyright 2020 The Anton Project Authors) - the big numbers
  (Top 10 ranks, the Library's counts), drawn into pictures in
  `script.meganexus/resources/media/rank` by `review/make_rank_images.py`; the font itself and its
  licence are kept in `review/assets/fonts` and are not shipped.
- **Barlow** (Copyright 2017 The Barlow Project Authors), **Poppins** (Copyright 2020 The Poppins
  Project Authors) and **Fira Sans** (Copyright 2012-2015 The Mozilla Foundation and Telefonica S.A.),
  SIL Open Font License 1.1, no reserved names - the interface's letters in
  `skin.meganexus/fonts/Barlow`, `Poppins` and `FiraSans`, with the letters they lack taken from
  Noto Sans, Noto Sans Symbols, Noto Sans Symbols 2 and Noto Sans Math (Copyright 2022 The Noto Project
  Authors, SIL Open Font License 1.1) and an outlined copy of each; each folder holds its OFL.txt and a
  NOTICE.txt saying what was changed (made by `review/make_ui_fonts.py`).
- **Chakra Petch, Chewy, Righteous, Silkscreen, Playfair Display SC, Black Han Sans** (SIL Open Font
  License 1.1) and **Liberation Sans** (SIL Open Font License 1.1) - the words of our apps' logos
  (MegaIPTV, MegaSport, Music, Retro, Poker, Guess It), drawn into pictures by `review/make_app_logos.py`;
  the fonts and their licences are kept in `review/assets/fonts` and are not shipped.

## Icons and pictures

- **Google Material Symbols** - player icons in `skin.meganexus/media/meganexus/player`,
  Apache License 2.0.
- **GoSquared flag icons** - subtitle language flags in
  `skin.meganexus/media/windows/subtitles/flags`, MIT License.
- **Home images** in `skin.meganexus/extras/home-images` - CC0.
- **TMDB logo** (`script.meganexus/resources/media/meganexus_tmdb_short.png`,
  from themoviedb.org/about/logos-attribution) - credits TMDB as the source of
  *Trending now on TMDB*, as TMDB's attribution rules require. MegaNexus is not
  endorsed or certified by TMDB.
- **IMDb logo** (`script.meganexus/resources/media/imdb.png`) - shown next to
  IMDb ratings; IMDb is a trademark of IMDb.com, Inc.
- **HUB app tiles** (`skin.meganexus/media/meganexus/hub/app_*.png`) - the YouTube,
  Plex and Emby logos are trademarks of Google LLC, Plex, Inc. and Emby LLC, shown only
  to name the app a tile opens; the Jellyfin logo is by the Jellyfin contributors,
  CC BY-SA 4.0 (jellyfin/jellyfin-ux). MegaNexus is not endorsed by any of them.
- **HUB tiles** (`skin.meganexus/media/meganexus/hub/icon_*.png`) - Google Material Symbols (Apache 2.0) and
  Kodi's mark (from Kodi's own icon), a trademark of the XBMC Foundation, shown on the Kodi Settings tile.
- **Top bar icons** (`script.meganexus/resources/media/bar`) - Google Material Symbols, Apache License 2.0
  (sources in `review/assets/material_symbols`).
- **MegaSport backgrounds** (`script.meganexus/resources/media/sport_bg`) - photographs from Wikimedia
  Commons, cut to 16:9 and made smaller: CC BY 2.0, CC BY 4.0, CC BY-SA 2.0, CC BY-SA 4.0, CC0 and public
  domain; each picture's author, licence and page are in `sport_bg/CREDITS.md`. The changed pictures under a
  CC BY-SA licence stay under that licence.
- Rating logos and stream badge pictures are not bundled: they are loaded from
  their authors when shown (each badge set names its source in
  `plugin.video.meganexus/resources/badges/sets/sets.json`; Nebula's pictures:
  MIT, danielsdian/ColorfulAndConcise).

## Data

- **TRaSH Guides** release group tiers
  (`plugin.video.meganexus/resources/release_groups.json`) - MIT License,
  Copyright (c) 2021 TRaSH; see
  `plugin.video.meganexus/resources/licenses/TRaSH-Guides-LICENSE.txt`.

## Services

MegaNexus connects to services the user chooses (metadata, stream and subtitle
add-ons, Nuvio, Stremio, Trakt, Simkl, MDBList, TMDB, Plex, Jellyfin, Emby,
debrid and Usenet providers, Google Gemini). It is independent of all of them;
their names and logos belong to their owners.
