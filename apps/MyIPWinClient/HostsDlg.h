#if !defined(AFX_HOSTSDLG_H__2CD2E2A1_5045_4D2E_BE89_2BE06C3398A3__INCLUDED_)
#define AFX_HOSTSDLG_H__2CD2E2A1_5045_4D2E_BE89_2BE06C3398A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HostsDlg.h : header file
//

class CMyIPWinClientDlg;

/////////////////////////////////////////////////////////////////////////////
// CHostsDlg dialog

class CHostsDlg : public CToolTipDlg
{
// Construction
public:
	CHostMgr * m_pHostMgr;
	CHostsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHostsDlg)
	enum { IDD = IDD_HOSTS };
	CComboBox	m_HostCombo;
	CString	m_sNewHost;
	CString	m_sHost;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHostsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHostsDlg)
	afx_msg void OnDel();
	afx_msg void OnNew();
	virtual BOOL OnInitDialog();
	afx_msg void OnImport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void FillHostCombo();
	CMyIPWinClientDlg * m_pParent;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOSTSDLG_H__2CD2E2A1_5045_4D2E_BE89_2BE06C3398A3__INCLUDED_)
