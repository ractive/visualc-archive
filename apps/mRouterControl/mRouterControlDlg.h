// mRouterControlDlg.h : header file
//

#if !defined(AFX_MROUTERCONTROLDLG_H__D926B3EE_58B0_4E95_91E8_4F6D8C0BCEA0__INCLUDED_)
#define AFX_MROUTERCONTROLDLG_H__D926B3EE_58B0_4E95_91E8_4F6D8C0BCEA0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMRouterControlDlg dialog

class CMRouterControlDlg : public CDialog
{
// Construction
public:
	CMRouterControlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMRouterControlDlg)
	enum { IDD = IDD_MROUTERCONTROL_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMRouterControlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMRouterControlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnKill();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MROUTERCONTROLDLG_H__D926B3EE_58B0_4E95_91E8_4F6D8C0BCEA0__INCLUDED_)
