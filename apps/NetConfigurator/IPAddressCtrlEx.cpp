// IPAddressCtrlEx.cpp : implementation file
//

#include "stdafx.h"
#include "netconfigurator.h"
#include "IPAddressCtrlEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIPAddressCtrlEx

CIPAddressCtrlEx::CIPAddressCtrlEx()
{
}

CIPAddressCtrlEx::~CIPAddressCtrlEx()
{
}


BEGIN_MESSAGE_MAP(CIPAddressCtrlEx, CIPAddressCtrl)
	//{{AFX_MSG_MAP(CIPAddressCtrlEx)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIPAddressCtrlEx message handlers

CString CIPAddressCtrlEx::GetAddressString()
{
	if (IsBlank() || !IsWindowEnabled()) {
		return "";
	}

	BYTE b1 = 0, b2 = 0, b3 = 0, b4 = 0;
	GetAddress(b1, b2, b3, b4);

	CString sAdr;
	sAdr.Format("%d.%d.%d.%d", b1, b2, b3, b4);

	return sAdr;
}

void CIPAddressCtrlEx::SetAddressString(CString sIP)
{
	BYTE b1 = 0, b2 = 0, b3 = 0, b4 = 0;

	if (sscanf(sIP, "%d.%d.%d.%d", &b1, &b2, &b3, &b4) == EOF) {
		return;
	}

	SetAddress(b1, b2, b3, b4);
}
