/*************************************************************************
                          NTMessenger
**************************************************************************

Copyright (C) April, 2000 Jean-Pierre Bergamin, james@ractive.ch

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
***************************************************************************/


// NTMessenger.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "NTMessenger.h"
#include "NTMessengerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNTMessengerApp

BEGIN_MESSAGE_MAP(CNTMessengerApp, CWinApp)
	//{{AFX_MSG_MAP(CNTMessengerApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNTMessengerApp construction

CNTMessengerApp::CNTMessengerApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CNTMessengerApp object

CNTMessengerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CNTMessengerApp initialization

BOOL CNTMessengerApp::InitInstance()
{
	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CNTMessengerDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
