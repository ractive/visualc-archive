// HostsFile.cpp: implementation of the CHostsFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NTMessenger.h"
#include "HostsFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHostsFile::CHostsFile()
{

}

CHostsFile::~CHostsFile()
{

}

BOOL CHostsFile::GetHostArray(CStringArray *pHostArray)
{
	FILE * pHostsFile = fopen("hosts", "r");
	if (!pHostsFile) {
		return FALSE;
	}

	// Read all lines until the end of file is reached
	while (!feof(pHostsFile)) {
		CString sHost;
		if (fgetws(sHost.GetBuffer(512), 512, pHostsFile)) {
			sHost.ReleaseBuffer();
			sHost.TrimLeft();
			sHost.TrimRight();
			if (sHost.Left(1) == "#") {
				// This is a comment;
				continue;
			}
			if (sHost.IsEmpty()) {
				// Don't add empty strings
				continue;
			}
			
			pHostArray->Add(sHost);
		}
		else {
			sHost.ReleaseBuffer();
		}
	}

	fclose(pHostsFile);

	return TRUE;
}

BOOL CHostsFile::AddHost(char* sHost)
{
	FILE * pHostsFile = fopen("hosts", "wa");
	
	if (!pHostsFile) {
		return FALSE;
	}

	BOOL bSuccess = TRUE;

	if (fputs(sHost, pHostsFile) == EOF) {
		bSuccess = FALSE;
	}

	fclose(pHostsFile);

	return bSuccess;
}
