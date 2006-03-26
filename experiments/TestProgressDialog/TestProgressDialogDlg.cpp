// TestProgressDialogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestProgressDialog.h"
#include "TestProgressDialogDlg.h"

#include "ProgressDlg.h"

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


// Static member initialization
HANDLE CTestProgressDialogDlg::m_hStop = NULL;

/////////////////////////////////////////////////////////////////////////////
// CTestProgressDialogDlg dialog

CTestProgressDialogDlg::CTestProgressDialogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestProgressDialogDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestProgressDialogDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestProgressDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestProgressDialogDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestProgressDialogDlg, CDialog)
	//{{AFX_MSG_MAP(CTestProgressDialogDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_STARTTHREAD, OnStartThread)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestProgressDialogDlg message handlers

BOOL CTestProgressDialogDlg::OnInitDialog()
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
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestProgressDialogDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestProgressDialogDlg::OnPaint() 
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
HCURSOR CTestProgressDialogDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestProgressDialogDlg::OnStartThread() 
{
	// Create the stop event.
	m_hStop = CreateEvent(NULL, TRUE, FALSE, NULL);
	
	// Create the progress dialog
	CProgressDlg * pProgressDlg = new CProgressDlg;
	pProgressDlg->Create(IDD_PROGRESSDLG, this);

	// This event will be set if the user cancels the operation
	pProgressDlg->m_hStop = m_hStop;

	DWORD exit;

	threadInfo * pInfo = new threadInfo;
	pInfo->hStop = m_hStop;
	pInfo->hWnd = pProgressDlg->m_hWnd;

	// Start a thread that performs the operation
	CWinThread * pThread = AfxBeginThread(ThreadProc, pInfo, 0, CREATE_SUSPENDED, NULL);
	pThread->m_bAutoDelete = FALSE;
	pThread->ResumeThread();

	// Simulate a modal dialog box
	EnableWindow(FALSE);

	// Wait until the thread ends...
	DWORD dwSigHandle;
	while (dwSigHandle = WaitForSingleObject(pThread->m_hThread, 100)) {
		if (dwSigHandle == WAIT_TIMEOUT) {
			// ...and pump all messages through the progress dialog
			pProgressDlg->Pump();
			continue;
		}
		else if (dwSigHandle - WAIT_OBJECT_0 == 0) {
			break;
		}
	}

	EnableWindow(TRUE);

	// Give the thread one second to clean up
	WaitForSingleObject(pThread->m_hThread, 1000);

	// Get the exit code of the thread
	::GetExitCodeThread(pThread->m_hThread, &exit);
		
	delete pInfo;
	delete pThread;

	// Destroy the progress dialog
	pProgressDlg->DestroyWindow();

	delete pProgressDlg;
}

UINT CTestProgressDialogDlg::ThreadProc(LPVOID lParam)
{
	threadInfo * pInfo = (threadInfo *)lParam;

	CString * pString = new CString;

	// Simulate a lengthy operation
	for (int i = 0; i < 100; i++) {
		// Check if the cancel event was set
		if (WaitForSingleObject(pInfo->hStop, 0) == WAIT_OBJECT_0) {
			// End the thread
			return 1;
		}
		// Here you would do your work...
		Sleep(50);
		// A sample string to pass to the progress dialog
		// This could be any other object of course...
		pString->Format("Progress %d", i);

		// Post an update message to the progress dialog
		::PostMessage(pInfo->hWnd, WM_PROGRESS, (WPARAM)pString, i);
	}
	for (i = 100; i > 0; i--) {
		// Check if the cancel event was set
		if (WaitForSingleObject(pInfo->hStop, 0) == WAIT_OBJECT_0) {
			// End the thread
			return 1;
		}
		// Here you would do your work...
		Sleep(50);
		// A sample string to pass to the progress dialog
		// This could be any other object of course...
		CString * pString = new CString;
		pString->Format("Progress %d", i);

		// Post an update message to the progress dialog
		::PostMessage(pInfo->hWnd, WM_PROGRESS, (WPARAM)pString, i);
	}

	delete pString;

	return 0;
}
