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


// InternetHelper.cpp: implementation of the CInternetHelper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyIPWinClient.h"
#include "InternetHelper.h"
#include <winsock2.h>
#include <afxinet.h>
#include <raserror.h>
#include <ras.h>
#include "UpdateDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInternetHelper * CInternetHelper::m_pInstance = 0;
CRITICAL_SECTION CInternetHelper::csNotificationWnd = {0};

#define ICMP_ECHO 8
#define ICMP_ECHOREPLY 0

#define ICMP_MIN 8 // minimum 8 byte icmp packet (just header)

/* The IP header */
typedef struct iphdr 
{
	unsigned int h_len:4;          // length of the header
	unsigned int version:4;        // Version of IP
	unsigned char tos;             // Type of service
	unsigned short total_len;      // total length of the packet
	unsigned short ident;          // unique identifier
	unsigned short frag_and_flags; // flags
	unsigned char  ttl; 
	unsigned char proto;           // protocol (TCP, UDP etc)
	unsigned short checksum;       // IP checksum

	unsigned int sourceIP;
	unsigned int destIP;

} IpHeader;

//
// ICMP header
//
typedef struct _ihdr 
{
  BYTE i_type;
  BYTE i_code; // type sub code
  USHORT i_cksum;
  USHORT i_id;
  USHORT i_seq;
  // This is not the std header, but we reserve space for time
  ULONG timestamp;
} IcmpHeader;

#define STATUS_FAILED 0xFFFF
#define DEF_PACKET_SIZE 32
#define MAX_PACKET 1024//65536

#define xmalloc(s) HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,(s))
#define xfree(p)   HeapFree (GetProcessHeap(),0,(p))

#define DEF_PACKET_SIZE 32

CInternetHelper * CInternetHelper::Instance()
{
	// If we don't have an instance yet, create a new one.
	if (m_pInstance == 0) {
		m_pInstance = new CInternetHelper;
	}
	
	// Return the (one and only) instance
	return m_pInstance;
}

CInternetHelper::CInternetHelper() : CInternetSession(NULL, 1, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, INTERNET_FLAG_DONT_CACHE/* | INTERNET_FLAG_ASYNC*/)
{
	m_pRasDaemon = NULL;
	InitializeCriticalSection(&csNotificationWnd);
	EnableStatusCallback(TRUE);
}

CInternetHelper::~CInternetHelper()
{
	EndRASDaemon();
	EnableStatusCallback(FALSE);
}

BOOL CInternetHelper::CheckInternetConnection(CString * psHostToPing /* = NULL */)
{
	DWORD dwReserved = 0;
	DWORD dwFlags = INTERNET_CONNECTION_MODEM |INTERNET_CONNECTION_LAN | INTERNET_CONNECTION_PROXY;
	// First check if there "could" be a connection.
	// If you're connected via LAN this call always return TRUE
	if (InternetGetConnectedState(&dwFlags, 0) == FALSE) {
		// We are surely not connected
		return FALSE;
	}
	else {
		// Now check if we can ping to see if we are connected.
		CString sAnswer;
		CString sHostToPing;
		if (psHostToPing == NULL) {
			sHostToPing = _T("www.yahoo.com");
		}
		else {
			sHostToPing = *psHostToPing;
		}
		BOOL bRet = m_pInstance->Ping(sHostToPing, 32, sAnswer);
#ifdef _DEBUG
		if (bRet) {
			TRACE("Ping to %s successful\r\n", sHostToPing);
		}
		else {
			TRACE("Ping to %s NOT successful. Answer: %s\r\n", sHostToPing, sAnswer);
			
		}
#endif
		return bRet;
	}

}

