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

// NTMessengerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NTMessenger.h"
#include "NTMessengerDlg.h"
#include <lm.h>
#include "MultipleRecipientsDlg.h"
#include "OptionsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

TCHAR * CNTMessengerDlg::sAll = _T("To all");

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNTMessengerDlg dialog

CNTMessengerDlg::CNTMessengerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNTMessengerDlg::IDD, pParent), rb(_T("NTMessenger"))
{
	//{{AFX_DATA_INIT(CNTMessengerDlg)
	m_sName = _T("");
	m_sMessageText = _T("");
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_nMinutes = 0;

	m_bClose = false;

	rb.Bind(m_bStartMinimized, _T("StartMinimized"), 0);
	rb.Bind(m_bDeleteWhenSent, _T("DeleteWhenSent"), 0);
	rb.Bind(m_bRescan, _T("Rescan"), 0);
	rb.Bind(m_nMinutes, _T("Rescan Interval"), 1);
	rb.Bind(m_sPDC, _T("Domain Controller"), TEXT(""));
	rb.Bind(m_sDomain, _T("Domain"), TEXT(""));
}

CNTMessengerDlg::~CNTMessengerDlg()
{

}

void CNTMessengerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNTMessengerDlg)
	DDX_Control(pDX, IDC_CLEAR, m_ClearButton);
	DDX_Control(pDX, IDC_OPTIONS, m_OptionsButton);
	DDX_Control(pDX, IDC_SEND, m_SendButton);
	DDX_Control(pDX, IDC_SERVERCOMBO, m_ServerCombo);
	DDX_Text(pDX, IDC_NAME, m_sName);
	DDX_Text(pDX, IDC_MESSAGETEXT, m_sMessageText);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CNTMessengerDlg, CDialog)
	//{{AFX_MSG_MAP(CNTMessengerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_MULTIPLE, OnMultiple)
	ON_CBN_SELCHANGE(IDC_SERVERCOMBO, OnSelchangeServercombo)
	ON_BN_CLICKED(IDC_SEND, OnSend)
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	ON_BN_CLICKED(IDC_OPTIONS, OnOptions)
	ON_WM_TIMER()
	ON_COMMAND(IDC_ABOUT, OnAbout)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_TRAYNOTIFICATION, OnTrayNotification)
	ON_MESSAGE(WM_STARTUP, OnStartup)
	ON_COMMAND(ID_RESTORE, OnRestore)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNTMessengerDlg message handlers

BOOL CNTMessengerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	HICON hIcon = (HICON)LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_SENDICON), IMAGE_ICON, 48, 48, LR_DEFAULTCOLOR);
	m_SendButton.SetIcon(hIcon);
	hIcon = (HICON)LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_OPTIONSICON), IMAGE_ICON, 48, 48, LR_DEFAULTCOLOR);
	m_OptionsButton.SetIcon(hIcon);
	hIcon = (HICON)LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_CLEARICON), IMAGE_ICON, 48, 48, LR_DEFAULTCOLOR);
	m_ClearButton.SetIcon(hIcon);

	// Tooltip initialization
	EnableToolTips();
	m_ToolTip.Create(this);
	m_ToolTip.SetDelayTime(500);
	m_ToolTip.AddTool(GetDlgItem(IDC_SEND), _T("Send the message"));
	m_ToolTip.AddTool(GetDlgItem(IDC_OPTIONS), _T("Edit your preferences"));
	m_ToolTip.AddTool(GetDlgItem(IDC_OPTIONS), _T("Edit your preferences"));
	m_ToolTip.AddTool(GetDlgItem(IDC_CLEAR), _T("Clear the message text"));
	m_ToolTip.AddTool(GetDlgItem(IDC_MULTIPLE), _T("Click to select the recipients"));
	m_ToolTip.AddTool(GetDlgItem(IDC_SERVERCOMBO), _T("Enter the recipients, separated by a semicolon or choose from the list"));
	m_ToolTip.AddTool(GetDlgItem(IDC_NAME), _T("Enter your name the recipient will see"));

	// Trayicon initialization
	TrayIcon.SetMenu(IDR_TRAY);
	TrayIcon.SetNotificationWindow(this, WM_TRAYNOTIFICATION);
	TrayIcon.SetIcon(IDR_MAINFRAME);


	DWORD dwLevel = 101;
	LPWKSTA_INFO_101 pBuf = NULL;
	NET_API_STATUS nStatus;
	//
	// Call the NetWkstaUserGetInfo function;
	//  specify level 1.
	//
	nStatus = NetWkstaGetInfo(NULL,
								 dwLevel,
								 (LPBYTE *)&pBuf);
	//
	// If the call succeeds, print the information
	//  about the logged-on user.
	//
	if (nStatus != NERR_Success) {
        ErrorMsg(_T("Could not get user info"));
        return FALSE;
	}
	if (pBuf != NULL)
	{
		m_sName = pBuf->wki101_computername;
		m_sDomain = pBuf->wki101_langroup;
		// Free the allocated memory.
		NetApiBufferFree(pBuf);
	}

	FillServerCombo();

	UpdateData(FALSE);
	
	PostMessage(WM_STARTUP, 0, 0);

	RescanTimer();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CNTMessengerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CNTMessengerDlg::OnPaint() 
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

