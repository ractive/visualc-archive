// ShoppingListDoc.h : interface of the CShoppingListDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHOPPINGLISTDOC_H__D8A4E7A1_7FBE_47B9_B1DF_EB0C9902AA7E__INCLUDED_)
#define AFX_SHOPPINGLISTDOC_H__D8A4E7A1_7FBE_47B9_B1DF_EB0C9902AA7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ShoppingItems.h"

#define SHOP_ADDED 1
#define ITEM_ADDED 2

class CShoppingListDoc : public CDocument
{
protected: // create from serialization only
	CShoppingListDoc();
	DECLARE_DYNCREATE(CShoppingListDoc)

// Attributes
public:

// Operations
public:
	CStringArray m_saShops;
	CString m_sCurrentShop;
	CShoppingItems m_saItems;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShoppingListDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CShoppingListDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	void Cleanup();
	//{{AFX_MSG(CShoppingListDoc)
	afx_msg void OnAddShoppingItem();
	afx_msg void OnAddShop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOPPINGLISTDOC_H__D8A4E7A1_7FBE_47B9_B1DF_EB0C9902AA7E__INCLUDED_)
