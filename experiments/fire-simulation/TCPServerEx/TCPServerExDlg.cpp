// TCPServerExDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TCPServerEx.h"
#include "TCPServerExDlg.h"
#include "ServerSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTCPServerExDlg dialog

CTCPServerExDlg::CTCPServerExDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTCPServerExDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTCPServerExDlg)
	m_nPort = 1500;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pServerSocket = NULL;
}

void CTCPServerExDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCPServerExDlg)
	DDX_Control(pDX, IDC_STOP, m_StopCtrl);
	DDX_Control(pDX, IDC_LISTEN, m_ListenCtrl);
	DDX_Text(pDX, IDC_PORT, m_nPort);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCPServerExDlg, CDialog)
	//{{AFX_MSG_MAP(CTCPServerExDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LISTEN, OnListen)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCPServerExDlg message handlers

BOOL CTCPServerExDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTCPServerExDlg::OnPaint() 
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
HCURSOR CTCPServerExDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTCPServerExDlg::OnListen() 
{
	m_ListenCtrl.EnableWindow(FALSE);
	m_StopCtrl.EnableWindow(TRUE);
	
	UpdateData();
	
	if (!m_pServerSocket) {
		m_pServerSocket = new CServerSocket;
	}

	m_pServerSocket->Create(m_nPort);
	m_pServerSocket->Bind(m_nPort);
	DWORD dwSet = 1;
	/*if (!m_pServerSocket->IOCtl(FIONBIO, &dwSet)) {
		DWORD dwError = GetLastError();
	}*/

	m_pServerSocket->Listen();
}

void CTCPServerExDlg::OnStop() 
{
	m_ListenCtrl.EnableWindow(TRUE);
	m_StopCtrl.EnableWindow(FALSE);

	m_pServerSocket->Close();
	delete m_pServerSocket;
	m_pServerSocket = NULL;
}
