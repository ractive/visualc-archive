// NFOViewer.h : main header file for the NFOVIEWER application
//

#if !defined(AFX_NFOVIEWER_H__CE9A7880_2D89_4125_8C77_399B3F11007F__INCLUDED_)
#define AFX_NFOVIEWER_H__CE9A7880_2D89_4125_8C77_399B3F11007F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CNFOViewerApp:
// See NFOViewer.cpp for the implementation of this class
//

class CNFOViewerApp : public CWinApp
{
public:
	CNFOViewerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNFOViewerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CNFOViewerApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NFOVIEWER_H__CE9A7880_2D89_4125_8C77_399B3F11007F__INCLUDED_)
