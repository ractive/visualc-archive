#if !defined(AFX_PICHOLDER_H__2FF47A97_C6FF_40D6_BA02_1445B7DD4CC4__INCLUDED_)
#define AFX_PICHOLDER_H__2FF47A97_C6FF_40D6_BA02_1445B7DD4CC4__INCLUDED_

#include "Picture.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PicHolder.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPicHolder window

class CPicHolder : public CStatic
{
// Construction
public:
	CPicHolder();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPicHolder)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL Load(CString sFilePathName);
	virtual ~CPicHolder();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPicHolder)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	CPicture m_Picture;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICHOLDER_H__2FF47A97_C6FF_40D6_BA02_1445B7DD4CC4__INCLUDED_)
