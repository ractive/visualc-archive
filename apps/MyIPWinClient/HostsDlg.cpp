// HostsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "myipwinclient.h"
#include "MyIPWinClientDlg.h"
#include "HostsDlg.h"
#include "MyIPHelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHostsDlg dialog


CHostsDlg::CHostsDlg(CWnd* pParent /*=NULL*/)
	: CToolTipDlg(CHostsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHostsDlg)
	m_sNewHost = _T("");
	m_sHost = _T("");
	//}}AFX_DATA_INIT
}


void CHostsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHostsDlg)
	DDX_Control(pDX, IDC_HOSTS, m_HostCombo);
	DDX_Text(pDX, IDC_NEWHOSTNAME, m_sNewHost);
	DDX_CBString(pDX, IDC_HOSTS, m_sHost);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHostsDlg, CDialog)
	//{{AFX_MSG_MAP(CHostsDlg)
	ON_BN_CLICKED(IDC_DEL, OnDel)
	ON_BN_CLICKED(IDC_NEW, OnNew)
	ON_BN_CLICKED(IDC_IMPORT, OnImport)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHostsDlg message handlers

void CHostsDlg::OnDel() 
{
	UpdateData();

	if (!m_pHostMgr->DeleteHost(m_sHost)) {
		return;
	}
	
	FillHostCombo();

}

void CHostsDlg::OnNew() 
{
	UpdateData();		

	if (!m_pHostMgr->AddNewHost(m_sNewHost)) {
		return;
	}

	FillHostCombo();
}

BOOL CHostsDlg::OnInitDialog() 
{
	CToolTipDlg::OnInitDialog();
	FillHostCombo();

	AddTool(GetDlgItem(IDC_HOSTS), _T("Choose the host you want to delete form www.myip.org"));
	AddTool(GetDlgItem(IDC_DEL), _T("Delete the choosen host"));
	AddTool(GetDlgItem(IDC_NEWHOSTNAME), _T("Enter the new hostname you want to create and hit \"Add new Host\""));
	AddTool(GetDlgItem(IDC_NEW), _T("Add the new host on www.myip.org"));
	AddTool(GetDlgItem(IDC_IMPORT), _T("Get your hostlist form www.myip.org"));


	Activate(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CHostsDlg::FillHostCombo()
{
	m_HostCombo.ResetContent();
	for (int i = 0; i < m_pHostMgr->GetSize(); i++) {
		m_HostCombo.AddString(m_pHostMgr->GetHost(i));	
	}
	m_HostCombo.SetCurSel(0);
}

void CHostsDlg::OnImport() 
{
	// Try to import the current settings form www.myip.org
	if (!m_pHostMgr->Import()) {
		return;
	}

	// If is was successful, we refill the combobox.
	FillHostCombo();
}
