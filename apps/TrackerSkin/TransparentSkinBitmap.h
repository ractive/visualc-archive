// TransparentSkinBitmap.h: interface for the CTransparentSkinBitmap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSPARENTSKINBITMAP_H__82095CAC_E698_44A2_A462_749D75AE70FB__INCLUDED_)
#define AFX_TRANSPARENTSKINBITMAP_H__82095CAC_E698_44A2_A462_749D75AE70FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SkinBitmap.h"

class CTransparentSkinBitmap : public CSkinBitmap  
{
public:
	virtual void Draw(CDC *pDC);
	virtual void DrawPressed(CDC *pDC);
	CTransparentSkinBitmap(LPCTSTR sFileName, LPCTSTR sTransparentFilename, int nX, int nY);
	virtual ~CTransparentSkinBitmap();

protected:
	CBitmap m_TransparentBitmap;
	CString m_sTransparentFileName;
};

#endif // !defined(AFX_TRANSPARENTSKINBITMAP_H__82095CAC_E698_44A2_A462_749D75AE70FB__INCLUDED_)
