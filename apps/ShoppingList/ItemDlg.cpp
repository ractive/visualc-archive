// ItemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ShoppingList.h"
#include "ItemDlg.h"
#include "ShoppingListDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CItemDlg dialog


CItemDlg::CItemDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CItemDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CItemDlg)
	m_bInCart = FALSE;
	m_sName = _T("");
	m_sShop = _T("");
	//}}AFX_DATA_INIT

	m_pDoc = NULL;
}


void CItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CItemDlg)
	DDX_Control(pDX, IDC_ITEMSHOP, m_ShopCtrl);
	DDX_Check(pDX, IDC_ITEMINCART, m_bInCart);
	DDX_Text(pDX, IDC_ITEMNAME, m_sName);
	DDX_CBString(pDX, IDC_ITEMSHOP, m_sShop);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CItemDlg, CDialog)
	//{{AFX_MSG_MAP(CItemDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CItemDlg message handlers

BOOL CItemDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if (m_pDoc == NULL) {
		return TRUE;
	}
	
	int nSize = m_pDoc->m_saShops.GetSize();

	for (int i = 0; i < nSize; i++) {
		m_ShopCtrl.AddString(m_pDoc->m_saShops.GetAt(i));
	}

	int nFind = m_ShopCtrl.FindString(0, m_sCurrentShop);
	if (nFind != CB_ERR) {
		m_ShopCtrl.SetCurSel(nFind);
	}

	GetDlgItem(IDC_ITEMNAME)->SetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
