// SyncPair.h: interface for the CSyncPair class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYNCPAIR_H__CDFC0652_0204_4882_B5D0_93983CB0FAEA__INCLUDED_)
#define AFX_SYNCPAIR_H__CDFC0652_0204_4882_B5D0_93983CB0FAEA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FtpDir.h"
#include "LocalDir.h"
#include "Config.h"

class CSyncPair : public CObject
{
public:
	void Debug();
	DECLARE_SERIAL(CSyncPair)

	BOOL IsFtpPassiveMode();
	
	CString GetFtpDirectory();
	UINT	GetFtpPort();
	CString GetFtpPassword();
	CString GetFtpUsername();
	CString GetFtpServer();
	CString GetLocalDir();

	void IsFtpPassiveMode(BOOL b);
	void SetFtpDirectory(CString s);
	void SetFtpPort(UINT nPort);
	void SetFtpPassword(CString s);
	void SetFtpUsername(CString s);
	void SetFtpServer(CString s);
	void SetLocalDir(CString s);

	void Serialize( CArchive& ar );

	CSyncPair();
	CSyncPair(CString sLocalDir, CString sServer, CString sFtpDir, CString sUserName, \
					 CString sPassword, UINT nPort, BOOL bIncludeSubDirs, BOOL bPassiveMode, \
					 BOOL bSyncFtp, BOOL bSyncLocal, \
					 BOOL bAskLocalOverwrite, BOOL bAskFtpOverwirte, \
					 BOOL bFirstSync = FALSE);

	virtual ~CSyncPair();
	BOOL Sync(HWND hNotificationWnd, HANDLE hStop);
	BOOL m_bIncludeSubDirs;
	CConfig m_Config;
	void ThrowException(CFtpSyncException::ERRCODE dwFtpError, CString sAddInfo /* = "" */, DWORD dwLocalError /* = 0 */);

protected:
	BOOL Exit(HANDLE hStop);
	void CheckConflicts(CStringArray &saDown, CStringArray &saUp);
	BOOL m_bFirstSync;
	CFtpDir m_FtpDir;
	CLocalDir m_LocalDir;
};

#endif // !defined(AFX_SYNCPAIR_H__CDFC0652_0204_4882_B5D0_93983CB0FAEA__INCLUDED_)
