#if !defined(AFX_CONFLICTDLG_H__E4CEC7A9_5A32_4D9E_AD49_F7457F6F9F21__INCLUDED_)
#define AFX_CONFLICTDLG_H__E4CEC7A9_5A32_4D9E_AD49_F7457F6F9F21__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConflictDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConflictDlg dialog

class CConflictDlg : public CDialog
{
// Construction
public:
	CConflictDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConflictDlg)
	enum { IDD = IDD_CONFLICTDLG };
	int		m_nUpload;
	CString	m_sFile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConflictDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConflictDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFLICTDLG_H__E4CEC7A9_5A32_4D9E_AD49_F7457F6F9F21__INCLUDED_)
