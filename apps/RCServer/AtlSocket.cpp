#include "stdafx.h"

#include "atlsocket.h"

#include <atlwin.cpp>

CAtlSocket::CAtlSocket()
{
	m_hSocket = INVALID_SOCKET;
}

CAtlSocket::~CAtlSocket()
{
}


BOOL CAtlSocket::Accept(CAtlSocket& rConnectedSocket, SOCKADDR* lpSockAddr, int* lpSockAddrLen)
{
	_ASSERTE(rConnectedSocket.m_hSocket == INVALID_SOCKET);
	//_ASSERTE(CAsyncSocket::FromHandle(INVALID_SOCKET) == NULL);

	//rConnectedSocket.Attach(INVALID_SOCKET, FD_READ | FD_ACCEPT | FD_CONNECT | FD_CLOSE);

	if (!rConnectedSocket.CreateNotificationWindow()) {
		return FALSE;
	}

	SOCKET hTemp = accept(m_hSocket, lpSockAddr, lpSockAddrLen);

	if (hTemp == INVALID_SOCKET)
	{
		DWORD dwProblem = GetLastError();
		Detach();
		rConnectedSocket.m_hSocket = INVALID_SOCKET;
		SetLastError(dwProblem);
	}
	else if (m_hSocket != NULL)
	{
		rConnectedSocket.m_hSocket = hTemp;
		rConnectedSocket.Detach();
		rConnectedSocket.Attach(hTemp, FD_READ | FD_ACCEPT | FD_CONNECT | FD_CLOSE);
	}

	return (hTemp != INVALID_SOCKET);
}

LRESULT CAtlSocket::NetEvent(UINT uMsg,WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	SOCKET s=(SOCKET)wParam;
	if (s != m_hSocket)
	{
		bHandled=FALSE;
		return 0L;
	}

	if (m_hSocket==INVALID_SOCKET)
	{
		bHandled=TRUE;
		return 0L;
	}

	if (WM_SOCKET_NET_EVENT == uMsg)
	{
		UINT nError=WSAGETSELECTERROR(lParam);

		switch (WSAGETSELECTEVENT(lParam))
		{
		case FD_READ: {
				DWORD nBytes;
				if (!IOCtl(FIONREAD, &nBytes)) {
					nError = WSAGetLastError();
				}

				if (nBytes != 0 || nError != 0) {
					OnReceive(nError, nBytes);
				}
			
			}
			break;
		case FD_ACCEPT:
			OnAccept(nError);
			break;
		case FD_CONNECT:
			OnConnect(nError);
			break;
		case FD_WRITE:
			OnSend(nError);
			break;
		case FD_CLOSE:
			OnClose(nError);
			break;
		case FD_OOB:
			OnOOBData(nError);
			break;
		default:
			break;
		}

		AsyncSelect(FD_READ | FD_ACCEPT | FD_CONNECT | FD_CLOSE);
	}
	else
		bHandled=FALSE;

	return 0L;

}

void CAtlSocket::OnReceive(UINT nError, UINT nBytes)
{
	ATLTRACE(_T("OnReceive(%d)\n"),nError);
}
void CAtlSocket::OnAccept(UINT nError)
{
	ATLTRACE(_T("OnAccept(%d)\n"),nError);
}
void CAtlSocket::OnConnect(UINT nError)
{
	ATLTRACE(_T("OnConnect(%d)\n"),nError);
}
void CAtlSocket::OnSend(UINT nError)
{
	ATLTRACE(_T("OnSend(%d)\n"),nError);
}
void CAtlSocket::OnClose(UINT nError)
{
	ATLTRACE(_T("OnClose(%d)\n"),nError);
}
void CAtlSocket::OnOOBData(UINT nError)
{
	ATLTRACE(_T("OnOOBData(%d)\n"),nError);
}

BOOL CAtlSocket::Socket(int nSocketType, long lEvent,
	int nProtocolType, int nAddressFormat)
{
	_ASSERTE(m_hSocket == INVALID_SOCKET);

	m_hSocket = socket(nAddressFormat,nSocketType,nProtocolType);
	if (m_hSocket != INVALID_SOCKET)
	{
		//CAtlSocket::AttachHandle(m_hSocket, this, FALSE);
		return AsyncSelect(lEvent);
	}
	return FALSE;
}

