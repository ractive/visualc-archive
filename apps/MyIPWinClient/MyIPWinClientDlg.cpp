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



// MyIPWinClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyIPWinClient.h"
#include "MyIPWinClientDlg.h"
#include <afxinet.h>
#include <ras.h>
#include <rasdlg.h>
#include <raserror.h>
#include "SettingsDlg.h"
#include "CreateAccountDlg.h"
#include "WelcomeDlg.h"
#include "AboutBox.h"
#include "MyIPHelper.h"
#include "HostsDlg.h"
#include "NewPwdDlg.h"
#include "IPListDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_CONN 30

#define WM_TRAYNOTIFICATION		(WM_USER + 1)
#define WM_STARTUP				(WM_USER + 2)

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
};


/////////////////////////////////////////////////////////////////////////////
// CMyIPWinClientDlg dialog

CMyIPWinClientDlg::CMyIPWinClientDlg(CWnd* pParent /*=NULL*/)
	: CToolTipDlg(CMyIPWinClientDlg::IDD, pParent), rb("Client")
{
	//{{AFX_DATA_INIT(CMyIPWinClientDlg)
	m_sPassword = _T("");
	m_sUsername = _T("");
	m_sEmail = _T("");
	m_sHost = _T("");
	m_sStatus = _T("");
	m_sIPAddress = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// Really cool class. We bind the values to keys in the registry.
	// This is all. When the objects are destrutcted, the values are automatically
	// stored in the Registry.
	rb.Bind(m_sPassword, "val");
	rb.Bind(m_sUsername, "val2");
	rb.Bind(m_bStorePass, "st", 0);
	rb.Bind(m_bStoreUser, "st2", 0);
	rb.Bind(m_bAddToTray, "AddToTray", 0);
	rb.Bind(m_bMinChk, "MinUpdate", 0);
	rb.Bind(m_bAutoUpdate, "AutoUpdate", 0);
	rb.Bind(m_bMinimizeAtStartup, "MinimizeAtStartup", 0);
	rb.Bind(m_bUpdateAtStartup, "Update at startup", 0);
	rb.Bind(m_bUsePort18080, "Use port 18080", 0);
	rb.Bind(m_nMin, "Update interval", 0);
	rb.Bind(m_sEmail, "Email");
	rb.Bind(m_sMX, "MX-Record");
	rb.Bind(m_bLANConn, "LanConnection", 0);
	rb.Bind(m_bFirstStart, "FirstStart", 1);
	rb.Bind(m_bAlwaysSendIP, "Always send IP", 0);
	rb.Bind(m_sHost, "all", 0);
	rb.Bind(m_sHostToPing, "Ping host", "www.yahoo.com");
	rb.Bind(m_bWarn, "Warn no change", 0);
	m_sIPAddress = _T("");
	m_sMX = _T("");

	ThreadInfo.hRasEvent = INVALID_HANDLE_VALUE;
}

void CMyIPWinClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyIPWinClientDlg)
	DDX_Control(pDX, IDC_IPS, m_IPAddressCombo);
	DDX_Control(pDX, IDC_HOSTS, m_HostCombo);
	DDX_Control(pDX, IDC_MYIPORG, m_myiporg);
	DDX_Text(pDX, IDC_PASSWORD, m_sPassword);
	DDX_Text(pDX, IDC_USERNAME, m_sUsername);
	DDX_CBString(pDX, IDC_HOSTS, m_sHost);
	DDX_CBString(pDX, IDC_IPS, m_sIPAddress);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyIPWinClientDlg, CDialog)
	//{{AFX_MSG_MAP(CMyIPWinClientDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_BN_CLICKED(ID_SETTINGS, OnSettings)
	ON_COMMAND(ID_RESTORE, OnRestore)
	ON_COMMAND(ID_EXIT, OnExit)
	ON_MESSAGE(WM_TRAYNOTIFICATION, OnTrayNotification)
	ON_COMMAND(ID_ABOUT, OnAbout)
	ON_MESSAGE(WM_STARTUP, OnStartup)
	ON_BN_CLICKED(IDC_HOSTBUTTON, OnHostbutton)
	ON_BN_CLICKED(IDC_PASSBUTTON, OnPassbutton)
	ON_BN_CLICKED(IDC_GETIP, OnGetip)
	ON_BN_CLICKED(ID_ADVUPDATE, OnAdvupdate)
	ON_COMMAND(ID_CREATENEW, CreateAccount)
	ON_MESSAGE(WM_RASDAEMON, OnRasDaemonMsg)
	ON_BN_CLICKED(IDC_UPDATE, UpdateAccount)
	ON_COMMAND(ID_DELETEACC, OnDeleteacc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyIPWinClientDlg message handlers

BOOL CMyIPWinClientDlg::OnInitDialog()
{
	CToolTipDlg::OnInitDialog();

	m_myiporg.SetURL("http://www.myip.org");

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	UpdateData(FALSE);

	m_bUpdated = FALSE;

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	
	// We need to resize the dialog to make room for control bars.
	// First, figure out how big the control bars are.
	CRect rcClientStart;
	CRect rcClientNow;
	GetClientRect(rcClientStart);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 
				   0, reposQuery, rcClientNow);
	
	// Adjust the dialog window dimensions
	CRect rcWindow;
	GetWindowRect(rcWindow);
	rcWindow.bottom += rcClientStart.Height() - rcClientNow.Height();
	MoveWindow(rcWindow, FALSE);
	
	// And position the control bars
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
	int nWidth;
	UINT nID, nStyle;
	m_wndStatusBar.GetPaneInfo(0, nID, nStyle, nWidth);
	
	m_wndStatusBar.SetPaneInfo(0, nID, WS_EX_STATICEDGE | SBPS_STRETCH, nWidth);

	TrayIcon.SetMenu(IDR_TRAY);
	TrayIcon.SetNotificationWindow(this, WM_TRAYNOTIFICATION);

	ShowTrayIcon(m_bAddToTray);

	// Set the status bar, trayicon etc. correctly
	SetUpdated();

	// Add the tool tip descriptions
	AddTool(GetDlgItem(IDC_USERNAME), _T("Your username must only contain letters a-z and numbers 0-9"));
	AddTool(GetDlgItem(IDC_PASSWORD), _T("Your password must only contain letters a-z A-Z and numbers 0-9."));
	AddTool(GetDlgItem(IDC_PASSBUTTON), _T("Change your password on www.myip.org"));
	AddTool(GetDlgItem(IDC_IPS), _T("Update your host to this IP. If you leave it empty, www.myip.org will autodetect your IP"));
	AddTool(GetDlgItem(IDC_GETIP), _T("Get all the IPs of your machine."));
	AddTool(GetDlgItem(IDC_HOSTS), _T("Update the selected host"));
	AddTool(GetDlgItem(IDC_HOSTBUTTON), _T("Manage your hosts. Add/delete or import them from www.myip.org"));
	AddTool(GetDlgItem(IDC_UPDATE), _T("Updates your account at www.myip.org"));
	AddTool(GetDlgItem(ID_SETTINGS), _T("Change your application configuration"));
	AddTool(GetDlgItem(ID_ADVUPDATE), _T("Let's you choose the recordtype and see to which IP the hosts point to"));
	Activate(TRUE);

	m_hostMgr.Init(&m_sUsername, &m_sPassword, this, &m_bWarn);

	FillHostCombo();

	// Select the last selected host in the combo-box
	m_HostCombo.SetCurSel(m_HostCombo.FindString(-1, m_sHost));

	// Post a message that the dialog app started. OnStartup will be called.
	::PostMessage(m_hWnd, WM_STARTUP, 0, 0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyIPWinClientDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyIPWinClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMyIPWinClientDlg::UpdateAccount()
{
	// Get the new IP(s)
	if (m_bAlwaysSendIP) {
		OnGetip();
	}

	UpdateData();

	m_bUpdated = m_hostMgr.UpdateHost(m_sHost, m_sIPAddress, m_sMX);
	
	SetUpdated();
	if (m_bUpdated) {
		const int nIcons = 8;
		HICON aIcon[nIcons];
		aIcon[0] = AfxGetApp()->LoadIcon(IDI_ANIM1);
		aIcon[1] = AfxGetApp()->LoadIcon(IDI_ANIM2);
		aIcon[2] = AfxGetApp()->LoadIcon(IDI_ANIM3);
		aIcon[3] = AfxGetApp()->LoadIcon(IDI_ANIM4);
		aIcon[4] = AfxGetApp()->LoadIcon(IDI_ANIM5);
		aIcon[5] = AfxGetApp()->LoadIcon(IDI_ANIM6);
		aIcon[6] = AfxGetApp()->LoadIcon(IDI_ANIM7);
		aIcon[7] = AfxGetApp()->LoadIcon(IDI_ANIM8);
		TrayIcon.AnimateIcon(aIcon, nIcons, 3, 200);	
	}
}

void CMyIPWinClientDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	

	UpdateData();
	// Do we have to clear the strings if the user doesn't want to have them saved?
	if (!m_bStorePass) {
		m_sPassword.Empty();
		rb.Write(FALSE);
	}
	if (!m_bStoreUser) {
		m_sUsername.Empty();
		rb.Write(FALSE);
	}

	TrayIcon.KillAnimationThread();

	TrayIcon.RemoveIcon();

	CInternetHelper::Destroy();

	CDialog::OnDestroy();
	
}

void CMyIPWinClientDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	if (nType == SIZE_MINIMIZED) {
		// Hide the window if we have a tray icon.
		if (TrayIcon.IsSet()) {
			ShowTaskIcon(false);
		}
	}
}

