/*************************************************************************
  Bluesson
**************************************************************************

Copyright (C) June 2002 by Jean-Pierre Bergamin

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
***************************************************************************/

// Bluesson.h : main header file for the BLUESSON application
//

#if !defined(AFX_BLUESSON_H__8D32A52D_70DD_4174_BE20_10A4B61A83E5__INCLUDED_)
#define AFX_BLUESSON_H__8D32A52D_70DD_4174_BE20_10A4B61A83E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBluessonApp:
// See Bluesson.cpp for the implementation of this class
//

// A WM_COMDAEMON message is sent to the window which created this thread to
// indicate that the thread ended.
#define WM_COMDAEMON (WM_USER + 3)
#define COMACTIVITY		0
#define COMDAEMONDIED	1


class CBluessonApp : public CWinApp
{
public:
	CBluessonApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBluessonApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBluessonApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BLUESSON_H__8D32A52D_70DD_4174_BE20_10A4B61A83E5__INCLUDED_)
