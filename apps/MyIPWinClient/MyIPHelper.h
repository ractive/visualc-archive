/*************************************************************************
                     MyIPWinClient
**************************************************************************

Copyright (C) April, 2000 Jean-Pierre Bergamin, james@ractive.ch

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
***************************************************************************/

// MyIPHelper.h: interface for the CMyIPHelper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYIPHELPER_H__8ED93064_6CCA_45E2_ADE7_3B494A437837__INCLUDED_)
#define AFX_MYIPHELPER_H__8ED93064_6CCA_45E2_ADE7_3B494A437837__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "InternetHelper.h"
#include "MyIPException.h"

class CMyIPHelper : public CInternetHelper  
{
public:
	BOOL DeleteAccount(CString &sUser, CString &sPassword);
	BOOL ChangePwd(CString &sUsername, CString &sPassword, CString &sNewPwd);
	void StripTags(CString &sHTML);
	BOOL GetHosts(CString &sUsername, CString &sPassword, CStringArray * psaHosts, CStringArray *psaIPs, CStringArray *psaType);
	BOOL SendRequest(CString &sUrl);
	BOOL DelHost(CString &sUsername, CString &sPassword, CString &sDelHost);
	BOOL AddHost(const CString &sUsername, const CString &sPassword, const CString &sHostname);
	BOOL CreateUser(CString &sUsername, CString &sPassword, CString &sEmail);
	void URLPointsTo(CString& sUsername);
	static CMyIPHelper * Instance();
	BOOL UpdateAccount(CString &sUsername, CString &sPassword, CString sHost = "all", CString sIP = "", CString sRecordType = "", BOOL bWarn = TRUE, BOOL bOffline = FALSE);
	BOOL m_bUsePort18080;
	BOOL IsAccountAvailable(CString &sUsername);
	CMyIPHelper();
	virtual ~CMyIPHelper();
	BOOL SendPassword(CString& sUsername);

protected:
private:
	void ExceptionHandler(CException * pEx);
	void ExceptionHandler(CMyIPException * pEx);
	void ParseReply(CString &sBuf);
	void ThrowException(CMyIPException::ErrorCode errorCode);
	BOOL m_bWarn;
};

#endif // !defined(AFX_MYIPHELPER_H__8ED93064_6CCA_45E2_ADE7_3B494A437837__INCLUDED_)
