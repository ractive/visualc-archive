/*************************************************************************
                          HardLinker
**************************************************************************

Copyright (C) June, 2000 Jean-Pierre Bergamin, james@ractive.ch

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

The original context menu code was found at CodeGuru and is from Chris
from Smaller Animals Software
"CtxMenu, Copyright 1999, Smaller Animals Software:
  This code may be modifed and distributed free of charge or restrictions.
  This code is provided as-is. If you use this code in any application,
any bugs in the code are your responsibility."

***************************************************************************/


// HardLinker.cpp : Defines the initialization routines for the DLL.
//

#pragma data_seg(".text")
#define INITGUID
#include "stdafx.h"
#include <initguid.h>
#include <shlguid.h>
#include "HardLinker.h"
#include "ShellExt.h"
#pragma data_seg()

#include "SHUtils.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

unsigned int  g_cRefThisDll = 0;

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CHardLinkerApp

BEGIN_MESSAGE_MAP(CHardLinkerApp, CWinApp)
	//{{AFX_MSG_MAP(CHardLinkerApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHardLinkerApp construction

CHardLinkerApp::CHardLinkerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CHardLinkerApp object

CHardLinkerApp theApp;

BOOL CHardLinkerApp::InitInstance() 
{

   //InitializeCriticalSection(&g_critSectionBreak);

	return CWinApp::InitInstance();
}

int CHardLinkerApp::ExitInstance() 
{
	//DeleteCriticalSection(&g_critSectionBreak);
	
	return CWinApp::ExitInstance();
}

///////////////////////////////////////////////////////////////////////////
//
//  STDAPI DllCanUnloadNow(void)
//
//  PURPOSE: Tell whoever's interested if they can unload us or not.
//
//  Param				Type			Use
//	-----				----			---
//	none
//
//  Returns 
//		S_OK if it's OK to unload us.
//
///////////////////////////////////////////////////////////////////////////

STDAPI DllCanUnloadNow(void)
{
    ODS("In DLLCanUnloadNow\r\n");

    return (g_cRefThisDll == 0 ? S_OK : S_FALSE);
}

///////////////////////////////////////////////////////////////////////////
//
//  STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID *ppvOut)
//
//  PURPOSE: Create a class object of the type requested. This is how
//	Explorer talks to us.
//
//  Param			Type			Use
//	-----			----			---
//	rclsif			REFCLSID		class ID reference
//	riid			REFIID			interface ID reference
//	ppvOut			LPVOID *		ptr to an instance of the requested interface
//
//  Returns 
//		STDAPI status code
//
///////////////////////////////////////////////////////////////////////////
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID *ppvOut)
{
    ODS("In DllGetClassObject\r\n");

    *ppvOut = NULL;

    // file
    if (IsEqualIID(rclsid, CLSID_CreateHardLinkExtID))
    {
        CShellExtClassFactory *pcf;
		try {
			pcf = new CShellExtClassFactory;
		} catch (CMemoryException *e) {
			e->Delete();
			pcf=NULL;
		}

        return pcf->QueryInterface(riid, ppvOut);
    }

    return CLASS_E_CLASSNOTAVAILABLE;
}

