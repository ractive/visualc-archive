# visualc-archive

Source archive of the Windows programs Jean-Pierre "James" Bergamin wrote with
Visual C++ 6 and MFC between 1999 and 2004, plus a handful of Visual Studio 2005
console snippets from 2008 to 2012. Most of the applications were published as
free software on <http://www.ractive.ch/gpl> ("@ractive Software"); the rest are
experiments and test harnesses that never left the author's machine.

Each project was imported as one commit whose author date is the newest source
file in that project, so `git log` reads as a timeline. Where an older released
snapshot (zip) and a newer working copy both survived, the snapshot was committed
first and the working copy on top of it.

## Era and toolchain

Everything under `apps/` and `experiments/` was written in Microsoft Visual C++
6.0 (`.dsp`/`.dsw` project files) against MFC 6 and the Platform SDK of the day,
and built and tested on Windows 2000 and Windows XP. Several apps talk to
hardware or software that no longer exists: Ericsson T68 and Sony Ericsson
phones over Bluetooth serial ports, Winamp 2 and Windows Media Player 9,
the myip.org dynamic DNS service, NT messenger service popups. Installers were
made with NSIS (`.nsi` scripts are kept). Help files were written with the
WinHelp toolchain (`.hpj`/`.rtf`/`.cnt` kept, compiled `.hlp` dropped).
The `tools/` folder holds Visual Studio 2005 (`.sln`/`.vcproj`) console
programs.

## Building

Open the `.dsw` workspace of a project in Visual C++ 6. A modern Visual Studio
can open the `.dsp` files and convert them; expect to fix deprecated MFC and
Platform SDK calls, `_T()` versus plain-string mismatches and the occasional
missing header (DirectX, QuickTime, Winamp SDK). The code is 32-bit, ANSI
(`MBCS`) and was never compiled for x64.

**Binaries and installers are not included.** Build output (`Debug/`,
`Release/`), IDE state (`.ncb`, `.opt`, `.aps`, `.clw`, `.plg`), compiled help
and every `.exe`/`.dll`, including bundled third-party executables, were left
out. See `.gitignore`.

## Projects

Licence column: "GPL-2.0" means the project ships its own copy of the GNU GPL
v2 or states it in the About box or source headers. "none stated" means the
source carries no licence text; those projects are released here under the
repository licence (GPL-2.0, see `LICENSE`). Year is the newest source file.

### apps/

| Project | What it is | Version | Year | Licence | Status |
|---|---|---|---|---|---|
| [LaPlaya](apps/LaPlaya) | Movie player that plays all clips of a folder in a row: Explorer-style tree and list plus the Media Player control. `quicktime-experiment/` is a 1.1 variant trying QuickTime playback. | 1.2 (26 Jun 2001) | 2001 | GPL-2.0 | released on ractive.ch |
| [Bluesson](apps/Bluesson) | Ericsson T68 as Bluetooth remote control for Winamp: the phone's accessory menu (AT\*EAID) drives play, pause, volume and playlist over a serial port. | 0.9 | 2002 | GPL-2.0 | released on ractive.ch/t68 |
| [BlueRC](apps/BlueRC) | Fork of Bluesson for Sony Ericsson phones that controls Windows Media Player by sending keystrokes. About box still says Bluesson 0.9. | 0.9 | 2004 | GPL-2.0 | unreleased fork |
| [HardLinker](apps/HardLinker) | Explorer context-menu shell extension that creates NTFS hard links by right-dragging a file. NT4 support by Armin Gerritsen. | 1.0.0.2 | 2001 | LGPL-2.1 (source headers; bundled `license.txt` is GPL-2.0) | released on ractive.ch |
| [Hexer](apps/Hexer) | Number base converter: unsigned, signed, octal, hex, binary and double, with colour button, drag and drop and always-on-top. | 2.0 (resource says 1.2) | 2001 | GPL-2.0 | released on ractive.ch |
| [EMelodyLab](apps/EMelodyLab) | Ericsson EMelody (EMS) ringtone composer and player; saves and sends melodies over IrDA. | 1.3 (ReadMe says 1.0) | 2002 | GPL-2.0 | released on ractive.ch |
| [MyIPWinClient](apps/MyIPWinClient) | Windows client for the www.myip.org dynamic DNS service: tray icon, account and host management, IP detection and update. | 3.41 (13 Aug 2001) | 2001 | GPL-2.0 | released |
| [FTPSync](apps/FTPSync) | FTP to local directory synchroniser built on `CFtpConnection`, with conflict dialogs and tray icon. | 1.0 | 2002 | GPL-2.0 header in two files, otherwise none stated | unfinished |
| [DynPfiff](apps/DynPfiff) | Dynamic-DNS style IP updater living in the tray: detects local IPs, calls an update URL every N minutes and writes an HTML page from a template. | 1.1 | 2001 | GPL-2.0 | released on ractive.ch |
| [NTMessenger](apps/NTMessenger) | Sends NT messenger service popups (`net send` style) to computers of a domain; scans the domain and PDC, optional extra hosts file. | 1.0 | 2001 | GPL-2.0 (About box) | released |
| [NetConfigurator](apps/NetConfigurator) | Saves and applies named IP configurations (address, mask, gateway, DNS, DHCP) for laptops that move between networks. | 1.0 | 2002 | GPL-2.0 | released on ractive.ch |
| [MonteCarlo](apps/MonteCarlo) | Monte-Carlo estimation of pi with a worker thread and point plotting; a menu compares XML serialisation through CMarkup, Expat, pugxml and XMLite. German UI. | 1.0 | 2003 | none stated | experiment-grade app |
| [ShoppingList](apps/ShoppingList) | Doc/view shopping list (shops, items, "in cart") with serialisation and a stub `CAsyncSocket` for syncing to a phone or PDA. | 1.0 | 2004 | none stated | unfinished |
| [WinAmpRCServer](apps/WinAmpRCServer) | "WinAmpRC": TCP listener that drives Winamp through its IPC API from remote text commands. | 1.0 | 2003 | GPL-2.0 header in `WinAmpControl`, otherwise none stated | experiment |
| [RCServer](apps/RCServer) | ATL Windows Media Player plug-in listening on TCP port 4444 for play, pause, next and volume commands sent from a phone. | - | 2003 | none stated | experiment |
| [GifT68](apps/GifT68) | Converts images to 101x80 Ericsson T68 background GIFs. First commit is the dialog version shelling out to gifsicle, second the doc/view rewrite. | 1.0 | 2002 | none stated | unfinished |
| [GifsicleMT](apps/GifsicleMT) | Console filter quantising RGB triplets from stdin to the T68 palette, feeding gifsicle. | - | 2002 | none stated | tool |
| [TrackerSkin](apps/TrackerSkin) | Experimental editor and viewer for Sony Ericsson P800 "Tracker" skin INI files (IniFile, PropertyList, SkinButton, SkinBitmap classes). | 1.0 | 2003 | none stated | experiment |
| [mRouterControl](apps/mRouterControl) | One-button dialog that kills the Sony Ericsson "mRouter" process, using Microsoft's tlist/kill sample code. | 1.0 | 2003 | none stated | tool |

