// TestProgressDialog.h : main header file for the TESTPROGRESSDIALOG application
//

#if !defined(AFX_TESTPROGRESSDIALOG_H__715ED884_092B_45EE_8EC2_98C7ACAF3BD0__INCLUDED_)
#define AFX_TESTPROGRESSDIALOG_H__715ED884_092B_45EE_8EC2_98C7ACAF3BD0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestProgressDialogApp:
// See TestProgressDialog.cpp for the implementation of this class
//

class CTestProgressDialogApp : public CWinApp
{
public:
	CTestProgressDialogApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestProgressDialogApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestProgressDialogApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTPROGRESSDIALOG_H__715ED884_092B_45EE_8EC2_98C7ACAF3BD0__INCLUDED_)
