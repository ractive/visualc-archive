// SyncPair.cpp: implementation of the CSyncPair class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FTPSync.h"
#include "SyncPair.h"
#include "FtpSession.h"
#include "FirstSyncDlg.h"
#include "ConflictDlg.h"

#ifdef _DEBUG
#include "FileEntry.h"

#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CSyncPair, CObject, 1)


CSyncPair::CSyncPair() {

}

CSyncPair::CSyncPair(CString sLocalDir, CString sServer, CString sFtpDir, CString sUserName, \
					 CString sPassword, UINT nPort, BOOL bIncludeSubDirs, BOOL bPassiveMode, \
					 BOOL bSyncFtp, BOOL bSyncLocal, \
					 BOOL bAskLocalOverwrite, BOOL bAskFtpOverwirte, 
					 BOOL bFirstSync /* = FALSE */)
{
	m_LocalDir.m_sDirectory = sLocalDir;
	m_FtpDir.m_sServer = sServer;
	m_FtpDir.m_sDirectory = sFtpDir;
	m_FtpDir.m_sUsername = sUserName;
	m_FtpDir.m_sPassword = sPassword;
	m_FtpDir.m_nPort = nPort;
	m_FtpDir.m_bPassiveMode = bPassiveMode;

	m_bIncludeSubDirs = bIncludeSubDirs;

	m_bFirstSync = bFirstSync;
}

CSyncPair::~CSyncPair()
{

}

