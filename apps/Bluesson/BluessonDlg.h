/*************************************************************************
  Bluesson
**************************************************************************

Copyright (C) June 2002 by Jean-Pierre Bergamin

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

// BluessonDlg.h : header file
//

#if !defined(AFX_BLUESSONDLG_H__B3EF006D_75DC_46C1_A5ED_E4C9F5D0240D__INCLUDED_)
#define AFX_BLUESSONDLG_H__B3EF006D_75DC_46C1_A5ED_E4C9F5D0240D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CBluessonDlg dialog

#include "EricssonAT.h"
#include "TrayIcon.h"
#include "RegBinding.h"

class CBluessonDlg : public CDialog
{
// Construction
public:
	CBluessonDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CBluessonDlg)
	enum { IDD = IDD_BLUESSON_DIALOG };
	CComboBox	m_ComPortCtrl;
	CString	m_sWinAmpExe;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBluessonDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
	
// Implementation
protected:
	BOOL StartCommunication();
	CStatusBar  m_wndStatusBar;

	BOOL m_bWaitMenuEntry;
	CEricssonAT * m_pAT;
	HICON m_hIcon;
	void ShowTrayIcon(BOOL bShow);
	void ShowTaskIcon(bool bShow = true);


	// Generated message map functions
	//{{AFX_MSG(CBluessonDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRestore();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnGetWinAmpExe();
	afx_msg void OnSelchangeComport();
	afx_msg void OnReset();
	//}}AFX_MSG
	afx_msg void OnComdaemonMsg(UINT pParam, long lParam);
	afx_msg LRESULT OnTrayNotification(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnStartup(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bInit;
	CTrayIcon TrayIcon;
	int m_nComPort;
	BOOL m_bFirstStart;
	CRegBinding rb;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BLUESSONDLG_H__B3EF006D_75DC_46C1_A5ED_E4C9F5D0240D__INCLUDED_)