BOOL CAtlSocket::CreateSocket(UINT nSocketPort, int nSocketType,
	long lEvent, LPCTSTR lpszSocketAddress)
{
	if (!CreateNotificationWindow()) {
		return FALSE;
	}

	if (Socket(nSocketType, lEvent))
	{
		if (Bind(nSocketPort,lpszSocketAddress))
			return TRUE;
		int nResult = GetLastError();
		Close();
		WSASetLastError(nResult);
	}
	return FALSE;
}

BOOL CAtlSocket::Attach(SOCKET hSocket, long lEvent)
{
	_ASSERTE(hSocket != INVALID_SOCKET);

	m_hSocket = hSocket;
	//CAtlSocket::AttachHandle(hSocket, this);

	return AsyncSelect(lEvent);
}

SOCKET CAtlSocket::Detach()
{
	SOCKET hSocket = m_hSocket;
	if (AsyncSelect(0))
	{
		//CAtlSocket::KillSocket(hSocket, this);
		m_hSocket = INVALID_SOCKET;
		return hSocket;
	}
	return INVALID_SOCKET;
}

BOOL CAtlSocket::Bind(UINT nSocketPort, LPCTSTR lpszSocketAddress)
{
	USES_CONVERSION;

	SOCKADDR_IN sockAddr;
	memset(&sockAddr,0,sizeof(sockAddr));

	LPSTR lpszAscii = T2A((LPTSTR)lpszSocketAddress);
	sockAddr.sin_family = AF_INET;

	if (lpszAscii == NULL)
		sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	else
	{
		DWORD lResult = inet_addr(lpszAscii);
		if (lResult == INADDR_NONE)
		{
			WSASetLastError(WSAEINVAL);
			return FALSE;
		}
		sockAddr.sin_addr.s_addr = lResult;
	}

	sockAddr.sin_port = htons((u_short)nSocketPort);

	return Bind((SOCKADDR*)&sockAddr, sizeof(sockAddr));
}

void CAtlSocket::Close()
{
	if (m_hSocket != INVALID_SOCKET)
	{
		DestroyWindow();
		m_hWnd=NULL;

		closesocket(m_hSocket);
		//CAtlSocket::KillSocket(m_hSocket, this);
		m_hSocket = INVALID_SOCKET;
	}
}

BOOL CAtlSocket::Connect(LPCTSTR lpszHostAddress, UINT nHostPort)
{
	USES_CONVERSION;

	_ASSERTE(lpszHostAddress != NULL);

	SOCKADDR_IN sockAddr;
	memset(&sockAddr,0,sizeof(sockAddr));

	LPSTR lpszAscii = T2A((LPTSTR)lpszHostAddress);
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_addr.s_addr = inet_addr(lpszAscii);

	if (sockAddr.sin_addr.s_addr == INADDR_NONE)
	{
		LPHOSTENT lphost;
		lphost = gethostbyname(lpszAscii);
		if (lphost != NULL)
			sockAddr.sin_addr.s_addr = ((LPIN_ADDR)lphost->h_addr)->s_addr;
		else
		{
			WSASetLastError(WSAEINVAL);
			return FALSE;
		}
	}

	sockAddr.sin_port = htons((u_short)nHostPort);

	return Connect((SOCKADDR*)&sockAddr, sizeof(sockAddr));
}

int CAtlSocket::Receive(void* lpBuf, int nBufLen, int nFlags)
{
	return recv(m_hSocket, (LPSTR)lpBuf, nBufLen, nFlags);
}

int CAtlSocket::Send(const void* lpBuf, int nBufLen, int nFlags)
{
	return send(m_hSocket, (LPSTR)lpBuf, nBufLen, nFlags);
}

int CAtlSocket::SendTo(const void* lpBuf, int nBufLen, UINT nHostPort, LPCTSTR lpszHostAddress, int nFlags)
{
	USES_CONVERSION;

	SOCKADDR_IN sockAddr;

	memset(&sockAddr,0,sizeof(sockAddr));

	LPSTR lpszAscii = T2A((LPTSTR)lpszHostAddress);
	sockAddr.sin_family = AF_INET;

	if (lpszAscii == NULL)
		sockAddr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
	else
	{
		sockAddr.sin_addr.s_addr = inet_addr(lpszAscii);
		if (sockAddr.sin_addr.s_addr == INADDR_NONE)
		{
			LPHOSTENT lphost;
			lphost = gethostbyname(lpszAscii);
			if (lphost != NULL)
				sockAddr.sin_addr.s_addr = ((LPIN_ADDR)lphost->h_addr)->s_addr;
			else
			{
				WSASetLastError(WSAEINVAL);
				return FALSE;
			}
		}
	}

	sockAddr.sin_port = htons((u_short)nHostPort);

	return SendTo(lpBuf, nBufLen, (SOCKADDR*)&sockAddr, sizeof(sockAddr), nFlags);
}