BOOL CSyncPair::Sync(HWND hNotificationWnd, HANDLE hStop)
{	
	if (Exit(hStop)) {
		return TRUE;
	}

	HWND hWnd = AfxGetMainWnd()->m_hWnd;

	BOOL bAlwaysReplace = FALSE;

	UINT nRet = 0;

	if (m_bFirstSync) {
		CFirstSyncDlg dlg;
		nRet = dlg.DoModal();
		if (nRet == IDCANCEL) {
			return FALSE;
		}

	}

	BOOL bSuccess = FALSE;

	try {
		PostMessage(hNotificationWnd, WM_SYNCFILES, -1, -1);

		m_LocalDir.GetCurrentState(m_bIncludeSubDirs);
		m_FtpDir.GetCurrentState(m_bIncludeSubDirs);

#ifdef _DEBUG
		Debug();
#endif

		if (nRet == IDC_REPLACELOCAL) {
			// The local file entries are removed which
			// pretends the local directory is empty.
			// All FTP files are downloaded then
			m_LocalDir.RemoveCurrentFileEntries();
		}
		else if (nRet == IDC_REPLACEFTP) {
			// The FTP file entries are removed which
			// pretends the FTP directory is empty.
			// All local files are uploaded then
			m_FtpDir.RemoveCurrentFileEntries();
		}

		// Determine what files have to be up- and downloaded
		CStringArray saFileUpload;
		m_LocalDir.GetFileTransferList(saFileUpload, &m_FtpDir);

		CStringArray saFileDownload;
		m_FtpDir.GetFileTransferList(saFileDownload, &m_LocalDir);
		
		if (saFileDownload.GetSize() == m_FtpDir.m_CurrentFileEntries.GetCount() && saFileUpload.GetSize() == m_LocalDir.m_CurrentFileEntries.GetCount()) {
			//ASSERT(FALSE);
		}

		CheckConflicts(saFileUpload, saFileDownload);

#ifdef _DEBUG
		CString sSyncMsg;
		sSyncMsg.Format("Synchronising:\r\n\r\n%d Uploads, %d Downloads\r\n", saFileUpload.GetSize(), saFileDownload.GetSize());

		TRACE("==================\r\n" + sSyncMsg);
			
		//MessageBox(hWnd, sSyncMsg, "Synchronisation", MB_OK);
#endif
	
		PostMessage(hNotificationWnd, WM_SYNCFILES, saFileUpload.GetSize(), saFileDownload.GetSize());

		if (saFileUpload.GetSize() == 0 && saFileDownload.GetSize() == 0) {
			// Not much to do here :-)
			
			m_FtpDir.Done();
			return TRUE;
		}


		BOOL bUploaded = FALSE;
		BOOL bDownloaded = FALSE;

		int nFiles = saFileUpload.GetSize();
		for(int i = 0; m_Config.m_bSyncFtp && i < nFiles; i++) {
			if (Exit(hStop)) {
				break;
			}

			PostMessage(hNotificationWnd, WM_UPLOADFILE, i, (LPARAM)new CString(saFileUpload.GetAt(i)));

			CString sFile = m_LocalDir.m_sDirectory + "\\" + saFileUpload.GetAt(i);
			CString sFileName = sFile.Mid(sFile.ReverseFind('\\') + 1);
			
			BOOL bUp = TRUE;

			if (m_Config.m_bAskFtpOverwrite && m_FtpDir.FileExists(sFileName)) {
				CString sMsg = "WARNING! Do you want to overwrite the file\r\n\r\n" + sFileName + "\r\n\r\non the FTP server?";
				if (MessageBox(hWnd, sMsg, "File exists!", MB_YESNO | MB_ICONQUESTION) == IDNO) {
					// Don't upload the file
					bUp = FALSE;
				}
			}

			// Can we try to upload the file?
			if (bUp) {

				BOOL bSuccess = m_FtpDir.PutFile(sFile, sFileName);
				
				if (bSuccess) {
					TRACE(sFileName + " uploaded!!!\r\n");
					bUploaded = TRUE;
				}
				else {
					TRACE(sFileName + " NICHT uploaded!!! FEHLER IN PUT\r\n");
					DWORD dwError = GetLastError();
					CFtpSyncException get_error(CFtpSyncException::PUT, sFileName, dwError);

					MessageBox(hWnd, get_error.GetErrorMessage(), "Upload Error!", MB_OK | MB_ICONEXCLAMATION);
				}

				m_LocalDir.SetFileSyncStatus(sFileName, bSuccess);
			}
		}

		PostMessage(hNotificationWnd, WM_UPLOADDONE, 0, 0);

		nFiles = saFileDownload.GetSize();
		for(i = 0; m_Config.m_bSyncLocal && i < nFiles; i++) {
			if (Exit(hStop)) {
				break;
			}

			PostMessage(hNotificationWnd, WM_DOWNLOADFILE, i, (LPARAM)new CString(saFileDownload.GetAt(i)));

			CString sFileName = saFileDownload.GetAt(i);
			CString sFile = m_LocalDir.m_sDirectory + "\\" + sFileName;

			BOOL bDLOk = FALSE;

			// Check if the user wants to choose to overwrite local files or not
			if (m_Config.m_bAskLocalOverwrite) {
				bDLOk = m_FtpDir.GetFile(sFileName, sFile); // Gives an error 80 if the local file exists
			}
			else {
				bDLOk = m_FtpDir.GetFile(sFileName, sFile, FALSE); // Overwrites local files
			}

			DWORD dwError = GetLastError();
			if (!bDLOk) {
				if (dwError == 80) {
					// The file exists locally!
					if (m_Config.m_bAskLocalOverwrite) {
						CString sMsg = "WARNING! Do you want to overwrite the local file\r\n\r\n" + sFileName;
						if (MessageBox(hWnd, sMsg, "File exists!", MB_YESNO | MB_ICONQUESTION) == IDYES) {
							// Try again and replace the local file!
							bDLOk = m_FtpDir.GetFile(sFileName, sFile, FALSE);
						}
					}
				}
			}

			m_FtpDir.SetFileSyncStatus(sFileName, bDLOk);

			if (bDLOk) {
				TRACE(sFileName + " downloaded!!!\r\n");
				bDownloaded = TRUE;
			}
			else {
				CFtpSyncException get_error(CFtpSyncException::GET, sFileName, dwError);

				MessageBox(hWnd, get_error.GetErrorMessage(), "Download Error!", MB_OK | MB_ICONEXCLAMATION);
				TRACE(sFileName + " NICHT downloaded!!! FEHLER IN GET\r\n");
			}

		}

		PostMessage(hNotificationWnd, WM_DOWNLOADDONE, 0, 0);
		
		m_FtpDir.UpdateEntries(bUploaded);
		m_LocalDir.UpdateEntries(bDownloaded);



		m_FtpDir.Done();

		if (!Exit(hStop) && m_bFirstSync) {
			// If this was the first sync we up- or downloaded the whole dir
			// Now we sync if for the first time to complete the job
			m_bFirstSync = FALSE;
			Sync(hNotificationWnd, hStop);
			m_FtpDir.Done();
		}
		
		Debug();

		bSuccess = TRUE;

	}
	catch(CFtpSyncException * pFtpEx) {
		MessageBox(hWnd, pFtpEx->GetErrorMessage(), "FTP Error", MB_OK | MB_ICONEXCLAMATION);
		pFtpEx->Delete();
	}
	catch (CInternetException * pEx) {
		UINT nMaxError = 512;
		CString sError;
		LPTSTR pBuf = sError.GetBuffer(nMaxError);
		pEx->GetErrorMessage(pBuf, nMaxError);
		sError.ReleaseBuffer();
		MessageBox(hWnd, "Error while trying to contact " + GetFtpServer() + "\r\n\r\n" + sError, "Internet Error", MB_OK | MB_ICONEXCLAMATION);
		pEx->Delete();
	}
	
	//m_FtpDir.Done();
	
	return bSuccess;
}

