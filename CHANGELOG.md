# Changelog

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
