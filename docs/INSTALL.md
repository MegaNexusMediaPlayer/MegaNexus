# Install and set up MegaNexus

MegaNexus runs on Kodi 21 (Omega) and Kodi 22 (Piers): Android TV, Fire TV, CoreELEC / LibreELEC,
Windows, Linux and macOS.

## Install from the MegaNexus repository (recommended)

1. Kodi **Settings → File manager → Add source**: enter
   `https://meganexusmediaplayer.github.io/MegaNexus/` and name it `MegaNexus`.
2. **Add-ons → Install from zip file → MegaNexus → repository.meganexus-<version>.zip**.
3. **Add-ons → Install from repository → MegaNexus Repository → Video add-ons → MegaNexus Hub → Install.**

The interface (MegaNexus), MegaNexus Skin and MegaNexus Screensaver install themselves a few
seconds later. Kodi asks once to switch to the MegaNexus skin; answer **Yes**.

## Install from the zip

Download `MegaNexus-Complete-<version>.zip` from the
[releases](https://github.com/MegaNexusMediaPlayer/MegaNexus/releases/latest) (not the "Source
code" archive) and install it with **Add-ons → Install from zip file**. Updates then arrive by
themselves (HUB Settings → Backup & updates).

## First setup

Everything is optional: with nothing set up, MegaNexus starts with Cinemeta and a ready-made Home.

* **Set up on phone:** scan the QR code; set up accounts, add-ons, API keys, collections and the look on your phone.
* **Accounts & tracking:** Nuvio, Stremio, Trakt, Simkl, MDBList, WeTrakr, Plex, Jellyfin / Emby.
* **API keys:** TMDB, MDBList, Fanart.tv, TheIntroDB, Gemini (AI subtitles) and the debrid services — all in one place, each with a link to where you get it.
* **Debrid & Usenet:** TorBox, Premiumize, Offcloud, Real-Debrid, AllDebrid, Easynews; your Usenet provider, Newznab indexers, Prowlarr.
* **Collections:** default collections, Home rows, editing each card, import from a Nuvio account or a JSON export.

## Move to another device

* **TV:** HUB Settings → Backup & updates → **Backup** — choose *everything* or *everything except sign-ins, passwords, user names and API keys*; save it to a USB stick, network folder or Downloads.
* **Phone:** Set up on phone → **Backup** → *Download backup · with everything* or *Download backup · without sign-ins*.

On the new device install MegaNexus, then **Restore** (TV) or Backup → Restore (phone). A complete
backup holds your sign-ins — keep it private like a password.

## Troubleshooting

* **Phone page does not open:** phone and TV on the same Wi-Fi; a firewall on the TV device must allow TCP port 8765.
* **Video with sound but no picture (Linux, Intel graphics):** Kodi Settings → Player → Videos → turn off *Allow hardware acceleration – VAAPI*.
* **Slow on an old box:** HUB Settings → Performance & image cache → *Low-end device · RAM 128 MiB*; Help & diagnostics → System check shows add-ons that overload Kodi.
* **Report a problem:** HUB Settings → Help & diagnostics → Report a problem (the log goes with personal data removed), or a [GitHub issue](https://github.com/MegaNexusMediaPlayer/MegaNexus/issues) with device, Kodi version and MegaNexus version.
