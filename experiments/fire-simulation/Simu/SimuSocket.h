#if !defined(AFX_SIMUSOCKET_H__FD95F2B4_0230_4381_83F9_1217F25D8B7D__INCLUDED_)
#define AFX_SIMUSOCKET_H__FD95F2B4_0230_4381_83F9_1217F25D8B7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SimuSocket.h : header file
//

class CSimuDoc;

/////////////////////////////////////////////////////////////////////////////
// CSimuSocket command target

class CSimuSocket : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	CSimuSocket(HWND hWnd);
	virtual ~CSimuSocket();

// Overrides
public:
	void SendResult(CString &sBuf);
	void SendData(LPCTSTR buf, DWORD dwLen);
	CSimuDoc * CSimuSocket::GetDocument();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimuSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnAccept(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CSimuSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	CString m_sRecv;
	CSimuSocket * m_pClientSocket;
	HWND m_hWnd;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMUSOCKET_H__FD95F2B4_0230_4381_83F9_1217F25D8B7D__INCLUDED_)
