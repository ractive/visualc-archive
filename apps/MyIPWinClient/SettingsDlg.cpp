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


// SettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyIPWinClient.h"
#include "SettingsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingsDlg dialog


CSettingsDlg::CSettingsDlg(CWnd* pParent /*=NULL*/)
	: CToolTipDlg(CSettingsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSettingsDlg)
	m_bAddToTray = FALSE;
	m_bMinimizeAtStartup = FALSE;
	m_bStorePass = FALSE;
	m_bStoreUser = FALSE;
	m_bUpdateAtStartup = FALSE;
	m_bUsePort18080 = FALSE;
	m_bAutoUpdate = FALSE;
	m_bLANConn = FALSE;
	m_bModemConn = TRUE;
	m_bAlwaysSendIP = FALSE;
	m_bWarn = FALSE;
	//}}AFX_DATA_INIT
}


void CSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingsDlg)
	DDX_Control(pDX, IDC_LANCONN, m_LanConnection);
	DDX_Control(pDX, IDC_MODEMCONN, m_ModemConnection);
	DDX_Control(pDX, IDC_CONNECTIONTYPE, m_ConnectionType);
	DDX_Check(pDX, IDC_ADDTOTRAY, m_bAddToTray);
	DDX_Check(pDX, IDC_MINIMIZE, m_bMinimizeAtStartup);
	DDX_Check(pDX, IDC_STOREPASS, m_bStorePass);
	DDX_Check(pDX, IDC_STOREUSER, m_bStoreUser);
	DDX_Check(pDX, IDC_PORT18080, m_bUsePort18080);
	DDX_Check(pDX, IDC_AUTOUPDATE, m_bAutoUpdate);
	DDX_Check(pDX, IDC_LANCONN, m_bLANConn);
	DDX_Check(pDX, IDC_MODEMCONN, m_bModemConn);
	DDX_Check(pDX, IDC_ALWGETIP, m_bAlwaysSendIP);
	DDX_Check(pDX, IDC_WARN, m_bWarn);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSettingsDlg, CDialog)
	//{{AFX_MSG_MAP(CSettingsDlg)
	ON_BN_CLICKED(IDC_STOREPASS, OnStorepass)
	ON_BN_CLICKED(IDC_STOREUSER, OnStoreuser)
	ON_BN_CLICKED(IDC_AUTOUPDATE, OnAutoupdate)
	ON_BN_CLICKED(IDC_MODEMCONN, OnModem)
	ON_BN_CLICKED(IDC_LANCONN, OnLan)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingsDlg message handlers

void CSettingsDlg::ReDraw(CWnd *pWnd)
{
	// If we call it without a param, we redraw the whole dialog.
	if (pWnd == NULL)
		pWnd = this;

	pWnd->InvalidateRect(NULL);
	pWnd->UpdateWindow();

}

void CSettingsDlg::OnStorepass() 
{
	UpdateData();
	if (m_bStorePass && !m_bStoreUser) {
		// If you want to save the password you also
		// must save the username.
		m_bStoreUser = TRUE;
		UpdateData(FALSE);
	}
}
	
void CSettingsDlg::OnStoreuser() 
{
	// Read in the values;
	UpdateData();
	// If the Store user is not checked we also must remove the pass checkbox.
	if (!m_bStoreUser) {
		m_bStoreUser = m_bStorePass = FALSE;
		// Update the dialog box.
		UpdateData(FALSE);
	}
}

void CSettingsDlg::OnLan() 
{
	UpdateData();
	m_bLANConn = TRUE;
	m_bModemConn = FALSE;
	UpdateData(FALSE);
	
}

void CSettingsDlg::OnModem() 
{
	UpdateData();
	m_bLANConn = FALSE;
	m_bModemConn = TRUE;
	UpdateData(FALSE);
}

void CSettingsDlg::OnAutoupdate() 
{
	UpdateData();

	// Enable/disable the connection type fileds
	if (m_bAutoUpdate) {
		m_ConnectionType.ModifyStyle(WS_DISABLED, 0);
		m_LanConnection.ModifyStyle(WS_DISABLED, 0);
		m_ModemConnection.ModifyStyle(WS_DISABLED, 0);
		GetDlgItem(IDC_LANTEXT)->ModifyStyle(WS_DISABLED, 0);
		GetDlgItem(IDC_MODEMTEXT)->ModifyStyle(WS_DISABLED, 0);
	}
	else {
		m_ConnectionType.ModifyStyle(0, WS_DISABLED);
		m_LanConnection.ModifyStyle(0, WS_DISABLED);
		m_ModemConnection.ModifyStyle(0, WS_DISABLED);
		GetDlgItem(IDC_LANTEXT)->ModifyStyle(0, WS_DISABLED);
		GetDlgItem(IDC_MODEMTEXT)->ModifyStyle(0, WS_DISABLED);
	}

	Invalidate();
}

BOOL CSettingsDlg::OnInitDialog() 
{
	CToolTipDlg::OnInitDialog();

	AddTool(GetDlgItem(IDC_ADDTOTRAY), _T("An icon is added to the system tray"));
	AddTool(GetDlgItem(IDC_STOREUSER), _T("Your username is stored in the registry"));
	AddTool(GetDlgItem(IDC_STOREPASS), _T("Your password is stored in the registry. UNENCRYPTED!!!"));
	AddTool(GetDlgItem(IDC_MINIMIZE), _T("The application is minimized at startup"));
	AddTool(GetDlgItem(IDC_PORT18080), _T("Use this if you are behind a proxy server and standard port 80 doesn't work."));
	AddTool(GetDlgItem(IDC_AUTOUPDATE), _T("When an internet connection is detected, your account is updated automatically"));
	AddTool(GetDlgItem(IDC_WARN), _T("When the IP did not change since the last update you'll get a warning"));
	AddTool(GetDlgItem(IDC_ALWGETIP), _T("Always get the IPs of your PC at startup. Use this if the autodetection of www.myip.org does not work (proxy)"));
	Activate(TRUE);
	
	OnAutoupdate();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

