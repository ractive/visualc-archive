// TransparentSkinButton.cpp: implementation of the CTransparentSkinButton class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TrackerSkin.h"
#include "TransparentSkinButton.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTransparentSkinButton::CTransparentSkinButton(LPCTSTR sFileName,
											   LPCTSTR sTransparentFileName,
											   LPCTSTR sPressedFileName,
											   LPCTSTR sTransparentPressedFileName,
											   int nX, int nY) :
							CTransparentSkinBitmap(sFileName, sTransparentFileName, nX, nY)

{
	m_sPressedFileName = sPressedFileName;
	m_sTransparentPressedFileName = sTransparentPressedFileName;

	HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, m_sPressedFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_PressedBitmap.Attach(hBitmap);

	BITMAP bmp;
	m_PressedBitmap.GetBitmap(&bmp);
	m_PressedBitmap.SetBitmapDimension(bmp.bmWidth, bmp.bmHeight);

							
	hBitmap = (HBITMAP)LoadImage(NULL, m_sTransparentPressedFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_TransparentPressedBitmap.Attach(hBitmap);

	m_TransparentPressedBitmap.GetBitmap(&bmp);
	m_TransparentPressedBitmap.SetBitmapDimension(bmp.bmWidth, bmp.bmHeight);							
}

CTransparentSkinButton::~CTransparentSkinButton()
{

}

void CTransparentSkinButton::DrawPressed(CDC *pDC)
{
	CDC dc;
	dc.CreateCompatibleDC(pDC);

	CDC dc2;
	dc2.CreateCompatibleDC(pDC);

	dc.SelectObject(&m_PressedBitmap);
	dc2.SelectObject(&m_TransparentPressedBitmap);

	CSize dim = m_PressedBitmap.GetBitmapDimension();
	pDC->BitBlt(m_nX, m_nY, dim.cx, dim.cy, &dc, 0, 0, SRCINVERT);
	pDC->BitBlt(m_nX, m_nY, dim.cx, dim.cy, &dc2, 0, 0, SRCAND);
	pDC->BitBlt(m_nX, m_nY, dim.cx, dim.cy, &dc, 0, 0, SRCINVERT);
}