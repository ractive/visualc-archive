// TCPServerExDlg.h : header file
//

#if !defined(AFX_TCPSERVEREXDLG_H__208D8C5E_2F5D_45F3_85C5_829F1A4E4BEB__INCLUDED_)
#define AFX_TCPSERVEREXDLG_H__208D8C5E_2F5D_45F3_85C5_829F1A4E4BEB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CServerSocket;

/////////////////////////////////////////////////////////////////////////////
// CTCPServerExDlg dialog

class CTCPServerExDlg : public CDialog
{
// Construction
public:
	CTCPServerExDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTCPServerExDlg)
	enum { IDD = IDD_TCPSERVEREX_DIALOG };
	CButton	m_StopCtrl;
	CButton	m_ListenCtrl;
	UINT	m_nPort;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCPServerExDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CServerSocket * m_pServerSocket;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTCPServerExDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnListen();
	afx_msg void OnStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TCPSERVEREXDLG_H__208D8C5E_2F5D_45F3_85C5_829F1A4E4BEB__INCLUDED_)
