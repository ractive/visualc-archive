// VisuView.h : interface of the CVisuView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VISUVIEW_H__1869D6E5_FE9A_438B_AD3F_3111F01D5141__INCLUDED_)
#define AFX_VISUVIEW_H__1869D6E5_FE9A_438B_AD3F_3111F01D5141__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CVisuView : public CView
{
protected: // create from serialization only
	CVisuView();
	DECLARE_DYNCREATE(CVisuView)

// Attributes
public:
	CVisuDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVisuView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVisuView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CVisuView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in VisuView.cpp
inline CVisuDoc* CVisuView::GetDocument()
   { return (CVisuDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VISUVIEW_H__1869D6E5_FE9A_438B_AD3F_3111F01D5141__INCLUDED_)
