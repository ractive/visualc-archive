// ShoppingListView.h : interface of the CShoppingListView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHOPPINGLISTVIEW_H__56E03AC5_C034_481C_A66A_662F0D31AB84__INCLUDED_)
#define AFX_SHOPPINGLISTVIEW_H__56E03AC5_C034_481C_A66A_662F0D31AB84__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CShoppingListView : public CListView
{
protected: // create from serialization only
	CShoppingListView();
	DECLARE_DYNCREATE(CShoppingListView)

// Attributes
public:
	CShoppingListDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShoppingListView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL m_bHeaderInit;
	virtual ~CShoppingListView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CShoppingListView)
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ShoppingListView.cpp
inline CShoppingListDoc* CShoppingListView::GetDocument()
   { return (CShoppingListDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOPPINGLISTVIEW_H__56E03AC5_C034_481C_A66A_662F0D31AB84__INCLUDED_)
