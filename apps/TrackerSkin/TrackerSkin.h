// TrackerSkin.h : main header file for the TRACKERSKIN application
//

#if !defined(AFX_TRACKERSKIN_H__63AC1E51_1A25_4658_88F3_9805DD1A7BA9__INCLUDED_)
#define AFX_TRACKERSKIN_H__63AC1E51_1A25_4658_88F3_9805DD1A7BA9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTrackerSkinApp:
// See TrackerSkin.cpp for the implementation of this class
//

class CTrackerSkinApp : public CWinApp
{
public:
	CTrackerSkinApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrackerSkinApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTrackerSkinApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRACKERSKIN_H__63AC1E51_1A25_4658_88F3_9805DD1A7BA9__INCLUDED_)
