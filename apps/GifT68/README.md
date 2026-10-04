# GifT68 1.0

Converts images into 101x80 pixel background GIFs for the Ericsson T68 phone display.
The first commit ("Kopie von GifT68") is the dialog-based version that shells out to
`gifsicle` and the companion `GifsicleMT` quantiser with hard-coded paths; the second
commit replaces it with an MDI doc/view rewrite that loads pictures with Yovav Gad's
CPicture class. Both 2001-2002, unfinished, no licence stated. The bundled
`gifsicle.exe` and `mt.exe` were not imported.
