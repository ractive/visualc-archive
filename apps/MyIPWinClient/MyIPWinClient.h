/*************************************************************************
                     MyIPWinClient
**************************************************************************

Copyright (C) April, 2000 Jean-Pierre Bergamin, james@ractive.ch

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



// MyIPWinClient.h : main header file for the MyIPWINCLIENT application
//

#if !defined(AFX_MyIPWINCLIENT_H__73CD9915_351E_11D3_81C9_0000B4A265C3__INCLUDED_)
#define AFX_MyIPWINCLIENT_H__73CD9915_351E_11D3_81C9_0000B4A265C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyIPWinClientApp:
// See MyIPWinClient.cpp for the implementation of this class
//

class CMyIPWinClientApp : public CWinApp
{
public:
	void GetHostIP(CString &sHost, CString &sIP);
	void DelAllHosts();
	void DelHost(CString sHost);
	BOOL EnumHosts(CString &sHost, int nIndex, CString * psIP = NULL, CString * psRecordType = NULL);
	void AddHost(const CString &sHost, const CString * psIP = NULL, const CString * psRecordType = NULL);
	CMyIPWinClientApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyIPWinClientApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMyIPWinClientApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString m_sHostKey;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MyIPWINCLIENT_H__73CD9915_351E_11D3_81C9_0000B4A265C3__INCLUDED_)
