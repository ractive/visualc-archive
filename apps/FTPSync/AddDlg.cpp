// AddDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FTPSync.h"
#include "AddDlg.h"
#include "DirectoryPicker.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddDlg dialog


CAddDlg::CAddDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddDlg)
	m_sLocalFolder = _T("");
	m_sFTPServer = _T("");
	m_sFTPDirectory = _T("");
	m_bIncludeSubDirs = FALSE;
	m_bPassiveMode = FALSE;
	m_sPassword = _T("");
	m_nPort = 21;
	m_sUsername = _T("");
	m_bAnonymous = FALSE;
	m_nSyncMode = 0;
	m_nConflict = 0;
	m_nOverwriteFtp = 0;
	m_nOverwriteLocal = 0;
	//}}AFX_DATA_INIT
}


void CAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddDlg)
	DDX_Control(pDX, IDC_USERNAME, m_UsernameCtrl);
	DDX_Control(pDX, IDC_PASSWORD, m_PasswordCtrl);
	DDX_Text(pDX, IDC_LOCALFOLDER, m_sLocalFolder);
	DDX_Text(pDX, IDC_FTPSERVER, m_sFTPServer);
	DDX_Text(pDX, IDC_FTPDIRECTORY, m_sFTPDirectory);
	DDX_Check(pDX, IDC_INCLUDESUBDIRS, m_bIncludeSubDirs);
	DDX_Check(pDX, IDC_PASSIVEMODE, m_bPassiveMode);
	DDX_Text(pDX, IDC_PASSWORD, m_sPassword);
	DDX_Text(pDX, IDC_PORT, m_nPort);
	DDV_MinMaxUInt(pDX, m_nPort, 1, 65534);
	DDX_Text(pDX, IDC_USERNAME, m_sUsername);
	DDX_Check(pDX, IDC_ANONYMOUS, m_bAnonymous);
	DDX_Radio(pDX, IDC_SYNCTWOWAY, m_nSyncMode);
	DDX_Radio(pDX, IDC_CONFLICTASK, m_nConflict);
	DDX_Radio(pDX, IDC_ALWAYSOVERWRITEFTP, m_nOverwriteFtp);
	DDX_Radio(pDX, IDC_ALWAYSOVERWRITELOCAL, m_nOverwriteLocal);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddDlg, CDialog)
	//{{AFX_MSG_MAP(CAddDlg)
	ON_BN_CLICKED(IDC_CHOOSELOCAL, OnChooseLocalFolder)
	ON_BN_CLICKED(IDC_ANONYMOUS, OnAnonymous)
	ON_BN_CLICKED(IDC_SYNCFTP, OnSyncFtp)
	ON_BN_CLICKED(IDC_SYNCLOCAL, OnSyncLocal)
	ON_BN_CLICKED(IDC_SYNCTWOWAY, OnSyncTwoway)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddDlg message handlers

void CAddDlg::OnChooseLocalFolder() 
{
	UpdateData();
	CDirectoryPicker picker(m_hWnd, &m_sLocalFolder);
	UpdateData(FALSE);	
}

void CAddDlg::OnAnonymous() 
{
	UpdateData();
	
	if (m_bAnonymous) {
		m_sUsername = "Anonymous";
		m_sPassword = _T("user@example.com");
		m_PasswordCtrl.SetPasswordChar(0);
		UpdateData(FALSE);
	}

	m_PasswordCtrl.SetPasswordChar(m_bAnonymous ? 0 : '*');

	m_UsernameCtrl.EnableWindow(!m_bAnonymous);
	m_UsernameCtrl.SetReadOnly(m_bAnonymous);

	m_PasswordCtrl.EnableWindow(!m_bAnonymous);
	m_PasswordCtrl.SetReadOnly(m_bAnonymous);
}

