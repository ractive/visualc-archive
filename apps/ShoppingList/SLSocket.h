#if !defined(AFX_SLSOCKET_H__4D9F9AAF_2F16_4763_9EC3_8516D776014F__INCLUDED_)
#define AFX_SLSOCKET_H__4D9F9AAF_2F16_4763_9EC3_8516D776014F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SLSocket.h : header file
//

class CShoppingListDoc;

/////////////////////////////////////////////////////////////////////////////
// CSLSocket command target

class CSLSocket : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	CSLSocket();
	virtual ~CSLSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSLSocket)
	public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnOutOfBandData(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CSLSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	CSLSocket* m_pClientSocket;

	CShoppingListDoc * GetDocument();
	BOOL SendList();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SLSOCKET_H__4D9F9AAF_2F16_4763_9EC3_8516D776014F__INCLUDED_)
