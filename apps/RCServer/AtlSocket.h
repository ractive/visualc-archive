#ifndef ATL_SOCKET
#define ATL_SOCKET 1

#include "winsock2.h"
#include "ws2tcpip.h"


#define WM_SOCKET_NET_EVENT (WM_USER+42)

class CAtlSocket : public CWindowImpl<CAtlSocket>
{
public:
	DECLARE_WND_CLASS(_T("AtlSocket")) 
              // If this macro is not specified in your
              // class, ATL will generate a class name   ...
public:
	CAtlSocket();
	~CAtlSocket();


	BEGIN_MSG_MAP(CAtlSocket)
		MESSAGE_HANDLER(WM_SOCKET_NET_EVENT, NetEvent)	
	END_MSG_MAP()

	BOOL CreateSocket( UINT nSocketPort = 0, int nSocketType = SOCK_STREAM, long lEvent = FD_READ | FD_WRITE | FD_OOB | FD_ACCEPT | FD_CONNECT | FD_CLOSE, LPCTSTR lpszSocketAddress = NULL );
	BOOL Accept(CAtlSocket& rConnectedSocket, SOCKADDR* lpSockAddr, int* lpSockAddrLen);

// operations
	BOOL Bind(UINT nSocketPort, LPCTSTR lpszSocketAddress = NULL);
	BOOL Bind (const SOCKADDR* lpSockAddr, int nSockAddrLen);

	virtual void Close();

	BOOL Connect(LPCTSTR lpszHostAddress, UINT nHostPort);
	BOOL Connect(const SOCKADDR* lpSockAddr, int nSockAddrLen);

	BOOL IOCtl(long lCommand, DWORD* lpArgument);

	BOOL Listen(int nConnectionBacklog=5);

	virtual int Receive(void* lpBuf, int nBufLen, int nFlags = 0);

	int ReceiveFrom(void* lpBuf, int nBufLen,
		SOCKADDR* lpSockAddr, int* lpSockAddrLen, int nFlags = 0);

	enum { receives = 0, sends = 1, both = 2 };
	BOOL ShutDown(int nHow = sends);

	virtual int Send(const void* lpBuf, int nBufLen, int nFlags = 0);

	int SendTo(const void* lpBuf, int nBufLen,
		UINT nHostPort, LPCTSTR lpszHostAddress = NULL, int nFlags = 0);
	int SendTo(const void* lpBuf, int nBufLen,
		const SOCKADDR* lpSockAddr, int nSockAddrLen, int nFlags = 0);

	BOOL AsyncSelect(long lEvent = FD_READ | FD_WRITE | FD_OOB | FD_ACCEPT | FD_CONNECT | FD_CLOSE);


// attributes
	operator SOCKET() const;
	BOOL Attach(SOCKET hSocket, long lEvent = FD_READ | FD_WRITE | FD_OOB | FD_ACCEPT | FD_CONNECT | FD_CLOSE);
	SOCKET Detach();

	BOOL GetPeerName(SOCKADDR* lpSockAddr, int* lpSockAddrLen);

	BOOL GetSockName(SOCKADDR* lpSockAddr, int* lpSockAddrLen);

	BOOL SetSockOpt(int nOptionName, const void* lpOptionValue,
		int nOptionLen, int nLevel = SOL_SOCKET);
	BOOL GetSockOpt(int nOptionName, void* lpOptionValue,
		int* lpOptionLen, int nLevel = SOL_SOCKET);

	static int PASCAL GetLastError();

	BOOL Socket(int nSocketType=SOCK_STREAM, long lEvent =
	FD_READ | FD_WRITE | FD_OOB | FD_ACCEPT | FD_CONNECT | FD_CLOSE,
	int nProtocolType = 0, int nAddressFormat = PF_INET);

protected:
	BOOL CreateNotificationWindow();
	LRESULT NetEvent(UINT uMsg,WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual void OnReceive(UINT nError, UINT nBytes);
	virtual void OnAccept(UINT nError);
	virtual void OnConnect(UINT nError);
	virtual void OnSend(UINT nError);
	virtual void OnClose(UINT nError);
	virtual void OnOOBData(UINT nError);

	virtual BOOL ConnectHelper(const SOCKADDR* lpSockAddr, int nSockAddrLen);
	virtual int ReceiveFromHelper(void* lpBuf, int nBufLen,
		SOCKADDR* lpSockAddr, int* lpSockAddrLen, int nFlags);
	virtual int SendToHelper(const void* lpBuf, int nBufLen,
		const SOCKADDR* lpSockAddr, int nSockAddrLen, int nFlags);

public:

	SOCKET m_hSocket;
};

class CAtlSocketMulticast : public CAtlSocket
{
// Attributes
public:
	DECLARE_WND_CLASS(_T("AtlSocketMulticast")) 

// Operations
public:
	CAtlSocketMulticast();
	~CAtlSocketMulticast();

