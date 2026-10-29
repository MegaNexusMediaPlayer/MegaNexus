# Changelog

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
