// TransparentSkinBitmap.cpp: implementation of the CTransparentSkinBitmap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TrackerSkin.h"
#include "TransparentSkinBitmap.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTransparentSkinBitmap::CTransparentSkinBitmap(LPCTSTR sFileName, LPCTSTR sTransparentFilename, int nX, int nY) : CSkinBitmap(sFileName, nX, nY)
{
	m_sTransparentFileName = sTransparentFilename;
	HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, m_sTransparentFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_TransparentBitmap.Attach(hBitmap);

	BITMAP bmp;
	m_TransparentBitmap.GetBitmap(&bmp);
	m_TransparentBitmap.SetBitmapDimension(bmp.bmWidth, bmp.bmHeight);
}

CTransparentSkinBitmap::~CTransparentSkinBitmap()
{
	m_TransparentBitmap.Detach();
}

void CTransparentSkinBitmap::Draw(CDC *pDC)
{
	CDC dc;
	dc.CreateCompatibleDC(pDC);

	CDC dc2;
	dc2.CreateCompatibleDC(pDC);

	dc.SelectObject(&m_Bitmap);
	dc2.SelectObject(&m_TransparentBitmap);

	CSize dim = m_Bitmap.GetBitmapDimension();
	pDC->BitBlt(m_nX, m_nY, dim.cx, dim.cy, &dc, 0, 0, SRCINVERT);
	pDC->BitBlt(m_nX, m_nY, dim.cx, dim.cy, &dc2, 0, 0, SRCAND);
	pDC->BitBlt(m_nX, m_nY, dim.cx, dim.cy, &dc, 0, 0, SRCINVERT);
}

void CTransparentSkinBitmap::DrawPressed(CDC *pDC)
{
	// Do nothing
}