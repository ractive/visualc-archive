// WMPDlg.h : header file
//

#if !defined(AFX_WMPDLG_H__8D8F5682_B031_41FF_937F_1668F7F44060__INCLUDED_)
#define AFX_WMPDLG_H__8D8F5682_B031_41FF_937F_1668F7F44060__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wmpplayer4.h"

/////////////////////////////////////////////////////////////////////////////
// CWMPDlg dialog

class CWMPDlg : public CDialog
{
// Construction
public:
	CWMPDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWMPDlg)
	enum { IDD = IDD_WMP_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWMPDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWMPDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CWMPPlayer4 player;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WMPDLG_H__8D8F5682_B031_41FF_937F_1668F7F44060__INCLUDED_)