HCURSOR CNTMessengerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

bool CNTMessengerDlg::FillServerCombo()
{
	CWaitCursor wait;

	SERVER_INFO_100 * pSI_100;
	DWORD  dwEntriesRead;
	DWORD  dwTotalEntries;
	
	// Get the current content of the combobox edit line
	CString sSelection;
	m_ServerCombo.GetWindowText(sSelection);

	// Clean up
	m_ServerCombo.ResetContent();

	if (!m_sPDC.IsEmpty() && m_sPDC.Left(2) != "\\\\") {
		m_sPDC = "\\\\" + m_sPDC;
	}

	LPWSTR psDomain = NULL;
	if (!m_sDomain.IsEmpty()) {
		psDomain = (LPWSTR)(LPCTSTR)m_sDomain;
	}

	// Remove all entries from the server-array
	saServer.RemoveAll();

	// Get all the "servers" in the network
	NET_API_STATUS nas;
	do {
		nas = NetServerEnum (m_sPDC, 100, (LPBYTE*)&pSI_100, sizeof(SERVER_INFO_100) * 20, &dwEntriesRead, &dwTotalEntries, SV_TYPE_ALL, psDomain, 0);
		

		if ((nas == NERR_Success || nas == ERROR_MORE_DATA ) && pSI_100 != NULL ) {

			// Add all the names
			for (DWORD i = 0; i < dwEntriesRead; i++) {
				CString sName = (LPWSTR)pSI_100[i].sv100_name;
				saServer.Add(sName);
				m_ServerCombo.AddString(sName);
			}
			NetApiBufferFree (pSI_100);
		}
		else {
			CString sMsg;
			switch (nas) {
			case ERROR_ACCESS_DENIED: sMsg = TEXT("The user does not have access to the requested information."); break;
			case NERR_InvalidComputer: sMsg = TEXT("The computer name is invalid."); break;
			case ERROR_NO_BROWSER_SERVERS_FOUND:  sMsg = TEXT("No browser servers found."); break;
			case ERROR_MORE_DATA:  sMsg = TEXT("More entries are available with subsequent calls."); break;
			default:
				sMsg.Format(TEXT("Error number %d occured while scanning the network"), nas);
			}
			MessageBox(sMsg, TEXT("Network browsing error"), MB_OK | MB_ICONEXCLAMATION);
		}

		if (dwEntriesRead > 0) {
			// Don't select the first entry if our PC is the first one, we select the second one if this is possible.
			CString sMyPC;
			nas = NetServerGetInfo(NULL, 100, (LPBYTE*)&pSI_100);
			if (nas == NERR_Success) {
				sMyPC = (LPWSTR)pSI_100->sv100_name;
				NetApiBufferFree (pSI_100);
			}

			CString sPC;
			m_ServerCombo.GetLBText(0, sPC);
			if ((m_ServerCombo.GetCount() > 1) && (sPC == sMyPC)) {
				m_ServerCombo.SetCurSel(1);
			}
			else {
				m_ServerCombo.SetCurSel(0);
			}
		}
		
		else {
			ErrorMsg(_T("No computers found on the network."));
			return false;
		}

	} while(nas == ERROR_MORE_DATA );

	// Add the "To all" entry
	m_ServerCombo.AddString(sAll);

	// If the old combobox text was not empty we restore it
	if (!sSelection.IsEmpty()) {
		// Try to select the entry if it's still available
		if (m_ServerCombo.SetCurSel(m_ServerCombo.FindString(-1, sSelection)) == -1) {
			// Otherwise, just reset the text
			m_ServerCombo.SetWindowText(sSelection);
		}
	}

	return true;
}

