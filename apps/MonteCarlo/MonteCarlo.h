// MonteCarlo.h : main header file for the MONTECARLO application
//

#if !defined(AFX_MONTECARLO_H__6C8DEA59_5EFB_473C_AB86_5A65D0B0588E__INCLUDED_)
#define AFX_MONTECARLO_H__6C8DEA59_5EFB_473C_AB86_5A65D0B0588E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#define WM_PROGRESS (WM_USER + 1)

/////////////////////////////////////////////////////////////////////////////
// CMonteCarloApp:
// See MonteCarlo.cpp for the implementation of this class
//

class CMonteCarloApp : public CWinApp
{
public:
	CMonteCarloApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMonteCarloApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMonteCarloApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MONTECARLO_H__6C8DEA59_5EFB_473C_AB86_5A65D0B0588E__INCLUDED_)
