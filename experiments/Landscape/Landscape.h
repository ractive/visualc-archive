// Landscape.h : main header file for the LANDSCAPE application
//

#if !defined(AFX_LANDSCAPE_H__1B08F0D1_92A2_4456_A728_3FBFF0FA07BF__INCLUDED_)
#define AFX_LANDSCAPE_H__1B08F0D1_92A2_4456_A728_3FBFF0FA07BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLandscapeApp:
// See Landscape.cpp for the implementation of this class
//

class CLandscapeApp : public CWinApp
{
public:
	CLandscapeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLandscapeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CLandscapeApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LANDSCAPE_H__1B08F0D1_92A2_4456_A728_3FBFF0FA07BF__INCLUDED_)
