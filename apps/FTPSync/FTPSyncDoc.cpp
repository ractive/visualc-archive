// FTPSyncDoc.cpp : implementation of the CFTPSyncDoc class
//

#include "stdafx.h"
#include "FTPSync.h"
#include "AddDlg.h"
#include "SyncPair.h"
#include "FtpSyncException.h"
#include <imagehlp.h>

#include "FTPSyncDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFTPSyncDoc

IMPLEMENT_DYNCREATE(CFTPSyncDoc, CDocument)

BEGIN_MESSAGE_MAP(CFTPSyncDoc, CDocument)
	//{{AFX_MSG_MAP(CFTPSyncDoc)
	ON_COMMAND(ID_ADD, OnAdd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFTPSyncDoc construction/destruction

CFTPSyncDoc::CFTPSyncDoc()
{


}

CFTPSyncDoc::~CFTPSyncDoc()
{
	while(m_SyncPairs.GetCount()) {
		CSyncPair * p = (CSyncPair *)m_SyncPairs.RemoveHead();
		delete p;
	}

	m_SyncPairs.RemoveAll();

}

BOOL CFTPSyncDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;


	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFTPSyncDoc serialization

void CFTPSyncDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		m_SyncPairs.Serialize(ar);
	}
	else
	{
		m_SyncPairs.Serialize(ar);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFTPSyncDoc diagnostics

#ifdef _DEBUG
void CFTPSyncDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFTPSyncDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFTPSyncDoc commands

void CFTPSyncDoc::OnAdd() 
{
	CAddDlg dlg;

	if (dlg.DoModal() == IDCANCEL) {
		return;
	}

	CFileFind finder;
	BOOL bDirExists = finder.FindFile(dlg.m_sLocalFolder);
	finder.FindNextFile();

	bDirExists &= finder.IsDirectory();

	if (!bDirExists) {
		if (MessageBox(AfxGetMainWnd()->m_hWnd, "The local directory\r\n" + dlg.m_sLocalFolder + "\r\n does not exists!\r\n\r\nDo you want to create it?", "Directory does not exits", MB_YESNO | MB_ICONQUESTION) == IDYES) {
			CString sNew = dlg.m_sLocalFolder;
			if (sNew.Right(1) != "\\") {
				sNew += "\\";
			}
			if (!MakeSureDirectoryPathExists(sNew)) {
				return;
			}
		}
		else {
			return;
		}
	}
		


	CSyncPair * pNew = new CSyncPair(dlg.m_sLocalFolder, dlg.m_sFTPServer, dlg.m_sFTPDirectory,  dlg.m_sUsername, \
									 dlg.m_sPassword, dlg.m_nPort, dlg.m_bIncludeSubDirs, dlg.m_bPassiveMode, \
									 dlg.m_bSyncFtp, dlg.m_bSyncLocal, \
									 dlg.m_bAskLocalOverwrite, dlg.m_bAskFtpOverwrite,  \
									 TRUE);

	m_SyncPairs.AddHead(pNew);
		
	SetModifiedFlag(TRUE);

	UpdateAllViews(NULL);
}



POSITION CFTPSyncDoc::GetFirstPair()
{
	return m_SyncPairs.GetHeadPosition();
}

void CFTPSyncDoc::GetNextPair(POSITION &pos, CString &sLocalDir, CString &sFtp, UINT &nPort, UINT &nData)
{
	CSyncPair *next = (CSyncPair *)m_SyncPairs.GetNext(pos);
	sLocalDir = next->GetLocalDir();
	sFtp = "ftp://" + next->GetFtpServer();
	sFtp += "/" + next->GetFtpDirectory();
	nPort = next->GetFtpPort();
	nData = (UINT)(void *)next;
}

void CFTPSyncDoc::Sync(UINT nData, HWND hNotificationWnd, HANDLE hStop)
{
	POSITION pos = NULL;

	CSyncPair * pSyncPair = GetPtrFromData(nData, pos);
	
	if (!pSyncPair) {
		return;
	}
	try {
		PostMessage(hNotificationWnd, WM_STARTSYNC, (WPARAM)new CString(pSyncPair->GetFtpServer()), 0);
		if (!pSyncPair->Sync(hNotificationWnd, hStop)) {
			// FEHLER	
		}
	}
	catch (CFtpSyncException * pEx) {
		pEx->Delete();
	}
	catch (CInternetException * pInetEx) {
		pInetEx->Delete();
	}

}

BOOL CFTPSyncDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	
	return TRUE;
}


BOOL CFTPSyncDoc::CanCloseFrame(CFrameWnd* pFrame) 
{
	// Save the data always!
	
	Save();

	return TRUE;

	//return CDocument::CanCloseFrame(pFrame);
}

BOOL CFTPSyncDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDocument::OnSaveDocument(lpszPathName);
}


