// NFOViewerView.h : interface of the CNFOViewerView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_NFOVIEWERVIEW_H__F6C84B6A_417A_495F_9C24_6F4F2CA59072__INCLUDED_)
#define AFX_NFOVIEWERVIEW_H__F6C84B6A_417A_495F_9C24_6F4F2CA59072__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CNFOViewerView : public CScrollView
{
protected: // create from serialization only
	CNFOViewerView();
	DECLARE_DYNCREATE(CNFOViewerView)

// Attributes
public:
	CNFOViewerDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNFOViewerView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNFOViewerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CNFOViewerView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void FitWindow();
	CString m_lpszFileName;
	COLORREF m_bkColor;
	COLORREF m_textColor;
	HFONT m_hTerminalFont;
	//CFont m_Font;
	LOGFONT m_lf;
	int m_nLineHeight;
	int m_nCurPos;
	int m_nLines;
};

#ifndef _DEBUG  // debug version in NFOViewerView.cpp
inline CNFOViewerDoc* CNFOViewerView::GetDocument()
   { return (CNFOViewerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NFOVIEWERVIEW_H__F6C84B6A_417A_495F_9C24_6F4F2CA59072__INCLUDED_)
