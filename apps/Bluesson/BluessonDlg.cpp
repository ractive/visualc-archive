/*************************************************************************
  Bluesson
**************************************************************************

Copyright (C) June 2002 by Jean-Pierre Bergamin

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


// BluessonDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Bluesson.h"
#include "BluessonDlg.h"
#include "WinAmpControl.h"

#define WM_TRAYNOTIFICATION		(WM_USER + 1)
#define WM_STARTUP		(WM_USER + 2)


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
};


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
// CBluessonDlg dialog

CBluessonDlg::CBluessonDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBluessonDlg::IDD, pParent), rb("Bluesson")
{
	//{{AFX_DATA_INIT(CBluessonDlg)
	m_sWinAmpExe = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_bWaitMenuEntry = FALSE;
	m_pAT = NULL;
	
	rb.Bind(m_bFirstStart, "FirstStart", 1);
	rb.Bind(m_nComPort, "ComPort", 1);
	rb.Bind(m_sWinAmpExe, "WinampExe");

	if (m_nComPort == 0) {
		m_nComPort = 1;
	}
}

void CBluessonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBluessonDlg)
	DDX_Control(pDX, IDC_COMPORT, m_ComPortCtrl);
	DDX_Text(pDX, IDC_WINAMPEXE, m_sWinAmpExe);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBluessonDlg, CDialog)
	//{{AFX_MSG_MAP(CBluessonDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_COMMAND(ID_RESTORE, OnRestore)
	ON_BN_CLICKED(IDC_GETWINAMPEXE, OnGetWinAmpExe)
	ON_CBN_SELCHANGE(IDC_COMPORT, OnSelchangeComport)
	ON_BN_CLICKED(IDC_TEST, OnReset)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_COMDAEMON, OnComdaemonMsg)
	ON_MESSAGE(WM_TRAYNOTIFICATION, OnTrayNotification)
	ON_MESSAGE(WM_STARTUP, OnStartup)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBluessonDlg message handlers

BOOL CBluessonDlg::OnInitDialog()
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

	/*CTaskManager task_manager;
	CExeModuleInstance  *pProcess;

	if (task_manager.Populate()) {
		for (unsigned i = 0; i < task_manager.GetProcessCount(); i++) {
			pProcess = task_manager.GetProcessByIndex(i);
			TRACE("%s\r\n", pProcess->Get_Name());
			CString sProcess = pProcess->Get_Name();
			if ((sProcess.Find("EPMWOR~1.EXE") != -1) || (sProcess.Find("epmworker.exe") != -1)) {
				MessageBox("The Ericsson Mobile Phone Monitor is running!\r\n\r\nPlease close all applications that access your mobile phone!\r\nOtherwise the remote control won't work as expected.", "WARNING!", MB_OK | MB_ICONEXCLAMATION);
				break;
			}
		}
	}*/

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


	CWinAmpControl * pWACtrl = CWinAmpControl::GetInstance();

	HINSTANCE hWA = NULL;

	if (!pWACtrl->IsRunning()) {
		if (m_sWinAmpExe.IsEmpty()) {
			// Get a name for a temp file
			LPTSTR tmp = _tempnam(NULL, NULL);
			CString sTmpName = tmp;
			// Fake an mp3 file
			sTmpName += ".mp3";
			delete [] tmp;

			TCHAR app[MAX_PATH];

			try {
				CFile tmpfile;
				// Create the temp file
				if (tmpfile.Open(sTmpName, CFile::modeCreate)) {
					// Find the associated app for mp3 files
					HINSTANCE h = FindExecutable(sTmpName, NULL, app);
					tmpfile.Close();
					// Delete the temp file
					CFile::Remove(sTmpName);

					m_sWinAmpExe = app;
					if (m_sWinAmpExe.Right(10) != "Winamp.exe") {
						m_sWinAmpExe.Empty();
					}
				}
			}
			catch (CFileException * pEx) {
				pEx->Delete();
			}
			hWA = ShellExecute(NULL, "open", m_sWinAmpExe, NULL, NULL, SW_SHOW);
		}
		else {
			hWA = ShellExecute(NULL, "open", m_sWinAmpExe, NULL, NULL, SW_SHOW);
		}
		
		if (!hWA) {
			MessageBox("Winamp could not be started!\r\n\r\nMake sure that the path to the executable file is correct!", "Error", MB_OK | MB_ICONEXCLAMATION);
		}
	}
	

	m_pAT = new CEricssonAT();
	
	m_bInit = TRUE;
	
	int nEntry = 0;

	// Fill the COM-Port drop down list
	for (int i = 1; i <= 16; i++) {
		CString sPort;
		sPort.Format("COM %d", i);
		int nAdded = m_ComPortCtrl.AddString(sPort);
		if (i == m_nComPort) {
			nEntry = nAdded;
		}
		m_ComPortCtrl.SetItemData(nAdded, i);
	}

	m_ComPortCtrl.SetCurSel(nEntry);

	m_bInit = FALSE;

	TrayIcon.SetMenu(IDR_TRAY);
	TrayIcon.SetNotificationWindow(this, WM_TRAYNOTIFICATION);

	ShowTrayIcon(TRUE);

	UpdateData(FALSE);

	PostMessage(WM_STARTUP);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBluessonDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CBluessonDlg::OnDestroy()
{
	WinHelp(0L, HELP_QUIT);
	if (m_pAT) {
		m_pAT->KillComDaemon();
		m_pAT->ClosePort();

		delete m_pAT;
		m_pAT = NULL;
	}

	CWinAmpControl::Destroy();

	TrayIcon.KillAnimationThread();

	TrayIcon.RemoveIcon();

	CDialog::OnDestroy();
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBluessonDlg::OnPaint() 
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
HCURSOR CBluessonDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CBluessonDlg::OnComdaemonMsg(UINT pParam, long lParam) 
{
	if (lParam == COMACTIVITY) {
		CString sStatus;
		sStatus = m_wndStatusBar.GetPaneText(0);
		try {
			if (!m_pAT->Receive(sStatus)) {
				MessageBox("The phone reported an Error", "Error", MB_OK | MB_ICONEXCLAMATION);
			}
		}
		catch (CProtException *pEx) {
			pEx->Delete();

		}

		m_wndStatusBar.SetPaneText(0, sStatus);
	}
}


LRESULT CBluessonDlg::OnTrayNotification(WPARAM wParam, LPARAM lParam)
{
	return TrayIcon.OnTrayNotification(wParam, lParam);
}

LRESULT CBluessonDlg::OnStartup(WPARAM wParam, LPARAM lParam)
{
	if (m_bFirstStart) {
		m_bFirstStart = FALSE;
		CAboutDlg dlg;
		dlg.DoModal();
	}
	return StartCommunication();
}

void CBluessonDlg::ShowTrayIcon(BOOL bShow)
{
	TrayIcon.KillAnimationThread();
	if (bShow) {
		TrayIcon.SetIcon(IDR_MAINFRAME);
	}
	else {
		TrayIcon.RemoveIcon();
	}
}

void CBluessonDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	CDialog::OnSize(nType, cx, cy);
	if (nType == SIZE_MINIMIZED) {
		// Hide the window if we have a tray icon.
		if (TrayIcon.IsSet()) {
			ShowTaskIcon(false);
		}
	}
}