void CFTPSyncDoc::DelPair(UINT nData)
{
	POSITION pos = NULL;

	CSyncPair * pSyncPair = GetPtrFromData(nData, pos);
	if (!pSyncPair) {
		return;
	}

	delete pSyncPair;

	m_SyncPairs.RemoveAt(pos);

	SetModifiedFlag(TRUE);

	UpdateAllViews(NULL);
}

CSyncPair * CFTPSyncDoc::GetPtrFromData(UINT nData, POSITION &pos)
{
	pos = NULL;

	// First check if the pointer exists
	if ((pos = m_SyncPairs.Find((CSyncPair *)nData)) == NULL) {
		// The object is not in the list...
		ASSERT(FALSE);
		return NULL;
	}

	CSyncPair * pSyncPair = (CSyncPair *)m_SyncPairs.GetAt(pos);

	return pSyncPair;
}

void CFTPSyncDoc::EditPair(UINT nData)
{
	POSITION pos = NULL;

	CSyncPair * pSyncPair = GetPtrFromData(nData, pos);
	if (!pSyncPair) {
		return;
	}

	CAddDlg dlg;

	CFileFind finder;
	BOOL bDirExists = finder.FindFile(dlg.m_sLocalFolder);
	finder.FindNextFile();

	bDirExists &= finder.IsDirectory();

	if (!bDirExists) {
		if (MessageBox(AfxGetMainWnd()->m_hWnd, "The local directory\r\n" + dlg.m_sLocalFolder + "\r\n does not exists!\r\n\r\nDo you want to create it?", "Directory does not exits", MB_YESNO | MB_ICONQUESTION) == IDYES) {
			CString sNew = dlg.m_sLocalFolder;
			if (sNew.Right(1) != "\\") {
				sNew += "\\";
			}
			if (!MakeSureDirectoryPathExists(sNew)) {
				return;
			}
		}
		else {
			return;
		}
	}


	dlg.m_bIncludeSubDirs		= pSyncPair->m_bIncludeSubDirs;
	dlg.m_bPassiveMode			= pSyncPair->IsFtpPassiveMode();
	dlg.m_sFTPDirectory			= pSyncPair->GetFtpDirectory();
	dlg.m_sFTPServer			= pSyncPair->GetFtpServer();
	dlg.m_sPassword				= pSyncPair->GetFtpPassword();
	dlg.m_sUsername				= pSyncPair->GetFtpUsername();
	dlg.m_nPort					= pSyncPair->GetFtpPort();
	dlg.m_sLocalFolder			= pSyncPair->GetLocalDir();
								
	dlg.m_bAskFtpOverwrite		= pSyncPair->m_Config.m_bAskFtpOverwrite;
	dlg.m_bAskIfConflict		= pSyncPair->m_Config.m_bAskIfConflict;
	dlg.m_bAskLocalOverwrite	= pSyncPair->m_Config.m_bAskLocalOverwrite;
	dlg.m_bSyncFtp				= pSyncPair->m_Config.m_bSyncFtp;
	dlg.m_bSyncLocal			= pSyncPair->m_Config.m_bSyncLocal;
	dlg.m_bUpload				= pSyncPair->m_Config.m_bUpload;

	if (dlg.DoModal() == IDCANCEL) {
		return;
	}

	pSyncPair->m_bIncludeSubDirs = dlg.m_bIncludeSubDirs;
	pSyncPair->IsFtpPassiveMode(dlg.m_bPassiveMode);
	pSyncPair->SetFtpDirectory(dlg.m_sFTPDirectory);
	pSyncPair->SetFtpServer(dlg.m_sFTPServer);
	pSyncPair->SetFtpPassword(dlg.m_sPassword);
	pSyncPair->SetFtpUsername(dlg.m_sUsername);
	pSyncPair->SetFtpPort(dlg.m_nPort);
	pSyncPair->SetLocalDir(dlg.m_sLocalFolder);

	pSyncPair->m_Config.m_bAskFtpOverwrite	= dlg.m_bAskFtpOverwrite;
	pSyncPair->m_Config.m_bAskIfConflict	= dlg.m_bAskIfConflict;
	pSyncPair->m_Config.m_bAskLocalOverwrite= dlg.m_bAskLocalOverwrite;
	pSyncPair->m_Config.m_bSyncFtp			= dlg.m_bSyncFtp;
	pSyncPair->m_Config.m_bSyncLocal		= dlg.m_bSyncLocal;
	pSyncPair->m_Config.m_bUpload			= dlg.m_bUpload;


	SetModifiedFlag(TRUE);

	UpdateAllViews(NULL);
}

void CFTPSyncDoc::Save()
{
	DoSave(m_strPathName, TRUE);
}

void CFTPSyncDoc::Load()
{
	OnOpenDocument(m_strPathName);
}