BOOL CInternetHelper::StartRASDaemon(HANDLE hRASNotification /* = NULL */, BOOL bLANConnection /* = FALSE */, CString sHostToPing /* = "" */)
{
	if (hRASNotification)
		RASThreadInfo.hRasEvent = hRASNotification;
	else
		RASThreadInfo.hRasEvent = CreateEvent(NULL, FALSE, FALSE, "RasNotification");

	RASThreadInfo.hKillMe = CreateEvent(NULL, FALSE, FALSE, "KillMe");
	RASThreadInfo.bLANConnection = bLANConnection;
	RASThreadInfo.sHostToPing = sHostToPing;
	m_pRasDaemon = AfxBeginThread(RASDaemon, &RASThreadInfo);

	return m_pRasDaemon != NULL;
}

BOOL CInternetHelper::EndRASDaemon()
{
	if (m_pRasDaemon) {
		SetEvent(RASThreadInfo.hKillMe);
		// Give the thread 10 sec. time to kill himself.
		return WaitForSingleObject(m_pRasDaemon->m_hThread, 10000) == WAIT_OBJECT_0;
	}

	return TRUE; // or false?
}


UINT CInternetHelper::RASDaemon(LPVOID pInfo)
{
	const int nPollingIntervall = 60000; //milliseconds
	tagThreadInfo * pThreadInfo = (tagThreadInfo *)pInfo;
	if (pThreadInfo->bLANConnection) {
		// When the user is connected via a LAN we have to call
		// CheckInternetConnection to see if we are connected or not
		do {
			static BOOL bWasConnected = FALSE;
			// Check if we are connected
			BOOL bIsConnected = CheckInternetConnection(&(pThreadInfo->sHostToPing));
			// Compare this with the "old" connection status
			if (bWasConnected != bIsConnected) {
				// The status changed.
				bWasConnected = bIsConnected;
				EnterCriticalSection(&csNotificationWnd);
				::PostMessage(*(pThreadInfo->phNotificationWnd), WM_RASDAEMON, 0, bIsConnected ? CONNECTED : DISCONNECTED);
				LeaveCriticalSection(&csNotificationWnd);
			}
		} while (WaitForSingleObject(pThreadInfo->hKillMe, nPollingIntervall) != WAIT_OBJECT_0);

	}
	else {
		OSVERSIONINFO osinfo;
		osinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		GetVersionEx(&osinfo);
		if (osinfo.dwPlatformId == VER_PLATFORM_WIN32_NT) {
			HANDLE hArray[2];
			hArray[0] = pThreadInfo->hRasEvent;
			hArray[1] = pThreadInfo->hKillMe;
			while (1) {
				DWORD dwWaitRet = RasConnectionNotification((HRASCONN)INVALID_HANDLE_VALUE, pThreadInfo->hRasEvent, RASCN_Connection | RASCN_Disconnection);
				if (dwWaitRet != 0) {
					// Error
				}
				if ((dwWaitRet = WaitForMultipleObjects(2, hArray, FALSE, INFINITE)) == WAIT_OBJECT_0) {
					// There was a RasNotification
					ResetEvent(pThreadInfo->hRasEvent);
					BOOL bConnected = IsRASConnected();
					// Post a message to the notification window (if set with SetNotificationWnd)
					if (*(pThreadInfo->phNotificationWnd)) {
						EnterCriticalSection(&csNotificationWnd);
						::PostMessage(*(pThreadInfo->phNotificationWnd), WM_RASDAEMON, 0, bConnected ? CONNECTED : DISCONNECTED);
						LeaveCriticalSection(&csNotificationWnd);
					}
					continue;
				}
				else if (dwWaitRet = WAIT_OBJECT_0 + 1) {
					// The hKillMe event was set. End the thread.
					return 0;
				}
				else {
					// Error
				}
			}
		}
		else if (osinfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) {
			// As long as the thread should not be killed, check for a connection
			while (WaitForSingleObject(pThreadInfo->hKillMe, 5000 /*nPollingIntervall*/) != WAIT_OBJECT_0) {
				static BOOL bWasConnected = FALSE;
				// Check if we are connected
				BOOL bIsConnected = IsRASConnected();
				// Compare this with the "old" connection status
				if (bWasConnected != bIsConnected) {
					// The status changed.
					bWasConnected = bIsConnected;
					EnterCriticalSection(&csNotificationWnd);
					::PostMessage(*(pThreadInfo->phNotificationWnd), WM_RASDAEMON, 0, bIsConnected ? CONNECTED : DISCONNECTED);
					LeaveCriticalSection(&csNotificationWnd);
				}
			}
		}
		else {
			// OS Platform?
			return 1;
		}
	}

	return 0;
}

