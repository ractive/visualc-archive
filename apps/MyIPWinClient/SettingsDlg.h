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


#if !defined(AFX_SETTINGSDLG_H__063699C0_6DDA_11D3_82D7_0000B4A265C3__INCLUDED_)
#define AFX_SETTINGSDLG_H__063699C0_6DDA_11D3_82D7_0000B4A265C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettingsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSettingsDlg dialog

#include "ToolTipDlg.h"

class CSettingsDlg : public CToolTipDlg
{
// Construction
public:
	CSettingsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSettingsDlg)
	enum { IDD = IDD_SETTINGS };
	CButton m_LanConnection;
	CButton m_ModemConnection;
	CButton	m_ConnectionType;
	BOOL	m_bAddToTray;
	BOOL	m_bMinimizeAtStartup;
	BOOL	m_bStorePass;
	BOOL	m_bStoreUser;
	BOOL	m_bUpdateAtStartup;
	BOOL	m_bUsePort18080;
	BOOL	m_bAutoUpdate;
	BOOL	m_bLANConn;
	BOOL	m_bModemConn;
	BOOL	m_bAlwaysSendIP;
	BOOL	m_bWarn;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingsDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void ReDraw(CWnd * pWnd = NULL);

	// Generated message map functions
	//{{AFX_MSG(CSettingsDlg)
	afx_msg void OnStorepass();
	afx_msg void OnStoreuser();
	afx_msg void OnAutoupdate();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	afx_msg void OnLan();
	afx_msg void OnModem();
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGSDLG_H__063699C0_6DDA_11D3_82D7_0000B4A265C3__INCLUDED_)
