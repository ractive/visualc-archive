// ShoppingListDoc.cpp : implementation of the CShoppingListDoc class
//

#include "stdafx.h"
#include "ShoppingList.h"

#include "ShoppingListDoc.h"
#include "ItemDlg.h"
#include "ShopDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CShoppingListDoc

IMPLEMENT_DYNCREATE(CShoppingListDoc, CDocument)

BEGIN_MESSAGE_MAP(CShoppingListDoc, CDocument)
	//{{AFX_MSG_MAP(CShoppingListDoc)
	ON_COMMAND(ID_ADDSHOPPINGITEM, OnAddShoppingItem)
	ON_COMMAND(ID_ADDSHOP, OnAddShop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShoppingListDoc construction/destruction

CShoppingListDoc::CShoppingListDoc()
{
	// TODO: add one-time construction code here

}

CShoppingListDoc::~CShoppingListDoc()
{
	Cleanup();
}

BOOL CShoppingListDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	Cleanup();

	m_saItems.RemoveAll();

	m_saShops.RemoveAll();

	UpdateAllViews(NULL);

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CShoppingListDoc serialization

void CShoppingListDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		//ar << m_saShops;
		//ar << m_saItems;
	}
	else
	{
		// TODO: add loading code here
		//ar >> m_saShops;
		//ar >> m_saItems;
	}

	m_saShops.Serialize(ar);
	m_saItems.Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CShoppingListDoc diagnostics

#ifdef _DEBUG
void CShoppingListDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CShoppingListDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CShoppingListDoc commands

void CShoppingListDoc::OnAddShoppingItem() 
{
	CItemDlg dlg;

	dlg.m_pDoc = this;
	dlg.m_sCurrentShop = m_sCurrentShop;

	if (dlg.DoModal() == IDCANCEL) {
		return;
	}

	m_saItems.Add(dlg.m_sName, dlg.m_sShop, dlg.m_bInCart);
	UpdateAllViews(NULL, ITEM_ADDED);

	SetModifiedFlag();
}

void CShoppingListDoc::OnAddShop() 
{
	CShopDlg dlg;

	if (dlg.DoModal() == IDCANCEL) {
		return;
	}
	
	m_saShops.Add(dlg.m_sShop);

	UpdateAllViews(NULL, SHOP_ADDED);

	SetModifiedFlag();
}

void CShoppingListDoc::Cleanup()
{
	POSITION pos = NULL;

	for( pos = m_saItems.GetHeadPosition(); pos != NULL; ) {
		CShoppingItem *pItem = (CShoppingItem *)m_saItems.GetNext(pos);
		delete pItem;
	}
}
