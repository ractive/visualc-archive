/************************************************************
Module name: FileLink.h
Written by: Armin Gerritsen
************************************************************/

BOOL  CreateLink(const char*, const char*, DWORD& ) ;
BOOL  NT4CreateHardLink( const char*, const char*, DWORD& ) ;
BOOL  EnablePrivs( DWORD& ) ;
