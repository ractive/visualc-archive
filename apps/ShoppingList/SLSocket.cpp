// SLSocket.cpp : implementation file
//

#include "stdafx.h"
#include "ShoppingList.h"
#include "ShoppingListDoc.h"
#include "SLSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSLSocket

CSLSocket::CSLSocket()
{
	m_pClientSocket = NULL;
}

CSLSocket::~CSLSocket()
{
	if (m_pClientSocket) {
		m_pClientSocket->Close();
		delete m_pClientSocket;
		m_pClientSocket = NULL;
	}
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CSLSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CSLSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CSLSocket member functions

void CSLSocket::OnAccept(int nErrorCode) 
{
	if (m_pClientSocket == NULL) {
		m_pClientSocket = new CSLSocket();
	}
	else {
		m_pClientSocket->Close();
	}

	Accept(*m_pClientSocket);	
	
	CAsyncSocket::OnAccept(nErrorCode);
}

void CSLSocket::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CAsyncSocket::OnClose(nErrorCode);
}

void CSLSocket::OnConnect(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CAsyncSocket::OnConnect(nErrorCode);
}

void CSLSocket::OnOutOfBandData(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CAsyncSocket::OnOutOfBandData(nErrorCode);
}

void CSLSocket::OnReceive(int nErrorCode) 
{
	CString sBuf;

	LPTSTR buf = sBuf.GetBuffer(64000);

	int nRecv = Receive(buf, 64000);
	buf[nRecv] = '\0';


	sBuf.ReleaseBuffer();
	//sBuf.TrimLeft();
	//sBuf.TrimRight();

	if (sBuf == "GET LIST\r\n") {
		SendList();
	}
	
	CAsyncSocket::OnReceive(nErrorCode);
}

void CSLSocket::OnSend(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CAsyncSocket::OnSend(nErrorCode);
}

CShoppingListDoc * CSLSocket::GetDocument()
{
	return (CShoppingListDoc *)((CFrameWnd *)AfxGetMainWnd())->GetActiveDocument();
}

BOOL CSLSocket::SendList()
{
	CShoppingListDoc * pDoc = GetDocument();

	CString sBuf("[SHOPS]\r\n");

	int nSize = pDoc->m_saShops.GetSize();
	for(int i = 0; i < nSize; i++) {
		sBuf += pDoc->m_saShops.GetAt(i);
		sBuf += '\0';
	}

	sBuf += "\r\n[ITEMS]\r\n";

	POSITION pos = NULL;

	for( pos = pDoc->m_saItems.GetHeadPosition(); pos != NULL; ) {
		CShoppingItem* pItem = (CShoppingItem *)pDoc->m_saItems.GetNext(pos);

		sBuf += pItem->m_sName;
		sBuf += '\0';
		sBuf += pItem->m_sShop;
		sBuf += '\0';
		sBuf += pItem->m_bInCart ? '1' : '0';
		sBuf += "\r\n";
	}

	sBuf += "\r\n\r\n";

	Send(sBuf, sBuf.GetLength());
	
	return TRUE;
}
