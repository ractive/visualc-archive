/*************************************************************************
                     MyIPWinClient
**************************************************************************

Copyright (C) April, 2000 Jean-Pierre Bergamin, james@ractive.ch

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
***************************************************************************/



// MyIPWinClientDlg.h : header file
//

#if !defined(AFX_MyIPWINCLIENTDLG_H__73CD9917_351E_11D3_81C9_0000B4A265C3__INCLUDED_)
#define AFX_MyIPWINCLIENTDLG_H__73CD9917_351E_11D3_81C9_0000B4A265C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMyIPWinClientDlg dialog

//#define WM_TRAYNOTIFICATION WM_USER + 10

#include "RegBinding.h"
#include "TrayIcon.h"	// Added by ClassView
#include "HyperLink.h"
#include "ToolTipDlg.h"
#include "MyIPException.h"
#include "HostMgr.h"	// Added by ClassView

class CMyIPWinClientDlg : public CToolTipDlg
{
	struct tagThreadInfo {
		HANDLE hRasEvent;
		HANDLE hKillMe;
		HWND hNotificationWnd;
	} ThreadInfo;
// Construction
public:
	BOOL m_bUpdated;
	BOOL m_bStorePass;
	BOOL m_bStoreUser;
	BOOL m_bUsePort18080;
	int	m_nMin;
	BOOL m_bMinChk;
	BOOL m_bUpdateAtStartup;
	CMyIPWinClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMyIPWinClientDlg)
	enum { IDD = IDD_MYIPWINCLIENT_DIALOG };
	CComboBox	m_IPAddressCombo;
	CComboBox	m_HostCombo;
	CHyperLink	m_myiporg;
	CString	m_sMX;
	CString	m_sPassword;
	CString	m_sUsername;
	CString	m_sEmail;
	CString	m_sHost;
	CString	m_sStatus;
	CString	m_sIPAddress;
	//}}AFX_DATA
	BOOL m_bMinimizeAtStartup;
	BOOL m_bWarn;
	BOOL m_bAddToTray;
	BOOL m_bAutoUpdate;
	BOOL m_bAlwaysSendIP;
	BOOL m_bLANConn;
	BOOL m_bFirstStart;
	CString m_sHostToPing;
	CRegBinding rb;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyIPWinClientDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void ShowTrayIcon(BOOL bShow = TRUE);
	void ShowTaskIcon(bool bShow = true);
	CTrayIcon TrayIcon;
	HICON m_hIcon;
	CStatusBar  m_wndStatusBar;

	// Generated message map functions
	//{{AFX_MSG(CMyIPWinClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSettings();
	afx_msg void OnRestore();
	afx_msg void OnExit();
	afx_msg LRESULT OnTrayNotification(WPARAM wParam, LPARAM lParam);
	afx_msg void OnAbout();
	afx_msg void OnStartup();
	afx_msg void OnHostbutton();
	afx_msg void OnPassbutton();
	afx_msg void OnGetip();
	afx_msg void OnAdvupdate();
	afx_msg void OnDeleteacc();
	//}}AFX_MSG
	afx_msg void OnRasDaemonMsg(UINT pParam, long lParam);
	afx_msg void UpdateAccount();
	afx_msg void CreateAccount();
	DECLARE_MESSAGE_MAP()
private:
	void FillHostCombo();
	CHostMgr m_hostMgr;
	CStringArray m_saHosts;
	void SetUpdated();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MyIPWINCLIENTDLG_H__73CD9917_351E_11D3_81C9_0000B4A265C3__INCLUDED_)
