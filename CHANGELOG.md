# Changelog

## 7.0.35 Beta

**License**
- 📜 The MegaNexus License now also says plainly: the code may not be used to train, fine-tune or prompt AI models, or be copied, translated or rewritten into another project with AI tools. Every MegaNexus file carries the license notice.
- 🗂️ This repository now holds the releases, the Kodi repository, the documentation and the issue tracker; the source code is no longer published here. Updates and the Kodi repository work exactly as before.
- 🐞 Problems and ideas: open an issue, or use *HUB Settings › Help & support › Report a problem*.

## 7.0.34 Beta

**Release badges on Home too**
- 🏷️ **Home and collections show the release badge** of the selected title under its details line - Released, In cinemas, Today, Tomorrow, Coming Friday, Coming soon - with the date, as on the title page.
- 🎬 Films switch to **In cinemas** once the cursor rests on them (TMDB's cinema and digital dates, fetched in the background - moving through Home stays as fast).
- 📝 The description on Home moves under the badge (two lines) only while a badge shows.

## 7.0.33 Beta

**Live TV / IPTV like Sport**
- 📺 **OK on the channel that plays enlarges it** right in the screen - the same playback, no new start and no TV mode switch.
- 📋 **OK on the enlarged channel: the group's channels on the left**, and beside them the **catch-up of the channel under the cursor** (the last 24 hours, newest first) - OK plays a programme from the archive.
- ↩️ **Back never stops the channel:** catch-up, channels, enlarged, small video, then the HUB button. Stop stops it; Info opens Kodi's own full-screen player.
- ⏳ Entering IPTV waits until IPTV Simple has loaded the channels and the guide after Kodi starts - nothing is reloaded after a suspend.
- ⚡ Channels switch faster: Kodi's "switch to full screen" is set once per visit instead of twice for every channel.
- 🧹 No key hints over an enlarged IPTV or Sport video.

**When a title comes out**
- 🏷️ **A release badge under the ratings** of every title: Released, In cinemas, Today, Tomorrow, Coming Friday, Coming soon - with the date. Episodes show their air day; films their cinema and digital / Blu-ray release from TMDB.
- 🎬 **Digital release filter** (Settings › Playback): a film only in cinemas, or an episode not aired yet, is not searched or played - also a manual search and Continue Watching - and you are told when it comes out. The same rules as AIOStreams.
- 🙈 **Hide unreleased titles** (Settings › Collections & Home rows): titles not out yet stay out of Home, collections and search, unaired episodes out of a series.
- 🔑 The user guide explains why a TMDB key is recommended (release badges, the filter, details and trailers for TMDB-only titles).

**Smoother**
- 📚 **Add to Library and Mark watched work in the background** - no loading screen over the page, a notification when done.
- 🌙 **The screensaver darkens once, a second earlier** - no second darkening.
- 🔅 **Dim the screensaver** 10-50 % (Settings › Screensaver), fading in like Kodi's Dim - 50 % is barely visible.

## 7.0.32 Beta

**Collections like an Android TV app**
- 🪟 **A collection opens in its own screen over Home:** Back closes it and Home is there exactly as it was - same row, same card, same place on the screen. Nothing is filled, scrolled or animated again (it used to take up to 2 seconds on a box).
- ⚡ **Collections open at once:** the rows the cursor loaded are shown as they are, the first posters, background and logo are in Kodi's memory while the tile is selected, and a reused screen never shows the last collection first.
- 🧈 Entering a collection fades in without the jump; Home no longer slides or flashes when you come back.

**Artwork from TMDB / Fanart.tv**
- 🖼️ **Backgrounds and title logos are prepared like the posters:** the one-time setup stores the poster, background and logo of every collection's first page (both rows), so selecting a title shows them at once.
- 🔁 **Changing the Artwork provider prepares the new pictures when you leave Settings** (never while you are still choosing) - collections no longer change their posters one by one.
- 💬 The setup screen reads "preparing collections · posters and artwork" and counts pictures.

**Cache and preparation**
- 🧹 **Clear MegaNexus images and metadata cache really clears:** Kodi's own copies of MegaNexus pictures are removed too (also those from an earlier image port), with progress and a count; the pictures are prepared again when you leave Settings.
- 🚀 **No preparation screen on every start:** Kodi's card-size poster copies were not recognised, so posters it had seemed missing.
- 📊 Cache usage counts every picture Kodi keeps for MegaNexus.

**Player**
- 🌑 **Leaving a film with "Adjust display refresh rate" on:** the screen goes black at once and fades to MegaNexus once the TV has switched back - no blink. The black at the film's start is shorter.
- 🎬 Trailers and films started from a collection open in Kodi's player and Back leaves them.

## 7.0.31 Beta

**Faster opening and browsing**
- ⚡ **MegaNexus opens much faster with many collections:** a collection is looked up on its own instead of copying the whole layout each time, and the opening check reads only the catalogs that changed since the last start (with 600 collections the check went from about 45 seconds to a few).
- 🏎️ Home rows and collections fill faster: each add-on's cache key is worked out once instead of for every catalog.

**Every title opens and plays**
- 🎬 **No more "Retry details":** when your metadata add-ons have no details for a title, MegaNexus asks Cinemeta (always installed) - a title known only by its TMDb ID is matched through TMDb when a TMDb key is set - and a film may also come from TMDb. Never a guessed title.
- 🧩 Anime titles opened by their MAL, Kitsu or AniList ID load their details.
- 🔗 **Sources for TMDb-only titles:** when none of your stream add-ons takes the TMDb ID, they are asked by the title's IMDb ID - only then, so nothing else slows down.
- 🎞️ Trailers are found for titles that only have a TMDb ID.
- 🧾 When a title's details cannot load, kodi.log says why.

**Player and phone**
- ▶️ **The Trailer button plays in Kodi's own full-screen player** on every device; Back or the end of the trailer returns to the title.
- 📱 **Save on the phone page works with large layouts** (hundreds of collections were rejected with "Bad request").
- 🔁 Continue Watching keeps using the last source after an AIOStreams link is copied again.
- 🧰 An AIOStreams add-on merged from several copies keeps its switched-on roles (metadata, streams, subtitles, sport).

## 7.0.30 Beta

**Smoother on Android TV and CoreELEC boxes**
- 🏎️ **Home and collections move more smoothly:** cards are prepared before they go on screen, Home asks Kodi only after a key press, and the poster transparency is one colour instead of five effects per poster.
- 🖼️ **Posters at card size** on Kodi 21: about a third of the pixels to decode and keep in memory, just as sharp.
- 🌫️ Posters fade in instead of popping up; the collection grid and the person page load them in the background, so the screen never stands still.

**Ready when MegaNexus opens**
- ⏱️ **Every start prepares Home and every collection:** the opening screen stays until Kodi has 90 % of their posters - the whole first page of every row, Series rows too. A first setup runs to the end; the day's new posters take at most a minute. Pictures that cannot load are skipped at once (and for a day). Back always skips.
- ⭐ **Ratings at once:** the MDBList ratings of all those titles arrive in a few requests and are kept for a day - at most 60 % of your daily MDBList requests, the rest stays for the titles you open.
- 📊 **Cache usage** (Performance) shows the posters Kodi keeps; select it to count again.

**Fixes**
- 🎬 **More like this → a title → its details** no longer stops at "Retry details" (titles opened by their TMDb id - also from people and calendars).
- 🧩 An AIOStreams add-on copied again (its link changes every time) no longer appears two or three times in every list - and its sources once.
- 🎨 Changing the theme closes the settings and opens Home in the new theme - no empty page left behind.
- 🍿 **Cinemeta only:** Home shows what Cinemeta offers - Popular and Featured, movies and series, as poster rows.

## 7.0.29 Beta

**Streams and playback**
- ⚡ **Sources open fast and keep coming:** the source list opens with the first results and fills in as each add-on answers; the built-in TorBox / Premiumize search no longer cuts the other add-ons off. Each link appears once.
- 🧭 **Choose by add-on:** a row above the sources - All, TorBox direct, Premiumize direct, then every add-on by name - and every source shows where it comes from.
- 🏆 **Smarter automatic choice:** at the same resolution REMUX, then Blu-ray, WEB-DL, WEBRip; then Dolby Vision / HDR and the best audio (TrueHD Atmos, DTS:X / DTS-HD MA, Atmos…).
- 🔁 **A source that does not play is skipped:** a debrid placeholder or an instant end no longer sends you back to the title page - Autoplay tries the next source, and a chosen source brings the list back without it. Add-ons that did not answer are asked again before "No streams found".
- 🎬 **Straight into the film:** the loading screen shows the title's picture and logo and stays until the film's picture moves; Back waits while a source starts; no page or wrong colours between loading and the film.
- 💾 **Downloads:** HUB Settings → Downloads; hold OK on a source to keep it on your device or network share. A blue ring by the clock shows the progress, and a lost connection or a restart carries on where it stopped. TorBox / Premiumize direct sources included.

**Player**
- ✨ Sharper, clearer icons; the bar hides after 5 seconds (not while paused or while one of its menus is open).
- 🏠 **Home while a film plays:** the film goes on behind Home; **Now playing** brings it back.
- ⏭️ **Skip intro / outro and Next episode** side by side, from TheIntroDB, Plex / Jellyfin / Emby markers or chapters; Next episode also from your "watched" percentage. The buttons go after 10 seconds.
- 💬 **Autosync subtitle offset** (on by default): lines a subtitle from your subtitle add-ons up with the video - no AI. A subtitle that cannot be downloaded gives way to the next release.

**Watching and tracking**
- 📺 **Series:** season pills, "Next · S5 E3" before them (the episode after your last one), Mark / Unmark watched on any episode with a long OK.
- ✅ **Every tracking service at once:** Mark watched, Unmark watched and Add to Library reach Trakt, Simkl and MDBList.
- ▶️ **Continue Watching:** one card per title, even when two apps saved it under different IDs or languages.
- 🔎 **Search** finds films and series again when a metadata add-on also lists sport; people with photos only.
- 📚 **Library:** 20 titles per row, then "Browse all"; grids keep your place after "Load more".
- 🎨 **Pictures from your services:** posters, backgrounds, logos and landscape cards from TMDB or Fanart.tv when you choose (Home & library → Artwork).

**Live TV and Sport**
- 📡 IPTV channels open on the click again; catch-up opens in the background and goes full screen once the picture is there.
- ⚽ Sport lists only sport, refreshes its catalogs on every visit and never empties itself when an add-on hiccups.

**Everything else**
- 📱 **Write with phone** on every on-screen keyboard.
- 🐞 **Report a problem** (Help & support): describe it on your phone; it reaches the developer with the Kodi log, personal data removed. Three reports a day.
- 📖 **User guide** in Help & support explains every screen and setting.
- 🎨 Your own interface colours in Themes, with a preview; the player follows the theme.
- ☕ Buy me a coffee · Ko-fi right under the phone set-up.

## 7.0.28 Beta

- 🖼️ **Wallpaper for Home and the HUB:** your own picture, a slideshow of a
  folder, or simply the screensaver's picture or slideshow behind MegaNexus
  Home, the catalogs, Library, Live TV, Sport and the HUB - darkened so text
  stays readable, without motion (Home stays as light as before). HUB Settings
  › Home & appearance › Wallpaper, or "Also as Home and HUB wallpaper" on the
  phone page. Off by default.

## 7.0.27 Beta

- 📏 **Widget sizes:** clock, weather, calendar and text each have Small,
  Normal and Large (Large is the earlier size, Normal 25 % and Small 50 %
  smaller; new scenes start at Normal) - in the TV's studio and on the phone.
  Every size has its own layout, so a widget stays in its corner.
- 🎬 **Preview shows your real screensaver:** Preview (HUB Settings ›
  Screensaver) and Show on TV (phone) play your video like the screensaver Kodi
  starts by itself - before, they showed only the MegaNexus picture.
- 🌘 **Gentle start:** when Kodi starts the screensaver the screen fades to
  black in a second, then the screensaver appears over three seconds. A video
  starts only once the screen is black (Kodi draws video below everything, so
  it used to flash in at full brightness before the fade).
- 🎛️ **The studio shows your video** behind its panel, like the preview.

## 7.0.26 Beta

- 📲 **Videos from an iPhone arrive:** sending a large video (a 40 MB 4K live
  wallpaper, for example) from the phone page could stay on "Please wait…"
  for ever - a piece whose answer was lost (iOS pauses a page when the screen
  locks, Wi-Fi drops for a moment) was never sent again. Each piece now has a
  time limit and a few new tries, the TV accepts a piece sent twice, and the
  button shows how far the upload is ("Uploading 37 %"). A file the phone
  cannot read (still in iCloud) says so at once.
- 🎞️ iPhone videos without a file extension, and older QuickTime files, are
  recognised by their content.

## 7.0.25 Beta

- 📱 **The screensaver from your phone:** the phone page (HUB Settings › Set
  up on phone) has a Screensaver tab with a live 16:9 preview of the TV.
  - 🖼️ **Your pictures:** pick a photo, drag and zoom to choose the frame,
    adjust brightness, contrast, colour and blur - the TV gets a sharp
    1920 × 1080 copy. Up to 40 pictures: one as the background or all of them
    as a slideshow.
  - 🎬 **Your video:** MP4, MOV, MKV or WebM up to 100 MB, sent in pieces and
    played silently in a loop.
  - 🕰️ **Widgets:** style, colour and position of the clock, weather,
    calendar and your text - the same choices as the TV's studio, saved on the
    TV as you tap.
  - 📺 **Show on TV:** the screensaver appears on the TV at once; any key
    closes it.
- 🌫️ **Calmer screensaver motion:** the picture now drifts and zooms so slowly
  you do not notice it (4 % over 2.5 minutes, 28 px over 3 minutes, before 10 %
  and 60 px within a minute), slideshow pictures cross-fade over 4 seconds,
  and the widgets move only 6 px every three minutes to protect OLED screens.
- 🪟 **Updates on Windows:** replacing the interface, skin and screensaver
  waits out a folder held open for a moment (an antivirus scanning the new
  files) instead of failing; leftovers of an update can no longer turn a
  finished update into an error.
- 🛠️ The phone page no longer resets a slideshow background to the MegaNexus
  picture when you press Save.


- 🌅 **MegaNexus Ambient - a Google TV-style screensaver:** your picture (or
  a slideshow of a folder) with a slow pan and soft shading at the top and
  bottom, and ready-made widgets: **clock** (time with the weather beside it,
  stacked, chip, classic serif, digital), **weather** (chip, card, five-day
  forecast with colour icons), **calendar** (month, today, week) and your own
  **text** (caption, quote). Each widget has only a style, a colour (eight
  Material tones) and a position (eight places); the widgets move a few pixels
  every minute to protect OLED screens.
- 🎛️ **Screensaver studio, live:** the studio opens over the screensaver
  itself with a Google TV-like side panel - Left / Right change a widget and
  you see it at once; the panel moves away from the widget you edit and can be
  hidden to see the whole screen. Changes are saved as you go.
- ⚙️ **Every screensaver setting in one place** (HUB Settings › Home &
  appearance › Screensaver): on / off, when it starts (the idle time that was
  only in Kodi's settings), background, studio and preview.
- 🌤️ **The weather and clock corner, the same on every screen:** top right on
  Home, collections, Library, Live TV, Sport, title details, the screensaver and
  now also the HUB - a colour weather icon (sun, cloud, rain, snow, storm,
  fog...), the temperature and the time in one modern font. It hides while a
  film plays in full screen, and without a weather location it shows no
  temperature (Kodi reported 32 °F).
- 😶 **Emoji in collection and catalog names are left out** instead of showing
  empty boxes (Kodi's font has no emoji).
- 🏷️ **Row titles can be hidden** (Home & appearance › Row titles; per row in
  Collections › Home rows).
- ⚽ **Sport: choose the stream, no error windows:** the streams of the
  channel under the cursor appear next to the channel list (also in the
  enlarged player) - OK plays that one. Every stream is checked before it
  plays: an offline one is skipped quietly instead of Kodi's "Playback failed"
  window, and a stream that cuts out reconnects by itself, then moves on to the
  next stream of the event.
- ▶️ **Continue Watching without duplicates:** a title started on one device
  and continued on another shows once, with its poster; live TV channels no
  longer appear in Continue Watching.
- 🎬 **A simpler player:** play / pause in one button on the left, then
  subtitles (searches every subtitle add-on at once and lists all versions,
  with "Subtitles off" while they are on), subtitle offset (Kodi's slider on
  top), audio stream (language, format and channels of each one; a video with
  a single stream says so) and diagnostics on / off; info and settings stay on
  the right. Previous, rewind, forward, next, bookmarks and the DVD menu
  buttons are gone (Live TV keeps its channel, guide and record buttons), and
  the chapter line on top of the player is no longer shown.
- 📊 **A clearer diagnostics window:** System (CPU, memory, interface FPS), Video
  (picture, codec and decoder, pixel format, HDR type, the Dolby Vision
  profile and FEL / MEL as the stream carries it, output mode, buffer) and
  Audio (format, channels, language, output), labels on the left and values on
  the right, without the explanation text. The Dolby Vision profile is now read
  for every Dolby Vision video, so the window can be switched on during
  playback from the player's new button.
- 🔬 **Dolby Vision diagnostics - source and processing kept apart:** the
  diagnostics window has a Dolby Vision section. *Source* is what the stream
  carries: profile (P5, P7, P8.1, P8.4...) and, for P7, FEL or MEL - from
  Kodi 22's `VideoPlayer.HdrDetail` (CoreELEC 22 adds FEL / MEL; upstream Kodi
  only says 7, shown as unknown) or, on CoreELEC 21, from Kodi's log; on
  CoreELEC 22 also the RPU, the dual-layer structure (ST-DL / DT-DL) and what
  the player changed (`Player.Process(video.sidedata)`). *Processing* is what
  the box does: the FEL path Kodi switched on (the driver's own log), the
  enhancement-layer decoder (`/sys/class/vfm/map`) and, once per video after
  a few seconds, a short check that turns the driver's frame-pairing log on
  for 2.5 s and counts base and enhancement frames paired with the same
  timestamp, then restores its setting. Only that check can show "P7 FEL ·
  full processing verified"; anything less says what is known ("source
  detected", "processing path active"). Off CoreELEC only Kodi's labels are read.
- 🖼️ **New covers for the built-in collections:** the Cinemeta collections
  (Discover and Genres) have MegaNexus's own covers; no third-party collection
  artwork is included any more.

## 7.0.23 Beta

- **The first collection after a Kodi start opens at once:** right after Home
  opened, the background poster preload read every collection's pages and
  Kodi's whole texture list and downloaded the posters Kodi lacked - on a
  CoreELEC box for about 9 minutes, and the first collection took over 10 s.
  It now starts 20 s after Home opens, waits whenever the cursor moves or a
  collection, title or video is open, and asks Kodi's thumbnail files instead
  of its database.
- **No downloads of posters Kodi already keeps:** resting on a collection card
  prepared its first posters in the image memory even when Kodi had them on
  its disk already (the image memory grew with every collection). They are
  now skipped.

## 7.0.22 Beta

- **"Browse all" lists the row's kind only:** inside a collection, the Movies
  and Series rows both opened the whole collection, so "Browse all" of a Series
  row showed films too. Each row now opens only its own kind, decided by the
  type of every catalog in the collection - not by the collection's name - so
  it works for any collection, also when opened from Kodi's add-on list.
- **Every kind of catalog in a collection is shown:** a collection showed only
  Movies and Series rows; sources of another type (e.g. an add-on's "anime"
  catalogs) were left out. They now get their own row with its own
  "Browse all".

## 7.0.21 Beta

- **Much faster on CoreELEC and Android boxes:** while a title was selected,
  MegaNexus re-read its whole settings file up to 15 times a second (on Kodi 21
  every new add-on object parses it again), and once per catalog when opening.
  On a CoreELEC box that kept the interface busy: collections took seconds to
  open and Back was slow. Settings are now read once and kept for 2 seconds,
  and a title's details are prepared once instead of on every tick.
- **Search shows Movies, Series and Anime:** instead of one row per catalog of
  every metadata add-on (named after the add-on), search now has one row per
  kind - Movies, Series, Anime, titles by people and Actors & crew - with the
  results of all enabled metadata add-ons merged. A title appears once, with
  its picture from whichever add-on has one.
- **Collection animations play in full:** Nuvio collections use animated WebP,
  which Kodi cannot play, and Kodi keeps every frame of a GIF in memory (the
  original 1000 px animations would need ~300 MB). Each animation is converted
  once to a small GIF (320 px, by the public image service wsrv.nl, which only
  receives the picture's public link) and kept in Kodi's temp folder. It plays
  once, from start to end, when the cursor rests on the card; then the cover
  returns. The switch in Home & appearance still turns animations off.
- **Smooth transitions:** a collection (and Home) slides in when it opens,
  titles open with a short fade and zoom, and Back fades between screens. All
  are GPU animations: no extra work for the processor.
- **Diagnostics overlay:** HUB Settings > Maintenance & updates. A corner window
  shows CPU, RAM and interface FPS, and while a video plays its resolution,
  frame rate, codec, decoder and pixel format, HDR type with the Dolby Vision
  profile and FEL / MEL (CoreELEC), display mode, audio format, channels and
  output, and the buffer - with a short explanation. It takes no focus, so
  menus and the player work as usual; turn it off in the same place.
- **Reset MegaNexus:** HUB Settings > Maintenance & updates erases every MegaNexus
  setting and saved file (add-ons, collections, accounts, preferences,
  Continue Watching, caches), restarts Kodi and starts like a new installation.
- **Preferred audio language:** HUB Settings > Playback > Automatic stream choice.
  It is Kodi's own preference, so Kodi picks that track as the video opens.

## 7.0.20 Beta

- **Subtitle add-ons and Sport add-ons have their own lists:** HUB Settings >
  Add-ons now shows *Subtitle add-ons* and *Sport add-ons* next to Metadata and
  Stream add-ons, each add-on with its own switch. The same lists open from
  HUB Settings > Subtitles and from Live TV, IPTV & Sport, and the phone setup
  page shows them too.
- **Sport is a role of its own:** *Your add-ons* now switches Streams,
  Metadata, Subtitles and Sport separately for every add-on (a role the
  add-on does not offer stays dimmed). A sports add-on - or AIOMetadata with
  sport catalogs - switched off for Sport leaves the Sport screen, whatever
  else it serves. All are on by default, as before.

## 7.0.19 Beta

(7.0.17 and 7.0.18 were test builds only.)

- **Smooth on CoreELEC and Android:** Home no longer prepares posters in the
  background (the collection under the cursor, the rest while idle). On a
  CoreELEC box that work - and MegaNexus asking Kodi's texture database ten
  times a second whether a poster was ready - made clicks do nothing for up to
  20 s and opening a collection slow. Posters are now prepared **only behind
  the One-time setup screen** (first start, after every update, or when Kodi
  lacks more than 10 % of them), 10 at a time on ARM boxes (30 on a PC), and
  MegaNexus checks Kodi's thumbnail files instead of its database. Afterwards
  Kodi's normal cache takes over; the ring next to HUB is gone.
- **Choose what each add-on is used for:** HUB Settings > Add-ons > *Your
  add-ons* lists every add-on with three switches - Streams, Metadata and
  Subtitles. AIOStreams may serve all three, AIOMetadata only metadata, a
  subtitle add-on only subtitles: a role the add-on's manifest does not offer
  is dimmed. Subtitles can now be switched per add-on too (all on by default,
  as before). Adding an add-on opens its switches right away.
- **Updating from the previous MegaNexus no longer loops on "Keep this
  skin?":** the previous backend kept restoring its own skin while MegaNexus 7
  asked for MegaNexus Skin. Its skin restore is now turned off first (bridge
  and MegaNexus Hub). If MegaNexus Skin is declined during the move,
  MegaNexus 7 removes itself and the previous MegaNexus stays as it was; the
  update is offered again at the next Kodi start. Normal updates of MegaNexus 7
  never ask for the skin again.
- **Cinemeta is the only built-in collection default:** the earlier optional
  add-on based collection preset, its bundled covers and its bundled animation
  table are removed (the package is about 30 MB smaller). Metadata add-ons and
  Nuvio bring their own collections.
- **Animated collection art comes from the collections themselves:** their own
  animation, or a GIF cover, animates on the focused card. The switch
  (Appearance > *Animated collection art and GIFs*) is on by default and keeps
  them still when off.
- **Catalogs that do not answer no longer slow the opening screen:** a
  catalog that failed or came back empty once is not waited for again for 7
  days (was 6 hours) - it is still retried in the background at every start
  and appears as soon as it answers. Sport catalogs no longer load behind the
  opening screen (they belong to Sport).
- **Each playback no longer leaves memory behind, and Kodi exits after
  watching:** the subtitle search kept two idle workers in every playback's
  add-on call, so Kodi kept each call (and its memory) until it exited - and
  then hung on Exit. The workers now end once the search is done.
- **A version the device cannot decode is stopped even before it starts:** the
  decoder check now begins when Kodi opens the file, and the loading screen
  closes at once with the reason (it waited a minute without a word).

## 7.0.16 Beta

- **The cursor stays on the titles when a collection opens.** While its titles
  were still loading the row showed one *Loading titles* card, which carries
  the collection's link - so does *Browse all* at the end of the row, and the
  cursor followed that link to the end. Placeholders are no longer remembered
  as a selection.
- **Collections open faster on Android.** Preparing the posters of the
  collection under the cursor started after a quarter of a second and kept
  Kodi's image loader busy just when the collection was opened. It now starts
  only when the cursor rests on a collection for 1.5 s, stops as soon as a
  collection opens, and the background work waits 3 s after Home opens.
- **The one-time poster preload runs again after every update.** MegaNexus
  then counts which posters of the collections' first screens Kodi really
  lacks; with more than 10 % missing the *One-time setup* screen fills them,
  otherwise Home opens at once.
- **The HUB picture shows at once** when MegaNexus opens (Android showed
  Kodi's busy spinner while the interface was starting).
- **Kodi closes properly after a stream that never showed a picture:** the
  progress tracker of such a playback never heard its stop and kept Kodi
  alive after Exit; it now also ends when Kodi exits.

## 7.0.15 Beta

(Everything since 7.0.5; 7.0.6 to 7.0.14 were test builds only.)

### Faster Home and collections
- **Collections open with all their posters at once.** Kodi makes its own copy
  of a poster the first time it shows it, so collections opened for the first
  time filled in one poster at a time (very visible on Android boxes).
  MegaNexus now lets Kodi prepare them in advance through invisible images:
  - **once per device** (or after many new collections) opening MegaNexus
    shows *One-time setup* with the progress and prepares the first screen of
    every collection, 30 posters at a time; Home opens at 90 % and the rest
    finishes in the background (Back skips it);
  - afterwards new posters are prepared in the background: the collection under
    the cursor first, the others while Home is idle; nothing is done twice.
  - A small **ring next to HUB** fills while this runs, shows a tick and fades
    out. About 30 KB per poster on the device. HUB Settings > Performance >
    *Prepare collection posters in advance (experimental)*, on by default.
- **Home opens at once after Kodi starts:** no more *Loading posters into
  memory* screen (it downloaded posters Kodi already had). Posters Kodi does
  not have load in the background, up to 80 % of the chosen image memory.
- **Opening MegaNexus and Sport:** the HUB picture of your theme with a blue
  ring that fills while catalogs load - no dark frame, no text.
- **Catalogs that do not load are not waited for:** a catalog that failed or
  came back empty used to be fetched again behind the opening screen every
  time (up to 40 s). Now it is retried in the background for 6 hours.
- The image server downloads up to 12 posters at once (was 6).

### Streams and playback
- **TorBox and Premiumize built in (beta):** add your API key (HUB Settings >
  API keys, with links) and their streams appear next to your stream add-ons,
  no add-on needed. TorBox closed its own search, so MegaNexus finds a title's
  torrents by its IMDb id in a public index and asks your service which ones it
  already has. **Cached only** (on by default) lists only those - they play at
  once; off, the others are listed as *Not cached* and choosing one starts the
  download on your account. Add-ons > TorBox & Premiumize.
- **Automatic stream choice:** Playback > *Automatic stream choice* orders
  every source (add-ons, TorBox, Premiumize) and Autoplay starts the first:
  highest resolution (up to 4K / 1080p / 720p), largest film and largest
  episode in GB, Dolby Vision (prefer / no preference / avoid), HDR, cached
  debrid results first, CAM releases last. Rows outside the limits move down,
  never away; your own Plex / Jellyfin copies stay first. Off keeps the
  add-ons' own order.
- **Starting a title:** its logo fills from left to right while the streams
  are searched, as in Stremio.
- **A version the device cannot show is stopped:** e.g. 4K HDR 10-bit without
  a fitting hardware decoder started its sound but never a picture, and the
  hidden player then blocked trailers ("Stop the current video"). MegaNexus
  reads Kodi's log from the start of playback and stops the video only when
  Kodi reports that its decoder cannot show it - never because a slow
  connection takes long.
- **Episodes show their own picture** (16:9 still) instead of the series poster.

### Tracking
- **MDBList as a tracking service:** Accounts & tracking > MDBList (uses your
  MDBList API key). What you watch is scrobbled to MDBList and its watched
  marks show in MegaNexus, next to Trakt and Simkl.

### Sport
- **Sport catalogs of any add-on go to Sport:** AIOMetadata's *⚽ Nogomet •
  Uživo*, *🎾 Tenis*... are recognised by type, id or sport emoji and shown in
  the Sport screen instead of as Home collections (they also ask for a genre,
  which hid all of them). Movie collections such as *Sports dramas* stay on
  Home. Events from such catalogs get streams from your stream add-ons.
- Sport says *No live or upcoming events right now* when your sport catalogs
  are empty (it said no sports add-on was installed).

### Reliability
- **Kodi closes properly again:** a background catalog refresher could wait
  forever, so Kodi stayed in memory after Exit (on Android the next start then
  competed with it). It now ends with MegaNexus or Kodi; a lost loading flag
  expires after 3 minutes; the counter of catalogs being opened is thread-safe
  (when it went wrong, all background work stopped for the session).
- Links in MegaNexus' playback log lose their query part (debrid CDN tokens).

## 7.0.5 Beta

- **Kodi closes properly again:** after browsing, a few idle background
  workers (catalog refresh, details preloading, cache revalidation) never
  ended, so Kodi waited for them forever on Exit and the old Kodi process kept
  its memory. On Android boxes the next start then had to compete with it,
  which made posters and menus slow. The workers now end with the interface.

## 7.0.4 Beta

- **Glass everywhere in MegaNexus:** the Kodi windows MegaNexus opens (choices
  such as the memory preset, yes/no and update questions, progress, text,
  the keyboard, notifications and the context menu) use the translucent
  MegaNexus look. Kodi's own settings, add-on browser and file manager keep
  Kodi's standard look.
- **Settings stay where you are:** turning a row On or Off near the bottom of
  a long list no longer jumps back to the top.
- **Posters after moving from the previous build:** the image server keeps its
  address, so the posters Kodi already cached show at once instead of loading
  one by one again.

## 7.0.3 Beta

- **One look everywhere:** Add-ons, Collections & Home rows, IPTV setup and the
  Continue Watching sync options open as translucent MegaNexus pages instead
  of Kodi's old list window.
- **Live TV, IPTV & Sport on one page:** IPTV status, set up with an Xtream
  account or an M3U playlist with TV guide, open the channels, and the Sport
  player and autoplay (the page was empty in 7.0.1–7.0.2).
- **Memory:** three presets in Performance: 128 MiB for low-end devices,
  **256 MiB (default, recommended)** and 512 MiB for high-end devices.

## 7.0.2 Beta

- **Moving from the previous build is all or nothing:** first MegaNexus Skin
  (asked until you accept it), then MegaNexus Screensaver, then every old
  add-on is turned off and Kodi asks to restart. Until then the previous
  MegaNexus keeps working, so nothing is left half-way.
- After the restart the old add-ons, their data and Kodi's cached installers
  of them are removed (a small backup stays in MegaNexus Hub's profile).
- The previous backend shows as **MegaNexus Hub (old)** until it is removed.

## 7.0.1 Beta

- **The skin comes first:** after installing, MegaNexus waits until you answer
  Kodi's "Keep this skin?" question. Setup starts only once MegaNexus Skin is on.
- **HUB Settings in setup order:** Set up on phone, Accounts & tracking (Nuvio,
  Stremio, then Trakt and Simkl), Add-ons, API keys, Collections & Home rows,
  **Local & network storage** (drives, Plex, Jellyfin), Continue Watching,
  Playback, Subtitles, Trailers, Live TV & Sport, Home & appearance,
  Performance, Backup & restore, Maintenance & updates.
- Add-ons: **Import add-ons from Stremio** right under Import from Nuvio.
- The phone page follows the same groups (Accounts, Add-ons, API keys,
  Collections, Display, Backup).
- Cleaner menus: no Kodi interface settings shortcut and no duplicated rows.

## 7.0 Beta — MegaNexus on its own

The first version under the MegaNexus name everywhere, and the start toward
the stable 7.x release.

**MegaNexus as its own add-ons**
- New add-ons: **MegaNexus Hub** (`plugin.video.meganexus`), **MegaNexus**
  (`script.meganexus`), **MegaNexus Skin** (`skin.meganexus`) and
  **MegaNexus Screensaver** (`screensaver.meganexus`).
- Updating from the earlier build moves everything on its own: settings, API
  keys, Nuvio / Stremio / Trakt / Simkl / Plex / Jellyfin sign-ins, add-ons,
  collections, Home folders, the local library and Continue Watching. The
  skin and screensaver switch over, the old add-ons are turned off and removed
  after one restart. A small backup of the old profile is kept.

**New**
- **Backup and restore:** every setting, account, add-on and collection in one
  file (HUB Settings → Maintenance, or the Backup tab on the phone page).
  Restore it on a new device and everything is the same.
- **API keys page** on the TV and phone: TMDb, MDBList, Fanart.tv and
  TheIntroDB, each with a link to the page where you get the key.
- **Stremio account (beta):** sign in, import your add-ons and Continue
  Watching, and optionally keep Continue Watching in sync.
- **Plex and Jellyfin / Emby (beta):** your own copy is offered first, with
  Home rows for Continue watching and Recently added. Ready for Jellyfin 12
  (new sign-in, Quick Connect).
- **Local storage (beta):** movies and series from your own drives.

**Easier start**
- A clear first screen: *I use Nuvio*, *I use Stremio*, *Restore a backup*,
  *Set up on your phone*, *Start simple* or *Step by step*. One sign-in brings
  your add-ons, metadata, collections and Continue Watching.
- After **Check for updates → Install**, Kodi asks to restart right away.

**Better**
- Simkl downloads only what changed, and nothing while a video plays.
- Trakt: watched marks for Trakt-only users, Mark watched goes to Trakt,
  watches made offline are sent later.
- Memory presets for low-end, standard and high-end devices.
- A failing button never closes MegaNexus any more; you see a short message.

## 6.0 series (2025–2026)

The 6.0 builds created MegaNexus: the remote-friendly Home with collections and
Continue Watching, phone setup, themes and the glass look, IPTV and Sport,
automatic updates, Kodi 22 support and the tracking services. 
