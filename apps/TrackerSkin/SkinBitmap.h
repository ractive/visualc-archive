// SkinBitmap.h: interface for the CSkinBitmap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKINBITMAP_H__422E3095_0BA8_4E7A_8554_BEEC7CBF8944__INCLUDED_)
#define AFX_SKINBITMAP_H__422E3095_0BA8_4E7A_8554_BEEC7CBF8944__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPropertyList;
class CPropertyItem;

class CSkinBitmap
{
public:
	CPropertyList *m_pPropertyList;
	void SetProperties(CPropertyList *pPropertyList);
	void SetMoveable(BOOL bMoveable);
	CRect GetRect();
	CPoint GetPos();
	BOOL SetPos(int x, int y);
	void DrawSelector(CDC *pDC);
	BOOL m_bSelected;
	BOOL Hit(const CPoint *pPoint) const;
	virtual void Draw(CDC* pDC);
	virtual void DrawPressed(CDC* pDC);
	CSkinBitmap(LPCTSTR sFileName, int nX, int nY);
	virtual ~CSkinBitmap();
	HGDIOBJ GetHandle();
	CArray <CPropertyItem *, CPropertyItem *> m_PropItems;
protected:
	BOOL m_bMoveable;
	int m_nX;
	int m_nY;
	int m_nWidth;
	int m_nHeight;
	CBitmap m_Bitmap;
	CString m_sFileName;
};

#endif // !defined(AFX_SKINBITMAP_H__422E3095_0BA8_4E7A_8554_BEEC7CBF8944__INCLUDED_)