void CNTMessengerDlg::ErrorMsg(LPTSTR pMsg)
{
	MessageBox(pMsg, _T("Error"), MB_OK | MB_ICONEXCLAMATION);
}

bool CNTMessengerDlg::ParseRecipients(CString& sServer)
{
	// Get all names, separated by ;
	saRecipients.RemoveAll();
	int nPos = -1, nOldPos = 0;
	sServer += ";";
	while ((nPos = sServer.Find(';', nOldPos)) != -1) {
		CString sSingleEntry =  sServer.Mid(nOldPos, nPos - nOldPos);
		if (!sSingleEntry.IsEmpty()) {
			sSingleEntry.TrimLeft();
			sSingleEntry.TrimRight();
			// Add the found name to the recipients list (if not "To all")
			if (sSingleEntry != sAll)
				saRecipients.Add(sSingleEntry);
		}
		nOldPos = nPos + 1;
	}
	return true;
}

void CNTMessengerDlg::OnMultiple() 
{
	CString sServer;

	m_ServerCombo.GetWindowText(sServer);

	if (!ParseRecipients(sServer)) {
		ErrorMsg(_T("Please check blabla"));
		return;
	}

	// Show the multiple recipients dlg
	CMultipleRecipientsDlg dlg;
	dlg.psaServer = &saServer;
	dlg.psaRecipients = &saRecipients;
	dlg.DoModal();
	// If the user added some names to the recipient's list, 
	// show them in the combobox edit line
	CString sWndText;
	for (int i = 0; i < saRecipients.GetSize(); i++) {
		if (!sWndText.IsEmpty()) {
			sWndText += _T("; ");
		}
		sWndText += saRecipients.GetAt(i);
	}

	m_ServerCombo.SetWindowText(sWndText);
	
}

void CNTMessengerDlg::OnSelchangeServercombo() 
{
	// We update the saRecipients string array with the server
	// the user selected
	
	CString sText;
	m_ServerCombo.GetWindowText(sText);
	if (!sText.IsEmpty()) {
		// If "To all" is selected we add all , else we only add the specific one
		saRecipients.RemoveAll();
		if (sText == sAll) {
			/*for (int i = 0; i < m_ServerCombo.GetCount(); i++) {
				m_ServerCombo.GetLBText(i, sText);
				saRecipients.Add(sText);
			}*/
		}
		else {
			saRecipients.Add(sText);
		}
	}
}

void CNTMessengerDlg::OnSend() 
{
	CWaitCursor wait;

	UpdateData();

	CString sServer;

	// Get the server string from the combo box
	int nCurSel = m_ServerCombo.GetCurSel();
	if (nCurSel == -1) {
		m_ServerCombo.GetWindowText(sServer);
	}
	else {
		m_ServerCombo.GetLBText(nCurSel, sServer);
	}

	if (sServer.IsEmpty()) {
		ErrorMsg(_T("Please enter a server-name"));
		return;
	}
	
	NET_API_STATUS nRet;
	
	if (sServer == sAll) {
		saRecipients.RemoveAll();
		sServer = m_sDomain + TEXT("*");
	}
	else {
		// update the recipients list
		if (!ParseRecipients(sServer)) {
			ErrorMsg(_T("Syntax error in the server field."));
		}
	}

	// if the list is empty we add the value that's in the combobox edit line
	if (saRecipients.GetSize() == 0) {
		saRecipients.Add(sServer);
	}
	
	bool bFailed = false;

	for (int i = 0; i < saRecipients.GetSize(); i++) {
		
		CString sHost = saRecipients.GetAt(i);
		
		// TATA!!!
		// Now we can send the message.
		// This is the most important line of the whole thing :-)
		nRet = NetMessageBufferSend(NULL, sHost, m_sName, (LPBYTE)(LPCTSTR)m_sMessageText, m_sMessageText.GetLength() * sizeof(_TCHAR));
		

		switch(nRet)
		{
			case ERROR_ACCESS_DENIED:
				ErrorMsg(_T("You do not have access to the requested function."));
				break;
 
			case ERROR_INVALID_PARAMETER:
				ErrorMsg(_T("ERROR: One of the passed parameters is invalid"));
				break;

			case ERROR_NOT_SUPPORTED:
				ErrorMsg(_T("This network request is not supported"));
				break;

			case NERR_NameNotFound: {
					CString sText = _T("The user name ") + sHost + _T(" could not be found or is not logged in.");
					ErrorMsg((LPTSTR)(LPCTSTR)sText);
				}
				break;
 
			case NERR_NetworkError:
				ErrorMsg(_T("A general failure occurred in the network hardware."));
				break;
 
			case NERR_Success:
				//ErrorMsg(_T("Message successfully sent!"));
				break;

			case NERR_BadReceive: {
					CString sText = _T("The message was sent, but could not be received by the remote host ") + sHost;
					ErrorMsg((LPTSTR)(LPCTSTR)sText);
				}
				break;

			default:
				ErrorMsg(_T("Unknown error"));
		}

		if (nRet != NERR_Success) {
			bFailed = true;
		}

	}

	// If the the msg could be sent to all the recipients and we delete the message
	// text if the user set this in the prefs.
	if (m_bDeleteWhenSent && !bFailed) {
		m_sMessageText.Empty();
		UpdateData(FALSE);
	}
}

