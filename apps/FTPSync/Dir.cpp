// Dir.cpp: implementation of the CDir class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FTPSync.h"
#include "Dir.h"
#include "FileEntry.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CDir, CObject, 1)


CDir::CDir()
{

}

CDir::~CDir()
{
	RemoveCurrentFileEntries();
	RemoveOldFileEntries();
}

BOOL CDir::GetCurrentState(BOOL bIncludeSubDir)
{
	m_bIncludeSubDirs = bIncludeSubDir;
	
	RemoveCurrentFileEntries();

	return ScanDir(m_sDirectory);
}

void CDir::Serialize(CArchive &ar)
{
	CObject::Serialize( ar );
	
	if (ar.IsStoring()) {
		ar << m_sDirectory;
		// Store the current file list
		m_OldFileEntries.Serialize(ar);
	}
	else {
		ar >> m_sDirectory;
		// Get the old file list
		m_OldFileEntries.Serialize(ar);
	}
}

BOOL CDir::ScanDir(CString sDir)
{
	CFileFind *finder = GetFileFinder();

	if (finder == NULL) {
		return FALSE;
	}

	BOOL bFound = FindFilesInDir(finder, sDir);
	if (!bFound) {
		TRACE("Nothing found\r\n\r\n");
		RemoveCurrentFileEntries();
		delete finder;
		return FALSE;
	}

	while(bFound) {
		bFound = finder->FindNextFile();
		if(finder->IsDots()) {
			continue;
		}

		if (finder->IsDirectory()) {
			continue;
			if (m_bIncludeSubDirs) {
				if (!ScanDir(finder->GetFileName())) {
					delete finder;
					return FALSE;
				}
			}

		}

		CFileEntry * pEntry = GetFileEntry(finder->GetFileName(), &m_CurrentFileEntries);

		finder->GetLastWriteTime(&pEntry->m_FileTime);
		pEntry->m_dwFileSize = finder->GetLength();
		finder->GetLastWriteTime(&pEntry->m_FileTime);
		pEntry->m_bSynced = TRUE;

#ifdef _DEBUG
		SYSTEMTIME st;
		char sTime[15];
		//char sDate[15];
		char sDateTime[31];
		sDateTime[0] = '\0';
		FileTimeToSystemTime(&pEntry->m_FileTime, &st);

		FILETIME flt;
		FileTimeToLocalFileTime(&pEntry->m_FileTime, &flt);
		FileTimeToSystemTime(&flt, &st);
		
		// Or use LOCALE_USER_DEFAULT???
		//GetDateFormat(LOCALE_SYSTEM_DEFAULT, DATE_SHORTDATE, &st, NULL, sDate, 15);
		GetTimeFormat(LOCALE_SYSTEM_DEFAULT, TIME_NOSECONDS, &st, NULL, sTime, 15);
		/*strcpy(sDateTime, sDate);
		strcat(sDateTime, " ");*/
		strcat(sDateTime, sTime);
		TRACE("  %-20.20s %7s\r\n", pEntry->m_sFileName, sDateTime);
#endif
	}

	finder->Close();

	delete finder;

	return TRUE;
}


void CDir::GetFileTransferList(CStringArray &saFileList, CDir * pOtherDir)
{
	// Walk through all current files and compare them with the old ones
	POSITION pos = m_CurrentFileEntries.GetHeadPosition();
	while(pos) {
		CFileEntry * pEntry = (CFileEntry *)m_CurrentFileEntries.GetNext(pos);
		
		pEntry->m_bSynced = TRUE;
		
		POSITION old_pos = m_OldFileEntries.GetHeadPosition();
		
		BOOL bChecked = FALSE;
		BOOL bAdded = FALSE;
		while(old_pos) {
			CFileEntry * pOldEntry = (CFileEntry *)m_OldFileEntries.GetNext(old_pos);

			// Check if we found the same file
			if (pOldEntry->m_sFileName == pEntry->m_sFileName) {
				// Check if the write time is the same...
				if ((CompareFileTime(&pOldEntry->m_FileTime, &pEntry->m_FileTime) == -1) ||
					(pOldEntry->m_dwFileSize != pEntry->m_dwFileSize)) {
					// The current file is newer or has a different size: add it to the transfer list
					saFileList.Add(pEntry->m_sFileName);

					// If the file is newer, it's not sycned!
					pEntry->m_bSynced = FALSE;
					bAdded = TRUE;
				}
				
				// The file was checked
				bChecked = TRUE;
				break;
			}
		}

		// If the file was not checked an was not in the old set, it's new
		if (!bChecked && old_pos == NULL) {
			// The current file is not in the old filelist
			// Add it also to the list
			saFileList.Add(pEntry->m_sFileName);
			bAdded = TRUE;
		}


		// Now we check if a file is missing on "the other side"
		// If yes, we add it to the transferlist (if not already added)
		if (!bAdded && !pOtherDir->FileExists(pEntry->m_sFileName)) {
			saFileList.Add(pEntry->m_sFileName);
		}
		
	}
}

