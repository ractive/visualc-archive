// mRouterControlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mRouterControl.h"
#include "mRouterControlDlg.h"

#include "common.h" 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_TASKS  256

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
// CMRouterControlDlg dialog

CMRouterControlDlg::CMRouterControlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMRouterControlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMRouterControlDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMRouterControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMRouterControlDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMRouterControlDlg, CDialog)
	//{{AFX_MSG_MAP(CMRouterControlDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_KILL, OnKill)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMRouterControlDlg message handlers

BOOL CMRouterControlDlg::OnInitDialog()
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

void CMRouterControlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMRouterControlDlg::OnPaint() 
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
HCURSOR CMRouterControlDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMRouterControlDlg::OnKill() 
{
	BOOL        ForceKill;
	DWORD       pid;
	CHAR        pname[MAX_PATH];
	TASK_LIST   tlist[MAX_TASKS]; 

    DWORD             i;     
	DWORD             numTasks;     
	TASK_LIST_ENUM    te;     
	int               rval = 0;     
	char              tname[PROCESS_SIZE];     
	LPSTR             p;     
	DWORD             ThisPid;     
	OSVERSIONINFO     verInfo = {0};     
	LPGetTaskList     GetTaskList;     
	LPEnableDebugPriv EnableDebugPriv; 	

    //     // Determine what system we're on and do the right thing    
	//     
	verInfo.dwOSVersionInfoSize = sizeof (verInfo);     
	GetVersionEx(&verInfo);      
	switch (verInfo.dwPlatformId) {     
	case VER_PLATFORM_WIN32_NT:        
		GetTaskList     = GetTaskListNT;        
		EnableDebugPriv = EnableDebugPrivNT;        
		break;      
	case VER_PLATFORM_WIN32_WINDOWS:        
		GetTaskList = GetTaskList95;        
		EnableDebugPriv = EnableDebugPriv95;        
		break;      
	default:        
		printf ("tlist requires Windows NT or Windows 95\n");        
		return;     
	} 

	numTasks = GetTaskList( tlist, MAX_TASKS ); 

	//     
	// enumerate all windows and try to get the window     
	// titles for each task     
	//     
	te.tlist = tlist;     
	te.numtasks = numTasks;     
	GetWindowTitles( &te );      
	ThisPid = GetCurrentProcessId();      
	for (i=0; i<numTasks; i++) {         
		//         
		// this prevents the user from killing KILL.EXE and         
		// it's parent cmd window too         
		//         
		if (ThisPid == tlist[i].dwProcessId) {             
			continue;         
		}
		if (MatchPattern( tlist[i].WindowTitle, "*KILL*" )) {             
			continue;         
		}    
		tname[0] = 0;         
		strcpy( tname, tlist[i].ProcessName );
        p = strchr( tname, '.' );
		if (p) {
			p[0] = '\0';
        }
		if (MatchPattern( tname, pname )) {
			tlist[i].flags = TRUE;
        }
		else if (MatchPattern( tlist[i].ProcessName, pname )) {
			tlist[i].flags = TRUE;
		}
		else if (MatchPattern( tlist[i].WindowTitle, pname )) {
			tlist[i].flags = TRUE;         
		}
    }
	
	for (i=0; i<numTasks; i++) {
		if (tlist[i].flags) {
			if (KillProcess( &tlist[i], ForceKill )) {
				printf( "process #%d [%s] killed\n", tlist[i].dwProcessId, tlist[i].ProcessName );
			}
			else {
				printf( "process #%d [%s] could not be killed\n", tlist[i].dwProcessId, tlist[i].ProcessName );
				rval = 1;
			}
		}
	} 
}
