# Changelog

## 9.1.3

Retro games, Guess It and Poker played with phones, what really goes to the TV in the diagnostics - and no more memory filling up after a game.

**Retro, Guess It and Poker (HUB)**
- A new row under the HUB's apps: Retro, Guess It and Poker. Everyone on the TV's Wi-Fi scans one code and plays with their phone - up to 8 phones at once, each one the next player.
- Retro plays free classics that may be shared - Doom, Heretic and Quake (their shareware), Freedoom 1 and 2, Tyrian 2.1, Commander Keen 4, Bio Menace, SkyRoads, One Must Fall 2097, Cave Story, Mr.Boom, Apotris and MeteoRain - and the games in your own folders, with their pictures and consoles. Each download is checked against its known checksum.
- Each phone gets the game's own controller and starts games and opens their menu. MegaNexus' own phone-pads add-on carries the phones into the game on Android, Linux (CoreELEC, LibreELEC) and Windows, Kodi 21 and 22. A Bluetooth controller plays along.
- Guess It: a party quiz from TMDB - films, series and actors from stills, posters, faces, taglines and plots; four answers, points for speed, the scores every five questions and a podium. Phones answer; with no phone, the remote plays. Nothing of the answer shows behind a question.
- Poker: no-limit Texas Hold'em for 2 to 8 players on a 3D table with everyone's name, chips and bets. Each phone holds its own two cards - face up only while a finger is on them - with Fold, Check / Call and Raise (Min, ½ Pot, Pot, All-in). Starting chips, blinds and time to play to choose; the blinds double every 10 hands, and a player whose phone is gone checks or folds after 10 seconds.

