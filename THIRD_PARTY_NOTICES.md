# Upstream acknowledgements

MegaNexus itself is under the [MegaNexus License](LICENSE.md). These parts keep their own licenses:

- [python-qrcode](https://github.com/lincolnloop/python-qrcode) in `plugin.video.meganexus/resources/lib/qrcode`: BSD license, see its `LICENSE` file.
- Noto Sans (SIL Open Font License): the text of the built-in collection covers, drawn by `review/make_collection_covers.py`.
- Google Sans, Fraunces and Oxanium (SIL Open Font License 1.1, no reserved names): reduced, renamed static instances in `skin.meganexus/fonts/ambient` (`review/make_ambient_fonts.py`), used by the MegaNexus Ambient screensaver widgets and the weather / clock corner of the MegaNexus screens; copyrights in `skin.meganexus/fonts/ambient/OFL.txt`.
- Subtitle flag icons in `skin.meganexus/media/windows/subtitles/flags`: MIT (GoSquared). Home images in `skin.meganexus/extras/home-images`: CC0.
- [Kodi 21.3 Estuary](https://github.com/xbmc/xbmc/tree/21.3-Omega/addons/skin.estuary): the skin foundation, standard dialogs, fonts and OSD. Code and artwork have the licenses described in `skin.meganexus/LICENSE.txt`.

The four component directories contain the detailed notices. Third-party Python code and skin assets retain their individual headers and license files. Do not remove them when redistributing or contributing.

This community project is independent of Nuvio, Kodi/Team Kodi, Simkl and the metadata/stream providers it can connect to. Collection labels identify categories and do not grant subscriptions or playback rights.

## Font handling in 6.0.10

This candidate references the Unicode font installed with Kodi through `special://xbmc/media/Fonts/arial.ttf`; it does not redistribute font binaries. Historic upstream font credits remain as attribution. Actual glyph coverage depends on the installed Kodi build.
