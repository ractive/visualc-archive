#if !defined(AFX_BITMAPHOLDER_H__A78B20DA_8E95_4013_9FA4_A607EE2018B9__INCLUDED_)
#define AFX_BITMAPHOLDER_H__A78B20DA_8E95_4013_9FA4_A607EE2018B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BitmapHolder.h : header file
//

class CSkinBitmap;
class CSkinButton;
class CPropertyList;

/////////////////////////////////////////////////////////////////////////////
// CBitmapHolder window

class CBitmapHolder : public CStatic
{
// Construction
public:
	CBitmapHolder();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBitmapHolder)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetPropertyList(CPropertyList * pPropertyList);
	BOOL ToggleTest();
	CPoint m_OffsetPoint;
	virtual ~CBitmapHolder();

	// Generated message map functions
protected:
	CPropertyList * m_pPropertyList;
	BOOL m_bTest;
	CList <CSkinBitmap *, CSkinBitmap *> m_SkinBitmaps;
	CSkinBitmap * m_pSelected;
	CPoint m_DragStart;
	BOOL m_bDragging;
	//{{AFX_MSG(CBitmapHolder)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	HCURSOR m_hHandCursor;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BITMAPHOLDER_H__A78B20DA_8E95_4013_9FA4_A607EE2018B9__INCLUDED_)
