// GifT68Doc.h : interface of the CGifT68Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GIFT68DOC_H__910F060D_EF35_461D_87CD_A61522C5E9D0__INCLUDED_)
#define AFX_GIFT68DOC_H__910F060D_EF35_461D_87CD_A61522C5E9D0__INCLUDED_

#include "Picture.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CGifT68Doc : public CDocument
{
protected: // create from serialization only
	CGifT68Doc();
	DECLARE_DYNCREATE(CGifT68Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGifT68Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	CPicture m_Picture;
	virtual ~CGifT68Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGifT68Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GIFT68DOC_H__910F060D_EF35_461D_87CD_A61522C5E9D0__INCLUDED_)
