// LandscapeDoc.h : interface of the CLandscapeDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LANDSCAPEDOC_H__899B4385_A265_4502_8D1C_079C0F7BC47B__INCLUDED_)
#define AFX_LANDSCAPEDOC_H__899B4385_A265_4502_8D1C_079C0F7BC47B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CLandscapeDoc : public CDocument
{
protected: // create from serialization only
	CLandscapeDoc();
	DECLARE_DYNCREATE(CLandscapeDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLandscapeDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLandscapeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLandscapeDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LANDSCAPEDOC_H__899B4385_A265_4502_8D1C_079C0F7BC47B__INCLUDED_)
