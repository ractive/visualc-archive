// TCPServerEx.h : main header file for the TCPSERVEREX application
//

#if !defined(AFX_TCPSERVEREX_H__E5382B3B_5ACD_4E6A_B123_B643F0C23AA8__INCLUDED_)
#define AFX_TCPSERVEREX_H__E5382B3B_5ACD_4E6A_B123_B643F0C23AA8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTCPServerExApp:
// See TCPServerEx.cpp for the implementation of this class
//

class CTCPServerExApp : public CWinApp
{
public:
	CTCPServerExApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCPServerExApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTCPServerExApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TCPSERVEREX_H__E5382B3B_5ACD_4E6A_B123_B643F0C23AA8__INCLUDED_)