void CMyIPWinClientDlg::OnSettings() 
{
	UpdateData();

	// Keep the value for the old connection type
	BOOL bOldLanConn = m_bLANConn;
	BOOL bOldAutoUpdate = m_bAutoUpdate;
	// Show the settings dialog and copy all variables to the
	// members of the dialog-class
	CSettingsDlg dlg;
	dlg.m_bAddToTray = m_bAddToTray;
	dlg.m_bMinimizeAtStartup = m_bMinimizeAtStartup;
	dlg.m_bStorePass = m_bStorePass;
	dlg.m_bStoreUser = m_bStoreUser;
	dlg.m_bUpdateAtStartup = m_bUpdateAtStartup;
	dlg.m_bUsePort18080 = m_bUsePort18080;
	dlg.m_bAutoUpdate = m_bAutoUpdate;
	dlg.m_bLANConn = m_bLANConn;
	dlg.m_bModemConn = !m_bLANConn;
	dlg.m_bAlwaysSendIP = m_bAlwaysSendIP;
	dlg.m_bWarn = m_bWarn;
	if (dlg.DoModal() == IDOK) {
		// If the user hit OK, take the new values
		m_bAddToTray = dlg.m_bAddToTray;
		m_bMinimizeAtStartup = dlg.m_bMinimizeAtStartup;
		m_bStorePass = dlg.m_bStorePass;
		m_bStoreUser = dlg.m_bStoreUser;
		m_bUpdateAtStartup = dlg.m_bUpdateAtStartup;
		m_bUsePort18080 = dlg.m_bUsePort18080;
		m_bLANConn = dlg.m_bLANConn;
		m_bAutoUpdate = dlg.m_bAutoUpdate;
		m_bAlwaysSendIP = dlg.m_bAlwaysSendIP;
		m_bWarn = dlg.m_bWarn;
		ShowTrayIcon(m_bAddToTray);
		CInternetHelper * pHelper = CInternetHelper::Instance();
		if (bOldAutoUpdate != m_bAutoUpdate) {
			// If the user wants to auto update from now on, we have to start the thread.
			// If he doesn't want to auto-update any more, we have to ent the thread.
			if (m_bAutoUpdate) {
				pHelper->SetNotificationWnd(m_hWnd);
				pHelper->StartRASDaemon(NULL, m_bLANConn);			
			}
			else {
				pHelper->EndRASDaemon();
			}
		}
		if (bOldLanConn != m_bLANConn) {
			// If the connection type changed, restart the thread which
			// automatically update the account.
			pHelper->EndRASDaemon();
			pHelper->SetNotificationWnd(m_hWnd);
			pHelper->StartRASDaemon(NULL, m_bLANConn);
		}
	}
}

