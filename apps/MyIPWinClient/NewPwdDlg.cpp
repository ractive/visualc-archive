// NewPwdDlg.cpp : implementation file
//

#include "stdafx.h"
#include "myipwinclient.h"
#include "NewPwdDlg.h"
#include "MyIPWinClientDlg.h"
#include "MyIPHelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewPwdDlg dialog


CNewPwdDlg::CNewPwdDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewPwdDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewPwdDlg)
	m_NewPwd = _T("");
	m_NewPwd2 = _T("");
	//}}AFX_DATA_INIT
}


void CNewPwdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewPwdDlg)
	DDX_Text(pDX, IDC_NEWPWD, m_NewPwd);
	DDX_Text(pDX, IDC_NEWPWD2, m_NewPwd2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewPwdDlg, CDialog)
	//{{AFX_MSG_MAP(CNewPwdDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewPwdDlg message handlers

void CNewPwdDlg::OnOK() 
{
	UpdateData();
	if (m_NewPwd.IsEmpty()) {
		MessageBox(_T("Please enter a password"), _T("Password not entered"), MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	if (m_NewPwd != m_NewPwd2) {
		MessageBox(_T("The passwords aren't the same, please reenter"), _T("Password missmatch"), MB_OK | MB_ICONEXCLAMATION);
		m_NewPwd = m_NewPwd2 = "";
		UpdateData(FALSE);
		GetDlgItem(IDC_NEWPWD)->SetFocus();
		return;
	}
	
	CMyIPHelper * pMyIPHelper = CMyIPHelper::Instance();
	
	// Try to change the pwd on www.myip.org
	if (!pMyIPHelper->ChangePwd(m_pParent->m_sUsername, m_pParent->m_sPassword, m_NewPwd)) {
		// If it wasn't successful, we don't quit the dialog and give an error message
		MessageBox(_T("The password couldn't be changed"), _T("Error"), MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	CDialog::OnOK();
}

BOOL CNewPwdDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_pParent = (CMyIPWinClientDlg *)GetParent();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
