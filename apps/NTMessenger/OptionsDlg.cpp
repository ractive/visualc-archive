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


// OptionsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NTMessenger.h"
#include "OptionsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsDlg dialog


COptionsDlg::COptionsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COptionsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COptionsDlg)
	m_bStartMinimized = FALSE;
	m_bDeleteWhenSent = FALSE;
	m_nMinutes = 0;
	m_bRescan = FALSE;
	m_sPDC = _T("");
	m_sDomain = _T("");
	//}}AFX_DATA_INIT

	m_bOnlyWorksations = FALSE;
}


void COptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsDlg)
	DDX_Check(pDX, IDC_STARTMINIMIZED, m_bStartMinimized);
	DDX_Check(pDX, IDC_DELETEWHENSENT, m_bDeleteWhenSent);
	DDX_Text(pDX, IDC_MINUTES, m_nMinutes);
	DDV_MinMaxUInt(pDX, m_nMinutes, 1, 999);
	DDX_Check(pDX, IDC_RESCAN, m_bRescan);
	DDX_Text(pDX, IDC_PDC, m_sPDC);
	DDX_Text(pDX, IDC_DOMAIN, m_sDomain);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsDlg, CDialog)
	//{{AFX_MSG_MAP(COptionsDlg)
	ON_BN_CLICKED(IDC_RESCAN, OnRescan)
	ON_BN_CLICKED(IDC_RESCANNOW, OnRescanNow)
	ON_BN_CLICKED(IDC_ONLYWORKSTATIONS, OnOnlyWorkstations)
	ON_BN_CLICKED(IDC_ALLPCS, OnAllPCs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsDlg message handlers

void COptionsDlg::OnRescan() 
{
	UpdateData();
	if (m_bRescan) {
		CWnd *pItem = GetDlgItem(IDC_MINUTES);
		pItem->ModifyStyle(WS_DISABLED, 0);
	}
	else {
		CWnd *pItem = GetDlgItem(IDC_MINUTES);
		pItem->ModifyStyle(0, WS_DISABLED);
	}
	
	InvalidateRect(NULL);
}

BOOL COptionsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	OnRescan();
	
	if (m_bOnlyWorksations) {
		((CButton *)GetDlgItem(IDC_ONLYWORKSTATIONS))->SetCheck(1);
	}
	else {
		((CButton *)GetDlgItem(IDC_ALLPCS))->SetCheck(1);
	
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void COptionsDlg::OnRescanNow() 
{
	m_bRescanNow = TRUE;
	EndDialog(IDOK);
}

void COptionsDlg::OnOnlyWorkstations() 
{
	m_bOnlyWorksations = TRUE;
	m_bRescanNow = TRUE;
}

void COptionsDlg::OnAllPCs() 
{
	m_bOnlyWorksations = FALSE;	
	m_bRescanNow = TRUE;
}
