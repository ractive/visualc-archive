// ConfigNameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NetConfigurator.h"
#include "ConfigNameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigNameDlg dialog


CConfigNameDlg::CConfigNameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigNameDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigNameDlg)
	m_sName = _T("");
	//}}AFX_DATA_INIT
}


void CConfigNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigNameDlg)
	DDX_Text(pDX, IDC_NAME, m_sName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigNameDlg, CDialog)
	//{{AFX_MSG_MAP(CConfigNameDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigNameDlg message handlers
