/*************************************************************************
                     Hexer
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

// HexerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Hexer.h"
#include "HexerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

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
// CHexerDlg dialog

CHexerDlg::CHexerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHexerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHexerDlg)
	m_sDecimal = _T("");
	m_sBinary = _T("");
	m_sOctal = _T("");
	m_sHex = _T("");
	m_sSigned = _T("");
	m_sDouble = _T("");
	m_bTopMost = FALSE;
	m_unPrecision = 8;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nBit = 64;
}

void CHexerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHexerDlg)
	DDX_Control(pDX, IDC_BITCOMBO, m_BitCombo);
	DDX_Control(pDX, IDC_SPIN, m_Spin);
	DDX_Control(pDX, IDC_DOUBLE, m_DoubleBox);
	DDX_Control(pDX, IDC_SIGNED, m_SignedBox);
	DDX_Control(pDX, IDC_OCTAL, m_OctalBox);
	DDX_Control(pDX, IDC_HEX, m_HexBox);
	DDX_Control(pDX, IDC_DECIMAL, m_DecimalBox);
	DDX_Control(pDX, IDC_BINARY, m_BinaryBox);
	DDX_Text(pDX, IDC_DECIMAL, m_sDecimal);
	DDX_Text(pDX, IDC_BINARY, m_sBinary);
	DDX_Text(pDX, IDC_OCTAL, m_sOctal);
	DDX_Text(pDX, IDC_HEX, m_sHex);
	DDX_Text(pDX, IDC_SIGNED, m_sSigned);
	DDX_Text(pDX, IDC_DOUBLE, m_sDouble);
	DDX_Check(pDX, IDC_ALWAYSONTOP, m_bTopMost);
	DDX_Text(pDX, IDC_PRECISION, m_unPrecision);
	DDV_MinMaxUInt(pDX, m_unPrecision, 0, 16);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHexerDlg, CDialog)
	//{{AFX_MSG_MAP(CHexerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_CALCULATE, OnCalculate)
	ON_EN_SETFOCUS(IDC_DECIMAL, OnSetfocusDecimal)
	ON_EN_SETFOCUS(IDC_HEX, OnSetfocusHex)
	ON_EN_SETFOCUS(IDC_BINARY, OnSetfocusBinary)
	ON_EN_SETFOCUS(IDC_OCTAL, OnSetfocusOctal)
	ON_EN_SETFOCUS(IDC_SIGNED, OnSetfocusSigned)
	ON_EN_SETFOCUS(IDC_DOUBLE, OnSetfocusDouble)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN, OnDeltaposSpin)
	ON_BN_CLICKED(IDC_COLORBUTTON, OnColorButton)
	ON_BN_CLICKED(IDC_ALWAYSONTOP, OnAlwaysontop)
	ON_CBN_SELCHANGE(IDC_BITCOMBO, OnSelchangeBitcombo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CHexerDlg message handlers

BOOL CHexerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	ASSERT((IDM_ALWAYSONTOP & 0xFFF0) == IDM_ALWAYSONTOP);
	ASSERT(IDM_ALWAYSONTOP < 0xF000);
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAlwaysOnTop;
		strAlwaysOnTop.LoadString(IDS_ALWAYSONTOP);
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ALWAYSONTOP, strAlwaysOnTop);
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	m_DecimalBox.m_pnBit = &m_nBit;
	m_HexBox.m_pnBit = &m_nBit;
	m_OctalBox.m_pnBit = &m_nBit;
	m_BinaryBox.m_pnBit = &m_nBit;
	m_SignedBox.m_pnBit = &m_nBit;
	m_DoubleBox.m_pnBit = &m_nBit;


	m_DecimalBox.SetBase(decimal);
	m_HexBox.SetBase(hex);
	m_OctalBox.SetBase(octal);
	m_BinaryBox.SetBase(binary);
	m_SignedBox.SetBase(dsigned);
	m_DoubleBox.SetBase(ddouble);

	OleInitialize(NULL);
	RegisterDragDrop(m_DecimalBox.m_hWnd,	m_DecimalBox.m_pDropTarget);
	RegisterDragDrop(m_HexBox.m_hWnd,		m_HexBox.m_pDropTarget);
	RegisterDragDrop(m_OctalBox.m_hWnd,		m_OctalBox.m_pDropTarget);
	RegisterDragDrop(m_BinaryBox.m_hWnd,	m_BinaryBox.m_pDropTarget);
	RegisterDragDrop(m_SignedBox.m_hWnd,	m_SignedBox.m_pDropTarget);
	RegisterDragDrop(m_DoubleBox.m_hWnd,	m_DoubleBox.m_pDropTarget);

	m_Color.Attach(IDC_COLORBUTTON, this);

	m_bTopMost = FALSE;

	SetOnTopIcon();
	FillBitCombo();
	m_BitCombo.SetCurSel(3);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CHexerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else if ((nID & 0xFFF0) == IDM_ALWAYSONTOP) {
		SwitchOnTop();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CHexerDlg::OnPaint() 
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
HCURSOR CHexerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CHexerDlg::OnCalculate() 
{
	Calculate();
}

void CHexerDlg::OnSetfocusDecimal() 
{
	m_Base = decimal;
}

void CHexerDlg::OnSetfocusHex() 
{
	m_Base = hex;
}

void CHexerDlg::OnSetfocusBinary() 
{
	m_Base = binary;
}

void CHexerDlg::OnSetfocusOctal() 
{
	m_Base = octal;
}

void CHexerDlg::OnSetfocusSigned() 
{
	m_Base = dsigned;
}

void CHexerDlg::OnSetfocusDouble() 
{
	m_Base = ddouble;	
}


void CHexerDlg::Calculate()
{
	UpdateData();

	unsigned int nBit = m_BitCombo.GetCurSel();
	if (nBit == -1) {
		nBit = 64;
	}
	else {
		nBit = m_BitCombo.GetItemData(nBit);
	}


	unsigned int i;
	unsigned __int64 nValue, nSignedValue;
	BOOL bRet = FALSE;
	// Convert the string to a decimal value
	switch (m_Base) {
	case hex:
		bRet = m_HexBox.Parse(&nValue);
		break;
	case decimal:
		bRet = m_DecimalBox.Parse(&nValue);
		break;
	case octal:
		bRet = m_OctalBox.Parse(&nValue);
		break;
	case binary:
		bRet = m_BinaryBox.Parse(&nValue);
		break;
	case dsigned:
		bRet = m_SignedBox.Parse(&nValue);
		break;
	case ddouble:
		bRet = m_DoubleBox.Parse(&nValue);
		break;
	default:
		bRet = FALSE;
	}

	if (bRet == FALSE) {
		return;
	}

	// Cast the result to the appropriate bit size
	unsigned __int64 n2Base = 1;

	switch(nBit) {
	case 8:
		nValue = (unsigned __int8)nValue;
		nSignedValue = (signed __int8)nValue;
		break;
	case 16:
		nValue = (unsigned __int16)nValue;
		nSignedValue = (signed __int16)nValue;
		break;
	case 32:
		nValue = (unsigned __int32)nValue;
		nSignedValue = (signed __int32)nValue;
		break;
	case 64:
		nValue = (unsigned __int64)nValue;
		nSignedValue = (signed __int64)nValue;
		break;
	default:
		nValue = 0;
	}

	// Convert the value to the corresponding base
	m_sBinary.Empty();

	for (i = 1; n2Base > 0 && n2Base <= nValue; i++) {
		if (i > nBit) {
			MessageBox("Overflow: The number exceeds 64 bit! Calculation is not correct!", "WARNING!", MB_OK | MB_ICONWARNING);
			break;
		}
		if (nValue & n2Base) {
			m_sBinary = "1" + m_sBinary;
		}
		else {
			m_sBinary = "0" + m_sBinary;
		}
		
		if (i%4 == 0) {
			m_sBinary = " " + m_sBinary;
		}
		n2Base = Int64ShllMod32(n2Base, 1);
		//n2Base = 1 << i;
	}
	if (m_sBinary.IsEmpty())
		m_sBinary = "0";

	m_sBinary.TrimLeft();

	m_sHex.Format("%I64x", nValue);
	m_sDecimal.Format("%I64u", nValue);
	m_sOctal.Format("%I64o", nValue);
	m_sSigned.Format("%I64d", nSignedValue);
	m_sDouble.Format("%.*lf", m_unPrecision, nValue);

	// COLORREF has form 0x00bbggrr
	COLORREF c = 0;
	c += ((DWORD)nValue & 0xFF) << 16;
	c += ((DWORD)nValue & 0xFF00);
	c += ((DWORD)nValue & 0xFF0000) >> 16;
	
	m_Color.SetBG(c);

	UpdateData(FALSE);
}

void CHexerDlg::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	unsigned __int64 nValue = 0;
	if(!m_DecimalBox.Parse(&nValue, NULL, TRUE)) {
		*pResult = 1;
		return;
	}

	nValue -= pNMUpDown->iDelta;
	m_DecimalBox.Convert(&nValue);
	m_sDecimal.Format("%I64u", nValue);
	UpdateData(FALSE);
	m_Base = decimal;
	Calculate();

	*pResult = 0;
}

void CHexerDlg::OnColorButton() 
{
	CColorDialog dlg;
	if (dlg.DoModal() == IDCANCEL) {
		return;
	}

	unsigned __int64 nValue = 0;
	nValue += (dlg.m_cc.rgbResult & 0xFF) << 16;
	nValue += (dlg.m_cc.rgbResult & 0xFF00);
	nValue += (dlg.m_cc.rgbResult & 0xFF0000) >> 16;

	m_sHex.Format("%I64x", nValue);
	m_Base = hex;
	UpdateData(FALSE);
	Calculate();
}

void CHexerDlg::SwitchOnTop()
{
	if (m_bTopMost) {
		SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		m_bTopMost = FALSE;
	}
	else {
		SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		m_bTopMost = TRUE;
	}

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	pSysMenu->CheckMenuItem(IDM_ALWAYSONTOP, MF_BYCOMMAND | m_bTopMost ? MF_CHECKED : MF_UNCHECKED);

	UpdateData(FALSE);
	SetOnTopIcon();
}

void CHexerDlg::OnAlwaysontop() 
{
	SwitchOnTop();
}

void CHexerDlg::SetOnTopIcon()
{

	WORD nIcon = m_bTopMost ? IDI_PINNED : IDI_NOTPINNED;
	HICON hIcon = (HICON)LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(nIcon), IMAGE_ICON, 15, 11, LR_DEFAULTCOLOR);
	if (hIcon) {
		((CButton *)GetDlgItem(IDC_ALWAYSONTOP))->SetIcon(hIcon);
	}

}

void CHexerDlg::FillBitCombo()
{
	int n = m_BitCombo.AddString(_T("8 Bit"));
	m_BitCombo.SetItemData(n, 8);

	n = m_BitCombo.AddString(_T("16 Bit"));
	m_BitCombo.SetItemData(n, 16);

	n = m_BitCombo.AddString(_T("32 Bit"));
	m_BitCombo.SetItemData(n, 32);

	n = m_BitCombo.AddString(_T("64 Bit"));
	m_BitCombo.SetItemData(n, 64);
}

void CHexerDlg::OnSelchangeBitcombo() 
{
	unsigned int nBit = m_BitCombo.GetCurSel();
	if (nBit == -1) {
		m_nBit = 64;
	}
	else {
		m_nBit = (unsigned short)m_BitCombo.GetItemData(nBit);
	}

	// Type double is only supported in 64bit mode
	if (m_nBit == 64) {
		m_DoubleBox.ModifyStyle(WS_DISABLED, 0);
		m_DoubleBox.SetReadOnly(FALSE);

	}
	else {
		m_sDouble.Empty();
		UpdateData(FALSE);
		m_DoubleBox.ModifyStyle(0, WS_DISABLED);
		m_DoubleBox.SetReadOnly(TRUE);
	}
	
}
