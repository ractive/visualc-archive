// EMelodyLab.h : main header file for the EMELODYLAB application
//

#if !defined(AFX_EMELODYLAB_H__50460CCD_E4BE_4295_A27D_0D86785897FD__INCLUDED_)
#define AFX_EMELODYLAB_H__50460CCD_E4BE_4295_A27D_0D86785897FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEMelodyLabApp:
// See EMelodyLab.cpp for the implementation of this class
//

class CEMelodyLabApp : public CWinApp
{
public:
	CEMelodyLabApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEMelodyLabApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEMelodyLabApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EMELODYLAB_H__50460CCD_E4BE_4295_A27D_0D86785897FD__INCLUDED_)
