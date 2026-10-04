# BlueRC 0.9 (Bluesson fork)

Fork of Bluesson that turns a Sony Ericsson phone into a remote control for Windows
Media Player instead of Winamp. It checks for the "SONY ERICSSON" manufacturer string,
adds a "MediaPlayer RC" accessory menu and drives the player window (class
`WMPlayerApp`) with synthetic keystrokes (F8/F9 and friends) through Mustafa Demirhan's
CKeystrokeEngine. The project files, About box and help still carry the Bluesson name.
The first commit is the 2002 snapshot (`BlueRC.zip`), the second the January 2004
working copy. GPL-2.0, see `LICENSE.TXT`.