BOOL CInternetHelper::IsRASConnected()
{

	LPRASCONN lprasconn = NULL;
	DWORD cb, dwWritten;
	cb = sizeof(RASCONN);

	if ((lprasconn = (LPRASCONN)malloc((UINT)cb)) != NULL) {
		free(lprasconn);
		lprasconn = (LPRASCONN)new UINT[cb];
		lprasconn->dwSize = sizeof(RASCONN);

		DWORD dwRet= RasEnumConnections(lprasconn, &cb, &dwWritten);
		if (dwRet == ERROR_BUFFER_TOO_SMALL) {
			// buffer too small - realloc size in dwBuf
			if ((lprasconn = (LPRASCONN)realloc(lprasconn, (UINT)cb)) != NULL) {
				dwRet = RasEnumConnections(lprasconn, &cb, &dwWritten);
			}
		}
		if (lprasconn != NULL) {
			free(lprasconn);
		}
		
		if (dwRet == 0) {
			// We have the connection information
			return dwWritten > 0;
		}
		else {
			return FALSE;
		}
	}

	return FALSE;

}

HWND CInternetHelper::SetNotificationWnd(HWND hWnd)
{
	HWND hOldNotificationWnd = hNotificationWnd;
	EnterCriticalSection(&csNotificationWnd);
	hNotificationWnd = hWnd;
	RASThreadInfo.phNotificationWnd = &hNotificationWnd;
	LeaveCriticalSection(&csNotificationWnd);
	return hOldNotificationWnd;
}

UINT CInternetHelper::ReadURLThreadProc(LPVOID pInfo)
{
	tagReadThreadInfo * pReadInfo = (tagReadThreadInfo *)pInfo;
	try {
		m_pInstance->ReadURL(pReadInfo->sURL, pReadInfo->buf, &pReadInfo->dwBufLen);
	}
	catch (CException * pEx) {
		pReadInfo->pEx = pEx;
		if (m_pInstance->m_pFile != NULL) {
			m_pInstance->m_pFile->Close();
			delete m_pInstance->m_pFile;
			m_pInstance->m_pFile = NULL;
		}
		if (m_pInstance->m_pServer != NULL) {
			m_pInstance->m_pServer->Close();
			delete m_pInstance->m_pServer;
			m_pInstance->m_pServer = NULL;
		}
		return 1;
	}
	return 0;
}

void CInternetHelper::ReadURL(LPCTSTR sURL, CString &sBuf)
{
	DWORD dwBufLen = 0;
	//ReadURL(sURL, NULL, &dwBufLen);

	if (dwBufLen == 0) {
		dwBufLen = 32 * 1024;
	}

	tagReadThreadInfo readInfo;
	readInfo.buf = sBuf.GetBuffer(dwBufLen);
	readInfo.dwBufLen = dwBufLen;
	readInfo.sURL = sURL;
	readInfo.pEx = NULL;

	// Disable the window so that the user can't close it, start a new
	// transaction etc.
	// Simulate modal behaviour.
	CWnd * pMainWnd = AfxGetMainWnd();
	BOOL bWasEnabled = !pMainWnd->EnableWindow(FALSE);

	CUpdateDlg dlg;
	dlg.Create(IDD_UPDATEDLG, pMainWnd);

	StatusCallback = &(dlg.UpdateDlg);
	StatusCallback(0, NULL, 0);

	CWinThread * pThread = NULL;
	pThread = AfxBeginThread(ReadURLThreadProc, &readInfo, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);

	pThread->m_bAutoDelete = false;
	pThread->ResumeThread();

	// Hmm, not sure but here could occur a "deadlock". If the Window gets not messages
	// any more and we call Pump at the wrong time, Pump will wait will a new
	// message arrives. Very unlikely, but possible.
	while (WaitForSingleObject(pThread->m_hThread, 150) != WAIT_OBJECT_0) {
		dlg.Pump();
	}

	dlg.DestroyWindow();
	
	sBuf.ReleaseBuffer();

	pMainWnd->EnableWindow(bWasEnabled);
	pMainWnd->SetForegroundWindow();

	DWORD exit;
	// If the thread exited successfully, it returns 0;
	::GetExitCodeThread(pThread->m_hThread, &exit);
	delete pThread;

	if (exit == 1 && readInfo.pEx != NULL) {
		throw readInfo.pEx;
	}
}

