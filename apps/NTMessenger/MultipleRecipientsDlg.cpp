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


// MultipleRecipientsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NTMessenger.h"
#include "MultipleRecipientsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMultipleRecipientsDlg dialog


CMultipleRecipientsDlg::CMultipleRecipientsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMultipleRecipientsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMultipleRecipientsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	psaServer = NULL;
}


void CMultipleRecipientsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMultipleRecipientsDlg)
	DDX_Control(pDX, IDC_RECIPIENTS, m_RecipientList);
	DDX_Control(pDX, IDC_SERVERS, m_ServerList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMultipleRecipientsDlg, CDialog)
	//{{AFX_MSG_MAP(CMultipleRecipientsDlg)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_LBN_DBLCLK(IDC_RECIPIENTS, OnRemove)
	ON_LBN_DBLCLK(IDC_SERVERS, OnAdd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultipleRecipientsDlg message handlers

void CMultipleRecipientsDlg::OnAdd() 
{
	if (m_ServerList.GetSelCount() > 0) {
		// Yes, we have a selection

		// Go through all items and see if it is selected or not.
		// If yes, add it to the recipient's list.
		for (int i = 0; i < m_ServerList.GetCount(); i++) {
			// Check if the current item is selected or not.
			if (m_ServerList.GetSel(i) > 0) {
				// If it is selected, get the servername (text)...
				CString sEntry;
				m_ServerList.GetText(i, sEntry);
				// ... add it to the recipients list ...
				m_RecipientList.AddString(sEntry);
				// ... and remove it from the server list.
				m_ServerList.DeleteString(i);

				// The selected item is not not in the list any more. This 
				// means, the index is -1
				i--;
			}
		}
	}
}

void CMultipleRecipientsDlg::OnRemove() 
{
	// Same as above, but the other way :-)

	if (m_RecipientList.GetSelCount() > 0) {
		// Yes, we have a selection

		// Go through all items and see if it is selected or not.
		// If yes, delete if the recipient's list.
		for (int i = 0; i < m_RecipientList.GetCount(); i++) {
			// Check if the current item is selected or not.
			if (m_RecipientList.GetSel(i) > 0) {
				// If it is selected, get the servername (text)...
				CString sEntry;
				m_RecipientList.GetText(i, sEntry);
				// ... add it to the server list ...
				m_ServerList.AddString(sEntry);
				// ... and remove it from the recipient list.
				m_RecipientList.DeleteString(i);

				// The selected item is not not in the list any more. This 
				// means, the index is -1
				i--;
			}
		}
	}
	
}

BOOL CMultipleRecipientsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	EnableToolTips();
	m_ToolTip.Create(this);
	m_ToolTip.SetDelayTime(500);
	m_ToolTip.AddTool(GetDlgItem(IDC_SERVERS), _T("Double click on an entry to add it to the recipients"));
	m_ToolTip.AddTool(GetDlgItem(IDC_RECIPIENTS), _T("Double click on an entry to remove it from the recipients"));
	m_ToolTip.AddTool(GetDlgItem(IDC_ADD), _T("Add the selected entry to the recipients"));
	m_ToolTip.AddTool(GetDlgItem(IDC_REMOVE), _T("Remove the selected entry from the recipients"));

	if (psaServer != NULL) {
		for (int i = 0; i < psaServer->GetSize(); i++) {
			m_ServerList.AddString(psaServer->GetAt(i));
		}
	}

	if (psaRecipients != NULL) {
		for (int i = 0; i < psaRecipients->GetSize(); i++) {
			m_RecipientList.AddString(psaRecipients->GetAt(i));
			m_ServerList.DeleteString(m_ServerList.FindString(-1, psaRecipients->GetAt(i)));
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CMultipleRecipientsDlg::OnOK() 
{
	// Add all server from the recipients list to the recipients string array.
	psaRecipients->RemoveAll();
	for (int i = 0; i < m_RecipientList.GetCount(); i++) {
		CString sEntry;
		m_RecipientList.GetText(i, sEntry);
		psaRecipients->Add(sEntry);
	}
	
	CDialog::OnOK();
}

BOOL CMultipleRecipientsDlg::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message== WM_LBUTTONDOWN || pMsg->message== WM_LBUTTONUP || pMsg->message== WM_MOUSEMOVE)
		m_ToolTip.RelayEvent(pMsg);
	
	return CDialog::PreTranslateMessage(pMsg);
}