void CMyIPWinClientDlg::ShowTaskIcon(bool bShow /* = true */)
{
	ShowWindow(bShow ? SW_SHOW : SW_HIDE);
}

void CMyIPWinClientDlg::OnRestore() 
{
	ShowTaskIcon(true);	
	ShowWindow(SW_RESTORE);
}

void CMyIPWinClientDlg::ShowTrayIcon(BOOL bShow)
{
	TrayIcon.KillAnimationThread();
	if (bShow) {
		if (m_bUpdated) {
			TrayIcon.SetIcon(IDR_TRAY);
		}
		else {
			TrayIcon.SetIcon(IDR_TRAYNOTUPDATED);		
		}
	}
	else {
		TrayIcon.RemoveIcon();
	}
}

void CMyIPWinClientDlg::OnExit() 
{
	EndDialog(0);	
}

LRESULT CMyIPWinClientDlg::OnTrayNotification(WPARAM wParam, LPARAM lParam)
{
	return TrayIcon.OnTrayNotification(wParam, lParam);
}

void CMyIPWinClientDlg::OnAbout() 
{
	CAboutBox box;
	box.DoModal();
}

void CMyIPWinClientDlg::OnStartup()
{
	if (m_bFirstStart) {
		// This is the only time we show this... for ever :-)
		m_bFirstStart = FALSE;
		CWelcomeDlg dlg;
		if (dlg.DoModal() == IDOK) {
			CreateAccount();
		}
		else {
			MessageBox(_T("If you want to import your existing account, go to \"Advanced Update\"\r\nand choose \"Import settings\""), "Import account!", MB_OK | MB_ICONINFORMATION);
		}
	}

	if (m_bAlwaysSendIP) {
		OnGetip();
	}

	Sleep(300);
	if (m_bMinimizeAtStartup)
		ShowWindow(SW_MINIMIZE);

	if (m_bAutoUpdate) {
		// Start the daemon which looks for internet connections.
		CMyIPHelper * pMyIPHelper = CMyIPHelper::Instance();
		pMyIPHelper->SetNotificationWnd(m_hWnd);
		pMyIPHelper->StartRASDaemon(NULL, m_bLANConn, m_sHostToPing);
	}

	const int nIcons = 8;
	HICON aIcon[nIcons];
	aIcon[0] = AfxGetApp()->LoadIcon(IDI_ANIM1);
	aIcon[1] = AfxGetApp()->LoadIcon(IDI_ANIM2);
	aIcon[2] = AfxGetApp()->LoadIcon(IDI_ANIM3);
	aIcon[3] = AfxGetApp()->LoadIcon(IDI_ANIM4);
	aIcon[4] = AfxGetApp()->LoadIcon(IDI_ANIM5);
	aIcon[5] = AfxGetApp()->LoadIcon(IDI_ANIM6);
	aIcon[6] = AfxGetApp()->LoadIcon(IDI_ANIM7);
	aIcon[7] = AfxGetApp()->LoadIcon(IDI_ANIM8);
	TrayIcon.AnimateIcon(aIcon, nIcons, 1, 100);
}

void CMyIPWinClientDlg::OnRasDaemonMsg(UINT pParam, long lParam)
{
	if (pParam == 0) {
		// This means we got a message from the RASDaemon


		// Are we connected?
		if (lParam == CONNECTED) {
			// Yes, we are. Update the account.
			UpdateAccount();
		}
		else if (lParam == DISCONNECTED) {
			// No. We are not. Set the state to no updated.
			m_bUpdated = FALSE;
			SetUpdated();
		}
	}
}

