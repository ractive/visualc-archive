// FtpDir.h: interface for the CFtpDir class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FTPDIR_H__CCBDBE42_4CCE_4A0F_8AB4_E1F3B723EF3E__INCLUDED_)
#define AFX_FTPDIR_H__CCBDBE42_4CCE_4A0F_8AB4_E1F3B723EF3E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Dir.h"
#include "FtpSession.h"

class CFtpDir : public CDir  
{
public:
	BOOL PutFile(CString sLocalFile, CString sRemoteFile);
	BOOL GetFile(CString sRemoteFile, CString sLocalFile);
	BOOL GetFile(CString sRemoteFile, CString sLocalFile, BOOL bFailIfExist);

	void Done();
	virtual char GetDelimiter();
	DECLARE_SERIAL(CFtpDir)


	CFtpDir();
	virtual ~CFtpDir();


	CString m_sServer;
	CString m_sUsername;
	CString m_sPassword;
	UINT	m_nPort;
	BOOL	m_bPassiveMode;

	void	Serialize(CArchive &ar);

	FindFilesInDir(CFileFind *pFinder, CString sDir);

protected:
	BOOL Open();

	CString m_sBasicDir;
	virtual CFileFind *  GetFileFinder();

	CFtpSession m_FtpSession;
};

#endif // !defined(AFX_FTPDIR_H__CCBDBE42_4CCE_4A0F_8AB4_E1F3B723EF3E__INCLUDED_)
