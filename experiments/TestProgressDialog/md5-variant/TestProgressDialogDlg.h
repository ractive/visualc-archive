// TestProgressDialogDlg.h : header file
//

#if !defined(AFX_TESTPROGRESSDIALOGDLG_H__708A4006_8ED3_4C68_9987_23CBD5C063FB__INCLUDED_)
#define AFX_TESTPROGRESSDIALOGDLG_H__708A4006_8ED3_4C68_9987_23CBD5C063FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestProgressDialogDlg dialog

class CTestProgressDialogDlg : public CDialog
{
// Construction
public:
	CTestProgressDialogDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestProgressDialogDlg)
	enum { IDD = IDD_TESTPROGRESSDIALOG_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestProgressDialogDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	static HANDLE m_hStop;
	static UINT ThreadProc(LPVOID lParam);
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestProgressDialogDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnStartThread();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTPROGRESSDIALOGDLG_H__708A4006_8ED3_4C68_9987_23CBD5C063FB__INCLUDED_)