void CBluessonDlg::ShowTaskIcon(bool bShow /* = true */)
{
	ShowWindow(bShow ? SW_SHOW : SW_HIDE);
}


void CBluessonDlg::OnRestore() 
{
	ShowTaskIcon(true);	
	ShowWindow(SW_RESTORE);
}

void CBluessonDlg::OnCancel() 
{
	if (MessageBox("Do you really want to quit the application?\r\n\r\nMinimize it to send it to the tray.", "Quit", MB_YESNO | MB_ICONQUESTION) == IDNO) {
		return;
	}
	
	CDialog::OnCancel();
}

void CBluessonDlg::OnOK() 
{
	if (MessageBox("Do you really want to quit the application?\r\n\r\nMinimize it to send it to the tray.", "Quit", MB_YESNO | MB_ICONQUESTION) == IDNO) {
		return;
	}
	CDialog::OnOK();
}

void CBluessonDlg::OnGetWinAmpExe() 
{
	TCHAR szFileName[MAX_PATH] = "";

    OPENFILENAME ofn;
    memset(&ofn, 0, sizeof(ofn));

    // fill OPENFILENAME structure 
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = m_hWnd;
    ofn.lpstrFilter = "WinAmp executable (Winamp.exe)\0winamp.exe;*.exe\0All Files (*.*)\0*.*\0\0";
    ofn.lpstrFile = szFileName;
    ofn.lpstrTitle = "Select WinAmp program file";
    ofn.nMaxFile = 256;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = "exe";


    if(GetOpenFileName(&ofn)) {
		m_sWinAmpExe = szFileName;
		UpdateData(FALSE);
	}
	
}

