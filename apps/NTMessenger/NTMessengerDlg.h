/*************************************************************************
                          NTMessenger
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


// NTMessengerDlg.h : header file
//

#if !defined(AFX_NTMESSENGERDLG_H__D96E6EE9_47C3_47F2_A180_891A96B23D84__INCLUDED_)
#define AFX_NTMESSENGERDLG_H__D96E6EE9_47C3_47F2_A180_891A96B23D84__INCLUDED_

#include "TrayIcon.h"	// Added by ClassView
#include "RegBinding.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WM_TRAYNOTIFICATION		(WM_USER + 1)
#define WM_STARTUP				(WM_USER + 2)

/////////////////////////////////////////////////////////////////////////////
// CNTMessengerDlg dialog

class CNTMessengerDlg : public CDialog
{
// Construction
public:
	CNTMessengerDlg(CWnd* pParent = NULL);	// standard constructor
	~CNTMessengerDlg();
// Dialog Data
	//{{AFX_DATA(CNTMessengerDlg)
	enum { IDD = IDD_NTMESSENGER_DIALOG };
	CButton	m_ClearButton;
	CButton	m_OptionsButton;
	CButton	m_SendButton;
	CComboBox	m_ServerCombo;
	CString	m_sName;
	CString	m_sMessageText;
	//}}AFX_DATA
	BOOL m_bStartMinimized;
	BOOL m_bDeleteWhenSent;
	BOOL m_bRescan;
	int m_nMinutes;
	CString m_sPDC;
	CString m_sDomain;
	CRegBinding rb;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNTMessengerDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CNTMessengerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnMultiple();
	afx_msg void OnSelchangeServercombo();
	afx_msg void OnSend();
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClear();
	afx_msg void OnOptions();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnAbout();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	afx_msg LRESULT OnTrayNotification(WPARAM wParam, LPARAM lParam);
	afx_msg void OnRestore();
	afx_msg void OnStartup();
	DECLARE_MESSAGE_MAP()
private:
	bool m_bClose;
	CToolTipCtrl m_ToolTip;
	enum {TimerID = 1};
	void RescanTimer();
	bool ParseRecipients(CString& sServer);

	CStringArray saServer;
	CStringArray saRecipients;
	static _TCHAR * sAll;

	void ErrorMsg(LPTSTR pMsg);
	bool FillServerCombo();
	CTrayIcon TrayIcon;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NTMESSENGERDLG_H__D96E6EE9_47C3_47F2_A180_891A96B23D84__INCLUDED_)
