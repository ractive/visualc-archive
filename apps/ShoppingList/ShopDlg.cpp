// ShopDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ShoppingList.h"
#include "ShopDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShopDlg dialog


CShopDlg::CShopDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShopDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShopDlg)
	m_sShop = _T("");
	//}}AFX_DATA_INIT
}


void CShopDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShopDlg)
	DDX_Text(pDX, IDC_SHOPNAME, m_sShop);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShopDlg, CDialog)
	//{{AFX_MSG_MAP(CShopDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShopDlg message handlers
