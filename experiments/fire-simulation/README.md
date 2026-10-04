# Fire simulation experiments (2002-2004)

A family of small projects around a wildfire spread simulation that streams its grid
over TCP to visualisers:

- `fireLib/`: Collin D. Bevins' fireLib 1.0.4 (Rothermel fire spread model) as
  distributed, with its permissive `license.txt`, `README` and documentation.
- `FireSim/`: Bevins' `fireSim.c` demo wrapped in a VC6 console project.
- `Simu/`: MFC doc/view visualiser that receives "MAP" grid data from the simulator
  over a socket or via files in `C:\IPC` and includes its own copy of fireLib.
- `Visu/`: Win32/OpenGL client based on NeHe lesson 34 that renders received fire-map
  data as a coloured height map; the server address is a `#define` in `Visu.cpp`.
- `VisuSquare/`: MFC doc/view version of Visu drawing the grid as coloured squares.
- `TCPServer/`, `TCPClient/`, `TCPServerEx/`: MFC `CSocket` test programs
  (receive server on port 1500, client sending random 2^n byte packets with MB/s
  statistics, dialog server with listen/stop).
- `cperf/`, `sperf/`: BSD-sockets style TCP throughput tester, client and server
  (`cperf ip port MB bs buf [-d]`, `sperf ip port br buf [-d]`).

Own code states no licence and falls under the repository licence; fireLib and the
NeHe code keep their own terms (see `THIRD_PARTY.md`).
