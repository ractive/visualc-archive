// FtpDir.cpp: implementation of the CFtpDir class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FTPSync.h"
#include "FtpDir.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CFtpDir, CDir, 1)


CFtpDir::CFtpDir()
{

}

CFtpDir::~CFtpDir()
{

}


CFileFind * CFtpDir::GetFileFinder()
{
	if (!Open()) {
		return NULL;
	}

	CFtpFileFind *pFinder = new CFtpFileFind(m_FtpSession.GetConnection());
	return (CFileFind *)pFinder;
}


void CFtpDir::Serialize(CArchive &ar)
{
	CDir::Serialize( ar );
	
	if (ar.IsStoring()) {
		ar << m_bPassiveMode;
		ar << m_nPort;
		ar << m_sPassword;
		ar << m_sServer;
		ar << m_sUsername;
	}
	else {
		ar >> m_bPassiveMode;
		ar >> m_nPort;
		ar >> m_sPassword;
		ar >> m_sServer;
		ar >> m_sUsername;	
	}
}

BOOL CFtpDir::Open()
{
	if (!m_FtpSession.Open(m_sServer, m_sUsername, m_sPassword, m_nPort, m_bPassiveMode)) {
		return FALSE;
	}
	
	BOOL bSuccess = TRUE;

	if (m_sBasicDir.IsEmpty()) {
		bSuccess = m_FtpSession.GetConnection()->GetCurrentDirectory(m_sBasicDir);
	}

	return bSuccess;
}


BOOL CFtpDir::FindFilesInDir(CFileFind *pFinder, CString sDir)
{
	TRACE("=== FTP ====\r\n");
	ASSERT(m_FtpSession.GetConnection());

	if (m_sBasicDir.Right(1) != GetDelimiter()) {
		m_sBasicDir += GetDelimiter();
	}

	if (!sDir.IsEmpty()) {
		CString sNewDir;
		if (sDir.Left(1) == "/") {
			// It's an absolute path
			sNewDir = sDir;
		}
		else {
			// sDir is relative path
			// Add the basic dir
			sNewDir = m_sBasicDir + sDir;
		}
		if (!m_FtpSession.GetConnection()->SetCurrentDirectory(sNewDir)) {
			
			delete pFinder;
			ThrowException(CFtpSyncException::CHANGEDIR, sNewDir);
		}
	}

	return pFinder->FindFile(NULL, INTERNET_FLAG_EXISTING_CONNECT | INTERNET_FLAG_RELOAD);
}

char CFtpDir::GetDelimiter()
{
	return '/';
}

void CFtpDir::Done()
{
	m_FtpSession.CloseConnection();
	m_sBasicDir.Empty();
}

BOOL CFtpDir::PutFile(CString sLocalFile, CString sRemoteFile)
{
	return m_FtpSession.PutFile(sLocalFile, sRemoteFile);
}

BOOL CFtpDir::GetFile(CString sRemoteFile, CString sLocalFile)
{
	return m_FtpSession.GetConnection()->GetFile(sRemoteFile, sLocalFile);
}

BOOL CFtpDir::GetFile(CString sRemoteFile, CString sLocalFile, BOOL bFailIfExist)
{
	return m_FtpSession.GetConnection()->GetFile(sRemoteFile, sLocalFile, bFailIfExist);
}

