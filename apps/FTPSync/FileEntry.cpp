// FileEntry.cpp: implementation of the CFileEntry class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FTPSync.h"
#include "FileEntry.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CFileEntry, CObject, 1)

CFileEntry::CFileEntry()
{

}

CFileEntry::~CFileEntry()
{

}

void CFileEntry::Serialize(CArchive &ar)
{
	CObject::Serialize( ar );
	
	if (ar.IsStoring()) {
		ar << m_dwFileSize;
		ar << m_FileTime.dwHighDateTime;
		ar << m_FileTime.dwLowDateTime;
		ar << m_sFileName;
	}
	else {
		ar >> m_dwFileSize;
		ar >> m_FileTime.dwHighDateTime;
		ar >> m_FileTime.dwLowDateTime;
		ar >> m_sFileName;
	}
}