BOOL CAtlSocket::AsyncSelect(long lEvent)
{
	_ASSERTE(m_hSocket != INVALID_SOCKET);

	return WSAAsyncSelect(m_hSocket, m_hWnd,
		WM_SOCKET_NET_EVENT, lEvent) != SOCKET_ERROR;
}


int CAtlSocket::ReceiveFromHelper(void* lpBuf, int nBufLen, SOCKADDR* lpSockAddr, int* lpSockAddrLen, int nFlags)
{
	return recvfrom(m_hSocket, (LPSTR)lpBuf, nBufLen, nFlags, lpSockAddr, lpSockAddrLen);
}

int CAtlSocket::SendToHelper(const void* lpBuf, int nBufLen, const SOCKADDR* lpSockAddr, int nSockAddrLen, int nFlags)
{
	return sendto(m_hSocket, (LPSTR)lpBuf, nBufLen, nFlags, lpSockAddr, nSockAddrLen);
}

BOOL CAtlSocket::ConnectHelper(const SOCKADDR* lpSockAddr, int nSockAddrLen)
{
	return connect(m_hSocket, lpSockAddr, nSockAddrLen) != SOCKET_ERROR;
}

/////////////////////////////////////////////////////////////////////////////
// CAtlSocketBlocking Constructor

CAtlSocketBlocking::CAtlSocketBlocking()
{
	m_pbBlocking = NULL;
	m_nConnectError = -1;
	m_nTimeOut = 2000;
}

/////////////////////////////////////////////////////////////////////////////
// CAtlSocketBlocking Operations

void CAtlSocketBlocking::CancelBlockingCall()
{
	if (m_pbBlocking != NULL)
	{
		*m_pbBlocking = FALSE;
		m_pbBlocking = NULL;
	}
}