void CSyncPair::Serialize(CArchive &ar)
{
	CObject::Serialize( ar );

	m_FtpDir.Serialize(ar);
	m_LocalDir.Serialize(ar);
	m_Config.Serialize(ar);

	if (ar.IsStoring()) {
		ar << m_bIncludeSubDirs;
		ar << m_bFirstSync;
	}
	else {
		ar >> m_bIncludeSubDirs;
		ar >> m_bFirstSync;
	}
}

CString CSyncPair::GetFtpServer()
{
	return m_FtpDir.m_sServer;
}

CString CSyncPair::GetFtpUsername()
{
	return m_FtpDir.m_sUsername;
}

CString CSyncPair::GetFtpPassword()
{
	return m_FtpDir.m_sPassword;
}

UINT CSyncPair::GetFtpPort()
{
	return m_FtpDir.m_nPort;
}

CString CSyncPair::GetFtpDirectory()
{
	return m_FtpDir.m_sDirectory;
}

BOOL CSyncPair::IsFtpPassiveMode()
{
	return m_FtpDir.m_bPassiveMode;
}

CString CSyncPair::GetLocalDir()
{
	return m_LocalDir.m_sDirectory;
}

void CSyncPair::SetFtpServer(CString s)
{
	m_FtpDir.m_sServer = s;
}

void CSyncPair::SetFtpUsername(CString s)
{
	m_FtpDir.m_sUsername = s;
}

void CSyncPair::SetFtpPassword(CString s)
{
	m_FtpDir.m_sPassword = s;
}

void CSyncPair::SetFtpPort(UINT nPort)
{
	m_FtpDir.m_nPort = nPort;
}

void CSyncPair::SetFtpDirectory(CString s)
{
	m_FtpDir.m_sDirectory = s;
}

void CSyncPair::SetLocalDir(CString s)
{
	m_LocalDir.m_sDirectory = s;
}

void CSyncPair::IsFtpPassiveMode(BOOL b)
{
	m_FtpDir.m_bPassiveMode = b;
}

void CSyncPair::CheckConflicts(CStringArray &saDown, CStringArray &saUp)
{
	// If a filename is in both lists, the files has been changed on both locations
	// Let the user decide which file to transfer
	int nDownFiles = saDown.GetSize();
	int nUpFiles = saUp.GetSize();

	for(int d = 0; d < nDownFiles; d++) {
		for(int u = 0; u < nUpFiles; u++) {
			if (saDown.GetAt(d) == saUp.GetAt(u)) {
				// This is a conflict!
				if (m_Config.m_bUpload && !m_Config.m_bAskIfConflict) {
					saDown.RemoveAt(d);
					d--; nDownFiles --;				
					break;
				}
				if (!m_Config.m_bUpload && !m_Config.m_bAskIfConflict) {
					saUp.RemoveAt(u);
					u--; nUpFiles--;
					break;
				}

				if (m_Config.m_bAskIfConflict) {
					CConflictDlg dlg;
					dlg.m_sFile = saDown.GetAt(d);
					int nRet = dlg.DoModal();
					if (nRet == IDCANCEL) {
						saDown.RemoveAt(d);
						d--; nDownFiles--;

						saUp.RemoveAt(u);
						u--; nUpFiles--;
						break;
					}
					else if (nRet == IDC_CONFLICTUPLOAD) {
						saDown.RemoveAt(d);
						d--; nDownFiles --;
						break;
					}
					else if (nRet == IDC_CONFLICTDOWNLOAD) {
						saUp.RemoveAt(u);
						u--; nUpFiles--;
						break;
					}
				}
			}
		}
	}
}

