#if !defined(AFX_PLAYTONEX_H__D88DAE61_05C0_4F33_BF8B_81D49E28B410__INCLUDED_)
#define AFX_PLAYTONEX_H__D88DAE61_05C0_4F33_BF8B_81D49E28B410__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// PlayToneX.h : main header file for PLAYTONEX.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPlayToneXApp : See PlayToneX.cpp for implementation.

class CPlayToneXApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYTONEX_H__D88DAE61_05C0_4F33_BF8B_81D49E28B410__INCLUDED)
