// LeftView.cpp : implementation of the CLeftView class
//

#include "stdafx.h"
#include "ShoppingList.h"

#include "ShoppingListDoc.h"
#include "LeftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CListView)

BEGIN_MESSAGE_MAP(CLeftView, CListView)
	//{{AFX_MSG_MAP(CLeftView)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, OnItemChanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeftView construction/destruction

CLeftView::CLeftView()
{
	// TODO: add construction code here
	m_bHeaderInit = FALSE;

}

CLeftView::~CLeftView()
{
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style |= LVS_REPORT | LVS_SHOWSELALWAYS;

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView drawing

void CLeftView::OnDraw(CDC* pDC)
{
	CShoppingListDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}


void CLeftView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();
	
	CListCtrl &listCtrl = GetListCtrl();


	if (!m_bHeaderInit) {
		DWORD dwExStyle = listCtrl.GetExtendedStyle();
		listCtrl.SetExtendedStyle(dwExStyle | LVS_EX_INFOTIP |LVS_EX_FULLROWSELECT);

		listCtrl.InsertColumn(0, "Shops", LVCFMT_LEFT, 170, 0);	

		m_bHeaderInit = TRUE;
	}

	if (listCtrl.GetItemCount() > 0) {
		listCtrl.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);
		GetDocument()->m_sCurrentShop = listCtrl.GetItemText(0, 0);
		GetDocument()->UpdateAllViews(this);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView diagnostics

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CListView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CShoppingListDoc* CLeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CShoppingListDoc)));
	return (CShoppingListDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLeftView message handlers

void CLeftView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if (pSender == this) {
		return;
	}

	if (lHint == ITEM_ADDED) {
		return;
	}

	CListCtrl &list = GetListCtrl();

	list.DeleteAllItems();

	CShoppingListDoc *pDoc = GetDocument();

	int nSize = pDoc->m_saShops.GetSize();
	for (int i = 0; i < nSize; i++) {
		int nNew = list.InsertItem(i, pDoc->m_saShops.GetAt(i));
		if (pDoc->m_saShops.GetAt(i) == pDoc->m_sCurrentShop) {
			list.SetItemState(nNew, LVIS_SELECTED, LVIS_SELECTED);
		}
	}
	
	
}

void CLeftView::OnItemChanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	if (pNMListView->iItem == -1) {
		return;
	}

	if (pNMListView->uChanged & LVIF_STATE) {
		if (pNMListView->uNewState & LVIS_SELECTED && 
			pNMListView->uNewState & LVIS_FOCUSED &&
			!(pNMListView->uOldState & LVIS_SELECTED) &&
			!(pNMListView->uOldState & LVIS_FOCUSED)) {

			CListCtrl &list = GetListCtrl();

			GetDocument()->m_sCurrentShop = list.GetItemText(pNMListView->iItem, 0);

			GetDocument()->UpdateAllViews(this);
		}
	}

	*pResult = 0;
}
