// HostsFile.h: interface for the CHostsFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HOSTSFILE_H__8A4995A6_B7C5_4EDC_BD99_4E9F98CF6924__INCLUDED_)
#define AFX_HOSTSFILE_H__8A4995A6_B7C5_4EDC_BD99_4E9F98CF6924__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CHostsFile  
{
public:
	BOOL AddHost(char* sHost);
	BOOL GetHostArray(CStringArray * pHostArray);
	CHostsFile();
	virtual ~CHostsFile();

};

#endif // !defined(AFX_HOSTSFILE_H__8A4995A6_B7C5_4EDC_BD99_4E9F98CF6924__INCLUDED_)
