// SyncProgressDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FTPSync.h"
#include "SyncProgressDlg.h"
#include "FTPSyncDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CSyncProgressDlg dialog


CSyncProgressDlg::CSyncProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSyncProgressDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSyncProgressDlg)
	m_sUploadFile = _T("");
	m_sDownloadFile = _T("");
	m_sOverall = _T("");
	//}}AFX_DATA_INIT
}


void CSyncProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSyncProgressDlg)
	DDX_Control(pDX, IDC_UPLOADPROGRESS, m_UploadProgressCtrl);
	DDX_Control(pDX, IDC_DOWNLOADPROGRESS, m_DownloadProgressCtrl);
	DDX_Text(pDX, IDC_UPLOADFILE, m_sUploadFile);
	DDX_Text(pDX, IDC_DOWNLOADFILE, m_sDownloadFile);
	DDX_Text(pDX, IDC_OVERALL, m_sOverall);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSyncProgressDlg, CDialog)
	//{{AFX_MSG_MAP(CSyncProgressDlg)
	ON_WM_CANCELMODE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_SYNCFILES, OnSyncFiles)
	ON_MESSAGE(WM_DOWNLOADFILE, OnDownloadFile)
	ON_MESSAGE(WM_UPLOADFILE, OnUploadFile)
	ON_MESSAGE(WM_UPLOADDONE, OnUploadDone)
	ON_MESSAGE(WM_DOWNLOADDONE, OnDownloadDone)
	ON_MESSAGE(WM_STARTSYNC, OnStartSync)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSyncProgressDlg message handlers

BOOL CSyncProgressDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSyncProgressDlg::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
}

LRESULT CSyncProgressDlg::OnSyncFiles(WPARAM wParam, LPARAM lParam)
{
	if (wParam == -1 && lParam == -1) {
		m_sOverall = "Getting directory content...";
	}
	else {
		m_UploadProgressCtrl.SetRange32(0, wParam);
		m_UploadProgressCtrl.SetStep(1);
		
		m_DownloadProgressCtrl.SetRange32(0, lParam);
		m_DownloadProgressCtrl.SetStep(1);

		m_sOverall.Format("Uplods: %d, Downloads: %d", wParam, lParam);
	}

	UpdateData(FALSE);

	return 0;	
}

LRESULT CSyncProgressDlg::OnUploadFile(WPARAM wParam, LPARAM lParam)
{
	CString * pFileName = (CString *)lParam;

	m_sUploadFile = *pFileName;

	delete pFileName;

	m_UploadProgressCtrl.StepIt();

	UpdateData(FALSE);

	return 0;	
}

LRESULT CSyncProgressDlg::OnDownloadFile(WPARAM wParam, LPARAM lParam)
{
	CString * pFileName = (CString *)lParam;

	m_sDownloadFile = *pFileName;

	delete pFileName;

	m_DownloadProgressCtrl.StepIt();

	UpdateData(FALSE);

	return 0;	
}

LRESULT CSyncProgressDlg::OnUploadDone(WPARAM wParam, LPARAM lParam)
{
	m_sUploadFile = "Files uploaded!";

	UpdateData(FALSE);

	return 0;	
}

LRESULT CSyncProgressDlg::OnDownloadDone(WPARAM wParam, LPARAM lParam)
{
	m_sDownloadFile = "Files downloaded!";

	UpdateData(FALSE);

	return 0;	
}

LRESULT CSyncProgressDlg::OnStartSync(WPARAM wParam, LPARAM lParam)
{
	CString * pFtp = (CString *)wParam;

	SetWindowText("Synchronising with " + *pFtp);

	delete pFtp;

	return 0;	
}


BOOL CSyncProgressDlg::Pump()
{
	MSG msg;

	// Retrieve and dispatch any waiting messages.

	while (::PeekMessage (&msg, NULL, 0, 0, PM_NOREMOVE)) {
		if (!AfxGetApp ()->PumpMessage ()) {
			::PostQuitMessage (0);
			return FALSE;
		}
	}
	return TRUE;
}


void CSyncProgressDlg::OnCancel() 
{
	SetEvent(m_hStop);
}
