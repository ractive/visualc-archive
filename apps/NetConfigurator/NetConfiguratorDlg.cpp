// NetConfiguratorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NetConfigurator.h"
#include "NetConfiguratorDlg.h"
#include "NetConfigDlg.h"
#include "ConfigNameDlg.h"
#include "WaitDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

BOOL Pump(HWND hWnd) {
	if (!::IsWindow(hWnd)) {
		return FALSE;
	}

	MSG msg;
	// Retrieve and dispatch any waiting messages.
	while (::PeekMessage (&msg, NULL, 0, 0, PM_NOREMOVE)) {
		if (!AfxGetApp ()->PumpMessage ()) {
			::PostQuitMessage (0);
			return FALSE;
		}
	}

	return TRUE;
}

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetConfiguratorDlg dialog

CNetConfiguratorDlg::CNetConfiguratorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNetConfiguratorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetConfiguratorDlg)
	m_sConfigFile = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNetConfiguratorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetConfiguratorDlg)
	DDX_Control(pDX, IDC_SETTINGSCOMBO, m_ConfigCtrl);
	DDX_CBString(pDX, IDC_SETTINGSCOMBO, m_sConfigFile);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CNetConfiguratorDlg, CDialog)
	//{{AFX_MSG_MAP(CNetConfiguratorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_MODIFY, OnModify)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_APPLY, OnApply)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetConfiguratorDlg message handlers

BOOL CNetConfiguratorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	
	GetConfigs();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CNetConfiguratorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CNetConfiguratorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CNetConfiguratorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CNetConfiguratorDlg::OnAdd() 
{
	CNetConfigDlg dlg;
	if (dlg.DoModal() == IDCANCEL) {
		return;
	}
	
	CConfigNameDlg cdlg;
	
	while(true) {
		if (cdlg.DoModal() == IDCANCEL) {
			return;
		}

		// Check if the file already exists. If yes, ask for a new name again...
		CFileFind finder;
		if (!finder.FindFile(m_sSystemDirectory + "\\" + cdlg.m_sName + ".ncfg")) {
			break;
		}

		if (MessageBox("There's already a setting with the same name.\r\n\rDo you want to overwrite it?.", "File exists", MB_YESNO | MB_ICONQUESTION) == IDYES) {
			break;
		}
	}


	WriteConfigFile(m_sSystemDirectory + "\\" + cdlg.m_sName + ".ncfg", dlg.m_bStaticIP, dlg.m_bStaticDNS, dlg.m_sIP, dlg.m_sMask, dlg.m_sGW, dlg.m_sDNS1, dlg.m_sDNS2);
	
	GetConfigs();
}

void CNetConfiguratorDlg::OnModify() 
{
	UpdateData();

	CNetConfigDlg dlg;

	if (!ParseConfigFile(m_sSystemDirectory + "\\" + m_sConfigFile, dlg.m_bStaticIP, dlg.m_bStaticDNS, dlg.m_sIP, dlg.m_sMask, dlg.m_sGW, dlg.m_sDNS1, dlg.m_sDNS2)) {
		return;
	}

	if (dlg.DoModal() == IDCANCEL) {
		return;
	}

	WriteConfigFile(m_sSystemDirectory + "\\" + m_sConfigFile, dlg.m_bStaticIP, dlg.m_bStaticDNS, dlg.m_sIP, dlg.m_sMask, dlg.m_sGW, dlg.m_sDNS1, dlg.m_sDNS2);
}

void CNetConfiguratorDlg::OnDelete() 
{
	UpdateData();
	if (MessageBox("Are you sure you want to delete this configuration?", "Delete configuration", MB_YESNO | MB_ICONQUESTION) == IDNO) {
		return;
	}

	if (!DeleteFile(m_sSystemDirectory + "\\" + m_sConfigFile)) {
		MessageBox("The file could not be deleted!", "Error", MB_OK | MB_ICONEXCLAMATION);
	}

	GetConfigs();
}