void CAddDlg::OnSyncFtp() 
{
	UpdateData();

	GetDlgItem(IDC_ALWAYSOVERWRITELOCAL)->EnableWindow(FALSE);
	GetDlgItem(IDC_ASKOVERWRITELOCAL)->EnableWindow(FALSE);

	GetDlgItem(IDC_ALWAYSOVERWRITEFTP)->EnableWindow(TRUE);
	GetDlgItem(IDC_ASKOVERWRITEFTP)->EnableWindow(TRUE);

	GetDlgItem(IDC_CONFLICTASK)->EnableWindow(FALSE);
	GetDlgItem(IDC_CONFLICTUPLOAD)->EnableWindow(FALSE);
	GetDlgItem(IDC_CONFLICTDOWNLOAD)->EnableWindow(FALSE);

	m_nConflict = 1;

	UpdateData(FALSE);
}

void CAddDlg::OnSyncLocal() 
{
	UpdateData();
	GetDlgItem(IDC_ALWAYSOVERWRITELOCAL)->EnableWindow(TRUE);
	GetDlgItem(IDC_ASKOVERWRITELOCAL)->EnableWindow(TRUE);

	GetDlgItem(IDC_ALWAYSOVERWRITEFTP)->EnableWindow(FALSE);
	GetDlgItem(IDC_ASKOVERWRITEFTP)->EnableWindow(FALSE);

	GetDlgItem(IDC_CONFLICTASK)->EnableWindow(FALSE);
	GetDlgItem(IDC_CONFLICTUPLOAD)->EnableWindow(FALSE);
	GetDlgItem(IDC_CONFLICTDOWNLOAD)->EnableWindow(FALSE);

	m_nConflict = 2;

	UpdateData(FALSE);

}

void CAddDlg::OnOK() 
{
	UpdateData();

	m_bSyncFtp		= (m_nSyncMode == 0 || m_nSyncMode == 1);
	m_bSyncLocal	= (m_nSyncMode == 0 || m_nSyncMode == 2);

	m_bAskLocalOverwrite	= m_nOverwriteLocal == 1;
	
	m_bAskFtpOverwrite		= m_nOverwriteFtp == 1;

	m_bAskIfConflict		= m_nConflict == 0;
	m_bUpload				= m_nConflict == 1;	
	
	CDialog::OnOK();
}

BOOL CAddDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if (m_bSyncFtp && m_bSyncLocal) {
		m_nSyncMode = 0;
	}
	else if (m_bSyncFtp) {
		m_nSyncMode = 1;
	}
	else {
		m_nSyncMode = 2;
	}

	if (m_bAskLocalOverwrite) {
		m_nOverwriteLocal = 1;
	}
	else {
		m_nOverwriteLocal = 0;
	}

	if (m_bAskFtpOverwrite) {
		m_nOverwriteFtp = 1;
	}
	else {
		m_nOverwriteFtp = 0;
	}
	
	if (m_bAskIfConflict) {
		m_nConflict = 0;
	}
	else if (m_bUpload) {
		m_nConflict = 1;
	}
	else {
		m_nConflict = 2;
	}

	if (m_sUsername == "Anonymous" && m_sPassword == _T("user@example.com")) {
		m_bAnonymous = TRUE;
	}

	UpdateData(FALSE);
	
	OnAnonymous();

	if (m_nSyncMode == 1) {
		OnSyncFtp();
	}
	else if (m_nSyncMode == 2) {
		OnSyncLocal();
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CAddDlg::OnSyncTwoway() 
{
	UpdateData();

	GetDlgItem(IDC_ALWAYSOVERWRITELOCAL)->EnableWindow(TRUE);
	GetDlgItem(IDC_ASKOVERWRITELOCAL)->EnableWindow(TRUE);

	GetDlgItem(IDC_ALWAYSOVERWRITEFTP)->EnableWindow(TRUE);
	GetDlgItem(IDC_ASKOVERWRITEFTP)->EnableWindow(TRUE);

	GetDlgItem(IDC_CONFLICTASK)->EnableWindow(TRUE);
	GetDlgItem(IDC_CONFLICTUPLOAD)->EnableWindow(TRUE);
	GetDlgItem(IDC_CONFLICTDOWNLOAD)->EnableWindow(TRUE);

}
