#if !defined(AFX_MELODYEDIT_H__3E18065E_A603_420A_BF53_A7D1B552E7A1__INCLUDED_)
#define AFX_MELODYEDIT_H__3E18065E_A603_420A_BF53_A7D1B552E7A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MelodyEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMelodyEdit window

#define WM_PLAYTONE (WM_USER + 2)

class CMelodyEdit : public CEdit
{
// Construction
public:
	CMelodyEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMelodyEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMelodyEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMelodyEdit)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MELODYEDIT_H__3E18065E_A603_420A_BF53_A7D1B552E7A1__INCLUDED_)
