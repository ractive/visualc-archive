// WMP.h : main header file for the WMP application
//

#if !defined(AFX_WMP_H__95236D14_9203_4D47_9883_A596CE043370__INCLUDED_)
#define AFX_WMP_H__95236D14_9203_4D47_9883_A596CE043370__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWMPApp:
// See WMP.cpp for the implementation of this class
//

class CWMPApp : public CWinApp
{
public:
	CWMPApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWMPApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWMPApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WMP_H__95236D14_9203_4D47_9883_A596CE043370__INCLUDED_)
