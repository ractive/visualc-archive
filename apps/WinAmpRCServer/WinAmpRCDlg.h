// WinAmpRCDlg.h : header file
//

#if !defined(AFX_WINAMPRCDLG_H__0487721A_D6FC_4C19_BF9C_A615E587A299__INCLUDED_)
#define AFX_WINAMPRCDLG_H__0487721A_D6FC_4C19_BF9C_A615E587A299__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWinAmpRCDlg dialog

#include "ListenSocket.h"

class CWinAmpRCDlg : public CDialog
{
// Construction
public:
	void SendInfoEx();
	void SendInfo();
	void OnAccept();
	void OnCloseSocket();
	CString m_sWinAmpExe;
	CWinAmpRCDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWinAmpRCDlg)
	enum { IDD = IDD_WINAMPRC_DIALOG };
	UINT	m_nPort;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinAmpRCDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	CListenSocket m_ConnectSocket;
	CListenSocket m_ListenSocket;

// Implementation
protected:
	BOOL m_bConnectionAccepted;
	BOOL m_bConnected;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWinAmpRCDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnListen();
	afx_msg void OnDestroy();
	afx_msg void OnStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINAMPRCDLG_H__0487721A_D6FC_4C19_BF9C_A615E587A299__INCLUDED_)
