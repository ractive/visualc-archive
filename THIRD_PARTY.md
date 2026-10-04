# Third-party components

Code in this repository that was not written by Jean-Pierre Bergamin, listed per
project with its author and licence as stated in the bundled files. All of it is
kept with its original headers; nothing was relicensed. Bundled third-party
executables (gifsicle, mt, installers) were removed on import.

## Classes reused across several apps

| Component | Files | Author | Licence | Used in |
|---|---|---|---|---|
| CHyperLink hyperlink control | `HyperLink.cpp/.h` | Chris Maunder, 1997-1998 (CodeProject); hand cursor and parts from Paul DiLascia's Jan 1998 MSJ column | free for any use, notice must stay | LaPlaya (and quicktime-experiment), EMelodyLab, MyIPWinClient |
| CRegBinding registry binding | `RegBinding.cpp/.h` | Joerg Dentler, 1998 | free, author not liable, notice must stay | Bluesson, BlueRC, LaPlaya (and quicktime-experiment), DynPfiff, NTMessenger, MyIPWinClient |
| CTrayIcon system-tray helper | `TrayIcon.cpp/.h` | own wrapper (GPL header) whose core is taken from Paul DiLascia's MSDN "C/C++ Q&A" tray icon code (Microsoft Systems Journal) | MSJ sample code | Bluesson, BlueRC, DynPfiff, FTPSync, NTMessenger, MyIPWinClient |
| Winamp SDK front-end header | `FRONTEND.H` | Nullsoft Inc., 1997-2000 (Justin Frankel) | Winamp SDK, freely redistributable header | Bluesson, BlueRC, WinAmpRCServer |
| CSerial / CProtException serial port classes | `Serial.cpp/.h`, `ProtException.cpp/.h` | Hewlett Packard and Jean-Pierre Bergamin, 2001 (from the HPComm project) | GPL-2.0 | Bluesson, BlueRC |

## Per project

### apps/Bluesson and apps/BlueRC
| Component | Files | Author | Licence |
|---|---|---|---|
| CKeystrokeEngine / CWindowEngine (send keystrokes to another window) | `KeystrokeEngine.cpp/.h`, `WindowEngine.cpp/.h` | Mustafa Demirhan, 2002, macroangel.com (CodeProject "KeyTest") | zlib-style: free use, no misrepresentation, notice must stay |
| CRegBinding, CTrayIcon, FRONTEND.H, CSerial | see above | | |

### apps/HardLinker
| Component | Files | Author | Licence |
|---|---|---|---|
| CtxMenu shell-extension sample (basis of `ShellExt.cpp`, `ShellExtReg.cpp`, `ShellCtxMenu.cpp`) | derived code, credited in the headers | Smaller Animals Software, 1999 | free sample code, credit must stay |
| Filelink: hard-link creation on Windows NT 4 | `Filelink.cpp/.h` | Armin Gerritsen (armin.gerritsen@philips.com) | contributed to HardLinker; no separate licence stated, distributed with HardLinker under its licence |

The author's own HardLinker sources carry LGPL-2.1 headers while the bundled
`license.txt` and `ReadMe.txt` point to the GNU GPL/LGPL.

### apps/Hexer
| Component | Files | Author | Licence |
|---|---|---|---|
| CColorBtn colour picker button | `colorbtn.cpp/.h` | Bob Ryan, 1998 (ryan@cyberzone.net) | free use, author accepts no liability, notice must stay |

### apps/MonteCarlo
| Component | Files | Author | Licence |
|---|---|---|---|
| CMarkup XML class | `Markup.cpp/.h` | First Objective Software, Inc. (Ben Bryant), 1999-2001 | First Objective Software licence (free use of the class in applications) |
| Pug XML parser | `pugxml.h` | Kristen Wegner, 2003 | MIT-style |
| XMLite XML parser | `XMLite.cpp/.h` | Cho, Kyung-Min ("bro"), 2002 (CodeProject) | free, as published on CodeProject |
| ExpatImpl C++ wrapper for Expat | `ExpatImpl.h` | Descartes Systems Sciences, Inc., 1994-2002 (Tim Smith) | free use with notice; Expat itself (not bundled) is MIT |

