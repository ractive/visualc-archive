// UpdateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DynPfiff.h"
#include "UpdateDlg.h"
#include <afxinet.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUpdateDlg dialog

CUpdateDlg * CUpdateDlg::pPseudoThis = NULL;

CUpdateDlg::CUpdateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUpdateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUpdateDlg)
	//}}AFX_DATA_INIT

	pPseudoThis = this;
}


void CUpdateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUpdateDlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUpdateDlg, CDialog)
	//{{AFX_MSG_MAP(CUpdateDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUpdateDlg message handlers

void CUpdateDlg::UpdateDlg(DWORD dwStatus, void *pStatusInfo, DWORD dwInfoLen)
{
	CString sMsg;
	CString sStatus;
	if (pStatusInfo != NULL) {
		strcpy(sStatus.GetBuffer(dwInfoLen), (const char*)pStatusInfo);
		sStatus.ReleaseBuffer();
	}
	switch (dwStatus) {
	case INTERNET_STATUS_RESOLVING_NAME:
		sMsg = "Resolving name: " + sStatus;
		break;
	case INTERNET_STATUS_NAME_RESOLVED:
		sMsg = sStatus + " resolved";
		break;
	case INTERNET_STATUS_CONNECTING_TO_SERVER:
		sMsg = "Connecting to " + sStatus;
		break;
	case INTERNET_STATUS_CONNECTED_TO_SERVER:
		sMsg = "Connected to " + sStatus;
		break;
	case INTERNET_STATUS_SENDING_REQUEST:
		sMsg = "Sending Request...";
		break;
	case INTERNET_STATUS_REQUEST_SENT:
		sMsg = "Waiting for response...";
		break;
	case INTERNET_STATUS_RECEIVING_RESPONSE:
		//sMsg = "Receiving Response";
		break;
	case INTERNET_STATUS_RESPONSE_RECEIVED:
		//sMsg = "Response received";
		break;
	case INTERNET_STATUS_CLOSING_CONNECTION:
		sMsg = "Closing connection";
		break;
	case INTERNET_STATUS_CONNECTION_CLOSED:
		sMsg = "Connection closed";
		break;
	case INTERNET_STATUS_HANDLE_CREATED:
		//sMsg = "Handle created";
		break;
	case INTERNET_STATUS_HANDLE_CLOSING:
		//sMsg = "Closing handle";
		break;
	case INTERNET_STATUS_REQUEST_COMPLETE:
		sMsg = "Request complete";
		break;
	default:
		sMsg = "Connecting...";
	}
	if (!sMsg.IsEmpty()) {
		pPseudoThis->SetDlgItemText(IDC_TEXT, sMsg);
		TRACE("%s\n", sMsg);
	}

}

BOOL CUpdateDlg::Pump()
{
	MSG msg;

	// Retrieve and dispatch any waiting messages.

	while (::PeekMessage (&msg, NULL, 0, 0, PM_NOREMOVE)) {
		if (!AfxGetApp ()->PumpMessage ()) {
			::PostQuitMessage (0);
			return FALSE;
		}
	}

	// Simulate the framework's idle processing mechanism.
/*
	LONG lIdle = 0;
	while (AfxGetApp ()->OnIdle (lIdle++));
*/
	return TRUE;

}
