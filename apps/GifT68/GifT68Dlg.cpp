// GifT68Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "GifT68.h"
#include "GifT68Dlg.h"

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
// CGifT68Dlg dialog

CGifT68Dlg::CGifT68Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGifT68Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGifT68Dlg)
	m_sInputFile = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGifT68Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGifT68Dlg)
	DDX_Control(pDX, IDC_GIFIMAGECONVERTED, m_ConvertedGif);
	DDX_Control(pDX, IDC_GIFIMAGE, m_GifImage);
	DDX_Text(pDX, IDC_GIFFILE, m_sInputFile);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGifT68Dlg, CDialog)
	//{{AFX_MSG_MAP(CGifT68Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN, OnOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGifT68Dlg message handlers

BOOL CGifT68Dlg::OnInitDialog()
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

void CGifT68Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGifT68Dlg::OnPaint() 
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
		/*CPaintDC dc(this);
		
		CRect rc;
		m_GifImage.GetWindowRect(rc);
		int m_nWidthX = m_Picture.m_Width > 131 ? 131 : m_Picture.m_Width;
		int m_nWidthY = m_Picture.m_Height > 131 ? 131 : m_Picture.m_Height;
		rc.right = rc.left + m_nWidthX;
		rc.bottom = rc.top + m_nWidthY;
		m_GifImage.SetWindowPos(NULL, 0, 0, m_nWidthX, m_nWidthY, SWP_NOMOVE | SWP_NOZORDER | SWP_NOREPOSITION);
		m_GifImage.GetClientRect(rc);
		m_Picture.Show(&dc, rc);*/
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGifT68Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CGifT68Dlg::OnOpen() 
{
    OPENFILENAME ofn;
    memset(&ofn, 0, sizeof(ofn));

    // fill OPENFILENAME structure 
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = m_hWnd;
    ofn.lpstrFilter = "GIF files (*.gif)\0*.gif\0All Files (*.*)\0*.*\0\0";
    ofn.lpstrFile = m_sInputFile.GetBuffer(MAX_PATH);
    ofn.lpstrTitle = "Open EMELODY file...";
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = "mp3";

	BOOL bRet = GetOpenFileName(&ofn);
	m_sInputFile.ReleaseBuffer();

    if (bRet) {
		if (!m_Picture.Load(m_sInputFile)) {
			MessageBox("The image could not be loaded!");
		}
		else {
			SetCurrentDirectory("E:\\Eigene Dateien\\VisualC\\GifT68\\");
			
			/*STARTUPINFO sui = {0};
			sui.cb = sizeof(sui);
			sui.lpReserved = NULL;
			sui.lpReserved2 = NULL;
			sui.lpDesktop = NULL;
			sui.lpTitle = NULL;
			PROCESS_INFORMATION pi;

			CString sArgument = "--resize 101x80 --transform-color mt \"" + m_sInputFile + "\" > \"E:\\Eigene Dateien\\T68\\bg_images\\test.gif\"";
			if (CreateProcess("E:\\Eigene Dateien\\VisualC\\GifT68\\gifsicle.exe", (LPTSTR)(LPCTSTR)sArgument, NULL, FALSE, DETACHED_PROCESS, NORMAL_PRIORITY_CLASS, NULL, "E:\\Eigene Dateien\\VisualC\\GifT68\\", &sui, &pi)) {
				while(WaitForSingleObject(pi.hProcess, 500) != WAIT_OBJECT_0) {
					//Pump(m_hWnd);
				}
				DWORD dwReturn;
				GetExitCodeProcess(pi.hProcess, &dwReturn);
			}
			else {
				DWORD dwError = GetLastError();
			}*/


			CString sArgument = "gifsicle --resize 101x80 --transform-color mt \"" + m_sInputFile + "\" > \"E:\\Eigene Dateien\\T68\\bg_images\\test.gif\"";
			//CString sArgument = "\"E:\\Eigene Dateien\\VisualC\\GifT68\\gifsicle\" --resize 101x80 --transform-color mt \"" + m_sInputFile + "\" > \"E:\\Eigene Dateien\\T68\\bg_images\\test.gif\"";
			int ret = system(sArgument);
			sArgument = "gifsicle --batch --color-method diversity \"E:\\Eigene Dateien\\T68\\bg_images\\test.gif\"";
			ret = system(sArgument);

			m_GifImage.Load(m_sInputFile);
			m_GifImage.InvalidateRect(NULL);
			m_GifImage.UpdateWindow();

			m_ConvertedGif.Load("E:\\Eigene Dateien\\T68\\bg_images\\test.gif");
			m_ConvertedGif.InvalidateRect(NULL);
			m_ConvertedGif.UpdateWindow();

			UpdateData(FALSE);
		}

	}

		
}
