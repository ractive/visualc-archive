/*************************************************************************
                          HardLinker
**************************************************************************

Copyright (C) June, 2000 Jean-Pierre Bergamin, james@ractive.ch

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

The original context menu code was found at CodeGuru and is from Chris
from Smaller Animals Software
"CtxMenu, Copyright 1999, Smaller Animals Software:
  This code may be modifed and distributed free of charge or restrictions.
  This code is provided as-is. If you use this code in any application,
any bugs in the code are your responsibility."

***************************************************************************/


#ifndef SHUTILSH
#define SHUTILSH

/////////////////////////////////////////////////////////////
// shell extension name
#define	SHELLEXNAME				"HardLinker"

/////////////////////////////////////////////////////////////
// safe data access for data shared between threads
//extern CRITICAL_SECTION g_critSectionBreak;
//template <class T> T GET_SAFE( T a ) {EnterCriticalSection(&g_critSectionBreak); T z = a; LeaveCriticalSection(&g_critSectionBreak); return z;}
//template <class T> void SET_SAFE( T & a , T b) {EnterCriticalSection(&g_critSectionBreak); a = b; LeaveCriticalSection(&g_critSectionBreak);}

/////////////////////////////////////////////////////////////
// just like TRACE0
#ifdef _DEBUG
#define ODS(sz) {if (strlen(sz)>0) {OutputDebugString(SHELLEXNAME); OutputDebugString("=>");} OutputDebugString(sz);}
#else
#define ODS(x)
#endif

#define ResultFromShort(i)  ResultFromScode(MAKE_SCODE(SEVERITY_SUCCESS, 0, (USHORT)(i)))

/////////////////////////////////////////////////////////////
// macro to determine # of args in an array
#define ARRAYSIZE(a)    (sizeof(a)/sizeof(a[0]))

/////////////////////////////////////////////////////////////
// pump msgs
extern void	ShMsgPump();

/////////////////////////////////////////////////////////////
// conversion routines
extern int  LocalToWideChar(LPWSTR pWide, LPTSTR pLocal, DWORD dwChars);
extern int  WideCharToLocal(LPTSTR pLocal, LPWSTR pWide, DWORD dwChars);

extern STDMETHODIMP CreateShellExtMenu(HMENU hMenu, UINT indexMenu, UINT idCmdFirst, UINT idCmdLast, UINT uFlags, HBITMAP hbmp);
extern STDMETHODIMP GetSelectedFiles(LPCITEMIDLIST pIDFolder, LPDATAOBJECT & pDataObj, CStringArray &csaPaths, CString& sDropTarget);

#endif