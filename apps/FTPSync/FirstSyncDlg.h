#if !defined(AFX_FIRSTSYNCDLG_H__BC76658E_662D_4BAA_9953_C5F64F7AEBB1__INCLUDED_)
#define AFX_FIRSTSYNCDLG_H__BC76658E_662D_4BAA_9953_C5F64F7AEBB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FirstSyncDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFirstSyncDlg dialog

class CFirstSyncDlg : public CDialog
{
// Construction
public:
	CFirstSyncDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFirstSyncDlg)
	enum { IDD = IDD_FIRSTSYNCDLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFirstSyncDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFirstSyncDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FIRSTSYNCDLG_H__BC76658E_662D_4BAA_9953_C5F64F7AEBB1__INCLUDED_)
