// SkinBitmap.cpp: implementation of the CSkinBitmap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TrackerSkin.h"
#include "SkinBitmap.h"
#include "PropertyList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSkinBitmap::CSkinBitmap(LPCTSTR sFileName, int nX, int nY)
{
	m_sFileName = sFileName;
	HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, m_sFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_Bitmap.Attach(hBitmap);
	BITMAP bmp;
	m_Bitmap.GetBitmap(&bmp);

	m_Bitmap.SetBitmapDimension(bmp.bmWidth, bmp.bmHeight);
	
	m_nWidth = bmp.bmWidth;
	m_nHeight = bmp.bmHeight;
	m_nX = nX;
	m_nY = nY;

	m_bMoveable = TRUE;
	m_bSelected = 0;
}

CSkinBitmap::~CSkinBitmap()
{
	int nSize = m_PropItems.GetSize();
	for (int i = 0; i < nSize; i++) {
		delete (CPropertyItem *)m_PropItems.GetAt(i);
	}

	m_PropItems.RemoveAll();
	m_Bitmap.Detach();
}

HGDIOBJ CSkinBitmap::GetHandle()
{
	return m_Bitmap.GetSafeHandle();
}

void CSkinBitmap::Draw(CDC *pDC)
{
	CDC dc;
	dc.CreateCompatibleDC(pDC);

	dc.SelectObject(m_Bitmap);

	CSize dim = m_Bitmap.GetBitmapDimension();
	pDC->BitBlt(m_nX, m_nY, dim.cx, dim.cy, &dc, 0, 0, SRCCOPY);
}

void CSkinBitmap::DrawPressed(CDC *pDC)
{
	// Do nothing
}

BOOL CSkinBitmap::Hit(const CPoint *pPoint) const
{
	return ((pPoint->x >= m_nX && pPoint->x <= m_nX + m_nWidth) && (pPoint->y >= m_nY && pPoint->y <= m_nY + m_nHeight));
}

void CSkinBitmap::DrawSelector(CDC *pDC)
{
	if (!m_bSelected || !m_bMoveable) {
		return;
	}

	CRect rect(m_nX, m_nY, m_nX + m_nWidth, m_nY + m_nHeight);
	pDC->DrawDragRect(&rect, CSize(2, 2), NULL, CSize(2, 2));
}

BOOL CSkinBitmap::SetPos(int x, int y)
{
	if (!m_bMoveable) {
		// Ignore the new Positions
		return FALSE;
	}

	m_nX = x;
	m_nY = y;

	//m_pPropertyList->InvalidateRect(NULL, FALSE);
	//m_pPropertyList->UpdateWindow();
	m_pPropertyList->InvalidateDataPart();

	return TRUE;
}

CPoint CSkinBitmap::GetPos()
{
	return CPoint(m_nX, m_nY);
}

CRect CSkinBitmap::GetRect()
{
	return CRect(GetPos(), CSize(m_nWidth, m_nHeight));
}

void CSkinBitmap::SetMoveable(BOOL bMoveable)
{
	m_bMoveable= bMoveable;
}

void CSkinBitmap::SetProperties(CPropertyList *pPropertyList)
{
	m_pPropertyList = pPropertyList;
	pPropertyList->ResetContent();
	
	CPropertyItem * pBitmap = new CPropertyItemStr("Bitmap", m_sFileName, PIT_FILE, "");
	m_PropItems.Add(pBitmap);

	pPropertyList->AddPropItem(pBitmap);

	CPropertyItem * pX = new CPropertyItemInt("Left", &m_nX, PIT_EDIT, "");
	m_PropItems.Add(pX);
	int x = pPropertyList->AddPropItem(pX);

	CPropertyItem * pY = new CPropertyItemInt("Top", &m_nY, PIT_EDIT, "");
	m_PropItems.Add(pY);
	pPropertyList->AddPropItem(pY);
}