void CInternetHelper::ReadURL(LPCTSTR sURL, char * buf, DWORD * pdwBufLen)
{
	const int nReadBlockSize = 1024;

	CInternetSession session;

	m_pServer = NULL;
	m_pFile = NULL;

	CString sServerName;
	CString sObject;
	INTERNET_PORT nPort;
	DWORD dwServiceType;
	
	AfxParseURL(sURL, dwServiceType, sServerName, sObject, nPort);

	m_pServer = GetHttpConnection(sServerName, nPort);

	DWORD dwHttpRequestFlags = 	INTERNET_FLAG_EXISTING_CONNECT | INTERNET_FLAG_NO_AUTO_REDIRECT | INTERNET_FLAG_RELOAD;

	m_pFile = m_pServer->OpenRequest(CHttpConnection::HTTP_VERB_GET, sObject, NULL, 1, NULL, NULL, dwHttpRequestFlags);
	CString sHeaders(_T("Accept: text/*\r\nUser-Agent: MyIP Windows client\r\n"));

	m_pFile->AddRequestHeaders(sHeaders);
	m_pFile->SendRequest();

	if (*pdwBufLen == 0) {
		DWORD dwBufLen = sizeof(DWORD);
		m_pFile->QueryInfo(HTTP_QUERY_FLAG_NUMBER  | HTTP_QUERY_CONTENT_LENGTH, pdwBufLen, &dwBufLen);
	}
	else {

		char sz[nReadBlockSize];

		int nPos = 0;


		unsigned int nCounter = 0;

		// Now the HTML code which is given by the CGI script is read in now.
		while (m_pFile->Read(sz, nReadBlockSize)) {
			nCounter += strlen(sz);
			
			if (nCounter >= *pdwBufLen) {
				// The buffer is too small
				return;
			}
			strcat(buf, sz);
		}
	}

	m_pFile->Close();
	m_pServer->Close();
	delete m_pServer;
	delete m_pFile;
	m_pServer = NULL;
	m_pFile = NULL;
}

void CInternetHelper::Destroy()
{
	if (m_pInstance != 0) {
		delete m_pInstance;
	}
}

BOOL CInternetHelper::RASHangupUp()
{
	LPRASCONN lprasconn = NULL;
	DWORD cb, dwWritten;
	cb = sizeof(RASCONN);
	if ((lprasconn = (LPRASCONN)malloc((UINT)cb)) != NULL) {
		lprasconn->dwSize = sizeof(RASCONN);

		DWORD dwRet= RasEnumConnections(lprasconn, &cb, &dwWritten);
		if (dwRet == ERROR_BUFFER_TOO_SMALL) {
			// buffer too small - realloc size in dwBuf
			if ((lprasconn = (LPRASCONN)realloc(lprasconn, (UINT)cb)) != NULL) {
				dwRet = RasEnumConnections(lprasconn, &cb, &dwWritten);
			}
			else
			{
				free(lprasconn);
				return FALSE;
			}
		}
		else if (dwRet == ERROR_NOT_ENOUGH_MEMORY) {
			free(lprasconn);
			//MessageBox(NULL, "Not enough memory to get connection information", "Error", MB_OK | MB_ICONEXCLAMATION);
			return FALSE;
		}
		else if (dwRet != 0) // other error
		{ 
			free(lprasconn);
			return FALSE;
		}
		
		if (dwRet == 0) {
			// We have the connection information
			if (RasHangUp(lprasconn->hrasconn) != 0) {
				// Could not hangup
				free(lprasconn);
				return FALSE;
			}
		}

		free(lprasconn);

	}

	return TRUE;

}

