// RCServerSocket.h: interface for the CRCServerSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RCSERVERSOCKET_H__3802E9E1_E6C6_47AD_B3F6_7D0E4D18B0E1__INCLUDED_)
#define AFX_RCSERVERSOCKET_H__3802E9E1_E6C6_47AD_B3F6_7D0E4D18B0E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AtlSocket.h"
#include "wmp.h"

class CRCServerSocket : public CAtlSocket  
{
public:
	int SendToClient(const void* lpBuf, int nBufLen, int nFlags);
	CRCServerSocket();
	virtual ~CRCServerSocket();
	void OnReceive(UINT nError, UINT nBytes);
	void OnConnect(UINT nError);
	void OnAccept(UINT nError);
	void OnClose(UINT nError);
	
	CComPtr<IWMPControls> m_spControls;
	CComPtr<IWMPSettings> m_spSettings;

	CRCServerSocket * m_pClientSocket;
};

#endif // !defined(AFX_RCSERVERSOCKET_H__3802E9E1_E6C6_47AD_B3F6_7D0E4D18B0E1__INCLUDED_)