void CNTMessengerDlg::OnClose() 
{
	saRecipients.RemoveAll();
	saServer.RemoveAll();
	KillTimer(TimerID);
	m_bClose = true;
	CDialog::OnClose();
}

LRESULT CNTMessengerDlg::OnTrayNotification(WPARAM wParam, LPARAM lParam)
{
	return TrayIcon.OnTrayNotification(wParam, lParam);
}

void CNTMessengerDlg::OnRestore()
{
	ShowWindow(SW_SHOW);
	ShowWindow(SW_RESTORE);
}

void CNTMessengerDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	if (nType == SIZE_MINIMIZED) {
		ShowWindow (SW_HIDE);
	}
}

void CNTMessengerDlg::OnClear() 
{
	// Empty the message window
	m_sMessageText.Empty();
	UpdateData(FALSE);
	// Set the focus to the message window again.
	GetDlgItem(IDC_MESSAGETEXT)->SetFocus();
}

void CNTMessengerDlg::OnOptions() 
{
	COptionsDlg dlg;
	dlg.m_bDeleteWhenSent = m_bDeleteWhenSent;
	dlg.m_bStartMinimized = m_bStartMinimized;
	dlg.m_bRescan = m_bRescan;
	dlg.m_nMinutes = m_nMinutes;
	dlg.m_sPDC = m_sPDC;
	dlg.m_sDomain = m_sDomain;
	if (dlg.DoModal() == IDOK) {
		m_bDeleteWhenSent = dlg.m_bDeleteWhenSent;
		m_bStartMinimized = dlg.m_bStartMinimized;
		m_bRescan = dlg.m_bRescan;
		m_sPDC = dlg.m_sPDC;
		m_sDomain = dlg.m_sDomain;
		if (m_nMinutes != (int)dlg.m_nMinutes) {
			KillTimer(TimerID);
			m_nMinutes = dlg.m_nMinutes;
			RescanTimer();
		}
		m_nMinutes = dlg.m_nMinutes;
	}
}

void CNTMessengerDlg::OnStartup()
{
	if (m_bStartMinimized) {
		ShowWindow(SW_MINIMIZE);
	}
}

void CNTMessengerDlg::RescanTimer()
{
	if (m_bRescan && m_nMinutes > 0) {
		SetTimer(TimerID, m_nMinutes * 1000 * 60, NULL);
	}
	else {
		KillTimer(TimerID);
	}
}

void CNTMessengerDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == TimerID) {
		FillServerCombo();
	}
	CDialog::OnTimer(nIDEvent);
}

BOOL CNTMessengerDlg::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message== WM_LBUTTONDOWN || pMsg->message== WM_LBUTTONUP || pMsg->message== WM_MOUSEMOVE)
		m_ToolTip.RelayEvent(pMsg);
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CNTMessengerDlg::OnAbout() 
{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
}

void CNTMessengerDlg::OnOK() 
{
	// Don't do anything, otherwise pressing return would exit the app
}

void CNTMessengerDlg::OnCancel() 
{
	// If the user wants to close the app we call OnCancel.
	// If the user just pressed Esc we don't close.
	if (m_bClose)	
		CDialog::OnCancel();
}
