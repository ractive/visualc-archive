// ConnectSocket.cpp : implementation file
//

#include "stdafx.h"
#include "Visu.h"
#include "ConnectSocket.h"
#include "VisuDoc.h"
#include "VisuView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConnectSocket

CConnectSocket::CConnectSocket()
{

}

CConnectSocket::~CConnectSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CConnectSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CConnectSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CConnectSocket member functions

void CConnectSocket::OnAccept(int nErrorCode) 
{
	Accept(*m_ConnectSocket);
	
	CAsyncSocket::OnAccept(nErrorCode);
}

void CConnectSocket::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CAsyncSocket::OnClose(nErrorCode);
}

void CConnectSocket::OnConnect(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CAsyncSocket::OnConnect(nErrorCode);
}

void CConnectSocket::OnOutOfBandData(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CAsyncSocket::OnOutOfBandData(nErrorCode);
}

void CConnectSocket::OnReceive(int nErrorCode) 
{
	CString sRecv = "";
	int nRecv = Receive(sRecv.GetBuffer(256), 256);
	sRecv.ReleaseBuffer();

	int n = atoi(sRecv);

	CMainFrame * pMF = (CMainFrame *)AfxGetMainWnd();
	CVisuDoc * pDoc = (CVisuDoc *)pMF->GetActiveDocument();
	pDoc->x = n;
	pDoc->y = n;

	AfxGetMainWnd()->InvalidateRect(NULL);
	AfxGetMainWnd()->UpdateWindow();
	
	CString sOK = "OK\r\n";

	Send(sOK.GetBuffer(sOK.GetLength()), sOK.GetLength());
	sOK.ReleaseBuffer();

	CAsyncSocket::OnReceive(nErrorCode);
}

void CConnectSocket::OnSend(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CAsyncSocket::OnSend(nErrorCode);
}
