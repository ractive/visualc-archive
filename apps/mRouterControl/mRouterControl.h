// mRouterControl.h : main header file for the MROUTERCONTROL application
//

#if !defined(AFX_MROUTERCONTROL_H__6E5BE38C_5443_465D_B566_1446C010BCCA__INCLUDED_)
#define AFX_MROUTERCONTROL_H__6E5BE38C_5443_465D_B566_1446C010BCCA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMRouterControlApp:
// See mRouterControl.cpp for the implementation of this class
//

class CMRouterControlApp : public CWinApp
{
public:
	CMRouterControlApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMRouterControlApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMRouterControlApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MROUTERCONTROL_H__6E5BE38C_5443_465D_B566_1446C010BCCA__INCLUDED_)
