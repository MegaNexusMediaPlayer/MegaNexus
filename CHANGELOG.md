# Changelog

## 9.0.2

Smooth and steady: nothing moves under the remote, nothing flashes.

**No flashes**
- Fire TV Cube and other Amlogic boxes (CoreELEC, LibreELEC): the whole picture no longer flashes when a trailer, a Sport or an IPTV preview stops or switches. The box's video driver blacked its video layer out on every stop; it now keeps the last frame, under the interface.
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
