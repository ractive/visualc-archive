// ProgressDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestProgressDialog.h"
#include "ProgressDlg.h"
#include "md5.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgressDlg dialog


CProgressDlg::CProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProgressDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProgressDlg)
	m_sText = _T("");
	//}}AFX_DATA_INIT
	FILE * test;
	ifstream file("C:\\divx.log");
	//test = fopen("C:\\PPM.LOG", "r");
	MD5 context(file);
	//fclose(test);
	TRACE("OUTPUT: %s", context.hex_digest());
}


void CProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProgressDlg)
	DDX_Control(pDX, IDC_PROGRESS1, m_ProgressCtrl);
	DDX_Text(pDX, IDC_SOMETEXT, m_sText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProgressDlg, CDialog)
	//{{AFX_MSG_MAP(CProgressDlg)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_PROGRESS, OnProgress)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgressDlg message handlers

BOOL CProgressDlg::Pump()
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

LRESULT CProgressDlg::OnProgress(WPARAM wParam, LPARAM lParam)
{
	// Here we update the dialog
	// We end here as a result of a WM_PROGRESS message
	m_ProgressCtrl.SetPos(lParam);
	if (wParam) {
		CString * pString = (CString *)wParam;
		m_sText = *pString;
		UpdateData(FALSE);
		delete pString;
	}

	return 1;
}

void CProgressDlg::OnStop() 
{
	// Set the stop event. This will force the thread to end
	SetEvent(m_hStop);
}