void CNetConfiguratorDlg::GetConfigs()
{
	LPTSTR pBuff = m_sSystemDirectory.GetBuffer(1024);
	GetSystemDirectory(pBuff, 1024);
	m_sSystemDirectory.ReleaseBuffer();

	//CStringArray saConfigFiles;

	m_ConfigCtrl.ResetContent();

	CFileFind finder;
	BOOL bFound = finder.FindFile(m_sSystemDirectory + "\\*.ncfg");
	while (bFound) {
		bFound = finder.FindNextFile();
		//saConfigFiles.Add(finder.GetFileName());
		m_ConfigCtrl.AddString(finder.GetFileName());
	}

	if (m_ConfigCtrl.GetCount()) {
		m_ConfigCtrl.SetCurSel(0);
	}
}

BOOL CNetConfiguratorDlg::WriteConfigFile(CString sFileName, BOOL bStaticIP, BOOL bStaticDNS, CString &sIP, CString &sMask, CString &sGW, CString &sDNS1, CString &sDNS2)
{
	

	CFile file;
	if (!file.Open(sFileName, CFile::modeWrite | CFile::modeCreate)) {
		MessageBox("The file could not be created!", "Error", MB_ICONEXCLAMATION | MB_OK);
		return FALSE;
	}



	CString cont;

	if (!bStaticIP) {
		sIP = "dhcp";
	}
	if (!bStaticDNS) {
		sDNS1 = "dhcp";
		sDNS2 = "dhcp";
	}

	//cont.Format("pushd interface ip\r\nset address name=\"LAN-Verbindung\" source=static addr=%s mask=%s\r\nset address name=\"LAN-Verbindung\" gateway=%s gwmetric=0\r\nset dns name=\"LAN-Verbindung\" source=static addr=%s\r\nadd dns name=\"LAN-Verbindung\" addr=%s\r\nset wins name=\"LAN-Verbindung\" source=static addr=none\r\npopd", dlg.m_sIP, dlg.m_sMask, dlg.m_sGW, dlg.m_sDNS1, dlg.m_sDNS2);
	cont.Format("# NetConfigurator settings\r\n# http://www.ractive.ch/gpl/netconfigurator.html for mor info\r\n\r\nip=%s\r\nmask=%s\r\ngateway=%s\r\ndns1=%s\r\ndns2=%s\r\n", sIP, sMask, sGW, sDNS1, sDNS2);

	try {
		file.Write(cont, cont.GetLength());
	}
	catch (CFileException * fe) {
		MessageBox("Not all of the content could be written to the file. Disk full?", "Error", MB_ICONEXCLAMATION | MB_OK);
		fe->Delete();
		return FALSE;
	}

	file.Close();

#ifdef _DEBUG
	MessageBox(cont);
#endif

	return TRUE;
}