BOOL CAtlSocketBlocking::OnMessagePending()
{
	MSG msg;
	if (::PeekMessage(&msg, NULL, WM_PAINT, WM_PAINT, PM_REMOVE))
	{
		::DispatchMessage(&msg);
		return FALSE;   // usually return TRUE, but OnIdle usually causes WM_PAINTs
	}
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CAtlSocketBlocking Implementation

CAtlSocketBlocking::~CAtlSocketBlocking()
{
	if (m_hSocket != INVALID_SOCKET)
		Close();
}

void CAtlSocketBlocking::Close()
{
	if (m_hSocket != INVALID_SOCKET)
	{
		CancelBlockingCall();

		AsyncSelect(0);
		CAtlSocket::Close();
		m_hSocket = INVALID_SOCKET;
	}
}

int CAtlSocketBlocking::Receive(void* lpBuf, int nBufLen, int nFlags)
{
	if (m_pbBlocking != NULL)
	{
		WSASetLastError(WSAEINPROGRESS);
		return  FALSE;
	}
	int nResult;
	while ((nResult = CAtlSocket::Receive(lpBuf, nBufLen, nFlags)) == SOCKET_ERROR)
	{
		if (GetLastError() == WSAEWOULDBLOCK)
		{
			if (!PumpMessages(FD_READ))
				return SOCKET_ERROR;
		}
		else
			return SOCKET_ERROR;
	}
	return nResult;
}

int CAtlSocketBlocking::Send(const void* lpBuf, int nBufLen, int nFlags)
{
	if (m_pbBlocking != NULL)
	{
		WSASetLastError(WSAEINPROGRESS);
		return  FALSE;
	}

	int nLeft, nWritten;
	PBYTE pBuf = (PBYTE)lpBuf;
	nLeft = nBufLen;

	while (nLeft > 0)
	{
		nWritten = SendChunk(pBuf, nLeft, nFlags);
		if (nWritten == SOCKET_ERROR)
			return nWritten;

		nLeft -= nWritten;
		pBuf += nWritten;
	}
	return nBufLen - nLeft;
}

int CAtlSocketBlocking::SendChunk(const void* lpBuf, int nBufLen, int nFlags)
{
	int nResult;
	while ((nResult = CAtlSocket::Send(lpBuf, nBufLen, nFlags)) == SOCKET_ERROR)
	{
		if (GetLastError() == WSAEWOULDBLOCK)
		{
			if (!PumpMessages(FD_WRITE))
				return SOCKET_ERROR;
		}
		else
			return SOCKET_ERROR;
	}
	return nResult;
}

BOOL CAtlSocketBlocking::ConnectHelper(const SOCKADDR* lpSockAddr, int nSockAddrLen)
{
	if (m_pbBlocking != NULL)
	{
		WSASetLastError(WSAEINPROGRESS);
		return  FALSE;
	}

	m_nConnectError = -1;

	if (!CAtlSocket::ConnectHelper(lpSockAddr, nSockAddrLen))
	{
		if (GetLastError() == WSAEWOULDBLOCK)
		{
			ATLTRACE(_T("Pumping\n"));
			while (PumpMessages(FD_CONNECT))
			{
				if (m_nConnectError != -1)
				{
					WSASetLastError(m_nConnectError);
					return (m_nConnectError == 0);
				}
			}
		}
		return FALSE;
	}
	return TRUE;
}

int CAtlSocketBlocking::ReceiveFromHelper(void* lpBuf, int nBufLen, SOCKADDR* lpSockAddr, int* lpSockAddrLen, int nFlags)
{
	if (m_pbBlocking != NULL)
	{
		WSASetLastError(WSAEINPROGRESS);
		return  FALSE;
	}
	int nResult;
	while ((nResult = CAtlSocket::ReceiveFromHelper(lpBuf, nBufLen, lpSockAddr, lpSockAddrLen, nFlags)) == SOCKET_ERROR)
	{
		if (GetLastError() == WSAEWOULDBLOCK)
		{
			if (!PumpMessages(FD_READ))
				return SOCKET_ERROR;
		}
		else
			return SOCKET_ERROR;
	}
	return nResult;
}

int CAtlSocketBlocking::SendToHelper(const void* lpBuf, int nBufLen, const SOCKADDR* lpSockAddr, int nSockAddrLen, int nFlags)
{
	if (m_pbBlocking != NULL)
	{
		WSASetLastError(WSAEINPROGRESS);
		return  FALSE;
	}
	int nResult;
	while ((nResult = CAtlSocket::SendToHelper(lpBuf, nBufLen, lpSockAddr, nSockAddrLen, nFlags)) == SOCKET_ERROR)
	{
		if (GetLastError() == WSAEWOULDBLOCK)
		{
			if (!PumpMessages(FD_WRITE))
				return SOCKET_ERROR;
		}
		else
			return SOCKET_ERROR;
	}
	return nResult;
}

BOOL CAtlSocketBlocking::PumpMessages(UINT uStopFlag)
{
	// The same socket better not be blocking in more than one place.
	_ASSERTE(m_pbBlocking == NULL);

	_ASSERTE(m_hWnd != NULL);

	BOOL bBlocking = TRUE;
	m_pbBlocking = &bBlocking;

	// This is not a timeout in the WinSock sense, but more
	// like a WM_KICKIDLE to keep message pumping alive
	UINT nTimerID = SetTimer(1, m_nTimeOut);

	if (nTimerID == 0)
	{
		ATLTRACE(_T("No Timer Resources Available - Seriously up the Swannae"));
	}

	BOOL bPeek = TRUE;

	while (bBlocking)
	{
		try
		{
			MSG msg;
			if (::PeekMessage(&msg, m_hWnd,
				WM_SOCKET_NET_EVENT, WM_SOCKET_NET_EVENT, PM_REMOVE))
			{
				if (msg.message == WM_SOCKET_NET_EVENT && (SOCKET)msg.wParam == m_hSocket)
				{
					if (WSAGETSELECTEVENT(msg.lParam) == FD_CLOSE)
					{
						break;
					}
					if (WSAGETSELECTEVENT(msg.lParam) == uStopFlag)
					{
						if (uStopFlag == FD_CONNECT)
							m_nConnectError = WSAGETSELECTERROR(msg.lParam);
						break;
					}
				}
//				if (msg.wParam != 0 || msg.lParam != 0)
//					CSocket::AuxQueueAdd(msg.message, msg.wParam, msg.lParam);

				bPeek = TRUE;
			}
			else if(::PeekMessage(&msg, m_hWnd, WM_TIMER, WM_TIMER, PM_NOREMOVE))
			{
				// If our pump timer has expired...
				if (msg.wParam == (UINT) nTimerID)
				{
					::PeekMessage(&msg, m_hWnd, WM_TIMER, WM_TIMER, PM_REMOVE);
					break;
				}
			}

/*			else if (::PeekMessage(&msg, m_hWnd,
						WM_TIMER, WM_TIMER, PM_REMOVE))
			{
			break;
			}
*/

			if (bPeek && ::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
			{
				if (OnMessagePending())
				{
					// allow user-interface updates
					
				}
				else
				{
					bPeek = FALSE;
				}
			}
			else
			{
				// no work to do -- allow CPU to sleep
				WaitMessage();
				bPeek = TRUE;
			}
		}
		catch(...)
		{
			ATLTRACE(_T("Error: caught exception in PumpMessage - continuing.\n"));
			bPeek = TRUE;
		}
	}

	KillTimer(nTimerID);

	if (!bBlocking)
	{
		WSASetLastError(WSAEINTR);
		return FALSE;
	}
	m_pbBlocking = NULL;

	PostMessage(WM_SOCKET_NET_EVENT, 0, 0);

	return TRUE;
}

//int CAtlSocketBlockingTimeout::SendString(LPCTSTR lpszStr, UINT uTimeOut, int nFlags)
//{
//	// If a timeout value was specified, set it
//	if (uTimeOut > 0)
//		SetTimeOut(uTimeOut);
//
//	// Call base class function
//	int nRet = CAtlSocketBlocking::Send(lpszStr, strlen(lpszStr), nFlags);
//
//	// If we previously set a timeout
//	if (uTimeOut > 0)
//	{
//		KillTimeOut();
//		// If the operation timedout, set a more
//		// natural error message
//		if (GetLastError() == WSAEINTR)
//			SetLastError(WSAETIMEDOUT);
//	}
//	return nRet;
//}
//
//
//int CAtlSocketBlockingTimeout::ReceiveString(LPTSTR lpszStr, UINT uTimeOut, int nFlags)
//{
//	static char szBuf[256];
//	memset(szBuf, 0, sizeof(szBuf));
//
//	// If a timeout value was specified, set it
//	if (uTimeOut > 0)
//		SetTimeOut(uTimeOut);
//
//	// Call base class function
//	int nRet = CAtlSocketBlocking::Receive(szBuf, sizeof(szBuf), nFlags);
//
//	// If we previously set a timeout
//	if (uTimeOut > 0)
//	{
//		KillTimeOut();
//		// If the operation timedout, set a more
//		// natural error message
//		if (nRet == SOCKET_ERROR)
//		{
//			if (GetLastError() == WSAEINTR)
//				SetLastError(WSAETIMEDOUT);
//		}
//	}
//
//	// Fill in the CString reference
//	lpszStr=new TCHAR[_tcslen(szBuf)];
//	_tcscpy(lpszStr,szBuf);
//	//str = szBuf;
//	return nRet;
//}

BOOL CAtlSocketBlockingTimeout::OnMessagePending() 
{
	MSG msg;
	// Watch for our timer message
	if(::PeekMessage(&msg, m_hWnd, WM_TIMER, WM_TIMER, PM_NOREMOVE))
	{
		// If our timer expired...
		if (msg.wParam == (UINT) m_nTimerID)
		{
			// Remove the message
			::PeekMessage(&msg, m_hWnd, WM_TIMER, WM_TIMER, PM_REMOVE);
			// And cancel the call
			CancelBlockingCall();
			return FALSE;
		}
	}
	// Call base class function
	return CAtlSocketBlocking::OnMessagePending();
} 


BOOL CAtlSocketBlockingTimeout::SetTimeOut(UINT uTimeOut) 
{ 
	m_nTimerID = SetTimer(2,uTimeOut);
	return m_nTimerID;
} 


BOOL CAtlSocketBlockingTimeout::KillTimeOut() 
{ 
	return KillTimer(m_nTimerID);
} 

/////////////////////////////////////////////////////////////////////////////
// CAtlSocketMulticast

CAtlSocketMulticast::CAtlSocketMulticast()
{
	m_uiRef=0;                                                  
}

CAtlSocketMulticast::~CAtlSocketMulticast()
{
	DropMembership();
}


/////////////////////////////////////////////////////////////////////////////
// CAtlSocketMulticast member functions
BOOL CAtlSocketMulticast::CreateSocket(UINT nPort, LPCTSTR lpszMulticastAddress, LPCTSTR lpszInterface, int iTTL )
{
	USES_CONVERSION;
	unsigned long addr = inet_addr(T2A((TCHAR*)lpszInterface));
	return CreateSocket(nPort,lpszMulticastAddress,addr,iTTL);    
}

BOOL CAtlSocketMulticast::CreateSocket(UINT nPort, LPCTSTR lpszMulticastAddress, unsigned long ulInterface, int iTTL)
{
	m_uiMulticastPort=nPort;
	_tcsnset(m_szMulticastAddress,_T('\0'),16);
	_tcsncpy(m_szMulticastAddress,lpszMulticastAddress,15);
	
	if (!CAtlSocket::CreateSocket(nPort,SOCK_DGRAM))
		return FALSE;
	
	// set TTL	
    if (!SetTTL(iTTL))
    	return FALSE;
    	
    // set wish to transmit upon a MultiCast Address
	if (!MulticastInterface(ulInterface))
		return FALSE;
    
    // set wish to receive MultiCast Address
	if (!AddMembership(lpszMulticastAddress, ulInterface))
		return FALSE;

	return TRUE;
}

BOOL CAtlSocketMulticast::SetTTL(int iTTL)
{
	return SetSockOpt(IP_MULTICAST_TTL, (char *)&iTTL, sizeof(iTTL) , IPPROTO_IP);
}

BOOL CAtlSocketMulticast::MulticastInterface(LPCTSTR lpszInterface)
{
	USES_CONVERSION;
	unsigned long addr = inet_addr(T2A((TCHAR*)lpszInterface));
    return MulticastInterface(addr);
} 

BOOL CAtlSocketMulticast::MulticastInterface( unsigned long ulInterface)
{
	return SetSockOpt(IP_MULTICAST_IF, (char *)&ulInterface, sizeof(ulInterface) , IPPROTO_IP);
}
 
BOOL CAtlSocketMulticast::AddMembership(LPCTSTR lpszMulticastAddress, LPCTSTR lpszInterface)
{
	USES_CONVERSION;
	unsigned long addr = inet_addr(T2A((TCHAR*)lpszInterface));
    return AddMembership(lpszMulticastAddress, addr);
}

BOOL CAtlSocketMulticast::AddMembership(LPCTSTR lpszMulticastAddress, unsigned long ulInterface)
{
	if (0!=m_uiRef) return FALSE;
	USES_CONVERSION;
	m_mreq.imr_multiaddr.s_addr = inet_addr(T2A((TCHAR*)lpszMulticastAddress));
	m_mreq.imr_interface.s_addr = ulInterface;
    
	if (!SetSockOpt(IP_ADD_MEMBERSHIP, (char *)&m_mreq, sizeof(m_mreq) , IPPROTO_IP))
		return FALSE;
	
	m_uiRef++;
	return TRUE;
}

BOOL CAtlSocketMulticast::DropMembership()
{
	if (0==m_uiRef) return FALSE;
	m_uiRef--;
	return SetSockOpt(IP_DROP_MEMBERSHIP, (char *)&m_mreq, sizeof(m_mreq) , IPPROTO_IP);
}

int CAtlSocketMulticast::SendMulti(const void FAR* lpBuf, int nBufLen, int nFlags)
{
	return SendTo(lpBuf,nBufLen,m_uiMulticastPort,m_szMulticastAddress,nFlags);
}

int CAtlSocketMulticast::SendMultiPort(const void FAR* lpBuf, int nBufLen, unsigned int uiPort, int nFlags)
{
	return SendTo( lpBuf, nBufLen, m_uiMulticastPort+uiPort, m_szMulticastAddress, nFlags);
}


#ifdef _DEBUG
#define _ATLSOCK_INLINE
#else
#define _ATLSOCK_INLINE inline
#endif

// inlines are stuffed at the bottom
#ifdef _ATLSOCK_INLINE

_ATLSOCK_INLINE CAtlSocket::operator SOCKET() const
	{ return m_hSocket; }
_ATLSOCK_INLINE BOOL CAtlSocket::GetPeerName(SOCKADDR* lpSockAddr, int* lpSockAddrLen)
	{ return (SOCKET_ERROR != getpeername(m_hSocket, lpSockAddr, lpSockAddrLen)); }
_ATLSOCK_INLINE BOOL CAtlSocket::GetSockName(SOCKADDR* lpSockAddr, int* lpSockAddrLen)
	{ return (SOCKET_ERROR != getsockname(m_hSocket, lpSockAddr, lpSockAddrLen)); }
_ATLSOCK_INLINE BOOL CAtlSocket::SetSockOpt(int nOptionName, const void* lpOptionValue, int nOptionLen, int nLevel)
	{ return (SOCKET_ERROR != setsockopt(m_hSocket, nLevel, nOptionName, (LPCSTR)lpOptionValue, nOptionLen)); }
_ATLSOCK_INLINE BOOL CAtlSocket::GetSockOpt(int nOptionName, void* lpOptionValue, int* lpOptionLen, int nLevel)
	{ return (SOCKET_ERROR != getsockopt(m_hSocket, nLevel, nOptionName, (LPSTR)lpOptionValue, lpOptionLen)); }
//_ATLSOCK_INLINE CAtlSocket* PASCAL CAtlSocket::FromHandle(SOCKET hSocket)
//	{ return CAtlSocket::LookupHandle(hSocket, FALSE); }
_ATLSOCK_INLINE int PASCAL CAtlSocket::GetLastError()
	{ return WSAGetLastError(); }
_ATLSOCK_INLINE BOOL CAtlSocket::Bind(const SOCKADDR* lpSockAddr, int nSockAddrLen)
	{ return (SOCKET_ERROR != bind(m_hSocket, lpSockAddr, nSockAddrLen)); }
_ATLSOCK_INLINE BOOL CAtlSocket::Connect(const SOCKADDR* lpSockAddr, int nSockAddrLen)
	{ return ConnectHelper(lpSockAddr, nSockAddrLen); }
_ATLSOCK_INLINE BOOL CAtlSocket::IOCtl(long lCommand, DWORD* lpArgument)
	{ return (SOCKET_ERROR != ioctlsocket(m_hSocket, lCommand, lpArgument)); }

BOOL CAtlSocket::Listen(int nConnectionBacklog)
	{ return (SOCKET_ERROR != listen(m_hSocket, nConnectionBacklog)); }

_ATLSOCK_INLINE int CAtlSocket::ReceiveFrom(void* lpBuf, int nBufLen, SOCKADDR* lpSockAddr, int* lpSockAddrLen, int nFlags)
	{ return ReceiveFromHelper(lpBuf, nBufLen, lpSockAddr, lpSockAddrLen, nFlags); }
_ATLSOCK_INLINE BOOL CAtlSocket::ShutDown(int nHow)
	{ return (SOCKET_ERROR != shutdown(m_hSocket,nHow)); }
_ATLSOCK_INLINE int CAtlSocket::SendTo(const void* lpBuf, int nBufLen, const SOCKADDR* lpSockAddr, int nSockAddrLen, int nFlags)
	{ return SendToHelper(lpBuf, nBufLen, lpSockAddr, nSockAddrLen, nFlags); }

_ATLSOCK_INLINE BOOL CAtlSocketBlocking::CreateSocket(UINT nSocketPort, int nSocketType, LPCTSTR lpszSocketAddress)
	{ return CAtlSocket::CreateSocket(nSocketPort, nSocketType, FD_READ | FD_WRITE | FD_OOB | FD_ACCEPT | FD_CONNECT | FD_CLOSE, lpszSocketAddress); }
_ATLSOCK_INLINE BOOL CAtlSocketBlocking::IsBlocking()
	{ return (m_pbBlocking != NULL); }
//_AFXSOCK_INLINE CSocket* PASCAL CSocket::FromHandle(SOCKET hSocket)
//	{ return (CSocket*)CAsyncSocket::LookupHandle(hSocket, FALSE); }
_ATLSOCK_INLINE BOOL CAtlSocketBlocking::Attach(SOCKET hSocket)
	{ return CAtlSocket::Attach(hSocket); }

#endif //_ATLSOCK_INLINE

BOOL CAtlSocket::CreateNotificationWindow()
{
	HWND hWnd;
	RECT rc;

	memset(&rc,0,sizeof(RECT));

	hWnd=Create(NULL, rc, _T("Atl Socket Notification Window"), WS_OVERLAPPED | WS_POPUP, 0, 0);

	if (!hWnd)
	{
		int nError = GetLastError();
		ATLTRACE(_T("Failed to Create Socket Notificaton Window\n"));
		return FALSE;
	}

	return TRUE;
}
