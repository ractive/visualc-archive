/*************************************************************************
                     DynPfiff
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


// DynPfiffDlg.h : header file
//

#if !defined(AFX_DYNPFIFFDLG_H__CB85D18E_EC87_49AB_815E_8DE61AA5D532__INCLUDED_)
#define AFX_DYNPFIFFDLG_H__CB85D18E_EC87_49AB_815E_8DE61AA5D532__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDynPfiffDlg dialog

#define WM_TRAYNOTIFICATION		(WM_USER + 1)


#include "RegBinding.h"
#include "TrayIcon.h"

class CDynPfiffDlg : public CDialog
{
// Construction
public:
	CDynPfiffDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDynPfiffDlg)
	enum { IDD = IDD_DYNPFIFF_DIALOG };
	CStatic	m_UpdateIcon;
	CComboBox	m_IPCombo;
	CString	m_sUpdateURL;
	CString	m_sIP;
	CString	m_sStatus;
	CString	m_sHTMLFile;
	CString	m_sTemplateFile;
	BOOL	m_bSendIP;
	BOOL	m_bSetOffline;
	int	m_nMin;
	BOOL	m_bSound;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDynPfiffDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	CRegBinding rb;

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDynPfiffDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnUpdate();
	afx_msg void OnClose();
	afx_msg void OnSendip();
	afx_msg void OnSetoffline();
	afx_msg void OnRestore();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	afx_msg LRESULT OnTrayNotification(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	UINT m_nUpdateTimer;
	CTrayIcon TrayIcon;
	void BuildURL(CString &sURL);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DYNPFIFFDLG_H__CB85D18E_EC87_49AB_815E_8DE61AA5D532__INCLUDED_)
