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
