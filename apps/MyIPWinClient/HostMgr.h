// HostMgr.h: interface for the CHostMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HOSTMGR_H__C175A91F_0CF1_4CB6_B8D1_FC9A5C0F76F9__INCLUDED_)
#define AFX_HOSTMGR_H__C175A91F_0CF1_4CB6_B8D1_FC9A5C0F76F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMyIPWinClientDlg;

struct hostEntry {
	CString sHostName;
	CString sIP;
	CString sRecordType;
};

class CHostMgr  
{

public:
	void SetHost(const CString &sHost, const CString &sIP, const CString &sRecordType);
	hostEntry * GetHostEntry(int nIndex);
	BOOL AddNewHost(const CString &sHost);
	CString GetHost(int nIndex);
	int GetSize();
	BOOL Import();
	BOOL UpdateHost(CString &sHost, CString &sIP, CString &sRecordType);
	BOOL DeleteHost(CString &sHost);
	BOOL AddHost(CString &sHost, CString * psIP = NULL, CString * psRecordType = NULL);
	void Init(CString * psUsername, CString * psPassword, CMyIPWinClientDlg * pParent, BOOL* pbWarn);
	CHostMgr();
	virtual ~CHostMgr();
	void DeleteAll();
private:
	hostEntry * GetHostEntry(const CString &sHost, LPDWORD pdwIndex = NULL);
	CString* m_psUsername;
	CString* m_psPassword;
	BOOL* m_pbWarn;
	CPtrArray paHosts;
	CMyIPWinClientDlg * m_pParent;

};

#endif // !defined(AFX_HOSTMGR_H__C175A91F_0CF1_4CB6_B8D1_FC9A5C0F76F9__INCLUDED_)
