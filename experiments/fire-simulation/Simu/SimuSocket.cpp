// SimuSocket.cpp : implementation file
//

#include "stdafx.h"
#include "Simu.h"
#include "SimuSocket.h"
#include "SimuDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSimuSocket

CSimuSocket::CSimuSocket(HWND hWnd)
{
	m_pClientSocket = NULL;
	m_hWnd = hWnd;
}

CSimuSocket::~CSimuSocket()
{
	if (m_pClientSocket) {
		delete m_pClientSocket;
	}
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CSimuSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CSimuSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CSimuSocket member functions

void CSimuSocket::OnReceive(int nErrorCode) 
{
	CString sBuf;

	LPTSTR buf = sBuf.GetBuffer(64000);

	int nRecv = Receive(buf, 64000);
	buf[nRecv] = '\0';


	sBuf.ReleaseBuffer();
	GetDocument()->m_sRecv += sBuf;
	
	PostMessage(m_hWnd, WM_DATA, 0, 0);

	CAsyncSocket::OnReceive(nErrorCode);
}

CSimuDoc * CSimuSocket::GetDocument()
{
	return (CSimuDoc *)((CFrameWnd *)AfxGetMainWnd())->GetActiveDocument();
}

void CSimuSocket::OnAccept(int nErrorCode) 
{
	m_pClientSocket = new CSimuSocket(m_hWnd);

	Accept(*m_pClientSocket);
	
	CAsyncSocket::OnAccept(nErrorCode);
}

void CSimuSocket::OnConnect(int nErrorCode) 
{

	
	CAsyncSocket::OnConnect(nErrorCode);
}

void CSimuSocket::SendData(LPCTSTR buf, DWORD dwLen)
{
	m_pClientSocket->Send(buf, dwLen);
}

void CSimuSocket::SendResult(CString &sBuf)
{

}
