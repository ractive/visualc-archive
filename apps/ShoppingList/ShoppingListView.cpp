// ShoppingListView.cpp : implementation of the CShoppingListView class
//

#include "stdafx.h"
#include "ShoppingList.h"

#include "ShoppingListDoc.h"
#include "ShoppingListView.h"
#include "ShoppingItems.h"
#include "ItemDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShoppingListView

IMPLEMENT_DYNCREATE(CShoppingListView, CListView)

BEGIN_MESSAGE_MAP(CShoppingListView, CListView)
	//{{AFX_MSG_MAP(CShoppingListView)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShoppingListView construction/destruction

CShoppingListView::CShoppingListView()
{
	// TODO: add construction code here
	m_bHeaderInit = FALSE;

}

CShoppingListView::~CShoppingListView()
{
}

BOOL CShoppingListView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style |= LVS_REPORT | LVS_SHOWSELALWAYS;

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CShoppingListView drawing

void CShoppingListView::OnDraw(CDC* pDC)
{
	CShoppingListDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

void CShoppingListView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	if (!m_bHeaderInit) {
		CListCtrl &listCtrl = GetListCtrl();

		DWORD dwExStyle = listCtrl.GetExtendedStyle();
		listCtrl.SetExtendedStyle(dwExStyle | LVS_EX_INFOTIP |LVS_EX_FULLROWSELECT);

		listCtrl.InsertColumn(0, "Shopping item", LVCFMT_LEFT, 300, 0);	
		listCtrl.InsertColumn(1, "Shop", LVCFMT_LEFT, 250, 1);

		m_bHeaderInit = TRUE;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CShoppingListView diagnostics

#ifdef _DEBUG
void CShoppingListView::AssertValid() const
{
	CListView::AssertValid();
}

void CShoppingListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CShoppingListDoc* CShoppingListView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CShoppingListDoc)));
	return (CShoppingListDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CShoppingListView message handlers
void CShoppingListView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//TODO: add code to react to the user changing the view style of your window
}

void CShoppingListView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if (lHint == SHOP_ADDED) {
		return;
	}

	CListCtrl &list = GetListCtrl();

	CShoppingListDoc * pDoc = GetDocument();
	
	if (pDoc->m_saItems.GetCount() == 0) {
		list.DeleteAllItems();
		return;
	}
	
	SetRedraw(FALSE);

	LVITEM lvi;

	if (lHint == ITEM_ADDED) {
		CShoppingItem * pItem = (CShoppingItem *)pDoc->m_saItems.GetTail();

		if (pItem->m_sShop == pDoc->m_sCurrentShop) {
			lvi.mask = LVIF_TEXT | LVIF_PARAM;
			lvi.lParam = (LPARAM)pItem;
			lvi.iItem = list.GetItemCount();
			lvi.iSubItem = 0;
			lvi.cchTextMax = 256;
			lvi.pszText = (LPTSTR)(LPCTSTR)pItem->m_sName;
			if (list.InsertItem(&lvi) == -1) {
				return;
			}

			lvi.mask = LVIF_TEXT;
			lvi.cchTextMax = 256;
			lvi.iSubItem = 1;
			lvi.pszText = (LPTSTR)(LPCTSTR)pItem->m_sShop;

			list.SetItem(&lvi);
		}
	}
	else {
		list.DeleteAllItems();

		POSITION pos = NULL;

		int i = 0;
		for( pos = pDoc->m_saItems.GetHeadPosition(); pos != NULL; ) {
			
			CShoppingItem* pItem = (CShoppingItem *)pDoc->m_saItems.GetNext(pos);

			if (pItem->m_sShop == pDoc->m_sCurrentShop) {
				lvi.mask = LVIF_TEXT | LVIF_PARAM;
				lvi.lParam = (LPARAM)pItem;
				lvi.iItem = i++;
				lvi.iSubItem = 0;
				lvi.cchTextMax = 256;
				lvi.pszText = (LPTSTR)(LPCTSTR)pItem->m_sName;
				if (list.InsertItem(&lvi) == -1) {
					return;
				}

				lvi.mask = LVIF_TEXT;
				lvi.cchTextMax = 256;
				lvi.iSubItem = 1;
				lvi.pszText = (LPTSTR)(LPCTSTR)pItem->m_sShop;

				list.SetItem(&lvi);
			}
			
		}
	}

	SetRedraw(TRUE);
}

void CShoppingListView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CListCtrl& ListCtrl = GetListCtrl();
	NMLISTVIEW* pNMListView = (NM_LISTVIEW *)pNMHDR;
	if (ListCtrl.HitTest(pNMListView->ptAction) == -1) {
		// The doubleclick was not on an item. Nothing to do!
		return;
	}

	CItemDlg dlg;

	CShoppingItem * pItem = (CShoppingItem *)ListCtrl.GetItemData(pNMListView->iItem);
	dlg.m_pDoc = GetDocument();
	dlg.m_sCurrentShop = pItem->m_sShop;
	dlg.m_sName = pItem->m_sName;
	dlg.m_sShop = pItem->m_sShop;
	dlg.m_bInCart = pItem->m_bInCart;

	if (dlg.DoModal() == IDCANCEL) {
		return;
	}

	pItem->m_sName = dlg.m_sName;
	pItem->m_sShop = dlg.m_sShop;
	pItem->m_bInCart = dlg.m_bInCart;

	GetDocument()->UpdateAllViews(NULL);

	GetDocument()->SetModifiedFlag();


	*pResult = 0;
}
