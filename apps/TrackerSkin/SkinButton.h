// SkinButton.h: interface for the CSkinButton class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKINBUTTON_H__84DCE102_754C_4AEC_B9B6_02090D3B03F3__INCLUDED_)
#define AFX_SKINBUTTON_H__84DCE102_754C_4AEC_B9B6_02090D3B03F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SkinBitmap.h"

class CSkinButton : public CSkinBitmap  
{
public:
	void DrawPressed(CDC *pDC);
	CSkinButton(LPCTSTR sFileName, LPCTSTR sPressedFileName, int nX, int nY);
	virtual ~CSkinButton();
protected:
	CBitmap m_PressedBitmap;
	CString m_sPressedFileName;
};

#endif // !defined(AFX_SKINBUTTON_H__84DCE102_754C_4AEC_B9B6_02090D3B03F3__INCLUDED_)
