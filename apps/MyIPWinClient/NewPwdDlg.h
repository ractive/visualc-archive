#if !defined(AFX_NEWPWDDLG_H__D631C62E_078E_4E84_BA8E_E10C1748293E__INCLUDED_)
#define AFX_NEWPWDDLG_H__D631C62E_078E_4E84_BA8E_E10C1748293E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewPwdDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewPwdDlg dialog

class CMyIPWinClientDlg;

class CNewPwdDlg : public CDialog
{
// Construction
public:
	CNewPwdDlg(CWnd* pParent = NULL);   // standard constructor
	CMyIPWinClientDlg * m_pParent;
// Dialog Data
	//{{AFX_DATA(CNewPwdDlg)
	enum { IDD = IDD_NEWPWD };
	CString	m_NewPwd;
	CString	m_NewPwd2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewPwdDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewPwdDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWPWDDLG_H__D631C62E_078E_4E84_BA8E_E10C1748293E__INCLUDED_)