void CSyncPair::ThrowException(CFtpSyncException::ERRCODE dwFtpError, CString sAddInfo /* = "" */, DWORD dwLocalError /* = 0 */)
{
	CFtpSyncException * pEx = new CFtpSyncException(dwFtpError, sAddInfo, dwLocalError);

	throw pEx;
}

void CSyncPair::Debug()
{
#ifdef _DEBUG
	POSITION pos = m_FtpDir.m_CurrentFileEntries.GetHeadPosition();
	TRACE("\r\n\r\n=== FTP Current ===\r\n");
	while(pos) {
		CFileEntry * pEntry = (CFileEntry *)m_FtpDir.m_CurrentFileEntries.GetNext(pos);
		SYSTEMTIME st;
		char sTime[15];
		char sDateTime[31];
		sDateTime[0] = '\0';
		FileTimeToSystemTime(&pEntry->m_FileTime, &st);

		FILETIME flt;
		FileTimeToLocalFileTime(&pEntry->m_FileTime, &flt);
		FileTimeToSystemTime(&flt, &st);
		
		GetTimeFormat(LOCALE_SYSTEM_DEFAULT, TIME_FORCE24HOURFORMAT, &st, NULL, sTime, 15);
		strcat(sDateTime, sTime);
		TRACE("  %-20.20s %7s\r\n", pEntry->m_sFileName, sDateTime);
	}

	pos = m_FtpDir.m_OldFileEntries.GetHeadPosition();
	TRACE("=== Old ===\r\n");
	while(pos) {
		CFileEntry * pEntry = (CFileEntry *)m_FtpDir.m_CurrentFileEntries.GetNext(pos);
		SYSTEMTIME st;
		char sTime[15];
		char sDateTime[31];
		sDateTime[0] = '\0';
		FileTimeToSystemTime(&pEntry->m_FileTime, &st);

		FILETIME flt;
		FileTimeToLocalFileTime(&pEntry->m_FileTime, &flt);
		FileTimeToSystemTime(&flt, &st);
		
		GetTimeFormat(LOCALE_SYSTEM_DEFAULT, TIME_FORCE24HOURFORMAT, &st, NULL, sTime, 15);
		strcat(sDateTime, sTime);
		TRACE("  %-20.20s %7s\r\n", pEntry->m_sFileName, sDateTime);
	}

	pos = m_LocalDir.m_CurrentFileEntries.GetHeadPosition();
	TRACE("\r\n\r\n=== Local Current ===\r\n");
	while(pos) {
		CFileEntry * pEntry = (CFileEntry *)m_LocalDir.m_CurrentFileEntries.GetNext(pos);
		SYSTEMTIME st;
		char sTime[15];
		char sDateTime[31];
		sDateTime[0] = '\0';
		FileTimeToSystemTime(&pEntry->m_FileTime, &st);

		FILETIME flt;
		FileTimeToLocalFileTime(&pEntry->m_FileTime, &flt);
		FileTimeToSystemTime(&flt, &st);
		
		GetTimeFormat(LOCALE_SYSTEM_DEFAULT, TIME_FORCE24HOURFORMAT, &st, NULL, sTime, 15);
		strcat(sDateTime, sTime);
		TRACE("  %-20.20s %7s\r\n", pEntry->m_sFileName, sDateTime);
	}

	pos = m_LocalDir.m_OldFileEntries.GetHeadPosition();
	TRACE("=== Local Old ===\r\n");
	while(pos) {
		CFileEntry * pEntry = (CFileEntry *)m_LocalDir.m_CurrentFileEntries.GetNext(pos);
		SYSTEMTIME st;
		char sTime[15];
		char sDateTime[31];
		sDateTime[0] = '\0';
		FileTimeToSystemTime(&pEntry->m_FileTime, &st);

		FILETIME flt;
		FileTimeToLocalFileTime(&pEntry->m_FileTime, &flt);
		FileTimeToSystemTime(&flt, &st);
		
		GetTimeFormat(LOCALE_SYSTEM_DEFAULT, TIME_FORCE24HOURFORMAT, &st, NULL, sTime, 15);
		strcat(sDateTime, sTime);
		TRACE("  %-20.20s %7s\r\n", pEntry->m_sFileName, sDateTime);
	}

#endif

}

BOOL CSyncPair::Exit(HANDLE hStop)
{
	return WaitForSingleObject(hStop, 0) == WAIT_OBJECT_0;
}