void CBluessonDlg::OnSelchangeComport() 
{
	if (m_bInit) {
		return;
	}

	CString sStatus;

	try {
		int nSel = m_ComPortCtrl.GetCurSel();
		int nSelPort = m_ComPortCtrl.GetItemData(nSel);

		if (nSelPort != m_pAT->m_nComPort) {
			m_nComPort = nSelPort;
			m_pAT->m_nComPort = m_nComPort;
			m_pAT->ClosePort();
			m_pAT->KillComDaemon();
		}
	}
	catch (CProtException * pEx) {
		sStatus = "The com-port could not be closed!";
		MessageBox(sStatus, "Error", MB_OK | MB_ICONEXCLAMATION);
		pEx->Delete();
	}

	StartCommunication();

	if (m_pAT->PortIsOpen()) {
		sStatus.Format("COM %d opened", m_pAT->m_nComPort);
	}
}

BOOL CBluessonDlg::StartCommunication()
{
	CString sStatus = "No port opened";

	try {
		m_wndStatusBar.SetPaneText(0, "Opening COM-Port");
		CWaitCursor wait;
		m_pAT->OpenPort(m_nComPort);
		m_pAT->CreateComDaemon(m_hWnd);
		m_pAT->UnleashDaemon();
		m_pAT->CheckForPhone();
	}
	catch (CProtException * pEx) {
		pEx->Delete();
		sStatus.Format("COM %d could not be opened!", m_pAT->m_nComPort);
		MessageBox("The COM-Port could not be opened!", "ERROR", MB_OK | MB_ICONEXCLAMATION);
	}
	
	if (m_pAT->PortIsOpen()) {
		sStatus.Format("COM %d opened", m_pAT->m_nComPort);
		m_wndStatusBar.SetPaneText(0, sStatus);
	}

	m_wndStatusBar.SetPaneText(0, sStatus);

	return TRUE;
}

void CBluessonDlg::OnReset() 
{
	CString sStatus;

	try {
		m_pAT->ClosePort();
		m_pAT->KillComDaemon();
	}
	catch (CProtException * pEx) {
		sStatus = "The com-port could not be closed!";
		MessageBox(sStatus, "Error", MB_OK | MB_ICONEXCLAMATION);
		pEx->Delete();
	}

	StartCommunication();

	if (m_pAT->PortIsOpen()) {
		sStatus.Format("COM %d opened", m_pAT->m_nComPort);
	}
}


//DEL void CBluessonDlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
//DEL {
//DEL 	// TODO: Add your message handler code here and/or call default
//DEL 	
//DEL 	CDialog::OnKeyUp(nChar, nRepCnt, nFlags);
//DEL }