void CNetConfiguratorDlg::OnApply() 
{
	UpdateData();

	CString sIP, sMask, sDNS1, sDNS2, sGW;
	BOOL bStaticIP = FALSE;
	BOOL bStaticDNS = FALSE;

	if (!ParseConfigFile(m_sSystemDirectory + "\\" + m_sConfigFile, bStaticIP, bStaticDNS, sIP, sMask, sGW, sDNS1, sDNS2)) {
		return;
	}

	char* tmpname = _tempnam("C:\\Temp", "netsh");


	FILE* tmp = NULL;
	tmp = fopen(tmpname, "wb");
	if (!tmp) {
		MessageBox("No temporary file could be created!", "Error", MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	CString cont = "pushd interface ip\r\nset address name=\"LAN-Verbindung\" source=";
	if (bStaticIP) {
		cont += "static addr=" + sIP + " mask=" + sMask + "\r\nset address name=\"LAN-Verbindung\" gateway=" + sGW + " gwmetric=0";
	}
	else {
		cont += "dhcp";
	}

	cont += "\r\nset dns name=\"LAN-Verbindung\" source=";

	if (bStaticDNS) {
		cont += "static addr=" + sDNS1;
		if (!sDNS2.IsEmpty()) {
			cont += "\r\nadd dns name=\"LAN-Verbindung\" addr=" + sDNS2;
		}
	}
	else {
		cont += "dhcp";
	}
	
	cont += "\r\n";

	if (bStaticDNS) {
		cont += "set wins name=\"LAN-Verbindung\" source=static addr=none";
	}
	else {
		cont += "set wins name=\"LAN-Verbindung\" source=dhcp";
	}

	cont += "\r\npopd";
	fwrite(cont, sizeof(TCHAR), cont.GetLength(), tmp);
	fclose(tmp);

	STARTUPINFO sui = {0};
	sui.cb = sizeof(sui);
	sui.lpReserved = NULL;
	sui.lpReserved2 = NULL;
	sui.lpDesktop = NULL;
	sui.lpTitle = NULL;
	sui.dwFlags = STARTF_USESHOWWINDOW;
    sui.wShowWindow = SW_HIDE;

	PROCESS_INFORMATION pi = {0};

	CString sCommandLine = m_sSystemDirectory + "\\netsh.exe";
	CString sCL = sCommandLine + " exec ";
	sCL += tmpname;
	
	CWaitDlg dlg;
	dlg.Create(IDD_WAIT, this);
	dlg.CenterWindow(this);
	dlg.ShowWindow(TRUE);

	CWaitCursor wait;
	EnableWindow(FALSE);
	
	if (CreateProcess(NULL, (LPTSTR)(LPCSTR)sCL, NULL, NULL, FALSE, 0, NULL, NULL, &sui, &pi)) {
		while(WaitForSingleObject(pi.hProcess, 500) != WAIT_OBJECT_0) {
			Pump(dlg.m_hWnd);
		}

		DWORD dwReturn;
		GetExitCodeProcess(pi.hProcess, &dwReturn);

		if (dwReturn != 0) {
			MessageBox("The new configuration could not be applied properly.\r\n\r\nWhen switching to DHCP this could also indicate that DHCP was already running.\r\n\r\nPlease make sure that you close the network configuration dialog of the control panel\r\nbefore you apply the new configuration.", "Error", MB_OK | MB_ICONEXCLAMATION);
		}

		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}

	EnableWindow(TRUE);
	dlg.DestroyWindow();


	DWORD dwError = GetLastError();
#ifdef _DEBUG
	MessageBox(cont);
#endif
	DeleteFile(tmpname);
	delete[] tmpname;
}

BOOL CNetConfiguratorDlg::ParseConfigFile(CString sFileName, BOOL &bStaticIP, BOOL &bStaticDNS, CString &sIP, CString &sMask, CString &sGW, CString &sDNS1, CString &sDNS2)
{
	FILE* fp = NULL;
	fp = fopen(sFileName, "r");
	if (!fp) {
		MessageBox("The file could not be opened!", "Error", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	CString sName, sValue;
	sName.GetBuffer(128);
	sValue.GetBuffer(128);

	bStaticDNS = TRUE;
	bStaticIP = TRUE;

	char buf[128];
	while (!feof(fp)) {
		fgets(buf, 128, fp);

		// Skip comments and empty lines
		if (buf[0] == '#' || buf[0] == '\n' || strlen(buf) == 0) {
			continue;
		}

		sValue.Empty();
		sName.Empty();

		LPTSTR pValue = sValue.GetBuffer(128);
		LPTSTR pName = sName.GetBuffer(128);
		if (sscanf(buf, "%[^=]=%s", pName, pValue) == EOF) {
			continue;
		}

		sValue.ReleaseBuffer();
		sName.ReleaseBuffer();

		if (sName == "ip") {
			if (sValue == "dhcp") {
				bStaticIP = FALSE;
			}
			else {
				sIP = sValue;
			}
		}
		else if (sName == "dns1") {
			if (sValue == "dhcp") {
				bStaticDNS = FALSE;
			}
			else {
				sDNS1 = sValue;
			}
		}
		else if (sName == "dns2") {
			if (sValue == "dhcp") {
				bStaticDNS = FALSE;
			}
			else {
				sDNS2 = sValue;
			}
		}
		else if (sName == "gateway") {
			sGW = sValue;
		}
		else if (sName == "mask") {
			sMask = sValue;
		}
	}

	fclose(fp);

	return TRUE;
}
