/*************************************************************************
                     MyIPWinClient
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


// MyIPWinClient.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MyIPWinClient.h"
#include "MyIPWinClientDlg.h"
#include <afxsock.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyIPWinClientApp

BEGIN_MESSAGE_MAP(CMyIPWinClientApp, CWinApp)
	//{{AFX_MSG_MAP(CMyIPWinClientApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyIPWinClientApp construction

CMyIPWinClientApp::CMyIPWinClientApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMyIPWinClientApp object

CMyIPWinClientApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMyIPWinClientApp initialization

BOOL CMyIPWinClientApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	SetRegistryKey(_T("@ractive Software"));
	m_sHostKey = "SOFTWARE\\";
	m_sHostKey += m_pszRegistryKey;
	m_sHostKey += "\\";
	m_sHostKey += AfxGetAppName();
	m_sHostKey += "\\Hosts";

	// Try to init the socket-stuff
	if (!AfxSocketInit()) {
		return FALSE;
	}

	CMyIPWinClientDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

void CMyIPWinClientApp::AddHost(const CString &sHost, const CString * psIP /* = NULL */, const CString * psRecordType /* = NULL */)
{
	int nPos = -1;
	CString sHostName = sHost;
	if ((nPos = sHostName.Find('.')) != -1) {
		sHostName = sHostName.Left(nPos);
	}

	DWORD dwDisp;
	HKEY hKey;
	CString sData;
	if (psIP != NULL)
		sData += *psIP;

	if (psRecordType != NULL)
		sData += " " + *psRecordType;

	RegCreateKeyEx(HKEY_CURRENT_USER, m_sHostKey, NULL, _T("Hosts"), REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &dwDisp);
	RegSetValueEx(hKey, sHostName, 0, REG_SZ, (BYTE *)(LPTSTR)(LPCTSTR)sData, sData.GetLength());
}

BOOL CMyIPWinClientApp::EnumHosts(CString &sHost, int nIndex, CString * psIP /* = NULL */, CString * psRecordType /* = NULL */)
{
	DWORD dwDisp;
	HKEY hKey;
	RegCreateKeyEx(HKEY_CURRENT_USER, m_sHostKey, NULL, _T("Hosts"), REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &dwDisp);
	CString sName;
	DWORD dwLen = 512;
	DWORD dwType = REG_SZ;
	DWORD dwIndex = 0;
	DWORD dwDataLen = 0;
	BYTE * pData = NULL;
	if (psIP != NULL) {
		dwDataLen = 512;
		pData = (BYTE *)psIP->GetBuffer(dwDataLen);
	}


	long nRet = RegEnumValue(hKey, nIndex, sHost.GetBuffer(dwLen), &dwLen, NULL, &dwType, pData, &dwDataLen);
	if (psIP != NULL) {
		psIP->ReleaseBuffer();
		if (psRecordType == NULL) {
			char sTemp[64];
			sscanf(*psIP, "%s", sTemp);
			*psIP = sTemp;
		}
		else {
			char sTemp[64];
			sTemp[0] = '\0';
			sscanf(*psIP, "%s %s", sTemp, psRecordType->GetBuffer(64));
			psRecordType->ReleaseBuffer();
			*psIP = sTemp;
		}
		
	}
	sHost.ReleaseBuffer();

	if (nRet != ERROR_SUCCESS && nRet != ERROR_NO_MORE_ITEMS) {
		return FALSE;
	}

	sHost += _T(".myip.org");
	return (nRet != ERROR_NO_MORE_ITEMS);
}

void CMyIPWinClientApp::DelHost(CString sHost)
{
	int nPos = -1;
	if ((nPos = sHost.Find('.')) != -1) {
		sHost = sHost.Left(nPos);
	}
	HKEY hKey;
	DWORD dwDisp;
	RegCreateKeyEx(HKEY_CURRENT_USER, m_sHostKey, NULL, _T("Hosts"), REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &dwDisp);
	RegDeleteValue(hKey, sHost);
}

void CMyIPWinClientApp::DelAllHosts()
{
	int nIndex = 0;
	CString sHost;
	while(EnumHosts(sHost, nIndex++)) {
		DelHost(sHost);
	}
}

void CMyIPWinClientApp::GetHostIP(CString &sHost, CString &sIP)
{
	int nPos = -1;
	if ((nPos = sHost.Find('.')) != -1) {
		sHost = sHost.Left(nPos);
	}

	CString sKey = m_sHostKey + "\\" + sHost;
	DWORD dwLen = 512, dwType;
	long error = RegQueryValueEx(HKEY_CURRENT_USER, sKey, NULL, &dwType, (BYTE *)sIP.GetBuffer(dwLen), &dwLen);
	if (error != ERROR_SUCCESS) {
		int x = 1;
	}
	sIP.ReleaseBuffer();
}
