// LinksDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EMelodyLab.h"
#include "LinksDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLinksDlg dialog


CLinksDlg::CLinksDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLinksDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLinksDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLinksDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLinksDlg)
	DDX_Control(pDX, IDC_EMELODYURL, m_EmelodyUrl);
	DDX_Control(pDX, IDC_MAILURL, m_MailUrl);
	DDX_Control(pDX, IDC_MOBILEHITSURL, m_MobileHitsUrl);
	DDX_Control(pDX, IDC_ERICSSONTONESURL, m_EricssonUrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLinksDlg, CDialog)
	//{{AFX_MSG_MAP(CLinksDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLinksDlg message handlers