void CInternetHelper::getIPs(CStringArray *psaIPs)
{
	char szHostName[128];

	if(gethostname(szHostName, 128) == 0 )
	{
		// Get host adresses
		struct hostent * pHost;
 
		pHost = gethostbyname(szHostName);
 
		for(int i = 0; pHost!= NULL && pHost->h_addr_list[i]!= NULL; i++ )
 		{
			CString str;
 
 			for(int j = 0; j < pHost->h_length; j++)
 			{
				CString addr;
 
 				if( j > 0 )
 					str += ".";
 
 				addr.Format("%u", (unsigned int)((unsigned char*)pHost->h_addr_list[i])[j]);
				str += addr;
 			}
  			// str now contains one local IP address - do whatever you want to do with it (probably add it to a list)
			psaIPs->Add(str);
 		}
	}
	else {
		int error = WSAGetLastError();
	}
}

void CInternetHelper::OnStatusCallback(DWORD dwContext, DWORD dwInternetStatus, LPVOID lpvStatusInformation, DWORD dwStatusInformationLength)
{
	StatusCallback(dwInternetStatus, lpvStatusInformation, dwStatusInformationLength);
}

BOOL CInternetHelper::Ping(CString strHost, UINT nPacketSize, CString &sAnswer)
{
	SOCKET				sockRaw;
	struct sockaddr_in	dest,from;
	struct hostent		*hp;
	int					bread,datasize;
	int					fromlen = sizeof(from);
	int					timeout = 10;
	char				*dest_ip;
	char				*icmp_data;
	char				*recvbuf;
	unsigned int		addr=0;
	int					bwrote;

	WSAOVERLAPPED ov;
	ov.hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	sockRaw = INVALID_SOCKET;
	sockRaw = WSASocket(AF_INET,
					   SOCK_RAW,
					   IPPROTO_ICMP,
					   NULL, 0, WSA_FLAG_OVERLAPPED);
  
	if (sockRaw == INVALID_SOCKET) 
	{
		sAnswer.Format("WSASocket() failed: %d",WSAGetLastError());
		return FALSE;
	}

	bread = setsockopt(sockRaw,SOL_SOCKET,SO_RCVTIMEO,(char*)&timeout,
  					sizeof(timeout));
	if(bread == SOCKET_ERROR) 
	{
  		sAnswer.Format("failed to set recv timeout: %d",WSAGetLastError());
		return FALSE;
	}
	
//	timeout = 1000;
	bwrote = setsockopt(sockRaw,SOL_SOCKET,SO_SNDTIMEO,(char*)&timeout,
  					sizeof(timeout));
	if(bwrote == SOCKET_ERROR) 
	{
  		sAnswer.Format("failed to set send timeout: %d",WSAGetLastError());
		return FALSE;
	}
	memset(&dest,0,sizeof(dest));

	hp = gethostbyname(strHost);
	
	if (!hp)
	{
		addr = inet_addr(strHost);
	}
	if ((!hp)  && (addr == INADDR_NONE) ) 
	{
		sAnswer.Format("Unable to resolve %s",strHost);
		return FALSE;
	}
	
	if (hp != NULL)
	  memcpy(&(dest.sin_addr),hp->h_addr,hp->h_length);
	else
  		dest.sin_addr.s_addr = addr;

	if (hp)
		dest.sin_family = hp->h_addrtype;
	else
		dest.sin_family = AF_INET;

	dest_ip = inet_ntoa(dest.sin_addr);

	if (nPacketSize > 0) 
	{
		datasize = nPacketSize;
		if (datasize == 0)
			datasize = DEF_PACKET_SIZE;
	}
	else
	  datasize = DEF_PACKET_SIZE;
	
	datasize += sizeof(IcmpHeader);  

	icmp_data = (char*)xmalloc(MAX_PACKET);
	recvbuf = (char*)xmalloc(MAX_PACKET);
	
	if (!icmp_data) 
	{
		sAnswer.Format("HeapAlloc failed %d",GetLastError());
		return FALSE;
	}
	
	memset(icmp_data,0,MAX_PACKET);

	IcmpHeader *icmp_hdr;
	char *datapart;

	icmp_hdr = (IcmpHeader*)icmp_data;

	icmp_hdr->i_type = ICMP_ECHO;
	icmp_hdr->i_code = 0;
	icmp_hdr->i_id = (USHORT)GetCurrentProcessId();
	icmp_hdr->i_cksum = 0;
	icmp_hdr->i_seq = 0;
  
	datapart = icmp_data + sizeof(IcmpHeader);
	  //
	  // Place some junk in the buffer.
	  //
	memset(datapart,'E', datasize - sizeof(IcmpHeader));

	//int bwrote;

	((IcmpHeader*)icmp_data)->i_cksum = 0;
	((IcmpHeader*)icmp_data)->timestamp = GetTickCount();

	((IcmpHeader*)icmp_data)->i_seq = seq_no++;
	((IcmpHeader*)icmp_data)->i_cksum = Checksum((USHORT*)icmp_data, 
										datasize);

	bwrote = sendto(sockRaw,icmp_data,datasize,0,(struct sockaddr*)&dest,
				sizeof(dest));
	if (bwrote == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSAETIMEDOUT) 
		{
	  		sAnswer = "timed out";
			return FALSE;
		}
		sAnswer.Format("sendto failed: %d",WSAGetLastError());
		return FALSE;
	}
	if (bwrote < datasize ) 
	{
		sAnswer.Format("Wrote %d bytes",bwrote);
	}
	bread = recvfrom(sockRaw,recvbuf,MAX_PACKET,0,(struct sockaddr*)&from,
			         &fromlen);
	if (bread == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSAETIMEDOUT) 
		{
	  		sAnswer = "timed out";
			return FALSE;
		}
		sAnswer.Format("recvfrom failed: %d",WSAGetLastError());
		return FALSE;
	}
	sAnswer = Decode_Resp(recvbuf,bread,&from);
	Sleep(500);
	xfree(icmp_data);
	xfree(recvbuf);
	closesocket(sockRaw);
	return TRUE;

}

