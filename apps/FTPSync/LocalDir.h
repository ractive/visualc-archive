// LocalDir.h: interface for the CLocalDir class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOCALDIR_H__23379DDC_D959_43BB_9D0C_D7FBD7BBB8AF__INCLUDED_)
#define AFX_LOCALDIR_H__23379DDC_D959_43BB_9D0C_D7FBD7BBB8AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Dir.h"

class CLocalDir : public CDir
{
public:
	virtual char GetDelimiter();
	DECLARE_SERIAL(CLocalDir)

	CLocalDir();
	virtual ~CLocalDir();
	FindFilesInDir(CFileFind *pFinder, CString sDir);

protected:

	virtual CFileFind *  GetFileFinder();
};

#endif // !defined(AFX_LOCALDIR_H__23379DDC_D959_43BB_9D0C_D7FBD7BBB8AF__INCLUDED_)
