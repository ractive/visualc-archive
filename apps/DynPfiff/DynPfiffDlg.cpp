/*************************************************************************
                     DynPfiff
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


// DynPfiffDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DynPfiff.h"
#include "DynPfiffDlg.h"
#include "InternetHelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

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
// CDynPfiffDlg dialog

CDynPfiffDlg::CDynPfiffDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDynPfiffDlg::IDD, pParent), rb("Settings")
{
	//{{AFX_DATA_INIT(CDynPfiffDlg)
	m_sUpdateURL = _T("");
	m_sIP = _T("");
	m_sStatus = _T("");
	m_sHTMLFile = _T("");
	m_sTemplateFile = _T("");
	m_bSendIP = FALSE;
	m_bSetOffline = FALSE;
	m_nMin = 0;
	m_bSound = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	rb.Bind(m_bSendIP, _T("Send IP"), FALSE);
	rb.Bind(m_sHTMLFile, _T("HTML file"), _T(""));
	rb.Bind(m_sTemplateFile,_T("Template file"), _T(""));
	rb.Bind(m_sUpdateURL, _T("Update URL"), _T(""));
	rb.Bind(m_nMin, _T("Repeat"), 0);
	rb.Bind(m_bSound, _T("Sound"), TRUE);

	m_nUpdateTimer = 1;
}

void CDynPfiffDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDynPfiffDlg)
	DDX_Control(pDX, IDC_UPDATEICON, m_UpdateIcon);
	DDX_Control(pDX, IDC_IPS, m_IPCombo);
	DDX_Text(pDX, IDC_UPDATEURL, m_sUpdateURL);
	DDX_CBString(pDX, IDC_IPS, m_sIP);
	DDX_Text(pDX, IDC_STATUS, m_sStatus);
	DDX_Text(pDX, IDC_HTMLFILE, m_sHTMLFile);
	DDX_Text(pDX, IDC_TEMPLATEFILE, m_sTemplateFile);
	DDX_Check(pDX, IDC_SENDIP, m_bSendIP);
	DDX_Check(pDX, IDC_SETOFFLINE, m_bSetOffline);
	DDX_Text(pDX, IDC_MIN, m_nMin);
	DDV_MinMaxUInt(pDX, m_nMin, 0, 360);
	DDX_Check(pDX, IDC_SOUND, m_bSound);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDynPfiffDlg, CDialog)
	//{{AFX_MSG_MAP(CDynPfiffDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_SENDIP, OnSendip)
	ON_BN_CLICKED(IDC_SETOFFLINE, OnSetoffline)
	ON_COMMAND(ID_RESTORE, OnRestore)
	ON_WM_SIZE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_TRAYNOTIFICATION, OnTrayNotification)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDynPfiffDlg message handlers

BOOL CDynPfiffDlg::OnInitDialog()
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	CInternetHelper * pInternetHelper = CInternetHelper::Instance();
	CStringArray saIPs;

	pInternetHelper->SetNotificationWnd(m_hWnd);

	UpdateData(FALSE);

	pInternetHelper->getIPs(&saIPs);
	for (int i = 0; i < saIPs.GetSize(); i++) {
		m_IPCombo.AddString(saIPs.GetAt(i));
	}
	int nCount = -1;
	if (nCount = m_IPCombo.GetCount()) {
		m_IPCombo.SetCurSel(nCount - 1);
	}

	// Trayicon initialization
	TrayIcon.SetMenu(IDR_TRAY);
	TrayIcon.SetNotificationWindow(this, WM_TRAYNOTIFICATION);
	TrayIcon.SetIcon(IDR_MAINFRAME);

	if (m_nMin > 0) {
		SetTimer(m_nUpdateTimer, m_nMin * 1000 * 60, NULL);
	}

	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDynPfiffDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDynPfiffDlg::OnPaint() 
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
HCURSOR CDynPfiffDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDynPfiffDlg::OnUpdate() 
{
	CWaitCursor wait;

	UpdateData();

	if (m_nMin > 0) {
		SetTimer(m_nUpdateTimer, m_nMin * 1000 * 60, NULL);
	}

	CString sURL = m_sUpdateURL;
	BuildURL(sURL);

	m_sStatus.Empty();
	/*ShowWindow(SW_SHOW);
	ShowWindow(SW_RESTORE);*/
	CInternetHelper * pInternetHelper = CInternetHelper::Instance();
	int nRet = 0;
	pInternetHelper->ReadURL(sURL, m_sStatus);

	
	int nStart, nPos;
	TCHAR success[] = _T("SUCCESS");
	TCHAR error[] = _T("ERROR");
	DWORD dwFlags = MB_OK;
	CString sCaption;

	if (nPos = m_sStatus.Find(success) != -1) {
		// Cool. The update was successful.
		// Extract the message
		nStart = m_sStatus.Find(_T("-"), nPos) + 2;
		m_sStatus = m_sStatus.Mid(nStart);

		sCaption = _T("Successful update");
		dwFlags |= MB_ICONINFORMATION;

		m_UpdateIcon.SetIcon(AfxGetApp()->LoadIcon(IDI_SUCCICON));
	}
	else if (nPos = m_sStatus.Find(error) != -1) {
		nStart = m_sStatus.Find(_T("-"), nPos) + 2;
		m_sStatus = m_sStatus.Mid(nStart);

		sCaption = _T("Error during update");
		dwFlags |= MB_ICONSTOP;

		m_UpdateIcon.SetIcon(AfxGetApp()->LoadIcon(IDI_ERRICON));
	}
	else {
		m_UpdateIcon.SetIcon(AfxGetApp()->LoadIcon(IDI_ERRICON));
		if (nRet == 404) {
			m_sStatus = _T("Skript not found! Check the update URL");
		}
		else {
			m_sStatus.Format(_T("Error no. %ud occured"), nRet);
		}
	}

	m_UpdateIcon.ModifyStyle(0, WS_VISIBLE);
	m_UpdateIcon.InvalidateRect(NULL);
	m_UpdateIcon.UpdateWindow();
	if (m_bSound) {
		MessageBeep(MB_OK);
	}
	UpdateData(FALSE);
}

void CDynPfiffDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(m_nUpdateTimer);
	CInternetHelper::Destroy();
	UpdateData();
	CDialog::OnClose();
}


void CDynPfiffDlg::OnSendip() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	static int nOldSelection = m_IPCombo.GetCurSel();
	if (m_bSendIP) {
		// Enable the combobox and select the old selection
		m_IPCombo.ModifyStyle(WS_DISABLED, 0);
		m_IPCombo.SetCurSel(nOldSelection);
	}
	else {
		// Disable the combo box and remove any selection
		m_IPCombo.ModifyStyle(0, WS_DISABLED);
		nOldSelection = m_IPCombo.GetCurSel();
		m_IPCombo.SetCurSel(-1);
	}
}

void CDynPfiffDlg::BuildURL(CString &sURL)
{
	BOOL bParamSet = FALSE;
	if (m_bSetOffline || (!m_sIP.IsEmpty() && m_bSendIP) || !m_sHTMLFile.IsEmpty() || !m_sTemplateFile.IsEmpty()) {
		sURL += _T("?");
	}
	if (m_bSetOffline) {
		sURL += _T("ip=offline");
		bParamSet = TRUE;
	}
	else if (!m_sIP.IsEmpty() && m_bSendIP) {
		sURL += _T("ip=") + m_sIP;
		bParamSet = TRUE;
	}
	
	if (!m_sHTMLFile.IsEmpty()) {
		if (bParamSet)
			sURL += _T("&");
		sURL += _T("htmlfile=") + m_sHTMLFile;
	}
	if (!m_sTemplateFile.IsEmpty()) {
		if (bParamSet)
			sURL += _T("&");
		sURL += _T("template=") + m_sTemplateFile;
	}


}

void CDynPfiffDlg::OnSetoffline() 
{
	UpdateData();
	static int nOldSelection = m_IPCombo.GetCurSel();
	if (!m_bSetOffline) {
		// Enable the combobox and select the old selection
		m_IPCombo.ModifyStyle(WS_DISABLED, 0);
		GetDlgItem(IDC_SENDIP)->ModifyStyle(WS_DISABLED, 0);
		GetDlgItem(IDC_SENDIP)->InvalidateRect(NULL);
		m_IPCombo.SetCurSel(nOldSelection);
	}
	else {
		// Disable the combo box and remove any selection
		m_IPCombo.ModifyStyle(0, WS_DISABLED);
		GetDlgItem(IDC_SENDIP)->ModifyStyle(0, WS_DISABLED);
		GetDlgItem(IDC_SENDIP)->InvalidateRect(NULL);
		nOldSelection = m_IPCombo.GetCurSel();
		m_IPCombo.SetCurSel(-1);
	}
}

LRESULT CDynPfiffDlg::OnTrayNotification(WPARAM wParam, LPARAM lParam)
{
	return TrayIcon.OnTrayNotification(wParam, lParam);
}

void CDynPfiffDlg::OnRestore() 
{
	ShowWindow(SW_SHOW);
	ShowWindow(SW_RESTORE);
}

void CDynPfiffDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	if (nType == SIZE_MINIMIZED) {
		ShowWindow(SW_HIDE);
	}
}

void CDynPfiffDlg::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent == m_nUpdateTimer) {
		TRACE("AUTO-UPDATE\r\n");
		OnUpdate();
	}

	CDialog::OnTimer(nIDEvent);
}
