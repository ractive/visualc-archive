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

// CreateAccountDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyIPWinClient.h"
#include "CreateAccountDlg.h"
#include "MyIPHelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCreateAccountDlg dialog


CCreateAccountDlg::CCreateAccountDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCreateAccountDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCreateAccountDlg)
	m_sEmail = _T("");
	m_sPassword = _T("");
	m_sPassword2 = _T("");
	m_sUsername = _T("");
	//}}AFX_DATA_INIT
}


void CCreateAccountDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCreateAccountDlg)
	DDX_Text(pDX, IDC_EMAIL, m_sEmail);
	DDX_Text(pDX, IDC_PASSWORD, m_sPassword);
	DDX_Text(pDX, IDC_PASSWORD2, m_sPassword2);
	DDX_Text(pDX, IDC_USERNAME, m_sUsername);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCreateAccountDlg, CDialog)
	//{{AFX_MSG_MAP(CCreateAccountDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCreateAccountDlg message handlers

void CCreateAccountDlg::OnOK() 
{
	UpdateData();
	int nPassLen = m_sPassword.GetLength();
	if ((nPassLen < 6) || (nPassLen > 15)) {
		MessageBox("The password must have 6 characters minimum\nand 15 caracters maxium.", "Password error", MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	if (m_sPassword != m_sPassword2) {
		m_sPassword.Empty();
		m_sPassword2.Empty();
		MessageBox("Plese reenter the password and the confirmation. They did not match.", "Reenter Password", MB_OK | MB_ICONEXCLAMATION);
		UpdateData(FALSE);
		return;
	}
	if (m_sEmail.IsEmpty()) {
		MessageBox("Plese enter a valid E-Mail address!\r\nThis is required to create a new account.", "Enter E-Mail adress", MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	
	CWaitCursor wait;

	CMyIPHelper * pMyIPHelper = CMyIPHelper::Instance();
	
	//pMyIPHelper->IsAccountAvailable(m_sUsername);

	if (m_bCreated = pMyIPHelper->CreateUser(m_sUsername, m_sPassword, m_sEmail)) {
		CDialog::OnOK();
	}
}
