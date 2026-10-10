# Install and set up MegaNexus 7

MegaNexus runs on Kodi 21 (Omega) and Kodi 22 (Piers): Android TV, Fire TV,
CoreELEC / LibreELEC, Windows, Linux and macOS.

## Install from the MegaNexus repository (recommended)

1. Kodi **Settings → File manager → Add source**: enter
   `https://meganexusmediaplayer.github.io/MegaNexus/` and name it `MegaNexus`.
2. **Add-ons → Install from zip file → MegaNexus → repository.meganexus-<version>.zip**.
3. **Add-ons → Install from repository → MegaNexus Repository → Video add-ons →
   MegaNexus Hub → Install.**

The interface (MegaNexus), MegaNexus Skin and MegaNexus Screensaver install
themselves a few seconds later. Kodi asks once to switch to the MegaNexus skin;
answer **Yes**.

## Install from the zip

Download `MegaNexus-Complete-<version>.zip` from the
[releases](https://github.com/MegaNexusMediaPlayer/MegaNexus/releases/latest)
(not the "Source code" archive) and install it with **Add-ons → Install from
zip file**. Updates then arrive automatically from GitHub (HUB Settings →
Maintenance & updates).

## Updating from the earlier build

Install the update as usual. MegaNexus 7 then:

1. moves your settings, API keys, sign-ins (Nuvio, Stremio, Trakt, Simkl,
   Plex, Jellyfin), add-ons, collections, Home folders, the local library and
   Continue Watching to the new add-ons;
2. switches to MegaNexus Skin and MegaNexus Screensaver and turns the old
   add-ons off;
3. asks to restart Kodi. After the restart the old add-ons are removed; a
   small copy of the old profile stays in MegaNexus Hub's profile
   (`previous-profile-backup.zip`).

## First setup

Everything is optional: with nothing set up MegaNexus starts with Cinemeta and
a ready-made Home.

* **HUB Settings → Set up on phone:** scan the QR code; set up accounts,
  add-ons, API keys, collections and the look on your phone.
* **Accounts & tracking services:** Nuvio account, Trakt, Simkl, and in beta
  Stremio, Plex and Jellyfin / Emby.
* **Add-ons:** your configured add-on links, metadata and stream add-ons on or
  off, and **API keys** (TMDb, MDBList, Fanart.tv, TheIntroDB) with links to
  where you get them.
* **Collections:** default collections, Home rows, editing each card, import
  from a Nuvio account or a JSON export.

## Move to another device

When MegaNexus is set up the way you like:

* **TV:** HUB Settings → Maintenance → **Back up settings to a file**, choose a
  USB stick, network folder or Downloads.
* **Phone:** Set up on phone → **Backup** → Download backup.

On the new device install MegaNexus, then **Restore settings from a backup**
(TV) or Backup → Restore (phone). Settings, accounts, API keys, add-ons,
collections, Home folders, the local library and Continue Watching come along.
The file holds your sign-ins: keep it private like a password.

## Beta features (off by default)

* **Plex / Jellyfin / Emby:** connect in Accounts; your own copy of a title is
  listed first when you play it. Home rows: Collections → Home rows. Plex
  needs Plex Pass or Remote Watch Pass outside your home network.
* **Stremio:** sign in to import its add-ons and Continue Watching; "Keep in
  sync" exchanges Continue Watching continuously.
* **Local storage:** movies and series on your own drives (Kodi's video
  library), as Home rows.

## Troubleshooting

* **Phone page does not open:** phone and TV on the same Wi-Fi; a firewall on
  the TV device must allow TCP port 8765.
* **Video with sound but no picture (Linux, Intel graphics):** Kodi Settings →
  Player → Videos → turn off *Allow hardware acceleration – VAAPI*.
* **Slow on an old box:** HUB Settings → Performance → choose *Low-end device ·
  RAM 128 MiB*; Maintenance → System check shows add-ons that overload Kodi; a
  clean Kodi install is fastest.
* Report bugs at [GitHub issues](https://github.com/MegaNexusMediaPlayer/MegaNexus/issues)
  with device, Kodi version and MegaNexus version. Remove tokens and private
  links from logs.
