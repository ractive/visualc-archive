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


// ToolTipDlg.cpp : implementation file
//

#include "stdafx.h"
#include "myipwinclient.h"
#include "ToolTipDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolTipDlg dialog


CToolTipDlg::CToolTipDlg(UINT ID, CWnd* pParent /*=NULL*/)
	: CDialog(ID, pParent)
{
	//{{AFX_DATA_INIT(CToolTipDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}



BEGIN_MESSAGE_MAP(CToolTipDlg, CDialog)
	//{{AFX_MSG_MAP(CToolTipDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolTipDlg message handlers

BOOL CToolTipDlg::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message== WM_LBUTTONDOWN || pMsg->message== WM_LBUTTONUP || pMsg->message== WM_MOUSEMOVE)
		m_ToolTip.RelayEvent(pMsg);
	
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CToolTipDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	EnableToolTips();
	m_ToolTip.Create(this);
	m_ToolTip.SetDelayTime(200);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CToolTipDlg::AddTool(CWnd *pWnd, LPCTSTR lpszText, LPRECT lpRectTool /* = NULL */, UINT nIDTool /* = 0 */)
{
	return m_ToolTip.AddTool(pWnd, lpszText, lpRectTool, nIDTool);
}

void CToolTipDlg::Activate(BOOL bActivate)
{
	m_ToolTip.Activate(bActivate);
}
