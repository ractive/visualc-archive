#if !defined(AFX_LISTENSOCKET_H__D7BB703C_F373_4980_B5E1_CD20DBDA75C8__INCLUDED_)
#define AFX_LISTENSOCKET_H__D7BB703C_F373_4980_B5E1_CD20DBDA75C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListenSocket.h : header file
//

#include "RecvCommand.h"

/////////////////////////////////////////////////////////////////////////////
// CListenSocket command target

class CListenSocket : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	CListenSocket();
	virtual ~CListenSocket();

// Overrides
public:
	void SetParent(CWnd* pWnd);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListenSocket)
	public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual BOOL OnMessagePending();
	virtual void OnOutOfBandData(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CListenSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	void PerformAction(CString &sCommand);
	CWnd* m_pWnd;
	CRecvCommand m_RecvCommand;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTENSOCKET_H__D7BB703C_F373_4980_B5E1_CD20DBDA75C8__INCLUDED_)
