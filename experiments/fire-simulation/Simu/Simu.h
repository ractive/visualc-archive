// Simu.h : main header file for the SIMU application
//

#if !defined(AFX_SIMU_H__5802B64C_C58A_4702_8396_7AF10A18DD23__INCLUDED_)
#define AFX_SIMU_H__5802B64C_C58A_4702_8396_7AF10A18DD23__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSimuApp:
// See Simu.cpp for the implementation of this class
//

class CSimuApp : public CWinApp
{
public:
	CSimuApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimuApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSimuApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMU_H__5802B64C_C58A_4702_8396_7AF10A18DD23__INCLUDED_)
