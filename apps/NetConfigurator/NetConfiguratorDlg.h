// NetConfiguratorDlg.h : header file
//

#if !defined(AFX_NETCONFIGURATORDLG_H__7865BF40_2178_4ED2_8F20_3B2F9BD974F4__INCLUDED_)
#define AFX_NETCONFIGURATORDLG_H__7865BF40_2178_4ED2_8F20_3B2F9BD974F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CNetConfiguratorDlg dialog

class CNetConfiguratorDlg : public CDialog
{
// Construction
public:
	BOOL ParseConfigFile(CString sFileName, BOOL &bStaticIP, BOOL &bStaticDNS, CString &sIP, CString &sMask, CString &sGW, CString &sDNS1, CString &sDNS2);
	BOOL WriteConfigFile(CString sFileName, BOOL bStaticIP, BOOL bStatisDNS, CString &sIP, CString &sMask, CString &sGW, CString &sDNS1, CString &sDNS2);
	CNetConfiguratorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CNetConfiguratorDlg)
	enum { IDD = IDD_NETCONFIGURATOR_DIALOG };
	CComboBox	m_ConfigCtrl;
	CString	m_sConfigFile;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetConfiguratorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString m_sSystemDirectory;
	void GetConfigs();
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CNetConfiguratorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAdd();
	afx_msg void OnModify();
	afx_msg void OnDelete();
	afx_msg void OnApply();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETCONFIGURATORDLG_H__7865BF40_2178_4ED2_8F20_3B2F9BD974F4__INCLUDED_)
