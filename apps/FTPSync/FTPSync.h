// FTPSync.h : main header file for the FTPSYNC application
//

#if !defined(AFX_FTPSYNC_H__E7F63E36_1C5F_44CE_B4CB_4B574415F0B5__INCLUDED_)
#define AFX_FTPSYNC_H__E7F63E36_1C5F_44CE_B4CB_4B574415F0B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#define WM_SYNCFILES		WM_USER + 1
#define WM_UPLOADFILE		WM_USER + 2
#define WM_DOWNLOADFILE		WM_USER + 3
#define WM_UPLOADDONE		WM_USER + 4
#define WM_DOWNLOADDONE		WM_USER + 5
#define WM_STARTSYNC		WM_USER + 6

/////////////////////////////////////////////////////////////////////////////
// CFTPSyncApp:
// See FTPSync.cpp for the implementation of this class
//

class CFTPSyncApp : public CWinApp
{
public:
	CFTPSyncApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFTPSyncApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CFTPSyncApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FTPSYNC_H__E7F63E36_1C5F_44CE_B4CB_4B574415F0B5__INCLUDED_)
