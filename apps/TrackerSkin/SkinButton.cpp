// SkinButton.cpp: implementation of the CSkinButton class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TrackerSkin.h"
#include "SkinButton.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSkinButton::CSkinButton(LPCTSTR sFileName, LPCTSTR sPressedFileName, int nX, int nY) : CSkinBitmap(sFileName, nX, nY)
{
	m_sPressedFileName = sPressedFileName;
	HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, m_sPressedFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_PressedBitmap.Attach(hBitmap);

	BITMAP bmp;
	m_PressedBitmap.GetBitmap(&bmp);
	m_PressedBitmap.SetBitmapDimension(bmp.bmWidth, bmp.bmHeight);
}

CSkinButton::~CSkinButton()
{

}

void CSkinButton::DrawPressed(CDC *pDC)
{
	CDC dc;
	dc.CreateCompatibleDC(pDC);

	dc.SelectObject(m_PressedBitmap);

	CSize dim = m_PressedBitmap.GetBitmapDimension();
	pDC->BitBlt(m_nX, m_nY, dim.cx, dim.cy, &dc, 0, 0, SRCCOPY);
}
