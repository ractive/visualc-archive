#if !defined(AFX_CONNECTSOCKET_H__DFFCBF0B_09F7_49AA_8357_124CDAFB203A__INCLUDED_)
#define AFX_CONNECTSOCKET_H__DFFCBF0B_09F7_49AA_8357_124CDAFB203A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConnectSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CConnectSocket command target

class CConnectSocket : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	CConnectSocket();
	virtual ~CConnectSocket();

// Overrides
public:
	CAsyncSocket *m_ConnectSocket;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConnectSocket)
	public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnOutOfBandData(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CConnectSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONNECTSOCKET_H__DFFCBF0B_09F7_49AA_8357_124CDAFB203A__INCLUDED_)
