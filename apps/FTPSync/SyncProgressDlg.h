#if !defined(AFX_SYNCPROGRESSDLG_H__F34A4EBF_B3A7_4EDB_9114_AC02D0CF87F4__INCLUDED_)
#define AFX_SYNCPROGRESSDLG_H__F34A4EBF_B3A7_4EDB_9114_AC02D0CF87F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SyncProgressDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSyncProgressDlg dialog

class CFTPSyncDoc;

class CSyncProgressDlg : public CDialog
{
// Construction
public:
	HANDLE m_hStop;
	static BOOL Pump();
	CSyncProgressDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSyncProgressDlg)
	enum { IDD = IDD_SYNCPROGRESSDLG };
	CProgressCtrl	m_UploadProgressCtrl;
	CProgressCtrl	m_DownloadProgressCtrl;
	CString	m_sUploadFile;
	CString	m_sDownloadFile;
	CString	m_sOverall;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSyncProgressDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSyncProgressDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	virtual void OnCancel();
	//}}AFX_MSG
	afx_msg LRESULT OnSyncFiles(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDownloadFile(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUploadFile(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUploadDone(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDownloadDone(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnStartSync(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYNCPROGRESSDLG_H__F34A4EBF_B3A7_4EDB_9114_AC02D0CF87F4__INCLUDED_)
