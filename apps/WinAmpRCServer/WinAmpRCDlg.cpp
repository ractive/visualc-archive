// WinAmpRCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WinAmpRC.h"
#include "WinAmpRCDlg.h"
#include "WinAmpControl.h"

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
// CWinAmpRCDlg dialog

CWinAmpRCDlg::CWinAmpRCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWinAmpRCDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWinAmpRCDlg)
	m_nPort = 4444;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_bConnected = FALSE;
	m_bConnectionAccepted = FALSE;
}

void CWinAmpRCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWinAmpRCDlg)
	DDX_Text(pDX, IDC_PORT, m_nPort);
	//}}AFX_DATA_MAP

	if (m_bConnected) {
		GetDlgItem(IDC_STOP)->EnableWindow(TRUE);
		GetDlgItem(IDC_LISTEN)->EnableWindow(FALSE);
	}
	else {
		GetDlgItem(IDC_STOP)->EnableWindow(FALSE);
		GetDlgItem(IDC_LISTEN)->EnableWindow(TRUE);
	}
}

BEGIN_MESSAGE_MAP(CWinAmpRCDlg, CDialog)
	//{{AFX_MSG_MAP(CWinAmpRCDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LISTEN, OnListen)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_STOP, OnStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinAmpRCDlg message handlers

BOOL CWinAmpRCDlg::OnInitDialog()
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


	m_ListenSocket.SetParent(this);
	m_ConnectSocket.SetParent(this);

	OnListen();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWinAmpRCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CWinAmpRCDlg::OnPaint() 
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
HCURSOR CWinAmpRCDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CWinAmpRCDlg::OnListen() 
{
	UpdateData();

	if (!m_bConnected) {

		if (!m_ListenSocket.Create(m_nPort/*, SOCK_DGRAM, FD_READ | FD_WRITE | FD_CONNECT | FD_ACCEPT | FD_CLOSE, NULL*/)) {
			int nError = m_ConnectSocket.GetLastError();
		}
		if (!m_ListenSocket.Listen()) {
			int nError = m_ConnectSocket.GetLastError();
		}
		else {
			m_bConnected = true;
		}
	}

	UpdateData(FALSE);

	/*char xxx[] = "alskdjf";
	if (m_Socket.SendTo(xxx, 7, m_nPort) < 0) {
		int nError = m_Socket.GetLastError();
	}*/
}

void CWinAmpRCDlg::OnAccept()
{
	if (m_bConnectionAccepted) {
		m_ConnectSocket.Close();
	}

	m_ListenSocket.Accept(m_ConnectSocket);
	m_bConnectionAccepted = TRUE;
}

void CWinAmpRCDlg::OnCloseSocket()
{
	if (m_bConnectionAccepted) {
		m_ConnectSocket.Close();
		m_bConnectionAccepted = FALSE;
	}
	else {
		MessageBox("Es besteht keine Verbindung!", "Fehler", MB_OK | MB_ICONEXCLAMATION);
	}
}


void CWinAmpRCDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	m_ConnectSocket.Close();
	m_ListenSocket.Close();
	CWinAmpControl::Destroy();	
}

void CWinAmpRCDlg::OnStop() 
{
	if (m_bConnectionAccepted) {
		m_ConnectSocket.Close();
		m_bConnectionAccepted = FALSE;
	}
	if (m_bConnected) {
		m_ListenSocket.Close();
		m_bConnected = FALSE;
	}

	UpdateData(FALSE);
}

void CWinAmpRCDlg::SendInfo()
{
	if (m_bConnectionAccepted) {
		CWinAmpControl * pWA = CWinAmpControl::GetInstance();
		CString sSong = pWA->GetCurrentSong();
		sSong += "\r\n\r\n";
		m_ConnectSocket.Send(sSong, sSong.GetLength());
	}
}

void CWinAmpRCDlg::SendInfoEx()
{
	if (m_bConnectionAccepted) {
		CWinAmpControl * pWACtrl = CWinAmpControl::GetInstance();
		CString sArtist;
		CString sTitle = pWACtrl->GetCurrentSong(&sArtist);
		CString sInfo;
		sInfo.Format("Interpret: %s\r\nTitle: %s\r\nLänge: %s\r\nSamplingrate: %d\r\nBitrate: %d\r\nKanäle: %d\r\n\r\n", sArtist, sTitle, pWACtrl->GetSongLength(), pWACtrl->GetSampleRate(), pWACtrl->GetBitRate(), pWACtrl->GetChannels());

		m_ConnectSocket.Send(sInfo, sInfo.GetLength());
	}

}
