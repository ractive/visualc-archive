// Visu.h : main header file for the VISU application
//

#if !defined(AFX_VISU_H__BF652C5A_5F20_4729_AD00_A00D429F9926__INCLUDED_)
#define AFX_VISU_H__BF652C5A_5F20_4729_AD00_A00D429F9926__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "ConnectSocket.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// CVisuApp:
// See Visu.cpp for the implementation of this class
//

class CVisuApp : public CWinApp
{
public:
	CVisuApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVisuApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CVisuApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	CConnectSocket m_ListenSocket;
	CConnectSocket m_ConnectSocket;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VISU_H__BF652C5A_5F20_4729_AD00_A00D429F9926__INCLUDED_)
