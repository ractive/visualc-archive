// ConflictDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FTPSync.h"
#include "ConflictDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConflictDlg dialog


CConflictDlg::CConflictDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConflictDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConflictDlg)
	m_nUpload = -1;
	m_sFile = _T("");
	//}}AFX_DATA_INIT
}


void CConflictDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConflictDlg)
	DDX_Radio(pDX, IDC_CONFLICTUPLOAD, m_nUpload);
	DDX_Text(pDX, IDC_FILE, m_sFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConflictDlg, CDialog)
	//{{AFX_MSG_MAP(CConflictDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConflictDlg message handlers

void CConflictDlg::OnOK() 
{
	if (m_nUpload == 0) {
		EndDialog(IDC_CONFLICTUPLOAD);
		return;
	}
	else {
		EndDialog(IDC_CONFLICTDOWNLOAD);
		return;
	}

	CDialog::OnOK();
}

BOOL CConflictDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_nUpload = 0;

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
