// RCServerSocket.cpp: implementation of the CRCServerSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RCServerSocket.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRCServerSocket::CRCServerSocket()
{
	m_pClientSocket = NULL;
	m_spControls = NULL;
	m_spSettings = NULL;
}

CRCServerSocket::~CRCServerSocket()
{
	if (m_pClientSocket) {
		m_pClientSocket->Close();
		delete m_pClientSocket;
	}
}

void CRCServerSocket::OnReceive(UINT nError, UINT nBytes)
{
	USES_CONVERSION;

	char *buf = new char[nBytes];
	int nRecv = Receive(buf, nBytes);
	
	buf[nRecv] = '\0';
	
	if (m_spControls && m_spSettings && buf[0] == 10) {
		buf++;
		HRESULT  hr = S_OK;
		if (strcmp(buf, "pause\r\n") == 0) {
			hr = m_spControls->pause();
		}
		else if (strcmp(buf, "play\r\n") == 0) {
			hr = m_spControls->play();
		}
		else if (strcmp(buf, "stop\r\n") == 0) {
			hr = m_spControls->stop();
		}
		else if (strcmp(buf, "next\r\n") == 0) {
			hr = m_spControls->next();
		}
		else if (strcmp(buf, "prev\r\n") == 0) {
			hr = m_spControls->previous();
		}
		else if (strcmp(buf, "volup\r\n") == 0) {
			long lVolume = 0;
			hr = m_spSettings->get_volume(&lVolume);
			if (SUCCEEDED(hr)) {
				lVolume += 10;
				lVolume = __min(lVolume, 100);
				m_spSettings->put_volume(lVolume);
			}
		}
		else if (strcmp(buf, "voldown\r\n") == 0) {
			long lVolume = 0;
			hr = m_spSettings->get_volume(&lVolume);
			if (SUCCEEDED(hr)) {
				lVolume -= 10;
				lVolume = __max(0, lVolume);
				m_spSettings->put_volume(lVolume);
			}
		}
		else if (strcmp(buf, "songinfo\r\n") == 0) {
			CComPtr<IWMPMedia> spMedia;
			hr = m_spControls->get_currentItem(&spMedia);
			if (SUCCEEDED(hr)) {
				CComBSTR sAuthor, sName;

				//hr = spMedia->get_durationString(&sDuration);
				spMedia->get_name(&sName);
				spMedia->getItemInfo(_T("Author"), &sAuthor);
				char s[256];
				s[0] = '\0';
				strcat(s, T2A(OLE2T(sAuthor)));
				if (strlen(s) > 0) {
					strcat(s, " - ");
				}
				strcat(s, T2A(OLE2T(sName)));
				strcat(s, "\r\n\r\n");
				Send(s, strlen(s), 0);
			}
		}
	}
}

void CRCServerSocket::OnConnect(UINT nError)
{
	ATLTRACE(_T("OnConnect(%d)\n"),nError);
}


void CRCServerSocket::OnAccept(UINT nError)
{
	m_pClientSocket = new CRCServerSocket();
	ATLTRACE(_T("OnAccept(%d)\n"),nError);
	Accept(*m_pClientSocket, NULL, 0);
	m_pClientSocket->m_spControls = m_spControls;
	m_pClientSocket->m_spSettings = m_spSettings;
}

void CRCServerSocket::OnClose(UINT nError)
{
	ATLTRACE(_T("OnClose(%d)\n"),nError);
}

int CRCServerSocket::SendToClient(const void *lpBuf, int nBufLen, int nFlags)
{
	if (m_pClientSocket) {
		return m_pClientSocket->Send(lpBuf, nBufLen, nFlags);
	}

	return -1;
}