### experiments/

| Project | What it is | Version | Year | Licence | Status |
|---|---|---|---|---|---|
| [fire-simulation](experiments/fire-simulation) | 2003 experiment family: a wildfire spread simulation (Collin Bevins' fireLib) streaming grid data over TCP to OpenGL and MFC visualisers, plus the socket test programs written for it. Subfolders: `fireLib`, `FireSim`, `Simu`, `Visu`, `VisuSquare`, `TCPServer`, `TCPClient`, `TCPServerEx`, `cperf`, `sperf`. | - | 2002-2004 | own code none stated; fireLib under Bevins' permissive licence | experiment |
| [Landscape](experiments/Landscape) | MFC doc/view port of NeHe OpenGL lesson 34 (height-map terrain from `Data/Terrain.raw`). | 1.0 | 2003 | none stated; NeHe terms for the tutorial code | experiment |
| [maptransform](experiments/maptransform) | Console HLS/RGB transform of a palette map file (Microsoft KB HLS code) for T68 image work. | - | 2002 | none stated | scratch |
| [OpenLogAnalyzer](experiments/OpenLogAnalyzer) | Apache `access_log` parser and timing experiment. | - | 2002 | none stated | scratch |
| [PlayToneX](experiments/PlayToneX) | ActiveX control skeleton that plays a resource wave (EMelody-related). | 1.0 | 2001 | none stated | skeleton |
| [TestProgressDialog](experiments/TestProgressDialog) | Test harness for a cancelable progress dialog; `md5-variant/` adds MD5 hashing of files. | 1.0 | 2001-2006 | none stated; MD5 under the RSA licence | test |
| [WMP](experiments/WMP) | Dialog test embedding the Windows Media Player 9 ActiveX control with ClassWizard-generated wrappers. | 1.0 | 2002 | none stated | test |
| [Test](experiments/Test) | Explorer-style splitter skeleton (`CTreeView` + `CListView`). | 1.0 | 2004 | none stated | skeleton |
| [NFOViewer](experiments/NFOViewer) | MFC doc/view skeleton registered for `.nfo` files, no drawing code yet. | 1.0 | 2001 | none stated | skeleton |

### tools/

| Project | What it is | Version | Year | Licence | Status |
|---|---|---|---|---|---|
| [tail](tools/tail) | `tail #lines file` reading the file backwards in blocks (VS2005). | - | 2012 | none stated | snippet |
| [sleep](tools/sleep) | `sleep ms` (VS2005). | - | 2009 | none stated | snippet |
| [ret](tools/ret) | Returns its first argument as exit code, for batch-file testing (VS2005). | - | 2008 | none stated | snippet |
| [binary_search](tools/binary_search) | Templated STL binary search with asserts (VS2005). | - | 2010 | none stated | snippet |
| [BinaryTree](tools/BinaryTree) | Templated binary tree with `boost::shared_ptr` and pre/in/post-order traversal (VS2005, expects Boost 1.34). | - | 2010 | none stated | snippet |
| [Beep](tools/Beep) | `\a` versus `Beep(440,150)` (VC6). | - | 2001 | none stated | scratch |
| [ctest](tools/ctest) | C string-replace experiments (VC6). | - | 2003 | none stated | scratch |
| [DirList](tools/DirList) | MFC console directory listing with `CFileFind`, hard-coded to `F:\` (VC6). | - | 2003 | none stated | scratch |

## Third-party code

Several projects bundle small third-party classes (hyperlink control, tray
icon, registry binding, keystroke engine, XML parsers and so on) with their
original headers. They are listed per project with author and licence in
[THIRD_PARTY.md](THIRD_PARTY.md). Bundled third-party executables were removed.

## What was changed on import

- Hard-coded test credentials in `apps/FTPSync/AddDlg.cpp` were blanked and
  four serialised test documents containing them were deleted.
- A hard-coded media path in `experiments/WMP/WMPDlg.cpp` was replaced with a
  placeholder.
- The private LAN `hosts` file of NTMessenger was removed.
- Everything else is byte-identical to the author's working copies, line
  endings included (`.gitattributes` disables text conversion).

## Licence

Published originally at <http://www.ractive.ch/gpl>. Unless a project states
otherwise, the code in this repository is licensed under the GNU General Public
License version 2 (see [LICENSE](LICENSE)). Third-party components keep their
own licences.
