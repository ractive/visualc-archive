#if !defined(AFX_ADDDLG_H__083044AB_A382_4603_9B02_275A045D571C__INCLUDED_)
#define AFX_ADDDLG_H__083044AB_A382_4603_9B02_275A045D571C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddDlg dialog

class CAddDlg : public CDialog
{
// Construction
public:
	CAddDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddDlg)
	enum { IDD = IDD_ADDDIALOG };
	CEdit	m_UsernameCtrl;
	CEdit	m_PasswordCtrl;
	CString	m_sLocalFolder;
	CString	m_sFTPServer;
	CString	m_sFTPDirectory;
	BOOL	m_bIncludeSubDirs;
	BOOL	m_bPassiveMode;
	CString	m_sPassword;
	UINT	m_nPort;
	CString	m_sUsername;
	BOOL	m_bAnonymous;
	int		m_nSyncMode;
	int		m_nConflict;
	int		m_nOverwriteFtp;
	int		m_nOverwriteLocal;
	//}}AFX_DATA

	BOOL m_bSyncFtp;
	BOOL m_bSyncLocal;

	BOOL m_bAskLocalOverwrite;
	
	BOOL m_bAskFtpOverwrite;

	BOOL m_bAskIfConflict;
	BOOL m_bUpload;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddDlg)
	afx_msg void OnChooseLocalFolder();
	afx_msg void OnAnonymous();
	afx_msg void OnSyncFtp();
	afx_msg void OnSyncLocal();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSyncTwoway();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDDLG_H__083044AB_A382_4603_9B02_275A045D571C__INCLUDED_)
