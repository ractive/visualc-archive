// FirstSyncDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FTPSync.h"
#include "FirstSyncDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFirstSyncDlg dialog


CFirstSyncDlg::CFirstSyncDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFirstSyncDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFirstSyncDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFirstSyncDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFirstSyncDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFirstSyncDlg, CDialog)
	//{{AFX_MSG_MAP(CFirstSyncDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFirstSyncDlg message handlers

void CFirstSyncDlg::OnOK() 
{
	if (((CButton *)GetDlgItem(IDC_REPLACEFTP))->GetCheck() == 1) {
		EndDialog(IDC_REPLACEFTP);
		return;
	}

	if (((CButton *)GetDlgItem(IDC_REPLACELOCAL))->GetCheck() == 1) {
		EndDialog(IDC_REPLACELOCAL);
		return;
	}
	
	CDialog::OnOK();
}

BOOL CFirstSyncDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	((CButton *)GetDlgItem(IDC_REPLACEFTP))->SetCheck(1);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
