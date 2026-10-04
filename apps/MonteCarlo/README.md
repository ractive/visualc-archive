# MonteCarlo 1.0

MFC doc/view application that estimates pi with the Monte-Carlo method in a worker
thread (`SimuThread`) and plots the random points. A menu lets you serialise the point
list to XML through four different parsers to compare them: CMarkup, Expat (via
ExpatImpl), pugxml and XMLite; an XML-RPC entry is greyed out. The user interface is
German. 2001-2003, no licence stated. The first commit is the September 2003 zip
snapshot, the second the later working copy. Third-party parsers: see `THIRD_PARTY.md`.
