// ShoppingItems.h: interface for the CShoppingItems class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHOPPINGITEMS_H__938BED31_8E04_4142_8EF1_C465CB379E38__INCLUDED_)
#define AFX_SHOPPINGITEMS_H__938BED31_8E04_4142_8EF1_C465CB379E38__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CShoppingItem : public CObject {
public:
	DECLARE_SERIAL(CShoppingItem);
	void Add(CString sName, CString sShop, BOOL bInCart);
	CShoppingItem(CString sName, CString sShop, BOOL bInCart = FALSE) {m_sName = sName; m_sShop = sShop, m_bInCart = bInCart;};
	CShoppingItem() {};
	CString m_sName;
	CString m_sShop;
	BOOL m_bInCart;
	void Serialize( CArchive& archive );
};

class CShoppingItems : public CObList  
{

public:
	DECLARE_SERIAL(CShoppingItems);

	CShoppingItems();
	virtual ~CShoppingItems();
	
	void Serialize( CArchive& archive );


	void Add(CString sName, CString sShop, BOOL bInCart);
};

#endif // !defined(AFX_SHOPPINGITEMS_H__938BED31_8E04_4142_8EF1_C465CB379E38__INCLUDED_)
