// FtpSession.h: interface for the CFtpSession class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FTPSESSION_H__5CAB0E65_700A_470A_BD06_65CAFFD33016__INCLUDED_)
#define AFX_FTPSESSION_H__5CAB0E65_700A_470A_BD06_65CAFFD33016__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFtpSession : public CInternetSession  
{
public:
	void CloseConnection();
	BOOL GetFile(CString sRemoteFile, CString sLocalFile);
	BOOL GetFile(CString sRemoteFile, CString sLocalFile, BOOL bFailIfExist);
	BOOL PutFile(CString sLocalFile, CString sRemoteFile);
	CFtpConnection * GetConnection();
	CFtpSession();
	virtual ~CFtpSession();

	BOOL Open(LPCTSTR pstrServer, LPCTSTR pstrUserName = NULL, LPCTSTR pstrPassword = NULL, INTERNET_PORT nPort = INTERNET_INVALID_PORT_NUMBER, BOOL bPassive = FALSE);

	virtual void OnStatusCallback(DWORD dwContext, DWORD dwInternetStatus, LPVOID lpvStatusInformation, DWORD dwStatusInformationLength);

	CFtpConnection * m_pFtpConnection;
};

#endif // !defined(AFX_FTPSESSION_H__5CAB0E65_700A_470A_BD06_65CAFFD33016__INCLUDED_)
