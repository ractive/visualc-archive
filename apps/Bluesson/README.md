# Bluesson 0.9

Use an Ericsson T68 (or other Ericsson phone with Bluetooth and the accessory menu
protocol, AT\*EAID) as a remote control for Winamp. Bluesson talks to the phone over
the Bluetooth serial port, builds menus on the phone and maps the choices to Winamp
commands (play, pause, stop, next, previous, volume, playlist) sent through the Winamp
IPC API (`FRONTEND.H`). It sits in the system tray. Released under the GPL on
<http://www.ractive.ch/t68>. The `hlp/` folder holds the WinHelp source; the compiled
`.hlp` is not included. The first commit is the November 2002 published snapshot
(`Bluesson.zip`), the second the later working copy.

Third-party classes: Mustafa Demirhan's keystroke engine, Joerg Dentler's CRegBinding,
Paul DiLascia's tray icon code (see `THIRD_PARTY.md`).