	BOOL CreateSocket(UINT nPort, LPCTSTR lpszMulticastAddress, LPCTSTR lpszInterface, int iTTL=0 );
    BOOL CreateSocket(UINT nPort, LPCTSTR lpszMulticastAddress, unsigned long ulInterface = INADDR_ANY, int iTTL=0 );

	int SendMulti(const void FAR* lpBuf, int nBufLen, int nFlags = 0);
	int SendMultiPort(const void FAR* lpBuf, int nBufLen, unsigned int uiPort, int nFlags=0);

	// set up TTL
	BOOL SetTTL(int iTTL=0);
	
	// set up an interface to transmit upon 
	BOOL MulticastInterface(LPCTSTR lpszInterface); 
	BOOL MulticastInterface(unsigned long ulInterface);
	// set up interface and multicast socket address to listen in on 
	BOOL AddMembership(LPCTSTR lpszMulticastAddress, LPCTSTR lpszInterface);
	BOOL AddMembership(LPCTSTR lpszMulticastAddress, unsigned long ulInterface = INADDR_ANY);
	// drop interface that we are listening in on
	BOOL DropMembership();

// Overrides
public:

// Implementation
protected:
	struct ip_mreq m_mreq;
	TCHAR	m_szMulticastAddress[16];
    UINT	m_uiMulticastPort;
    
    UINT	m_uiRef;
};

class CAtlSocketBlocking : public CAtlSocket
{
public:
	DECLARE_WND_CLASS(_T("AtlSocketBlocking")) 

	CAtlSocketBlocking();
	~CAtlSocketBlocking();

	BOOL CreateSocket(UINT nSocketPort = 0, int nSocketType=SOCK_STREAM,
		LPCTSTR lpszSocketAddress = NULL);

// Attributes
public:
	BOOL IsBlocking();
	BOOL Attach(SOCKET hSocket);

// Operations
public:
	void CancelBlockingCall();

// Overridable callbacks
protected:
	virtual BOOL OnMessagePending();

// Implementation
public:
	int m_nTimeOut;

	virtual void Close();
	virtual int Receive(void* lpBuf, int nBufLen, int nFlags = 0);
	virtual int Send(const void* lpBuf, int nBufLen, int nFlags = 0);

	int SendChunk(const void* lpBuf, int nBufLen, int nFlags);

protected:

	BOOL* m_pbBlocking;
	int m_nConnectError;

	virtual BOOL ConnectHelper(const SOCKADDR* lpSockAddr, int nSockAddrLen);
	virtual int ReceiveFromHelper(void* lpBuf, int nBufLen,
		SOCKADDR* lpSockAddr, int* lpSockAddrLen, int nFlags);
	virtual int SendToHelper(const void* lpBuf, int nBufLen,
		const SOCKADDR* lpSockAddr, int nSockAddrLen, int nFlags);

	virtual BOOL PumpMessages(UINT uStopFlag);

};

class CAtlSocketBlockingTimeout: public CAtlSocketBlocking
{
public:
	DECLARE_WND_CLASS(_T("AtlSocketBlockingTimeout")) 
	
	CAtlSocketBlockingTimeout(){m_nTimerID=0;};
	~CAtlSocketBlockingTimeout(){};

//	int SendString(LPCTSTR lpszStr, UINT uTimeOut = 0, int nFlags = 0);
//	int ReceiveString(LPTSTR lpszStr, UINT uTimeOut = 0, int nFlags = 0);

	BOOL SetTimeOut(UINT uTimeOut);
	BOOL KillTimeOut();

protected: 
	virtual BOOL OnMessagePending();
	
private:
	UINT m_nTimerID;

};

#endif
