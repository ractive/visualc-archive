// Dir.h: interface for the CDir class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIR_H__C4E321F2_E7B7_4069_BAA6_8F13A91A4234__INCLUDED_)
#define AFX_DIR_H__C4E321F2_E7B7_4069_BAA6_8F13A91A4234__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FtpSyncException.h"
class CFileEntry;

class CDir : public CObject
{
public:
	CFileEntry * GetFileEntry(CString sFileName, CObList * pList);
	void SetFileSyncStatus(CString sFile, BOOL bSynced);
	void ThrowException(CFtpSyncException::ERRCODE dwFtpError, CString sAddInfo = "", DWORD dwLocalError = 0);
	void UpdateEntries(BOOL bChanged);
	virtual char GetDelimiter();
	virtual BOOL FindFilesInDir(CFileFind * pFinder, CString sDir) {return FALSE;};
	BOOL FileExists(CString sFileName);
	void RemoveOldFileEntries();
	void RemoveCurrentFileEntries();
	DECLARE_SERIAL(CDir)

	CDir();
	virtual ~CDir();

	void Serialize(CArchive &ar);

	BOOL GetCurrentState(BOOL bIncludeSubDir);
	BOOL ScanDir(CString sDir);

	void GetFileTransferList(CStringArray &saFileList, CDir * pOtherDir);


	CString m_sDirectory;

	BOOL m_bIncludeSubDirs;

	CObList m_CurrentFileEntries;
	CObList m_OldFileEntries;
protected:
	virtual CFileFind * GetFileFinder() {return NULL;};
};

#endif // !defined(AFX_DIR_H__C4E321F2_E7B7_4069_BAA6_8F13A91A4234__INCLUDED_)
