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


#if !defined(AFX_TOOLTIPDLG_H__5225E0B4_F340_4801_93D6_4363E23A9190__INCLUDED_)
#define AFX_TOOLTIPDLG_H__5225E0B4_F340_4801_93D6_4363E23A9190__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ToolTipDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CToolTipDlg dialog

class CToolTipDlg : public CDialog
{
// Construction
public:
	void Activate(BOOL bActivate);
	BOOL AddTool(CWnd *pWnd, LPCTSTR lpszText, LPRECT lpRectTool = NULL, UINT nIDTool = 0);
	CToolTipDlg(UINT IDD, CWnd* pParent);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CToolTipDlg)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolTipDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CToolTipDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CToolTipCtrl m_ToolTip;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLTIPDLG_H__5225E0B4_F340_4801_93D6_4363E23A9190__INCLUDED_)
