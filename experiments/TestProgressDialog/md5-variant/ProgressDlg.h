#if !defined(AFX_PROGRESSDLG_H__8E27DBD3_739B_4E71_8900_078233A3EE46__INCLUDED_)
#define AFX_PROGRESSDLG_H__8E27DBD3_739B_4E71_8900_078233A3EE46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProgressDlg.h : header file
//

#define WM_PROGRESS (WM_USER + 1)

/////////////////////////////////////////////////////////////////////////////
// CProgressDlg dialog

class CProgressDlg : public CDialog
{
// Construction
public:
	HANDLE m_hStop;

	BOOL Pump();
	CProgressDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProgressDlg)
	enum { IDD = IDD_PROGRESSDLG };
	CProgressCtrl	m_ProgressCtrl;
	CString	m_sText;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgressDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProgressDlg)
	afx_msg void OnStop();
	//}}AFX_MSG
	afx_msg LRESULT OnProgress(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

struct threadInfo {
	HWND hWnd;
	HANDLE hStop;
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRESSDLG_H__8E27DBD3_739B_4E71_8900_078233A3EE46__INCLUDED_)
