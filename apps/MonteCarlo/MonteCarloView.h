// MonteCarloView.h : interface of the CMonteCarloView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MONTECARLOVIEW_H__66BB5EA0_8EF7_4D7F_B9C1_D76807764065__INCLUDED_)
#define AFX_MONTECARLOVIEW_H__66BB5EA0_8EF7_4D7F_B9C1_D76807764065__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMonteCarloView : public CView
{
protected: // create from serialization only
	CMonteCarloView();
	DECLARE_DYNCREATE(CMonteCarloView)

// Attributes
public:
	CMonteCarloDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMonteCarloView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMonteCarloView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	CRect m_cRect;
	//{{AFX_MSG(CMonteCarloView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MonteCarloView.cpp
inline CMonteCarloDoc* CMonteCarloView::GetDocument()
   { return (CMonteCarloDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MONTECARLOVIEW_H__66BB5EA0_8EF7_4D7F_B9C1_D76807764065__INCLUDED_)
