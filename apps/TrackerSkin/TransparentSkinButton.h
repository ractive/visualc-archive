// TransparentSkinButton.h: interface for the CTransparentSkinButton class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSPARENTSKINBUTTON_H__17B30C82_133C_4C83_A6A4_1408EB03BCCF__INCLUDED_)
#define AFX_TRANSPARENTSKINBUTTON_H__17B30C82_133C_4C83_A6A4_1408EB03BCCF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TransparentSkinBitmap.h"
#include "SkinButton.h"

class CTransparentSkinButton : public CTransparentSkinBitmap  
{
public:
	CTransparentSkinButton(LPCTSTR sFileName, LPCTSTR sTransparentFileName, LPCTSTR sPressedFileName, LPCTSTR sPressedTransparentFileName, int nX, int nY);
	virtual ~CTransparentSkinButton();
	void DrawPressed(CDC *pDC);
protected:
	CBitmap m_PressedBitmap;
	CString m_sPressedFileName;
	CBitmap m_TransparentPressedBitmap;
	CString m_sTransparentPressedFileName;
};

#endif // !defined(AFX_TRANSPARENTSKINBUTTON_H__17B30C82_133C_4C83_A6A4_1408EB03BCCF__INCLUDED_)
