// GifT68View.h : interface of the CGifT68View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GIFT68VIEW_H__1D194077_AAAE_40A9_A046_5C03AD177914__INCLUDED_)
#define AFX_GIFT68VIEW_H__1D194077_AAAE_40A9_A046_5C03AD177914__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CGifT68View : public CScrollView
{
protected: // create from serialization only
	CGifT68View();
	DECLARE_DYNCREATE(CGifT68View)

// Attributes
public:
	CGifT68Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGifT68View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGifT68View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGifT68View)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in GifT68View.cpp
inline CGifT68Doc* CGifT68View::GetDocument()
   { return (CGifT68Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GIFT68VIEW_H__1D194077_AAAE_40A9_A046_5C03AD177914__INCLUDED_)
