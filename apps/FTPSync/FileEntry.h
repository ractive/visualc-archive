// FileEntry.h: interface for the CFileEntry class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEENTRY_H__EDE735CD_EF6A_4BF6_A98A_5A5C3E8DF49B__INCLUDED_)
#define AFX_FILEENTRY_H__EDE735CD_EF6A_4BF6_A98A_5A5C3E8DF49B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFileEntry : public CObject
{
public:
	DECLARE_SERIAL(CFileEntry)

	void Serialize(CArchive &ar);

	CFileEntry();
	virtual ~CFileEntry();

	DWORD m_dwFileSize;
	FILETIME m_FileTime;
	CString m_sFileName; // relative to m_sDirectory
	BOOL m_bSynced;

};

#endif // !defined(AFX_FILEENTRY_H__EDE735CD_EF6A_4BF6_A98A_5A5C3E8DF49B__INCLUDED_)
