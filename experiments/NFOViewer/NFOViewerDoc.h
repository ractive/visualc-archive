// NFOViewerDoc.h : interface of the CNFOViewerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_NFOVIEWERDOC_H__365336D0_FECF_4910_BA18_6A917E635F5F__INCLUDED_)
#define AFX_NFOVIEWERDOC_H__365336D0_FECF_4910_BA18_6A917E635F5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CNFOViewerDoc : public CDocument
{
protected: // create from serialization only
	CNFOViewerDoc();
	DECLARE_DYNCREATE(CNFOViewerDoc)

// Attributes
public:
	CString m_sNFOContent;
	SIZE m_TextSize;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNFOViewerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNFOViewerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CNFOViewerDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NFOVIEWERDOC_H__365336D0_FECF_4910_BA18_6A917E635F5F__INCLUDED_)