void CMyIPWinClientDlg::SetUpdated()
{
	ShowTrayIcon(TrayIcon.IsSet());
		
	if (m_bUpdated) {
		m_wndStatusBar.SetPaneText(0, "Host: " + m_sHost + " updated!");	
	}
	else {
		m_wndStatusBar.SetPaneText(0, "Host: " + m_sHost + " NOT updated!");	
	}


}

void CMyIPWinClientDlg::CreateAccount()
{
	CCreateAccountDlg dlg;
	if (dlg.DoModal() == IDOK) {
		// When the new account could be created, we update the entries
		if (dlg.m_bCreated) {
			m_sUsername = dlg.m_sUsername;
			m_sEmail = dlg.m_sEmail;
			m_sPassword = dlg.m_sPassword;
			UpdateData(FALSE);
		}
	}
}

void CMyIPWinClientDlg::OnHostbutton() 
{
	UpdateData();
	CHostsDlg dlg;
	dlg.m_pHostMgr = &m_hostMgr;
	dlg.DoModal();
	FillHostCombo();
}

void CMyIPWinClientDlg::OnPassbutton() 
{
	UpdateData();
	CNewPwdDlg dlg;
	if (dlg.DoModal() == IDOK) {
		// If the update was successful, we get the new password for
		// the main wnd.
		m_sPassword = dlg.m_NewPwd;
		UpdateData(FALSE);
	}
}

void CMyIPWinClientDlg::OnGetip() 
{
	m_IPAddressCombo.ResetContent();
	CInternetHelper * pInternetHelper = CInternetHelper::Instance();
	CStringArray saIPs;
	pInternetHelper->getIPs(&saIPs);
	for (int i = 0; i < saIPs.GetSize(); i++) {
		m_IPAddressCombo.AddString(saIPs.GetAt(i));
	}
	int nCount = -1;
	if (nCount = m_IPAddressCombo.GetCount()) {
		m_IPAddressCombo.SetCurSel(nCount - 1);
	}
	
}

void CMyIPWinClientDlg::OnAdvupdate() 
{
	UpdateData();
	CIPListDlg dlg;
	dlg.m_pHostMgr = &m_hostMgr;
	dlg.DoModal();
}

void CMyIPWinClientDlg::FillHostCombo()
{
	m_HostCombo.ResetContent();
	for (int i = 0; i < m_hostMgr.GetSize(); i++) {
		m_HostCombo.AddString(m_hostMgr.GetHost(i));
	}
	m_HostCombo.AddString(_T("all"));
	m_HostCombo.SetCurSel(0);

}

void CMyIPWinClientDlg::OnDeleteacc() 
{
	UpdateData();
	if (MessageBox(_T("Are you sure you want to delete your account at www.myip.org?"), _T("Deletion confirmation"), MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES) {
		if (MessageBox(_T("Are you really sure?\r\n\r\nThere is no way back!"), _T("Deletion confirmation"), MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES) {
			CMyIPHelper * pMyIPHelper = CMyIPHelper::Instance();
			if (pMyIPHelper->DeleteAccount(m_sUsername, m_sPassword)) {
				MessageBox(_T("Your account has been deleted successfully!"), _T("Account deleted"), MB_OK | MB_ICONINFORMATION);
				// Delete all the entries in the Registry, too.
				m_hostMgr.DeleteAll();
				CMyIPWinClientApp * pApp = (CMyIPWinClientApp *)AfxGetApp();
				pApp->DelAllHosts();
				FillHostCombo();
				m_sUsername.Empty();
				m_sPassword.Empty();
				UpdateData(FALSE);
			}
			else {
				MessageBox(_T("Your account couldn't be deleted!"), _T("Account not deleted"), MB_OK | MB_ICONINFORMATION);
			}
		}
	}
	
}