### apps/GifT68
| Component | Files | Author | Licence |
|---|---|---|---|
| CPicture image loading class | `Picture.cpp/.h` | Dr. Yovav Gad, SuperMain.com, 2001 | "Copyfree": free use |
| gifsicle and mt executables | removed on import | Eddie Kohler (gifsicle, GPL) | the dialog version shells out to them; not included |

### apps/RCServer
| Component | Files | Author | Licence |
|---|---|---|---|
| Windows Media Player SDK headers and plug-in wizard output | `wmp.h`, `wmpplug.h`, `CPropertyDialog.h` | Microsoft Corporation | Windows Media Player SDK terms (redistributable with plug-in source) |

### apps/mRouterControl
| Component | Files | Author | Licence |
|---|---|---|---|
| tlist/kill process enumeration sample | `common.h` (the matching `common.c` is an empty file in the original tree) | Microsoft Corporation, 1994-1998, Microsoft Source Code Samples | Microsoft sample code licence |

### apps/NetConfigurator
| Component | Files | Author | Licence |
|---|---|---|---|
| CIPAddressCtrlEx extended IP address control | `IPAddressCtrlEx.cpp/.h` | unattributed in the file; most likely a CodeProject/CodeGuru class | unknown; kept as found |
| `dr_serverhourglass.avi` animation | `res/dr_serverhourglass.avi` | Pete's AVI Collection (pjs-inc.com) | free for use inside applications, standalone redistribution prohibited |

### apps/LaPlaya
| Component | Files | Author | Licence |
|---|---|---|---|
| CHyperLink, CRegBinding | see above | | |
| Windows Media Player 6.4 control wrapper | `mediaplayer2.cpp/.h` | ClassWizard-generated from Microsoft's type library | Microsoft redistributable wrapper code |

### apps/EMelodyLab, apps/MyIPWinClient, apps/DynPfiff, apps/NTMessenger, apps/FTPSync
Only the shared CHyperLink, CRegBinding and CTrayIcon classes listed above.

### experiments/fire-simulation
| Component | Files | Author | Licence |
|---|---|---|---|
| fireLib 1.0.4 wildfire spread library and `fireSim.c` demo | `fireLib/` (complete distribution with `license.txt`, `README`, `firelib.ps`), copies of `fireLib.c/.h` in `FireSim/` and `Simu/` | Collin D. Bevins, Systems for Environmental Management, 1996-1999 | permissive BSD/Tcl-style licence (see `fireLib/license.txt`) |
| NeHe OpenGL lesson 34 height-map code | `Visu/Visu.cpp` | Jeff Molofee (NeHe Productions) and Ben Humphrey | NeHe tutorial terms: free use with credit |
| BSD sockets throughput test code | `cperf/`, `sperf/` | ported from BSD sockets example code | BSD |

### experiments/Landscape
| Component | Files | Author | Licence |
|---|---|---|---|
| NeHe OpenGL lesson 34 (height-map terrain) and `Data/Terrain.raw` | `LandscapeView.cpp`, `Data/Terrain.raw` | Jeff Molofee (NeHe Productions) and Ben Humphrey | NeHe tutorial terms: free use with credit |

### experiments/TestProgressDialog
| Component | Files | Author | Licence |
|---|---|---|---|
| CProgressDlg progress dialog with cancel | `ProgressDlg.cpp/.h` | unattributed; typical CodeGuru class | unknown; kept as found |
| MD5 message digest | `md5-variant/md5.cpp/.h` | RSA Data Security, Inc., 1991-1992; C++ translation by Mordechai T. Abzug, 1995 | RSA MD5 licence (free use with attribution to "RSA Data Security, Inc. MD5 Message-Digest Algorithm") |

### experiments/maptransform
| Component | Files | Author | Licence |
|---|---|---|---|
| HLS/RGB conversion routines | in `maptransform.cpp` | Microsoft Knowledge Base sample | Microsoft sample code |

### experiments/WMP
| Component | Files | Author | Licence |
|---|---|---|---|
| Windows Media Player 9 control wrappers | `wmp*.cpp/.h` | ClassWizard-generated from Microsoft's type library | Microsoft redistributable wrapper code |

### tools/
No third-party code. `BinaryTree` expects Boost (not bundled).
