// ListenSocket.cpp : implementation file
//

#include "stdafx.h"
#include "WinAmpRC.h"
#include "ListenSocket.h"
#include "WinAmpControl.h"
#include "WinAmpRCDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListenSocket

CListenSocket::CListenSocket()
{
	m_pWnd = NULL;
}

CListenSocket::~CListenSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CListenSocket, CSocket)
	//{{AFX_MSG_MAP(CListenSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CListenSocket member functions

void CListenSocket::OnAccept(int nErrorCode) 
{
	if (nErrorCode != SOCKET_ERROR) {
		((CWinAmpRCDlg *)m_pWnd)->OnAccept();
	}
	
	CAsyncSocket::OnAccept(nErrorCode);
}

void CListenSocket::OnClose(int nErrorCode) 
{
	if (nErrorCode != SOCKET_ERROR) {
		((CWinAmpRCDlg *)m_pWnd)->OnCloseSocket();
	}
	
	CAsyncSocket::OnClose(nErrorCode);
}

void CListenSocket::OnConnect(int nErrorCode) 
{

	
	CAsyncSocket::OnConnect(nErrorCode);
}

BOOL CListenSocket::OnMessagePending() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	//return CAsyncSocket::OnMessagePending();
	return FALSE;
}

void CListenSocket::OnOutOfBandData(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CAsyncSocket::OnOutOfBandData(nErrorCode);
}

void CListenSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class

	int nLen = SOCKET_ERROR;
	char c = '\0';
	while(nLen = Receive(&c, 1)) {
		if (nLen == SOCKET_ERROR) {
			break;
		}
		m_RecvCommand.Add(c);
		if (m_RecvCommand.IsComplete()) {
			CString sCommand = m_RecvCommand.GetCommand();
			sCommand.TrimLeft();
			sCommand.TrimRight();
			PerformAction(sCommand);
		}
	}
	

	CAsyncSocket::OnReceive(nErrorCode);
}

void CListenSocket::OnSend(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CAsyncSocket::OnSend(nErrorCode);
}

void CListenSocket::SetParent(CWnd *pWnd)
{
	m_pWnd = pWnd;
}

void CListenSocket::PerformAction(CString &sCommand)
{
	CWinAmpControl * pWA = CWinAmpControl::GetInstance();
	
	int nSpace = sCommand.Find(' ');

	int nParameter = 0;

	if (nSpace != -1) {
		//sscanf((LPTSTR)(LPCTSTR)sCommand, "%d", &nParameter);
		nParameter = atoi(sCommand.Mid(nSpace));
		sCommand = sCommand.Left(nSpace);
	}

	if (sCommand.CompareNoCase("play") == 0) {
		pWA->Play();	
	}
	else if(sCommand.CompareNoCase("stop") == 0) {
		pWA->Stop();
	}
	else if(sCommand.CompareNoCase("pause") == 0) {
		pWA->Pause();
	}
	else if(sCommand.CompareNoCase("next") == 0) {
		pWA->Next();
	}
	else if(sCommand.CompareNoCase("prev") == 0) {
		pWA->Previous();
	}
	else if(sCommand.CompareNoCase("volup") == 0) {
		pWA->VolumeUp();
	}
	else if(sCommand.CompareNoCase("volset") == 0) {
		pWA->SetVolume(nParameter);
	}
	else if(sCommand.CompareNoCase("voldown") == 0) {
		pWA->VolumeDown();
	}
	else if(sCommand.CompareNoCase("songinfo") == 0) {
		((CWinAmpRCDlg *)m_pWnd)->SendInfo();
	}
	else if(sCommand.CompareNoCase("songinfoex") == 0) {
		((CWinAmpRCDlg *)m_pWnd)->SendInfoEx();
	}


#ifdef _DEBUG
	TRACE("Command: ");
	TRACE(sCommand);
	TRACE("\r\n");
#endif
}
