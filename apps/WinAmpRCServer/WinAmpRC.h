// WinAmpRC.h : main header file for the WINAMPRC application
//

#if !defined(AFX_WINAMPRC_H__921FCEE8_F932_4B28_8EED_F0969F62F26F__INCLUDED_)
#define AFX_WINAMPRC_H__921FCEE8_F932_4B28_8EED_F0969F62F26F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWinAmpRCApp:
// See WinAmpRC.cpp for the implementation of this class
//

class CWinAmpRCApp : public CWinApp
{
public:
	CWinAmpRCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinAmpRCApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWinAmpRCApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINAMPRC_H__921FCEE8_F932_4B28_8EED_F0969F62F26F__INCLUDED_)
