// Config.cpp: implementation of the CConfig class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FTPSync.h"
#include "Config.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CConfig, CObject, 1)

CConfig::CConfig()
{
	m_bAskFtpOverwrite = TRUE;;
	m_bAskIfConflict = TRUE;
	m_bAskLocalOverwrite = TRUE;;
	m_bSyncFtp = TRUE;;
	m_bSyncLocal = TRUE;;
	m_bUpload = TRUE;
}

CConfig::~CConfig()
{

}

void CConfig::Serialize(CArchive &ar)
{
	if (ar.IsStoring()) {
		ar << m_bAskFtpOverwrite;
		ar << m_bAskIfConflict;
		ar << m_bAskLocalOverwrite;
		ar << m_bSyncFtp;
		ar << m_bSyncLocal;
		ar << m_bUpload;
	}
	else {
		ar >> m_bAskFtpOverwrite;
		ar >> m_bAskIfConflict;
		ar >> m_bAskLocalOverwrite;
		ar >> m_bSyncFtp;
		ar >> m_bSyncLocal;
		ar >> m_bUpload;
	}
}