void CDir::RemoveCurrentFileEntries()
{
	while(m_CurrentFileEntries.GetCount()) {
		CFileEntry * fe = (CFileEntry *)m_CurrentFileEntries.RemoveHead();
		delete fe;
	}
}

void CDir::RemoveOldFileEntries()
{
	while(m_OldFileEntries.GetCount()) {
		CFileEntry * fe = (CFileEntry *)m_OldFileEntries.RemoveHead();
		delete fe;
	}	
}

BOOL CDir::FileExists(CString sFileName)
{
	POSITION pos = m_CurrentFileEntries.GetHeadPosition();
	while(pos) {
		CFileEntry *next = (CFileEntry *)m_CurrentFileEntries.GetNext(pos);
		if (next->m_sFileName == sFileName) {
			return TRUE;
		}
	}

	return FALSE;
}


char CDir::GetDelimiter()
{
	return '/';
}

void CDir::UpdateEntries(BOOL bChanged)
{
	if (bChanged) {
		if (!GetCurrentState(m_bIncludeSubDirs)) {
			ASSERT(FALSE);
		}
	}

	// Copy all elements form m_CurrentFileEntries to m_OldFileEntries

	POSITION pos = m_CurrentFileEntries.GetHeadPosition();
	while(pos) {
		CFileEntry * pEntry = (CFileEntry *)m_CurrentFileEntries.GetNext(pos);

		if (!pEntry->m_bSynced) {
			// don't update the old infos with the new if the file could ot be synced!
			continue;
		}
		
		CFileEntry * pOldEntry = GetFileEntry(pEntry->m_sFileName, &m_OldFileEntries);
		pOldEntry->m_FileTime.dwHighDateTime = pEntry->m_FileTime.dwHighDateTime;
		pOldEntry->m_FileTime.dwLowDateTime = pEntry->m_FileTime.dwLowDateTime;
		pOldEntry->m_dwFileSize = pEntry->m_dwFileSize;
		pOldEntry->m_bSynced = pEntry->m_bSynced;

	}

}

void CDir::ThrowException(CFtpSyncException::ERRCODE dwFtpError, CString sAddInfo /* = "" */, DWORD dwLocalError /* = 0 */)
{
	CFtpSyncException * pEx = new CFtpSyncException(dwFtpError, sAddInfo, dwLocalError);

	throw pEx;
}

void CDir::SetFileSyncStatus(CString sFile, BOOL bSynced)
{
	POSITION pos = m_CurrentFileEntries.GetHeadPosition();
	while(pos) {
		CFileEntry *next = (CFileEntry *)m_CurrentFileEntries.GetNext(pos);
		if (next->m_sFileName == sFile) {
			next->m_bSynced = bSynced;
			return;
		}
	}
}

CFileEntry * CDir::GetFileEntry(CString sFileName, CObList *pList)
{
	// Try to find the entry with the given filename
	POSITION pos = pList->GetHeadPosition();
	while (pos) {
		CFileEntry * pEntry = (CFileEntry *)pList->GetNext(pos);
		if (pEntry->m_sFileName == sFileName) {
			// Found! Return the pointer...
			return pEntry;
		}
	}

	// Create a new entry if needed
	CFileEntry * pNew = new CFileEntry;
	pNew->m_sFileName = sFileName;
	pList->AddHead(pNew);
	
	return pNew;
}
