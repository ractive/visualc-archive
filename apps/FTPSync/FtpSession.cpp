// FtpSession.cpp: implementation of the CFtpSession class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FTPSync.h"
#include "FtpSession.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFtpSession::CFtpSession()
{
	EnableStatusCallback(TRUE);
	m_pFtpConnection = NULL;
}

CFtpSession::~CFtpSession()
{
	EnableStatusCallback(FALSE);
	if (m_pFtpConnection) {
		m_pFtpConnection->Close();
		delete m_pFtpConnection;
		m_pFtpConnection = NULL;
	}

	Close();
}

BOOL CFtpSession::Open(LPCTSTR pstrServer, LPCTSTR pstrUserName /* = NULL */, LPCTSTR pstrPassword /* = NULL */, INTERNET_PORT nPort /* = INTERNET_INVALID_PORT_NUMBER */, BOOL bPassive /* = FALSE */)
{
	if (!m_pFtpConnection) {
		m_pFtpConnection = GetFtpConnection(pstrServer, pstrUserName, pstrPassword, nPort, bPassive);
	}

	return m_pFtpConnection != NULL;
}

void CFtpSession::OnStatusCallback(DWORD dwContext, DWORD dwInternetStatus, LPVOID lpvStatusInformation, DWORD dwStatusInformationLength)
{
	AFX_MANAGE_STATE( AfxGetAppModuleState( ) );

	CString sMsg;
	CString sStatus;
	if (lpvStatusInformation != NULL) {
		strcpy(sStatus.GetBuffer(dwStatusInformationLength), (const char*)lpvStatusInformation);
		sStatus.ReleaseBuffer();
	}
	switch (dwStatusInformationLength) {
	case INTERNET_STATUS_RESOLVING_NAME:
		sMsg = "Resolving name: " + sStatus;
		break;
	case INTERNET_STATUS_NAME_RESOLVED:
		sMsg = sStatus + " resolved";
		break;
	case INTERNET_STATUS_CONNECTING_TO_SERVER:
		sMsg = "Connecting to " + sStatus;
		break;
	case INTERNET_STATUS_CONNECTED_TO_SERVER:
		sMsg = "Connected to " + sStatus;
		break;
	case INTERNET_STATUS_SENDING_REQUEST:
		sMsg = "Sending Request...";
		break;
	case INTERNET_STATUS_REQUEST_SENT:
		sMsg = "Waiting for response...";
		break;
	case INTERNET_STATUS_RECEIVING_RESPONSE:
		sMsg = "Receiving Response";
		break;
	case INTERNET_STATUS_RESPONSE_RECEIVED:
		sMsg = "Response received";
		break;
	case INTERNET_STATUS_CLOSING_CONNECTION:
		sMsg = "Closing connection";
		break;
	case INTERNET_STATUS_CONNECTION_CLOSED:
		sMsg = "Connection closed";
		break;
	case INTERNET_STATUS_HANDLE_CREATED:
		sMsg = "Handle created";
		break;
	case INTERNET_STATUS_HANDLE_CLOSING:
		sMsg = "Closing handle";
		break;
	case INTERNET_STATUS_REQUEST_COMPLETE:
		sMsg = "Request complete";
		break;
	//default:
		//sMsg = "Connecting...";
	}
	if (!sMsg.IsEmpty()) {
		
		TRACE("%s\n", sMsg);
	}
}

CFtpConnection * CFtpSession::GetConnection()
{
	return m_pFtpConnection;
}

BOOL CFtpSession::PutFile(CString sLocalFile, CString sRemoteFile)
{
	return m_pFtpConnection->PutFile(sLocalFile, sRemoteFile);
}

BOOL CFtpSession::GetFile(CString sRemoteFile, CString sLocalFile)
{
	return m_pFtpConnection->GetFile(sRemoteFile, sLocalFile);
}

BOOL CFtpSession::GetFile(CString sRemoteFile, CString sLocalFile, BOOL bFailIfExist)
{
	return m_pFtpConnection->GetFile(sRemoteFile, sLocalFile, bFailIfExist);
}

void CFtpSession::CloseConnection()
{
	if (m_pFtpConnection) {
		m_pFtpConnection->Close();
		delete m_pFtpConnection;
		m_pFtpConnection = NULL;
	}
}
