// LocalDir.cpp: implementation of the CLocalDir class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FTPSync.h"
#include "LocalDir.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CLocalDir, CDir, 1)

CLocalDir::CLocalDir()
{

}

CLocalDir::~CLocalDir()
{

}

CFileFind * CLocalDir::GetFileFinder()
{
	return new CFileFind;
}


BOOL CLocalDir::FindFilesInDir(CFileFind *pFinder, CString sDir)
{
	TRACE("=== Local ====\r\n");

	if (!sDir.IsEmpty() && sDir.Right(1) != GetDelimiter()) {
		sDir += GetDelimiter();
	}

	return pFinder->FindFile(sDir + '*');
}

char CLocalDir::GetDelimiter()
{
	return '\\';
}
