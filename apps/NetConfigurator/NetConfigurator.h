// NetConfigurator.h : main header file for the NETCONFIGURATOR application
//

#if !defined(AFX_NETCONFIGURATOR_H__ABE5EA47_2490_4539_9A87_B3F374A55B80__INCLUDED_)
#define AFX_NETCONFIGURATOR_H__ABE5EA47_2490_4539_9A87_B3F374A55B80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CNetConfiguratorApp:
// See NetConfigurator.cpp for the implementation of this class
//

class CNetConfiguratorApp : public CWinApp
{
public:
	CNetConfiguratorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetConfiguratorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CNetConfiguratorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETCONFIGURATOR_H__ABE5EA47_2490_4539_9A87_B3F374A55B80__INCLUDED_)
