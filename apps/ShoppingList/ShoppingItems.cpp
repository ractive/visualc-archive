// ShoppingItems.cpp: implementation of the CShoppingItems class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ShoppingList.h"
#include "ShoppingItems.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CShoppingItem, CObject, 1)


void CShoppingItem::Serialize( CArchive& archive )
{
	CObject::Serialize( archive );
	if( archive.IsStoring() ) {
		archive << m_sName;
		archive << m_sShop;
		archive << m_bInCart;
	}
	else {
		archive >> m_sName;
		archive >> m_sShop;
		archive >> m_bInCart;			
	}
}

IMPLEMENT_SERIAL(CShoppingItems, CObList, 1)

CShoppingItems::CShoppingItems()
{

}

CShoppingItems::~CShoppingItems()
{

}

void CShoppingItems::Serialize( CArchive& archive )
{
	CObList::Serialize( archive );
}

void CShoppingItems::Add(CString sName, CString sShop, BOOL bInCart)
{
	CShoppingItem * pItem = new CShoppingItem(sName, sShop, bInCart);
	AddTail(pItem);
}
