// GifT68.h : main header file for the GIFT68 application
//

#if !defined(AFX_GIFT68_H__90EE7D4E_31B9_4F2C_8988_453C3D580AFC__INCLUDED_)
#define AFX_GIFT68_H__90EE7D4E_31B9_4F2C_8988_453C3D580AFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGifT68App:
// See GifT68.cpp for the implementation of this class
//

class CGifT68App : public CWinApp
{
public:
	CGifT68App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGifT68App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CGifT68App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GIFT68_H__90EE7D4E_31B9_4F2C_8988_453C3D580AFC__INCLUDED_)
