// BitmapHolder.cpp : implementation file
//

#include "stdafx.h"
#include "TrackerSkin.h"
#include "BitmapHolder.h"
#include "SkinBitmap.h"
#include "TransparentSkinBitmap.h"
#include "TransparentSkinButton.h"
#include "SkinButton.h"
#include "PropertyList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBitmapHolder

CBitmapHolder::CBitmapHolder()
{
	m_bDragging = FALSE;
	m_pSelected = NULL;
	m_bTest = FALSE;
	m_pPropertyList = NULL;

	m_hHandCursor = (HCURSOR)LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDC_HAND), IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE);

	SetCurrentDirectory("C:\\Dokumente und Einstellungen\\James\\Eigene Dateien\\P800\\Tracker Skins\\azure_src1\\");

	CSkinBitmap * pButton = new CSkinBitmap("Bitmaps\\background.bmp", 0, 0);
	pButton->SetMoveable(FALSE);
	
	m_SkinBitmaps.AddTail(pButton);
	
	m_SkinBitmaps.AddTail(new CSkinBitmap("Bitmaps\\ericsson.bmp", 10, 10));
	m_SkinBitmaps.AddTail(new CTransparentSkinButton("Bitmaps\\btn_bl.bmp", "Bitmaps\\btnm_bl.bmp", "Bitmaps\\btnp_bl.bmp", "Bitmaps\\btnm_bl.bmp", 50, 50));
	m_SkinBitmaps.AddTail(new CTransparentSkinButton("Bitmaps\\btn_sms.bmp", "Bitmaps\\btnm_top.bmp", "Bitmaps\\btnp_sms.bmp", "Bitmaps\\btnm_top.bmp", 100, 200));
	m_SkinBitmaps.AddTail(new CTransparentSkinButton("Bitmaps\\btn_mms.bmp", "Bitmaps\\btnm_top.bmp", "Bitmaps\\btnp_mms.bmp", "Bitmaps\\btnm_top.bmp", 100, 200));
	m_SkinBitmaps.AddTail(new CSkinButton("Bitmaps\\btn_menu.bmp", "Bitmaps\\btnp_menu.bmp", 100, 100));
}

CBitmapHolder::~CBitmapHolder()
{
	POSITION pos = NULL;

	for( pos = m_SkinBitmaps.GetHeadPosition(); pos != NULL; ) {
		delete m_SkinBitmaps.GetNext( pos );
	}
}


BEGIN_MESSAGE_MAP(CBitmapHolder, CStatic)
	//{{AFX_MSG_MAP(CBitmapHolder)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBitmapHolder message handlers

void CBitmapHolder::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	POSITION pos = NULL;
	CSkinBitmap * pBitmap = NULL;

	for( pos = m_SkinBitmaps.GetHeadPosition(); pos != NULL; ) {
		pBitmap = (CSkinBitmap *)m_SkinBitmaps.GetNext( pos );
		pBitmap->Draw(&dc);
	}

	if (m_pSelected) {
		if (m_bTest) {
			if (m_bDragging) {
				m_pSelected->DrawPressed(&dc);
			}
		}
		else {
			m_pSelected->DrawSelector(&dc);
		}
	}
	// Do not call CStatic::OnPaint() for painting messages
}

void CBitmapHolder::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CRect update_rect;
	CRect old_update_rect;
	POSITION pos = NULL;
	CSkinBitmap * pBitmap = NULL;
	
	BOOL bNewSelection = FALSE;

	m_bDragging = TRUE;

	// Get the rect of the old selection (if any)
	if (m_pSelected) {
		old_update_rect = m_pSelected->GetRect();
	}

	// Assume nothing will get selected
	m_pSelected = NULL;

	// Search through the objects if we have a hit
	for(pos = m_SkinBitmaps.GetHeadPosition(); pos != NULL; ) {
		pBitmap = (CSkinBitmap *)m_SkinBitmaps.GetNext( pos );
		if (pBitmap->Hit(&point)) {
			if (m_pSelected != pBitmap) {
				pBitmap->SetProperties(m_pPropertyList);
			}
			m_pSelected = pBitmap;
		}
	}
	
	if (m_pSelected) {		
		update_rect = m_pSelected->GetRect();
		
		if (!m_bTest) {
			// Mark the bitmap as selected
			m_pSelected->m_bSelected = TRUE;

			m_DragStart = point;
				
			m_OffsetPoint = m_pSelected->GetPos();
		}
	}

	InvalidateRect(update_rect, FALSE);
	InvalidateRect(old_update_rect, FALSE);
	UpdateWindow();

	CStatic::OnLButtonDown(nFlags, point);
}

void CBitmapHolder::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_bDragging = FALSE;
	if (m_bTest && m_pSelected) {
		InvalidateRect(m_pSelected->GetRect(), FALSE);
			
		UpdateWindow();
	}

	CStatic::OnLButtonUp(nFlags, point);
}

void CBitmapHolder::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_bDragging && !m_bTest) {
		CRect update_rect = m_pSelected->GetRect();
		
		CPoint d = point - m_DragStart + m_OffsetPoint;

		if (d.x < 0) {
			d.x = 0;
		}
		if (d.y < 0) {
			d.y = 0;
		}

		CRect cRect;
		GetClientRect(&cRect);

		if (d.x > cRect.right) {
			d.x = cRect.right;
		}
		if (d.y > cRect.bottom) {
			d.y = cRect.bottom;
		}

		if (m_pSelected->SetPos(d.x, d.y)) {
			InvalidateRect(update_rect, FALSE);
			
			UpdateWindow();
		}
	}

	CStatic::OnMouseMove(nFlags, point);
}

BOOL CBitmapHolder::ToggleTest()
{
	if (!m_bTest && m_pSelected) {
		// Remove borders from the bitmaps (if any)
		InvalidateRect(m_pSelected->GetRect(), FALSE);
	}
	
	m_bTest = !m_bTest;
	
	UpdateWindow();
	
	return m_bTest;
}

BOOL CBitmapHolder::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if (m_bTest && ::SetCursor(m_hHandCursor)) {
		return TRUE;
	}

	return CStatic::OnSetCursor(pWnd, nHitTest, message);
}

void CBitmapHolder::SetPropertyList(CPropertyList *pPropertyList)
{
	m_pPropertyList = pPropertyList;
}
