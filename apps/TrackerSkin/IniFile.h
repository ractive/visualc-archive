// IniFile.h: interface for the CIniFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INIFILE_H__5E196E7A_0675_49E7_BC91_C0813E3CEFD3__INCLUDED_)
#define AFX_INIFILE_H__5E196E7A_0675_49E7_BC91_C0813E3CEFD3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CIniFile : public CFile  
{
public:
	void WriteFile();
	BOOL ParseFile();
	CIniFile(const LPCTSTR sBaseDir, const LPCTSTR sFileName);
	virtual ~CIniFile();

protected:
	void DeleteValues();
	void ProcessLine(CString &sLine);
	CString m_sFileName;
	CString m_sBaseDir;
	CObList m_ValueList;
};

#endif // !defined(AFX_INIFILE_H__5E196E7A_0675_49E7_BC91_C0813E3CEFD3__INCLUDED_)