**Diagnostics**
- What really goes out to the TV and the receiver, on every system: the signal, its colour format and bits, what the TV and the receiver take, and the audio as it leaves the box (Amlogic, Linux, Android).
- Pixel format in plain words - "YUV 4:2:0 · 10-bit". With a hardware decoder, the bits only when the system or the film's own Dolby Vision metadata gives them, never a guess.
- Dolby Vision profile and pixel format are no longer "Unknown" on CoreELEC avdvplus (GitHub #40).
- LibreELEC's Dolby Vision builds: whether their own engine composes the full enhancement layer (FEL), as CroqueMr's CB1 and LibreELEC Hades report it, and why not when they fall back.

**Stream badges**
- Nuvio badge packs written for JavaScript import: letters and digits of every script and the look-ahead checks of resolution rules (FR-Badges: 238 of its 239 rules; GitHub #41). A rule Kodi cannot run is left out and named, instead of the whole pack being refused.

**Watch Party**
- Relays come from a list MegaNexus publishes, are checked before they are used, are rested when they refuse, and the host shares theirs with everyone in the party.

**Memory and stability**
- Every closed screen - Home, a game, Guess It, Poker - stayed in Kodi's memory until Kodi itself closed, so a box slowed down after a few games. They are now freed as they close, and a game lets go of the phones at once.
- Kodi could crash when Retro closed while a phone was still a controller.
- On Kodi 21 for Windows, Retro, Music and Sport now close properly.

## 9.1.2

Subtitles in the language they say, the right episode first, more of YouTube - and every title in the Library with its logo and plot.

**Subtitles**
- The video's own subtitle track in your language is put on first, before any is looked for.
- A subtitle whose lines are in another language than it is called is passed over for the next one. OpenSubtitles has uploads under the wrong language (a Hungarian one named Croatian, for one). Every language is weighed the same way: by its alphabet, then by its most common words. Serbian and Bosnian are right in either alphabet.
- Autosync no longer moves a subtitle that fits nowhere. A subtitle for another episode was moved by one or two minutes on pure chance; it now stays as it is.
- A subtitle you pick yourself - in MegaNexus' list or in Kodi's own subtitle settings - is never changed by anything automatic afterwards, and subtitles you switch off stay off.

**Sources**
- A series' source whose name says another episode (S02E07 for S2E2, another chapter) goes to the end of the list, marked as such, and Autoplay never takes it first. A debrid torrent plays the file the index named.
- Apple ProRes, DNxHD and CineForm sources go last on TV boxes (Amlogic, Android, ARM): no box decodes them in hardware, and one froze a Fire TV Cube. Started anyway, such a source is stopped at once and the next one plays.

**Library and Calendar**
- Every title under the cursor has its logo, plot, year, kind, genres and TMDB rating - Trakt's, Simkl's and MDBList's cards came with none of them. What MegaNexus was told before shows at once, the rest comes in place while you look (TMDB, else your metadata add-ons).
- The plot keeps to three lines: as wide as before when it fits, across the screen when it does not, and cut at a word with "…" when even that is not enough.

**YouTube**
- Its rows go on as you near their end - they no longer stop after YouTube's first two pages.
- Options in the app's top bar: the titles under the cards and the rows' titles (the app's own), which rows it shows (switched on and off at once), and Kodi's YouTube add-on's video quality, region and language, and Autoplay.
- Rows to add (Options › Rows): Live · News, Sports, Gaming and Music, Documentaries, History, Animals, Kids, DIY & crafts, Fashion & beauty, Anime and Learning.

**CoreELEC cpm, avdvplus and P3i**
- If the picture still goes black after a seek, restart the box once - a full restart, not sleep. A box that ran MegaNexus 9.1.0 or older since its last start keeps the setting that version left until it restarts (GitHub #39).

## 9.1.1

A Calendar, a new Library, Top 10 rows, AniList and MyAnimeList - and no black picture after a seek on CoreELEC cpm / avdvplus.

**Playback**
- A seek, a chapter skip or a resume turned the picture black while the sound went on, on CoreELEC "cpm" and "avdvplus" builds (Ugoos AM6B and others; GitHub #35, #37, #38). MegaNexus set the video driver's black-out (blackout_policy) to 1 before every film and every few seconds; these builds keep the last frame (0) and count on it during a seek. MegaNexus now notes the box's own value once per start and leaves it as it is - it keeps the frame only for small videos (trailers, Sport and IPTV previews), and only on boxes that black out by themselves. Restart the box once after updating.
- The pause screen, 5 s into a pause: the picture, the logo or title, the plot, the clock with when it ends, and the cast (Kodi's dimming kept away; Settings › Playback).
- The now-playing line over the title in the player: "4K · Dolby Vision · Dolby Atmos · English 5.1".

**Calendar**
- New, at the top of Home: the months from this one on as tiles in their own colours, with the year's last two digits in the big numbers; Left / Right past the ends goes a year on or back.
- A day holds what comes out then - your series' episodes and your films (Trakt's calendar when connected), then TMDB's most popular - and after them what you finished that day here, on Nuvio, Trakt and Simkl, each title once. Every day is asked anew.
- Its row at the foot of the screen with the date in the big numbers, Home's posters, and the logo, year and plot of the title under the cursor above them; Up / Down go a day back or on. It opens at once on today: the day is asked while the cursor stands on Calendar.
- The magnifier finds when a title comes out or came out and when you watched it. Options: the titles under the cards and the day's title, the Calendar's own.

**Library**
- One Library for everything you track: a tile for each service (MegaNexus, Trakt, Simkl, MDBList, WeTrakr, AniList, MyAnimeList) with how many titles it holds in the big numbers, each one's sections in place. It opens on the service you left it on.
- Its rows at the foot of the screen, one at a time - Down goes on to the next and from the last round to the first - with the logo, year and plot of the title under the cursor above them.
- The top bar: the magnifier (it searches the Library), Home, Library, Options (Sort, Show, the titles under the cards, the rows' titles), Settings and HUB. Back goes up to Home there.
- Browse all has a picture of its own, here and on Home.

**Home**
- Top 10 rows: any list - trending, popular, most watched, anticipated, a genre - from TMDB, Trakt, Simkl or MDBList, the big numbers in the poster's colour or one colour for all (Big numbers · colour).
- The magnifier before Home in the top bar, Calendar where Search was. On every screen the magnifier searches that screen, the bar stays while the cursor is on it, and each screen has its own name in it.
- Row titles off hides every row's title.

**AniList and MyAnimeList**
- Sign in on the phone page (HUB Settings › Accounts & tracking shows its QR code); an anime episode watched to its end is counted on your lists (the right part of a season, never lowered); their lists are in the Library, their marks on the posters.

**Title pages and menus**
- A long press says what it is about - Episode, Movie, Series or Anime options - with Choose stream manually first; a season's only option is Mark watched.
- An actor's page with who they are (born, died, where, biography), quick to open.
- The ratings of a series' episodes as a heatmap.

**Everywhere**
- The on-screen keyboard goes where the eye goes: a move onto a key the layout hides no longer jumps a row.
- HUB Settings in the order things are set up; Home & library on one page; the whole look in Themes, colours & screensaver.

**Diagnostics**
- Dolby Vision on LibreELEC's x86 builds with Dolby Vision output: FEL or MEL is read from the stream's own RPU, and whether Dolby Vision goes to the TV from what the build reports - it said "no Dolby Vision output" there.

## 9.1.0

Dolby Vision in the right colours after a trailer, every title page opens, a quieter Stremio sync.

**Playback**
- A Dolby Vision or HDR film or episode started after a trailer or a preview could play in the wrong colours, and the TV's refresh-rate switch stayed off afterwards: the setting MegaNexus pauses for small videos was lost when an account sync saved the add-on's settings at the same moment. It is never lost now - it is kept in Kodi's memory as well, and the sync no longer saves an old copy of the settings. If your "Adjust display refresh rate" is off since 9.0.x without you switching it off, switch it on once more.

**Title pages**
- A film or series whose card carries a TMDB id (search, catalogs of some add-ons) had no Play - only "Retry details" - when your metadata add-on answers with the same title under its IMDb id and you have no TMDb key (Power Rangers, 2017). It opens now: the answer counts when its name and kind are the card's, and both ids are kept, so the sources are found too. Another title is still refused (GitHub #36).

**Accounts**
- The Stremio account import leaves out Stremio's own Local Files add-on - it belongs to the computer Stremio runs on, and with it disabled in Stremio Server every sync reported it unavailable (GitHub #33).

## 9.0.9

Continue Watching like the Nuvio apps, your collections as poster rows, YouTube that keeps playing.

**Continue Watching**
- An episode started after the one before it was watched is there - also one started on another device for a few seconds, or one stopped half way right after the previous one ended (they disappeared).
- One order for every card, newest first, as in the Nuvio apps: a show's next episode stands where you watched the show, one out since then at its own day. The next episodes no longer wait at the end of the row; the film you just stopped stays first.
- The next episodes of the days ahead: the season's next one on its day ("Saturday", "20 Nov"), a new season's first within a week. One already out comes before tomorrow's.
- Up to 100 titles of the whole period you chose - it stopped at 50, and showed fewer once its rules had left some out.

**Home rows**
- Show as: each row of your collections as cards (as before) or as poster rows - each collection its own row of posters right on Home, its Movies and Series as two when it has both. HUB Settings › Collections & Home rows › Home rows, or the phone page (Collections).
- Move up / Move down on the TV too. Each row says what it is (Cards, Poster rows, Hidden) and opens its own page - it looked like an On/Off switch.

**YouTube**
- Steady playback for everyone: the YouTube add-on's own quality (up to 1080p, live too) - MPEG-DASH stopped after a minute or a seek on many devices. 4K (DASH) only when you choose it, never on Amlogic boxes; the YouTube add-on's setup wizard no longer switches DASH back on.
- The region and language set in the YouTube add-on count - the row from your region in its language.

**Playback**
- No "Playback failed" box while the next source is tried - only when none of them plays.
- An episode resumed after a source that did not open no longer starts without sound.

**Watchlist and Next episodes**
- Every card has its description.

**Music**
- The picture at the top of an album or artist page has its rounded corners - its mask was missing.

## 9.0.8

No more freezes, Home rows from your tracking, YouTube for your region.

**Freezes and the player**
- Kodi updating MegaNexus from its repository while MegaNexus was open could make the whole box stand still - fixed: nothing in MegaNexus waits on Kodi's main thread any more (stopping or pausing a film, a channel or a song, closing a window, a skin switch, installing an add-on), and the service stops at once when Kodi asks.
- Leaving a film right after Autosync or AI subtitles: nothing of the subtitles touches the player any more while it closes (wrong colours after a Dolby Vision film).
- Leaving a film waits until it is really closed, so its place is saved before the title page reads it.
- Smaller memory use: the intro-skip data of the last 8 shows only.

**Home rows: Watchlist and Next episodes**
- Two new rows, off until you switch them on (HUB Settings › Collections & Home rows › Home rows, or the phone page): your Watchlist and Next episodes - the next episode of every show you watch, also when a new season comes out.
- Each row takes its titles from the service you choose: Trakt, Simkl, MDBList, WeTrakr or all of them (Watchlist); Trakt's Up Next, Simkl or your MegaNexus history (Next episodes). Switched on, a row comes right under Continue Watching and can be moved like the others.
- A show marked watched to the end on any service is not offered again; a show Continue Watching already shows is never there twice.

**Tracking**
- Trakt: the whole watchlist (only its first page came); a film paused in its first minute no longer gets a 422.
- Simkl: an unknown title no longer holds back everything after it; other services' watched marks are no longer written as Simkl's.
- Next episodes in Continue Watching are asked for all shows at once (faster), and a kept episode list is not written again when nothing changed.
- Anime episodes from Nuvio stay episodes (they came back as films).

**Music**
- A film, an episode, an IPTV channel or Live Sport ends the music (a trailer or a YouTube video still pauses it).
- Back on the app's Home goes to its HUB button - what plays goes on; OK on HUB leaves the app.
- The album page no longer blinks when a song starts; an IPTV channel is never taken for a song; the small player's lines never lie over each other.
- Help › Music: Deezer through your own account (Ultra MAX, your ARL), step by step.

**YouTube**
- A row from your region (From Croatia, From Germany...) - its news, music, trailers and more in your language, in turn.
- The other rows as on YouTube, mostly English, this month and ranked for your region - without another region's videos (another script, another country's or language's channels), unless that is your region. No Football row (Sports is there); Cars are car reviews.
- Settings › YouTube › Rows on Home: which rows show. Back on Home goes to the HUB button, the video plays on.

**Backup**
- A backup holds the Music and YouTube apps too (sources, saved songs, artists, playlists, folders, channels) and your own collections kept aside; a music source's link (its ARL or key) only in a full backup.

## 9.0.7

Fixes for Amlogic devices and AFR on YouTube.

**Amlogic devices (Fire TV Cube, CoreELEC)**
- No more freezes or restarts while YouTube songs play: songs come as one whole stream (Settings › YouTube › Steady playback).
- No stall between two songs; a song that cannot play is passed at once.
- The screensaver comes over the music, and stays when the next song starts; the song's video no longer shows through the screens.
- An album's songs sit in their pill (bigger rows).

**AFR**
- The TV no longer switches its refresh rate for the YouTube app's videos, trailers or songs.

**Music**
- The song you choose is the one that plays - one that cannot play says so, it never plays another in its place.
- YouTube: a label's own upload (YouTube-verified) plays too; never a lyric video, a live, remix or sped-up version in place of the song; 4K uploads are left out (their sound did not come).
- First start: choose the artists you follow by part of the world (US, World, Europe, Asia, Balkan), every genre.
- When the queue ends the music goes on with the artist's songs or similar ones; a playlist goes round.

## 9.0.6

Apps on the HUB - YouTube and Music; a new HUB; every add-on used.

**The HUB**
- New tiles: MegaNexus, Channels (IPTV's new name), Live Sport, HUB Settings, Kodi Settings and Power - dark tiles, each with its icon and its words together in its middle, in your theme's colours (the second word, the icon and a soft glow at the foot in the accent); the focused tile lights up and grows. They follow the posters' transparency, as every screen does.
- The apps below them peek from the bottom of the screen; Down lifts the HUB away and the apps rise - YouTube, Music, and Plex, Jellyfin and Emby, which come later. The row stands still, only the cursor goes from app to app; the focused app lights up and grows.

**Music**
- A whole music app on MegaNexus' own Home: Recently played, Your playlists, For you, Your artists, New from your artists, Artists like yours and the charts, in square cards (artists in circles). The first time it asks which artists you follow, by genre - each profile its own, nobody else sees your songs.
- Library (your saved songs, albums, artists and playlists), Search, an artist's albums, singles & EPs, popular songs and fans also like, an album's or a playlist's page.
- The songs play from your sources (Eclipse music add-ons - you add their links, MegaNexus never runs their code and skips encrypted ones), your debrid cloud (the music in your TorBox or Real-Debrid) and, last, YouTube - only the artist's own channel with the same title and length, never an almost-the-same song. The order is yours (Settings › Music › Songs play from).
- Catalogues: Deezer, Apple Music, or Spotify with your own Spotify app. Playlists brought in from Spotify, Deezer and YouTube links, CSV (Exportify, TuneMyMusic, Soundiiz) and M3U files show on the app's Home.
- The music never stops: songs like the last one follow when the queue ends; one song fades into the next, the next started a moment early. Shuffle and Repeat.
- It plays on through all of MegaNexus and under the screensaver. A film, a trailer or a YouTube video pauses it and keeps its place: Play goes on from the same second.
- While a song plays its icon stands by your profile, a ring filling as it goes: Right from any screen's top bar (Up from the HUB's tiles) and OK opens the small player - Previous, Play / Pause, Next, Shuffle, Repeat, a bar to seek and Stop. Now playing shows the song's picture over the whole screen; "Playing from" says where the song comes from.
- Settings › Music and the phone page's Apps tab: sources, playlists, artists you follow, YouTube, your cloud, the order, catalogues, your Deezer profile and music folders.

**YouTube**
- YouTube in MegaNexus' own screen: categories in rows (live, music, gaming, sports, news, trailers, podcasts, football and more), Search, and your channels in circles at the bottom of Home. A card's options open, add or remove its channel.
- OK plays a video small at the top - its title, channel, LIVE, length, views and age beside it - and it plays on while you browse; OK again (or the round play by HUB) opens Kodi's player with Up next, Previous / Next and Autoplay.
- Videos play through Kodi's YouTube add-on, installed and set up before the app opens the first time. Nothing of YouTube is kept once the app closes, except your channels.
- Known: without a sign-in YouTube can send a stream whose sound starts a few seconds after the picture and which stops on a long seek - Kodi's YouTube add-on 7.4.4 and YouTube, not MegaNexus.

**Collections and add-ons**
- Choose what Home shows - your collections, the MegaNexus Catalog or one add-on's catalogs - on the phone (Collections › Home shows) or HUB Settings › Collections & Home rows › Home shows; then show, hide and order its rows and cards as before. Your own collections are kept aside and come back as they were. An add-on that asks a genre on every catalog (AIOMetadata) can be chosen too.
- Every add-on that offers metadata or catalogs is used: search, Browse all, trailers, More like this and Next episode no longer ask one add-on by name (BingeCat's lists and its AI search beside AIOMetadata). A newly added add-on is switched on at once for what it offers.

**Fixes**
- A show saved under two ids (IMDb, TMDB, TVDB) is one show: removed from Continue Watching it stays removed under both, one Next episode card, no stale card at the start (GitHub #31).
- Your Home layout is no longer replaced by an automatic one after going back to the HUB or a restart (GitHub #32).
- Remove from Continue Watching takes the card away at once.
- An IPTV channel no longer shows the music icon by the profile.
- The quick setup's collections follow its add-on when it had to be made again.

## 9.0.5

One Library, AI subtitles you can trust, quicker everywhere.

**One Library**
- Every saved title once - on this device, in the Nuvio account, on Trakt, Simkl, MDBList and WeTrakr - with the marks of every place it is in. The Local, Tracking services and Calendar tabs are gone: Local held only this device's titles (6 of a library of 70), and the Calendar's months never showed in the poster views.
- One row at the top: the places, each with how many titles it holds - choose one to see only its titles (the chosen one in white, the others dimmed) - then the filter (an icon: All, Movies, Series, Anime; in the accent colour while one is on), the order (an icon: recently added, A-Z, year) and the gear. Nothing wears a pill until the cursor is on it, as on Home, and the places stand evenly apart (the numbers' different widths spaced them unevenly). It always opens on everything, and the cards start right under the row.
- Anime: a title kept by an anime id, or in the public anime list MegaNexus keeps (Fribb's) by its IMDb or TMDB id.
- All six marks fit on a poster (WeTrakr, the sixth, did not), and the wide cards carry them too.
- The day a title was added is on its card ("31 Oct"); in the list, in the line beside the picture.
- Back from a film or a title page the Library no longer flashes and the cursor stays on its title: nothing is drawn again unless something changed, and then only what changed, in place.
- The pill of a place goes with the cursor - it stayed behind the chosen place when the cursor went on along the row or down to the cards.
- A saved title carries its marks at once: the Nuvio account it goes to at the next sync, and every tracking service the save reached. A title the account keeps by its TMDB id and this device by its IMDb id is one card.
- This device's files and the media servers are no longer in the Library - they have their own rows on Home.
- The Nuvio account's library sync no longer saves a title twice: a title kept here by its IMDb id and in the account by its TMDB id was taken for two titles, sent to the account again and pulled back (one account held 18 titles twice - Nuvio counted 71, the Library 53).

**AI subtitles**
- **The video's own track first:** the AI button turns on the video's own subtitle in your language whenever it has one (text or pictures), and translates only when it has none. The video's header now says which tracks are its own - Kodi's list took the translation itself for the video's Croatian track.
- **Every line on its own time:** Gemini sometimes slipped one or two lines in an answer, so a line's words came while someone else spoke - out of step, back in step, out again. Every answer is now checked line by line (names, numbers, the music note); one that slipped is asked again in smaller parts, and a line that keeps slipping is asked alone. Letters of a script the translation does not use (three Chinese characters in a Croatian line) are asked again too.
- **The whole film in your language:** no line is left in the original language. A line Gemini keeps getting wrong is asked alone, up to three times with your keys in turn; only when Gemini cannot be reached or its day is used up is the translation kept unfinished, and the next press makes it whole.
- **No sound descriptions:** [Thunder crashing], [Sighs] and the like are left out of every translation; a line that was only that goes, every other line keeps its own time.
- **The whole film:** the video's own subtitles are read to the last line, however slow its server (90 seconds read The Cycle only to 1:33 of 1:52, and nothing said so). A read that still stops short is used, but never kept as finished.
- Translations made before are made again once - they may carry slipped lines.

**Search**
- The add-ons' results show the moment they answer; the pictures chosen in Artwork (TMDB, fanart) follow into the same cards. They were fetched for every result first - on the PC "batman" answered in 1.6 s and showed at 5.7 s.

**Subtitles**
- Hebrew subtitles no longer come garbled ("שלום" was "ùìåí"), nor Arabic, Persian or Urdu ones: their Windows code pages (CP1255, CP1256) were missing from the ones a subtitle in a known language is read in, so such a file was read as Western European. Thanks for the report (#30).

**Out of the film and back**
- The player's Home button leaves the film playing behind MegaNexus, and it stays playing: the mark that it waits there went at the first moment Kodi did not say what played (its windows changing as the player was left), and the film was stopped.
- Now playing at the top of Home takes you back into the film, playing. It asked for Kodi's player while Home was still open, and Kodi refused ("there are active modal dialogs") - Home came straight back. MegaNexus' screens close first now.

**Next episode only at the end**
- Next episode no longer comes at the start of an episode whose file names its chapters wrongly (Marianne: one chapter, "End Credits", for the whole episode). A chapter called Credits counts only when the file has more than one chapter, it is not the first, and it lies in the last ten minutes or the last fifth of the video; an Intro chapter only in the first half.

**Quicker on slower boxes**
- The top row (Home, Search, Settings, HUB) comes the moment the cursor reaches it: the skin shows it by itself. It waited for MegaNexus to say so, which on a Fire TV Cube could take a second or two while later rows or Continue Watching were being worked on.
- A collection's screen opens quicker: a new screen is no longer told what it already is - rows it does not show and where a poster row already stands - each such call waited for Kodi's drawing on the Cube (about half a second of every collection's opening).

## 9.0.4

Know what you are watching.

**In the player**
- As a film or an episode starts, a box of the theme shows for six seconds the mode the display is in (Dolby Vision, HDR or SDR) with the age rating and IMDb's parents guide: sex & nudity, violence, language, alcohol & drugs, frightening scenes. On or off in Settings → Playback.
- Info works in every player: the Info key, or the Info button, opens our player with a panel from the bottom - the title's logo where the player shows it and the plot (a channel's or a stream's description when there is one). It goes by itself after ten seconds. Kodi's own info no longer opens.
- The player's Subtitles button names the subtitle on screen in full.
- IPTV: switching channels in the player no longer lays Kodi's channel banner over the picture.
- IPTV: the channel list no longer stays over the full-screen picture after a switch in the player.

**Home goes round**
- A view with more rows than Home holds (12) no longer turns a page at its 12th row (every row drawn again, the cursor back on the first): Down and Up go on through all of them, one row sliding in after the other. A row not ready yet comes empty and fills as you stay - holding Down goes straight on. Up to 12 rows Home is as before.
- A row that comes round before its titles holds empty cards at once, so held Down passes it instead of stopping there (Kodi cannot put the cursor on an empty list); its titles then take those cards where they stand.
- "Browse all" off: Right through a row that goes on by itself never stops at its end - empty cards wait there while the next titles load and take them where they stand.

**MegaNexus Catalog in place of Cinemeta**
- The built-in metadata add-on is now the MegaNexus Catalog Addon (Nuvio's TMDB catalogs): titles, plots and catalogs in your language and region - English (United States) at first; Settings › Metadata add-ons › MegaNexus Catalog · language & region, or on the phone under the add-on.
- An installed Cinemeta becomes it, with the same switch; Cinemeta's automatic Home becomes its catalogs, as poster rows. It switches itself on only while no other metadata add-on is there.
- Brought in again by a Nuvio import (any language) it stays one add-on, and Settings show the language it came with.
- A row your region leaves empty comes in English: the catalog answers nothing for Prime Video Movies / Series in some regions (Croatia among them). Only once that is proven - the catalog answered, asked again it was still empty, and the English one has titles; a slow or lost connection never moves a row. Checked again after a week.
- Collections & Home rows starts with "Home shows": your collections or the MegaNexus Catalog's, "automatic" when MegaNexus chose it because you have none of your own (it was "Default collections", halfway down the page).

**Setup and help**
- Quick setup · Free streams on the phone page: MegaNexus with PenguPlay - titles and catalogs from the MegaNexus Catalog (TMDB), streams from PenguPlay, no debrid service (PenguPlay asks you to sign in on its page; paste the link it makes). The debrid quick setup stays the main one; both are public services, added beside your own add-ons.
- The user guide follows HUB Settings, explains metadata, catalogs and collections in one place, and answers what the reports asked (Kodi's audio sync, refresh rate and HDR settings, removing a title from the Library, signing in to Nuvio again).

**Sport and IPTV**
- Sport: under the section's name, the event and when it starts in Kodi's own time; times without a zone stay as the add-on wrote them.
- Sport: no second LIVE badge over posters that carry their own.
- Sport: a notice "stream" (a status page) is never played; switching in the player no longer drops back to the HUB.
- IPTV: "OK · Full screen", as in Sport.

**Fixes**
- Kodi could stand still for good on waking from the screensaver: a background worker the screensaver had started kept it from ending, Kodi stopped it by force and locked up. The screensaver now ends its workers the way every MegaNexus screen does.
- The installer puts in only the components of its own version - left-over packages of an older version are never installed over newer ones.
- Posters: a rating poster your add-on gives (BetterPosters, RPDB, ERDB, Top Posters... - Xperience's poster choice) is the poster again. A hidden setting replaced every add-on's poster with MetaHub's plain English one - also a poster in your language - and a new title MetaHub does not have stayed empty. The plain poster now comes in only while the rating poster's service does not answer.
- Library: titles on WeTrakr show in the Library with its mark, and WeTrakr has its count at the top. The Library's copy of the services' lists pulled Trakt, Simkl and MDBList only - a title saved to WeTrakr reached it, but the Library never showed it there.
- Library: WeTrakr's mark is its own yellow "we", not a purple W; at the top the sixth place (WeTrakr, after MDBList) shows with its count - the screen filled five of the six - and the row sits closer to the word Library.
- Posters: an add-on's own picture is never sent through Plex's picture resizer (PenguPlay's sport posters asked a Plex address that is not there and stayed empty); a picture address with /thumb/ or /art/ is no longer taken for a Plex one.

## 9.0.3

- Amlogic boxes: after a Dolby Vision or HDR film or episode every colour of the interface stays right. 9.0.2 kept the film's last frame on the video layer, and the box stayed in that film's colour processing; the frame is now kept only while a trailer, Sport or IPTV preview plays.

## 9.0.2

Smooth and steady: nothing moves under the remote, nothing flashes.

**No flashes**
- Fire TV Cube and other Amlogic boxes (CoreELEC, LibreELEC): the whole picture no longer flashes when a trailer, a Sport or an IPTV preview stops or switches. The box's video driver blacked its video layer out on every stop; while a small video plays it now keeps the last frame, under the interface. Films and episodes black out as before.
- A trailer in the corner is hidden the moment the cursor moves on; it played on for up to a second under the next card.
- Kodi's "Adjust display refresh rate" comes back only once a small video is really gone (it came back halfway through the stop).
- Opening MegaNexus goes straight from the HUB's picture to the opening screen, without the bare wallpaper in between.
- Collections open whole: no empty page, no rows one at a time, the cursor already on its card.

**The cursor stays where you are**
- Continue Watching filling up after a film no longer sends the cursor back to the first card.
- A refresh in the background never moves the cursor, scrolls Home or plays the slide-in again (Kodi showing Home again after a film, the posters wall arriving).

**Fixes**
- A half-watched episode keeps its place: it no longer turns into "Next episode" from the start when the episode before it carries a newer date (GitHub #28).
- Windows with HDR: SDR trailers no longer switch the display to SDR and back (GitHub #29). Other systems are never touched.
- The video wallpaper is removed (settings, screens and code); pictures and slideshows stay.

## 9.0.1

Tracking made right: every service holds the same watch history, each in its own way.

**Same watch history everywhere** (HUB Settings > Accounts & tracking)
- Trakt, Simkl, MDBList and WeTrakr are compared with MegaNexus's own history; each one gets only what it is missing, with the date it was really watched. Nothing is removed and nothing is counted twice; you see what goes where and confirm first.
- Trakt's pauses are kept the same as here: one a later end made old is removed, a real one it lacks is sent (one per series).
- Nuvio and Stremio: a title finished since no longer shows as under way in their Continue Watching.
- Works with any one service too - only MDBList, only Nuvio, only Stremio.
- Anime is numbered the same everywhere: Simkl's episodes (Dragon Ball Z 1-291) are put on their TVDB places (S1-S9).

**Continue Watching**
- A finished title comes back only when it is really watched again (5 minutes, or 3 % where only a share is known); a pause and the end within 12 hours are one viewing.
- Imports keep the real date of a watch, never the time of the import; marks an earlier import had dated itself get their real date back.
- A resume of a few seconds from another app never replaces the end of a title.

**Trakt**
- Every page of the watched lists is read (Trakt pages them since 2026: only the first 100 films and shows were seen), and episodes come from the history.
- The sign-in no longer ends by itself: renewals are taken one at a time, as Trakt's single-use refresh tokens need. A backup restored on another device leaves Trakt for that device to sign in to.
- A film or episode finished while Trakt is signed out is sent with its real time after the next sign-in.
- The resume time uses the file's real length.

**WeTrakr**
- MegaNexus's own WeTrakr app is built in: just Connect and enter the code - no own app needed. The sign-in now finishes by itself on the TV and the phone.
- Now playing, pause and stop are reported while you watch (a resume or a seek moves the place), and an end marks the episode watched.

**Accounts**
- A service that is really signed out says so once, as a Kodi notification - never over a film.
- Backup on the phone: with everything, or without sign-ins.

**Also**
- The subtitle list opens at once and fills while the add-ons answer: add-ons on top, languages by full name on the right, yours first; the film waits while you choose.
- Trailers start at once from the title page and Back goes straight back; Home never stands still while one starts.
- A new Artwork choice is carried out at once behind the loading screen, one picture per title; the screensaver removes pictures not shown for a week, every week.
- Faster posters: a device that kept the old picture path is asked once to switch to vfs.meganexus.

## 9.0.0 Nightly-Stable

The nightly line made stable: everything since 8.0, tested on Android TV, Fire TV,
CoreELEC and PC, in one release.

**Watching**
- Home with Continue Watching, collections and catalog rows, trailers that fade in, and the title under the cursor in big.
- Title pages with ratings, seasons, episodes, cast and *More like this*; search across all metadata add-ons; Library and Calendar.
- Native posters (VFS): pictures through vfs.meganexus (C++), no port and no Python - recommended for everyone (Settings > Performance & image cache > Picture path). A device that kept the old path is asked once whether to switch.
- Trailers start at once from the title page, and leaving one goes straight back to the page - no empty picture in between; a trailer starting on Home no longer holds Home for a moment.
- A new Artwork choice (posters, backgrounds, logos) is carried out at once behind the loading screen: one picture per title, the old ones removed from Kodi's cache. Every week the screensaver removes the pictures not shown for a week.

**Streams**
- Every Stremio and Nuvio add-on by its link; TorBox, Premiumize, Offcloud and Easynews built in.
- Fast source search, stream badges, automatic best-stream choice; a source that does not start is skipped quietly and the next one tried - one message only when none plays.
- Native C++ Usenet player (vfs.meganexus) with your provider and Newznab indexers.

**Subtitles**
- One button searches every subtitle add-on, with the file's hash (OpenSubtitles marks the ones made for exactly your file).
- Autosync lines a subtitle up with the video's own subtitles; a subtitle from online is checked once in the background.
- AI subtitles in your language (Google Gemini, one or two keys): read from the video's own subtitles, shown while they translate, kept for next time.
- Long anime found by their absolute episode number too.
- The subtitle list opens at once and fills while the add-ons answer, like the source list: add-ons on top, languages by their full name on the right, your language first, and where each subtitle comes from. The film waits while you choose.

**Playback**
- Skip intro / recap / outro only with trusted times (TheIntroDB, SkipDB), shown as a pill that empties while the part runs; Next episode card at the right moment (TVmaze as a backup); the next episode loads straight over the film, and leaving asks nothing - it comes back where it started.
- Resume without a sound burst; a stream that breaks off is kept where it stopped, not marked watched.
- Entering and leaving a film never shows the HUB picture; Back stops the film at once; a TV mode switch (subtitles, HDR) never stops it by itself.
- Sport: a stream that does not answer gives way to the next at once; the streams come as soon as one add-on has them.

**Your progress everywhere**
- Nuvio, Stremio, Trakt, Simkl, MDBList and WeTrakr; Nuvio and Stremio sign in again by themselves when their session ends.
- Trakt stays signed in: its single-use renewals are taken one at a time, and a backup restored on another device leaves Trakt for that device to sign in to.
- An account that is signed out for good says so once, as a Kodi notification - never over a film.

**More**
- Watch Party, IPTV and Sport, set-up from the phone, profiles, themes and the screensaver.
- Backup with or without sign-ins, passwords and API keys - on the TV and on the phone.
