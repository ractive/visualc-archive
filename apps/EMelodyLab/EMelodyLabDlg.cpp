// EMelodyLabDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EMelodyLab.h"
#include "EMelodyLabDlg.h"
#include "LinksDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

#include "HyperLink.h"

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CHyperLink	m_PageUrl;
	CHyperLink	m_MailUrl;
	CHyperLink	m_WhitePaperUrl;
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
	DDX_Control(pDX, IDC_URL, m_PageUrl);
	DDX_Control(pDX, IDC_MAIL, m_MailUrl);
	DDX_Control(pDX, IDC_WHITEPAPERURL, m_WhitePaperUrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEMelodyLabDlg dialog

CString CEMelodyLabDlg::m_sMelody;
HANDLE CEMelodyLabDlg::m_hStop = NULL;
int CEMelodyLabDlg::m_nDuration = 0;
int CEMelodyLabDlg::m_nStart = -1;
int CEMelodyLabDlg::m_nStop = -1;
BOOL CEMelodyLabDlg::m_bLoop = FALSE;

CEMelodyLabDlg::CEMelodyLabDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEMelodyLabDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEMelodyLabDlg)
	m_nSpeed = 360;
	m_sAvailable = _T("");
	m_bPlayRight = FALSE;
	m_sMelody = _T("");
	m_bLoop = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bModified = FALSE;
}

void CEMelodyLabDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEMelodyLabDlg)
	DDX_Control(pDX, IDC_STOP, m_StopCtrl);
	DDX_Control(pDX, IDC_PLAY, m_PlayCtrl);
	DDX_Control(pDX, IDC_UPLOADURL, m_UploadUrl);
	DDX_Control(pDX, IDC_MELODY, m_MelodyCtrl);
	DDX_Text(pDX, IDC_SPEED, m_nSpeed);
	DDX_Text(pDX, IDC_AVAILABLE, m_sAvailable);
	DDX_Check(pDX, IDC_PLAYRIGHT, m_bPlayRight);
	DDX_Text(pDX, IDC_MELODY, m_sMelody);
	DDX_Check(pDX, IDC_LOOP, m_bLoop);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEMelodyLabDlg, CDialog)
	//{{AFX_MSG_MAP(CEMelodyLabDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PLAY, OnPlay)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_EN_CHANGE(IDC_MELODY, OnChangeMelody)
	ON_BN_CLICKED(IDC_OPEN, OnOpen)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_COMMAND(IDC_SAVEAS, OnSaveAs)
	ON_COMMAND(IDC_CLEAR, OnClear)
	ON_COMMAND(IDC_NEW, OnNew)
	ON_COMMAND(ID_HELP, OnHelp)
	ON_COMMAND(ID_LINKS, OnLinks)
	ON_BN_CLICKED(IDC_REWIND, OnRewind)
	ON_BN_CLICKED(IDC_LOOP, OnLoop)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_POS, OnPos)
	ON_MESSAGE(WM_PLAYTONE, OnPlayTone)
	ON_MESSAGE(WM_THREADEND, OnThreadEnd)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEMelodyLabDlg message handlers

