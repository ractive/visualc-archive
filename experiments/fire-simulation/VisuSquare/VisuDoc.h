// VisuDoc.h : interface of the CVisuDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VISUDOC_H__1A4C6FC7_665B_48DD_AFFD_31D090A7FC5C__INCLUDED_)
#define AFX_VISUDOC_H__1A4C6FC7_665B_48DD_AFFD_31D090A7FC5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CVisuDoc : public CDocument
{
protected: // create from serialization only
	CVisuDoc();
	DECLARE_DYNCREATE(CVisuDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVisuDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	int y;
	int x;
	virtual ~CVisuDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CVisuDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VISUDOC_H__1A4C6FC7_665B_48DD_AFFD_31D090A7FC5C__INCLUDED_)
