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


#if !defined(AFX_MULTIPLERECIPIENTSDLG_H__8F7347D7_B4A9_4070_A4B7_AF2A4FAC82C4__INCLUDED_)
#define AFX_MULTIPLERECIPIENTSDLG_H__8F7347D7_B4A9_4070_A4B7_AF2A4FAC82C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MultipleRecipientsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMultipleRecipientsDlg dialog

class CMultipleRecipientsDlg : public CDialog
{
// Construction
public:
	CStringArray * psaRecipients;
	CStringArray * psaServer;
	CMultipleRecipientsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMultipleRecipientsDlg)
	enum { IDD = IDD_MULTIPLEDLG };
	CListBox	m_RecipientList;
	CListBox	m_ServerList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultipleRecipientsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMultipleRecipientsDlg)
	afx_msg void OnAdd();
	virtual BOOL OnInitDialog();
	afx_msg void OnRemove();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CToolTipCtrl m_ToolTip;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTIPLERECIPIENTSDLG_H__8F7347D7_B4A9_4070_A4B7_AF2A4FAC82C4__INCLUDED_)
