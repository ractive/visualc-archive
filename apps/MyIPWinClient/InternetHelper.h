/*************************************************************************
                     MyIPWinClient
**************************************************************************

Copyright (C) April, 2000 Jean-Pierre Bergamin, james@ractive.ch

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
***************************************************************************/


// InternetHelper.h: interface for the CInternetHelper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INTERNETHELPER_H__82189E36_F684_4048_A215_04C3894170A0__INCLUDED_)
#define AFX_INTERNETHELPER_H__82189E36_F684_4048_A215_04C3894170A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WM_RASDAEMON	(WM_USER + 10)
#define DISCONNECTED	0
#define CONNECTED		1

#include <afxinet.h>

class CInternetHelper : public CInternetSession
{
	struct tagThreadInfo {
		HANDLE hRasEvent;
		HANDLE hKillMe;
		HWND * phNotificationWnd;
		BOOL bLANConnection;
		CString sHostToPing;
	} RASThreadInfo;

	struct tagReadThreadInfo {
		LPCTSTR sURL;
		char * buf;
		DWORD dwBufLen;
		CException * pEx;
	};

public:
	BOOL Ping(CString strHost, UINT nPacketSize, CString &sAnswer);
	void getIPs(CStringArray * psaIPs);
	BOOL RASHangupUp();
	static void Destroy();
	void ReadURL(LPCTSTR sURL, CString &sBuf);
	void ReadURL(LPCTSTR sURL, char * buf, DWORD * pdwBufLen);
	BOOL EndRASDaemon();
	HWND SetNotificationWnd(HWND hWnd);
	static BOOL IsRASConnected();
	BOOL StartRASDaemon(HANDLE hRASNotification = NULL, BOOL bLANConnection = FALSE, CString sHostToPing = "");
	static BOOL CheckInternetConnection(CString * psHostToPing = NULL);
	virtual ~CInternetHelper();
	static CInternetHelper * Instance();
protected:
	CInternetHelper();
private:
	CString Decode_Resp(char * buf, int bytes, struct sockaddr_in * from);
	USHORT Checksum(USHORT * buffer, int size);
	USHORT seq_no;
	CHttpConnection * m_pServer;
	CHttpFile * m_pFile;

	void (*StatusCallback)(DWORD dwStatus, void* pStatusInfo, DWORD dwInfoLen);

	HWND hNotificationWnd;
	static CRITICAL_SECTION csNotificationWnd;
	CWinThread * m_pRasDaemon;
	static CInternetHelper * m_pInstance;
	static UINT RASDaemon(LPVOID pInfo);
	static UINT ReadURLThreadProc(LPVOID pInfo);
	virtual void OnStatusCallback(DWORD dwContext, DWORD dwInternetStatus, LPVOID lpvStatusInformation, DWORD dwStatusInformationLength);

};

#endif // !defined(AFX_INTERNETHELPER_H__82189E36_F684_4048_A215_04C3894170A0__INCLUDED_)