BOOL CEMelodyLabDlg::OnInitDialog()
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
	
	// TODO: Add extra initialization here
	m_nTones = 0;
	m_nChars = 0;

	m_hStop = CreateEvent(NULL, TRUE, FALSE, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEMelodyLabDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CEMelodyLabDlg::OnPaint() 
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
HCURSOR CEMelodyLabDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CEMelodyLabDlg::OnPlay() 
{
	ResetEvent(m_hStop);

	UpdateData();

	m_StopCtrl.EnableWindow(TRUE);
	m_PlayCtrl.EnableWindow(FALSE);
	m_MelodyCtrl.SetReadOnly(TRUE);


	m_nDuration = 1000 * 60 / m_nSpeed;

	m_MelodyCtrl.GetSel(m_nStart, m_nStop);
	
	if (m_nStart == m_nStop) {
		m_nStop = m_sMelody.GetLength();
	}

	AfxBeginThread(PlayThread, m_hWnd);
}

int CEMelodyLabDlg::GetFrequency(CString s, int nOctave)
{
	if (s.IsEmpty()) {
		return -1;
	}

	s.MakeLower();

	int nFreq = 0;

	if		(s == "c") {
		nFreq = 264;
	}
	else if (			s == "#c"	|| s == "(b)d") {
		nFreq = 280;
	}
	else if (s == "d") {
		nFreq = 297;
	}
	else if (			s == "#d"	|| s == "(b)e") {
		nFreq = 314;
	}
	else if (s == "e"				|| s == "(b)f") {
		nFreq = 330;
	}
	else if (s == "f"|| s == "#e") {
		nFreq = 352;
	}
	else if (			s == "#f"	|| s == "(b)g") {
		nFreq = 373;
	}
	else if (s == "g") {
		nFreq = 396;
	}
	else if (			s == "#g"	|| s == "(b)a") {
		nFreq = 419;
	}
	else if (s == "a") {
		nFreq = 440;
	}
	else if (			s == "#a"	|| s == "(b)b") {
		nFreq = 470;
	}
	else if (s == "b") {
		nFreq = 495;
	}
	else if (			s == "#b") {
		nFreq = 2 * 264;
	}
	else {
		::MessageBox(NULL, "Invalid tone " + s, "Error", MB_OK | MB_ICONEXCLAMATION);
		return -1;
	}

	nFreq *= nOctave;

	return nFreq;
}

UINT CEMelodyLabDlg::PlayThread(LPVOID lParam)
{
	HWND hThisWnd = (HWND)lParam;

	while (1) {
		int nDuration = m_nDuration;

		int nOctave = 1;
		int nFrom = m_nStart;
		
		for (int i = m_nStart; i < m_nStop; i++) {
			if (WaitForSingleObject(m_hStop, 0) == WAIT_OBJECT_0) {
				::PostMessage(hThisWnd, WM_THREADEND, 0, 0);
				return 1;
			}

			CString s = m_sMelody[i];
			// Ignore spaces...
			if (s == " ") {
				continue;
			}

			if (s == "p" || s == "P") {
				nDuration = m_nDuration;
				if (s == "P") {
					nDuration *= 2;
				}
				int nStart = i;
				int nStop = i + 1;
				nFrom = i + 1;
				if (i + 1 < m_sMelody.GetLength() && m_sMelody[i + 1] == '.') {
					nDuration = (int)(1.5 * nDuration);
					nStop++;
					nFrom++;
					i++;
				}
				::PostMessage(hThisWnd, WM_POS, nStart, nStop);

				Sleep(nDuration);
				continue;
			}

			if (s == "+") {
				if (nOctave == 3) {
					::MessageBox(NULL, "Too much '+' signs. Allowed are max. 2!", "Error", MB_OK | MB_ICONEXCLAMATION);	
				}
				else {
					nOctave++;
				}
				continue;
			}


			if (s == "#") {
				i++;
				if (i >= m_nStop) {
					break;
				}
				s += m_sMelody[i];
			}
			else if (s == "(") {
				if (i + 3 >= m_nStop) {
					break;
				}
				s+= m_sMelody[++i];
				s+= m_sMelody[++i];
				s+= m_sMelody[++i];
			}

			if (s.Right(1).FindOneOf("CDEFGAB") != -1) {
				nDuration = 2 * m_nDuration;
			}
			else {
				nDuration = m_nDuration;
			}

			if (i + 1 < m_nStop) {
				if (m_sMelody[i + 1] == '.') {
					nDuration = (int)(1.5 * nDuration);
					i++;
				}
			}

			int nFreq = GetFrequency(s, nOctave);
			::PostMessage(hThisWnd, WM_POS, nFrom, i + 1);
			nFrom = i + 1;
			Beep(nFreq, nDuration);
			nOctave = 1;
		}

		if (!m_bLoop) {
			break;
		}

	}
	//::PostMessage(hThisWnd, WM_POS, m_nStop, m_nStop);

	::PostMessage(hThisWnd, WM_THREADEND, 0, 0);

	return 0;
}

void CEMelodyLabDlg::OnStop() 
{
	SetEvent(m_hStop);
	m_MelodyCtrl.SetFocus();
}

LRESULT CEMelodyLabDlg::OnPos(WPARAM wParam, LPARAM lParam)
{
	m_MelodyCtrl.SetFocus();
	m_MelodyCtrl.SetSel(wParam, lParam, FALSE);
	m_MelodyCtrl.UpdateData();
	return 0;
}

LRESULT CEMelodyLabDlg::OnThreadEnd(WPARAM wParam, LPARAM lParam)
{
	m_StopCtrl.EnableWindow(FALSE);
	m_PlayCtrl.EnableWindow(TRUE);
	m_MelodyCtrl.EnableWindow(TRUE);
	m_MelodyCtrl.SetReadOnly(FALSE);

	return 0;
}

LRESULT CEMelodyLabDlg::OnPlayTone(WPARAM wParam, LPARAM lParam)
{
	ResetEvent(m_hStop);

	UpdateData();

	if (!m_bPlayRight) {
		return 0;
	}

	m_nDuration = 1000 * 60 / m_nSpeed;

	m_nStart = wParam - 1;
	m_nStop = lParam;

	if (m_nStart < 0) {
		return 0;
	}

	int nCursor = m_nStart;
	// Check if the tone has prefixes (+, (b) and #)
	while (m_nStop < m_sMelody.GetLength()) {
		if (m_sMelody.Mid(nCursor, 1).FindOneOf("cdefgabcCDEFGABC") != -1) {
			break;
		}
		char c = m_sMelody[nCursor++];
		switch (c) {
		case '+':
			m_nStop++;
			break;
		case '#':
			m_nStop++;
			break;
		}

	}

	if (m_nStop < m_sMelody.GetLength() && m_sMelody[m_nStop] == '.') {
		m_nStop++;
	}

	BOOL bOldLoop = m_bLoop;
	m_bLoop = FALSE;
	PlayThread(m_hWnd);
	m_bLoop = bOldLoop;

	return 0;
}

void CEMelodyLabDlg::OnChangeMelody() 
{
	UpdateData();
	int m_nChars = m_sMelody.GetLength();

	m_bModified = TRUE;

	m_nTones = CountTones();

	if (m_nChars > 120 || m_nTones > 80) {
		MessageBox("The melody is too long! It may only contain 120 characters and 80 tones!", "Melody too long", MB_OK | MB_ICONINFORMATION);
		int nStart = -1;
		int nEnd = -1;
		m_MelodyCtrl.GetSel(nStart, nEnd);
		m_sMelody.Delete(nStart - 1, nEnd - nStart + 1);
		UpdateData(FALSE);
		m_MelodyCtrl.SetFocus();
		m_MelodyCtrl.SetSel(nStart - 1, nEnd - 1);
		m_nChars = m_sMelody.GetLength();
		m_nTones = CountTones();
	}

	m_sAvailable.Format("%d of 120 characters - %d of 80 tones used", m_nChars, m_nTones);
	UpdateData(FALSE);
}

int CEMelodyLabDlg::CountTones()
{
	CString sMel = m_sMelody;
	sMel.MakeLower();
	int nLength = sMel.GetLength();

	int nTones = 0;
	for (int i = 0; i < nLength; i++) {
		char c = sMel[i];
		if ((c >= 'a' && c <= 'g') || c == 'p') {
			nTones++;
		}
	}

	return nTones;
}

void CEMelodyLabDlg::OnOpen() 
{
    OPENFILENAME ofn;
    memset(&ofn, 0, sizeof(ofn));

    // fill OPENFILENAME structure 
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = m_hWnd;
    ofn.lpstrFilter = "EMELODY files (*.emy)\0*.emy\0All Files (*.*)\0*.*\0\0";
    ofn.lpstrFile = m_sFileName.GetBuffer(MAX_PATH);
    ofn.lpstrTitle = "Open EMELODY file...";
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = "mp3";

	BOOL bRet = GetOpenFileName(&ofn);
	m_sFileName.ReleaseBuffer();

    if (bRet) {
		CFile file;
		if (!file.Open(m_sFileName, CFile::modeRead)) {
			MessageBox("The file " + m_sFileName + " could not be opened!", "Error", MB_OK | MB_ICONEXCLAMATION);
			return;
		}

		CString sFileContent;
		const int nBufLen = 1024;
		LPTSTR sBuf = sFileContent.GetBuffer(nBufLen);
		file.Read(sBuf, nBufLen);
		file.Close();
		sFileContent.ReleaseBuffer();
		int nPos = -1;
		TCHAR sKeyWord[] = "MELODY:";
		if ((nPos = sFileContent.Find(sKeyWord)) == -1) {
			nPos = 0;
		}
		else {
			nPos += strlen(sKeyWord);
		}

		m_sMelody = sFileContent.Mid(nPos, sFileContent.Find("\r\n", nPos) - nPos);
	}

	UpdateData(FALSE);

	OnChangeMelody();

	SetWindowText("EMelodyLab - " + m_sFileName);
	
	m_bModified = FALSE;
}

void CEMelodyLabDlg::OnSave() 
{
	if (m_sFileName.IsEmpty()) {
		if (!GetSaveName()) {
			return;
		}
	}

	SaveMelody();
}

void CEMelodyLabDlg::SaveMelody()
{
	CString sMel;
	int nLen = m_sMelody.GetLength();
	for (int i = 0; i < nLen; i++) {
		if (m_sMelody[i] != ' ') {
			sMel += m_sMelody[i];
		}
	}
	
	CString sFileContent = "BEGIN:EMELODY\r\nVERSION:1.0\r\nMELODY:" + sMel + "\r\nEND:EMELODY";
	CFile file;
	if (!file.Open(m_sFileName, CFile::modeWrite | CFile::modeCreate)) {
		MessageBox("The file " + m_sFileName + " could not be opened!", "Error", MB_OK | MB_ICONEXCLAMATION);
		return;	
	}

	file.Write(sFileContent, sFileContent.GetLength());

	file.Close();

	m_bModified = FALSE;

	SetWindowText("EMelodyLab - " + m_sFileName);
}

void CEMelodyLabDlg::OnSaveAs() 
{
	if (!GetSaveName()) {
		return;
	}

	SaveMelody();
}

BOOL CEMelodyLabDlg::GetSaveName()
{
	OPENFILENAME ofn;
	memset(&ofn, 0, sizeof(ofn));

	// fill OPENFILENAME structure 
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = m_hWnd;
	ofn.lpstrFilter = "EMELODY files (*.emy)\0*.emy\0All Files (*.*)\0*.*\0\0";
	ofn.lpstrFile = m_sFileName.GetBuffer(MAX_PATH);
	ofn.lpstrTitle = "Save EMELODY file...";
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "mp3";

	BOOL bRet = GetSaveFileName(&ofn);
	m_sFileName.ReleaseBuffer();

	return bRet;
}

void CEMelodyLabDlg::OnOK() 
{
	if (!CheckSaveState()) {
		return;
	}
	
	CDialog::OnOK();
}

void CEMelodyLabDlg::OnCancel() 
{
	if (!CheckSaveState()) {
		return;
	}
	
	CDialog::OnCancel();
}

BOOL CEMelodyLabDlg::CheckSaveState()
{
	if (m_bModified) {
		UINT nRet = MessageBox("The melody is not saved yet! Would you like to save your changes?", "Save EMELODY?", MB_YESNOCANCEL | MB_ICONINFORMATION);
		if (nRet == IDCANCEL) {
			return FALSE;;
		}
		if (nRet == IDYES) {
			OnSave();
		}
	}

	return TRUE;
}


void CEMelodyLabDlg::OnClear() 
{
	UpdateData();

	if (m_sMelody.IsEmpty()) {
		return;
	}

	if (MessageBox("Do you want to clear the melody?\r\n\r\nThere's no undo function...", "Are you sure?", MB_YESNO | MB_ICONWARNING) == IDYES) {
		m_sMelody.Empty();
		UpdateData(FALSE);
		OnChangeMelody();
	}
}

void CEMelodyLabDlg::OnNew() 
{
	CheckSaveState();
	
	m_sMelody.Empty();
	m_sFileName.Empty();
	UpdateData(FALSE);

	m_bModified = FALSE;

	SetWindowText("EMelodyLab");
}

void CEMelodyLabDlg::OnHelp() 
{
	CAboutDlg dlg;
	dlg.DoModal();
}

void CEMelodyLabDlg::OnLinks() 
{
	CLinksDlg dlg;
	dlg.DoModal();
}

void CEMelodyLabDlg::OnRewind() 
{
	m_MelodyCtrl.SetFocus();
	m_MelodyCtrl.SetSel(0, 0, FALSE);
}

void CEMelodyLabDlg::OnLoop() 
{
	UpdateData();	
}