USHORT CInternetHelper::Checksum(USHORT *buffer, int size)
{
	unsigned long cksum=0;

	while(size >1) 
	{
		cksum+=*buffer++;
		size -=sizeof(USHORT);
	}
  
	if(size ) 
	{
		cksum += *(UCHAR*)buffer;
	}

	cksum = (cksum >> 16) + (cksum & 0xffff);
	cksum += (cksum >>16);
	return (USHORT)(~cksum);
}

CString CInternetHelper::Decode_Resp(char *buf, int bytes, sockaddr_in *from)
{
	/*IpHeader *iphdr;
	IcmpHeader *icmphdr;
	unsigned short iphdrlen;
	CString strRet = _T("");

	iphdr = (IpHeader *)buf;

	iphdrlen = iphdr->h_len * 4 ; // number of 32-bit words *4 = bytes

	if (bytes  < iphdrlen + ICMP_MIN) 
	{
		strRet.Format("Too few bytes from %s",inet_ntoa(from->sin_addr));
	}

	icmphdr = (IcmpHeader*)(buf + iphdrlen);

	if (icmphdr->i_type != ICMP_ECHOREPLY) 
	{
		strRet.Format("non-echo type %d recvd",icmphdr->i_type);
		return strRet;
	}
	if (icmphdr->i_id != (USHORT)GetCurrentProcessId()) 
	{
		strRet.Format("someone else's packet!");
		return strRet;
	}
	strRet.Format("%d bytes from %s: icmp_seq = %d.  time: %d ms",
		bytes, inet_ntoa(from->sin_addr),
		icmphdr->i_seq,
		GetTickCount()-icmphdr->timestamp);
	return strRet;*/
	return "";
}
