// HostMgr.cpp: implementation of the CHostMgr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "myipwinclient.h"
#include "HostMgr.h"
#include "MyIPHelper.h"
#include "MyIPWinClientDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHostMgr::CHostMgr()
{
	m_psUsername = NULL;
	m_psPassword = NULL;
}

CHostMgr::~CHostMgr()
{
	DeleteAll();
}

BOOL CHostMgr::AddHost(CString &sHost, CString * psIP /* = NULL */, CString * psRecordType /* = NULL */)
{
	ASSERT(m_psUsername != NULL && m_psPassword != NULL);

	// Add the host to our ptrArray

	hostEntry * entry = new hostEntry;

	entry->sHostName = sHost;
	entry->sRecordType = *psRecordType;
	entry->sIP = *psIP;

	paHosts.Add(entry);
	return TRUE;
}

BOOL CHostMgr::AddNewHost(const CString &sHost)
{
	ASSERT(m_psUsername != NULL && m_psPassword != NULL);

	CMyIPHelper * pMyIPHelper = CMyIPHelper::Instance();
	// Try to add the host to www.myip.org
	if (!pMyIPHelper->AddHost(*m_psUsername, *m_psPassword, sHost)) {
		return FALSE;
	}

	// If successful, add it also to the registry and to our ptrArray...
	CMyIPWinClientApp * pApp = (CMyIPWinClientApp *)AfxGetApp();
	pApp->AddHost(sHost);

	// ...and to our ptrArray
	hostEntry * entry = new hostEntry;

	entry->sHostName = sHost + _T(".myip.org");
	entry->sRecordType = "";
	entry->sIP = "";

	paHosts.Add(entry);

	return TRUE;
	
}


BOOL CHostMgr::DeleteHost(CString &sHost)
{
	hostEntry * entry = GetHostEntry(sHost);
	if (entry != NULL) {
		CMyIPHelper * pMyIPHelper = CMyIPHelper::Instance();
		
		// Try to delete the host on www.myip.org
		if (pMyIPHelper->DelHost(*m_psUsername, *m_psPassword, sHost)) {
			// if it was successful we also delete it from the registry...
			CMyIPWinClientApp * pApp = (CMyIPWinClientApp *)AfxGetApp();
			pApp->DelHost(sHost);

			//  ...and from our ptrArray
			DWORD dwIndex;
			hostEntry * entry = GetHostEntry(sHost, &dwIndex);
			delete entry;
			paHosts.RemoveAt(dwIndex);
			return TRUE;
		}
	}

	return FALSE;
}

void CHostMgr::Init(CString *psUsername, CString *psPassword, CMyIPWinClientDlg * pParent, BOOL* pbWarn)
{
	m_psUsername = psUsername;
	m_psPassword = psPassword;
	m_pParent = pParent;
	m_pbWarn = pbWarn;

	CMyIPWinClientApp * pApp = (CMyIPWinClientApp *)AfxGetApp();
	CString sHost, sIP, sRecordType;
	int nIndex = 0;
	while (pApp->EnumHosts(sHost, nIndex++, &sIP, &sRecordType)) {
		AddHost(sHost, &sIP, &sRecordType);
	}
}


hostEntry * CHostMgr::GetHostEntry(const CString &sHost, LPDWORD pdwIndex /* = NULL */)
{
	// Loop through all the entries until we find the hostname
	for (int i = 0; i < paHosts.GetSize(); i++) {
		hostEntry * entry = (hostEntry *)paHosts.GetAt(i);
		// When we find the host, we return the entry
		if (entry->sHostName == sHost) {
			if (pdwIndex != NULL) {
				*pdwIndex = i;
			}
			return entry;
		}
	}

	return NULL;
}

BOOL CHostMgr::UpdateHost(CString &sHost, CString &sIP, CString &sRecordType)
{
	CMyIPHelper * pMyIPHelper = CMyIPHelper::Instance();
	if (!pMyIPHelper->UpdateAccount(*m_psUsername, *m_psPassword, sHost, sIP, sRecordType, *m_pbWarn)) {
		return FALSE;
	}

	// The host could be updated on www.myip.org
	// Now we update our records (if it was not host "all")
	if (sHost != "all") {
		CMyIPWinClientApp * pApp = (CMyIPWinClientApp *)AfxGetApp();
		pApp->AddHost(sHost, &sIP, &sRecordType);
	}
	return TRUE;
}

BOOL CHostMgr::Import()
{
	CMyIPHelper * pMyIPHelper = CMyIPHelper::Instance();
	CStringArray saHosts, saIPs, saRecordType;
	// Try to import the setting from www.myip.org
	if (!pMyIPHelper->GetHosts(m_pParent->m_sUsername, m_pParent->m_sPassword, &saHosts, &saIPs, &saRecordType)) {
		return FALSE;
	}

	CMyIPWinClientApp * pApp = (CMyIPWinClientApp *)AfxGetApp();

	// The import was successful

	// Now we rebuild the registry and our records
	// First we delete all hosts
	pApp->DelAllHosts();
	DeleteAll();
	for(int i = 0; i < saHosts.GetSize(); i++) {
		// Add the host to our records...
		AddHost(saHosts.GetAt(i), &saIPs.GetAt(i), &saRecordType.GetAt(i));
		// ...and add it to the registry
		pApp->AddHost(saHosts.GetAt(i), &saIPs.GetAt(i), &saRecordType.GetAt(i));
	}
	
	return TRUE;

}

int CHostMgr::GetSize()
{
	return paHosts.GetSize();
}

CString CHostMgr::GetHost(int nIndex)
{
	ASSERT(nIndex < paHosts.GetSize());
	hostEntry * entry = (hostEntry *)paHosts.GetAt(nIndex);
	return entry->sHostName;
}


hostEntry * CHostMgr::GetHostEntry(int nIndex)
{
	ASSERT(nIndex < paHosts.GetSize());
	return (hostEntry *)paHosts.GetAt(nIndex);
}

void CHostMgr::SetHost(const CString &sHost, const CString &sIP, const CString &sRecordType)
{
	hostEntry * entry = (hostEntry *)GetHostEntry(sHost, NULL);
	entry->sIP = sIP;
	entry->sRecordType = sRecordType;

	CMyIPWinClientApp * pApp = (CMyIPWinClientApp *)AfxGetApp();
	pApp->AddHost(sHost, &sIP, &sRecordType);
}

void CHostMgr::DeleteAll()
{
	for (int i = 0; i < paHosts.GetSize(); i++) {
		hostEntry * entry = (hostEntry *)paHosts.GetAt(i);
		delete entry;
	}

	paHosts.RemoveAll();

}
