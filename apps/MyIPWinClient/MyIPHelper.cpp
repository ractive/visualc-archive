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

// MyIPHelper.cpp: implementation of the CMyIPHelper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyIPWinClient.h"
#include "MyIPHelper.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyIPHelper::CMyIPHelper()
{
	m_bUsePort18080 = FALSE;
}

CMyIPHelper::~CMyIPHelper()
{

}

BOOL CMyIPHelper::IsAccountAvailable(CString &sUsername)
{
	if (sUsername.IsEmpty()) {
		return FALSE;
	}
	
	CString sUrl = "http://www.myip.org";
	if (m_bUsePort18080) {
		sUrl += ":18080";
	}
	sUrl += "/cgi-bin/whois?login=" + sUsername + "&domain=myip.org";

	return SendRequest(sUrl);
}

BOOL CMyIPHelper::UpdateAccount(CString &sUsername, CString &sPassword, CString sHost /* = "all" */, CString sIP /* = "" */, CString sRecordType /* = "" */, BOOL bWarn /* = TRUE */, BOOL bOffline /* = FALSE */)
{
	// Check if the password and the username was entered.
	if (sPassword.IsEmpty() || sUsername.IsEmpty()) {
		AfxMessageBox("Please enter a username and a password!", MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	// Here we build the URL which will be used to update the account.
	// 
	// The whole work just for this string :-)

	CString sUrl = "http://www.myip.org";

	sUrl += "/cgi-bin/update.py?id=" + sUsername + "&pwd=" + sPassword;

	if (!sIP.IsEmpty() && sIP != "unknown") {
		sUrl += "&ip=" + sIP;
	}

	if (!sRecordType.IsEmpty() && sRecordType != "A") {
		sUrl += "&recordtype=" + sRecordType;
	}
	
	// Add the hostname that should be updated. If nothing is set, all hosts are updated.
	if (sHost != "all") {
		sUrl += "&hostname=" + sHost;
	}

	m_bWarn = bWarn;

	return SendRequest(sUrl);
}

CMyIPHelper * CMyIPHelper::Instance()
{
	return (CMyIPHelper *)CInternetHelper::Instance();
}

void CMyIPHelper::URLPointsTo(CString &sUsername)
{
	CString sURL = "http://www.myip.org/cgi-bin/showip?login=";
	sURL += sUsername;
	sURL += "&domain=myip.org";

	CString sBuf;
	ReadURL(sURL, sBuf);

	// We search for the IP-Address
	char find[] = "subdomain is pointing to:";
	int pos;
	if ((pos = sBuf.Find(find)) != -1 ) {
		// We found it.
		// Extract the IP form the HTML code.
		CString sIP = sBuf.Mid(pos + sizeof(find) + 3, 15);

		// Now cut everything from the right side which is not a number.
		sIP.TrimRight();
		char ch;
		int n = -1;
		ch = sIP.Right(1)[0];
		n = ch - '0';
		
		while (!(n >= 0 && n < 9)) {
			sIP = sIP.Left(sIP.GetLength() - 1);
			ch = sIP.Right(1)[0];
			n = ch - '0';
		}

		// Display a simple message box.
		CString sMsg = "The URL " + sUsername + ".myip.org points currently to " + sIP;
		MessageBox(NULL, sMsg, "Info", MB_OK | MB_ICONINFORMATION);
	}
}

BOOL CMyIPHelper::SendPassword(CString &sUsername)
{
	BOOL bRet = FALSE;

	CString sUrl = "http://www.myip.org";
	if (m_bUsePort18080) {
		sUrl += ":18080";
	}
	sUrl += "/cgi-bin/mailpassword?login=" + sUsername + "&domain=myip.org";

	return SendRequest(sUrl);
}

void CMyIPHelper::ThrowException(CMyIPException::ErrorCode errorCode)
{
	CMyIPException* pEx = new CMyIPException(errorCode);
	throw pEx;
}

BOOL CMyIPHelper::CreateUser(CString &sUsername, CString &sPassword, CString &sEmail)
{
	if (sPassword.IsEmpty() || sUsername.IsEmpty()) {
		AfxMessageBox("Please enter a username and a password!", MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}
	
	// Here we build the URL which will be used to create the account.

	CString sUrl = "http://www.myip.org";

	sUrl += "/cgi-bin/AddUser.py?id=" + sUsername + "&pwd=" + sPassword +"&email=" + sEmail;

	return SendRequest(sUrl);
}

BOOL CMyIPHelper::DeleteAccount(CString &sUser, CString &sPassword)
{
	if (sPassword.IsEmpty() || sUser.IsEmpty()) {
		AfxMessageBox("Please enter a username and a password!", MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}
	
	// Here we build the URL which will be used to create the account.

	CString sUrl = "http://www.myip.org";

	sUrl += "/cgi-bin/DelUser.py?id=" + sUser + "&pwd=" + sPassword;

	return SendRequest(sUrl);
}


BOOL CMyIPHelper::AddHost(const CString &sUsername, const CString &sPassword, const CString &sHostname)
{
	if (sPassword.IsEmpty() || sUsername.IsEmpty() || sHostname.IsEmpty()) {
		AfxMessageBox("Please enter a username and a password!", MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}
	
	// Here we build the URL which will be used to add a new host

	CString sUrl = "http://www.myip.org";

	sUrl += "/cgi-bin/AddHost.py?id=" + sUsername + "&pwd=" + sPassword  +"&host=" + sHostname + "&domain=myip.org";

	return SendRequest(sUrl);
}

BOOL CMyIPHelper::DelHost(CString &sUsername, CString &sPassword, CString &sDelHost)
{
	if (sPassword.IsEmpty() || sUsername.IsEmpty() || sDelHost.IsEmpty()) {
		AfxMessageBox("Please enter a username and a password!", MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}
	
	// Here we build the URL which will be used to create the account.

	CString sUrl = "http://www.myip.org";

	sUrl += "/cgi-bin/DelHost.py?id=" + sUsername + "&pwd=" + sPassword  +"&hostname=" + sDelHost;

	return SendRequest(sUrl);
}

void CMyIPHelper::ParseReply(CString &sBuf)
{
	// We search for the return "code"
	char find[] = "<title>";
	int pos;
	if ((pos = sBuf.Find(find)) != -1 ) {
		// We at least found something that could be correct
		pos += strlen(find);
		// Extract the returned code
		int pos2 = sBuf.Find("</title>", pos);
		CString sCode = sBuf.Mid(pos, pos2 - pos);
		sCode.TrimRight();
		CString sErrorMsg;
		// Let's see what we got...
		if (sCode == "Success") {
			// Great, it seems it worked.
			return;
		}
		else {
			// :-( There went something wrong. 
			CMyIPException::ErrorCode errCode;
			if (sCode == "Bad Password") {
				errCode = CMyIPException::BADPWD;
			}
			else if (sCode == "No Change") {
				errCode = CMyIPException::NOCHANGE;
			}
			else if (sCode == "User Not Found") {
				errCode = CMyIPException::BADUSER;
			}
			else if (sCode == "BADIP") {
				errCode = CMyIPException::BADIP;
			}
			else if (sCode == "BADEMAIL") {
				errCode = CMyIPException::BADEMAIL;
			}
			else if (sCode == "Hostname not found") {
				errCode = CMyIPException::BADHOSTNAME;
			}
			else if (sCode == "BAD1MX") {
				errCode = CMyIPException::BAD1MX;
			}
			else if (sCode.Left(6) == "SYSERR") {
				errCode = CMyIPException::SYSERR;
			}
			else if (sCode == "Illegal Character") {
				errCode = CMyIPException::INVPWD;
			}
			else if (sCode == "INVDOMAIN") {
				errCode = CMyIPException::INVDOMAIN;
			}
			else
				errCode = CMyIPException::UNKNOWN;
			// Throw the exception
			ThrowException(errCode);
		}
	}
	else {
		ThrowException(CMyIPException::PARSEFILE);
	}
}

BOOL CMyIPHelper::SendRequest(CString &sUrl)
{
	CWaitCursor wait;

	BOOL bRet = FALSE;

	CString sBuf;
	try {
		ReadURL(sUrl, sBuf);
		ParseReply(sBuf);
		// If we did not get an exception, the request was successful
		bRet = TRUE;
	}
	catch (CMyIPException * pEx) {
		int nError = pEx->m_ErrorCode;
		ExceptionHandler(pEx);
		if (m_bWarn && nError == CMyIPException::NOCHANGE) {
			if (MessageBox(NULL, _T("Do you want to force an update?\r\n\r\n(Normally it's not necessary)"), _T("No Change"), MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES) {
				return SendRequest(sUrl + _T("&force=1"));
			}
			else {
				// When the settings were the same and we don't force an update, it's also a succes
				return TRUE;
			}
		}
		else {
			return TRUE;
		}
		
	}
	catch (CException * pEx) {
		ExceptionHandler(pEx);
	}

	return bRet;
}

BOOL CMyIPHelper::GetHosts(CString &sUsername, CString &sPassword, CStringArray *psaHosts, CStringArray *psaIPs, CStringArray *psaType)
{
	CWaitCursor wait;

	// Check if the password and the username was entered.
	if (sPassword.IsEmpty() || sUsername.IsEmpty()) {
		AfxMessageBox("Please enter a username and a password!", MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}
	
	CString sUrl = "http://www.myip.org";

	sUrl += "/cgi-bin/Login.py?id=" + sUsername + "&pwd=" + sPassword;
	
	// Add the hostname that should be updated. If nothing is set, all hosts are updated.

	CString sBuf;
	ReadURL(sUrl, sBuf);

	char find[] = "<table>";
	int pos;
	if ((pos = sBuf.Find(find)) != -1 ) {
		// We at least found something that could be correct
		pos += strlen(find);
		// Extract the data between the table tags
		int pos2 = sBuf.Find("</table>", pos);
		CString sHosts = sBuf.Mid(pos, pos2 - pos);
		sHosts.TrimLeft();
		sHosts.TrimRight();
		sHosts += "\n";
		pos = pos2 = 0;
		while(!sHosts.IsEmpty()) {
			int nPos = sHosts.Find("</tr>", 1);
			if (nPos == -1)
				nPos = sHosts.GetLength();
			CString sLine = sHosts.Left(nPos);
			StripTags(sLine);
			sLine.TrimLeft();
			sLine.TrimRight();
			if (sLine.IsEmpty()) {
				break;
			}
			// Now we have the record entry in the form
			// Hostname space IP space Recordtype
			CString sHost, sIP, sType;
			sscanf(sLine, "%s %s %s", sHost.GetBuffer(64), sIP.GetBuffer(64), sType.GetBuffer(64));
			sHost.ReleaseBuffer();
			sIP.ReleaseBuffer();
			sType.ReleaseBuffer();
			if (sHost != "Hostname" && sIP != "IP") {
				psaHosts->Add(sHost);
				psaIPs->Add(sIP);
				psaType->Add(sType);
			}
			nPos = sHosts.Find("</tr>") + 5;
			sHosts = sHosts.Mid(nPos);
		}
		
	}
	else {
		ThrowException(CMyIPException::PARSEFILE);
	}

	return TRUE;
}

void CMyIPHelper::StripTags(CString &sHTML)
{
	int nPos = -1;
	while((nPos = sHTML.Find('<')) != -1) {
		int nPos2 = sHTML.Find('>', nPos);
		sHTML.Delete(nPos, nPos2 - nPos + 1);
		sHTML.Insert(nPos, ' ');
	}
}

BOOL CMyIPHelper::ChangePwd(CString &sUsername, CString &sPassword, CString &sNewPwd)
{
	if (sPassword.IsEmpty() || sUsername.IsEmpty() || sNewPwd.IsEmpty()) {
		AfxMessageBox("Please enter a username and a password!", MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}
	
	// Here we build the URL which will be used to create the account.

	CString sUrl = "http://www.myip.org";

	sUrl += "/cgi-bin/PWD.py?id=" + sUsername + "&pwd=" + sPassword  +"&n_pwd=" + sNewPwd + "&n_pwd2=" + sNewPwd;

	return SendRequest(sUrl);
}

void CMyIPHelper::ExceptionHandler(CMyIPException *pEx)
{
	if (!(pEx->m_ErrorCode == CMyIPException::NOCHANGE && !m_bWarn)) {
		TCHAR sErrorMsg[1024];
		pEx->GetErrorMessage(sErrorMsg, 1024);
		MessageBox(NULL, sErrorMsg, "Error", MB_OK | MB_ICONEXCLAMATION | MB_SETFOREGROUND);
	}
	pEx->Delete();
}

void CMyIPHelper::ExceptionHandler(CException *pEx)
{
	TCHAR sErrorMsg[1024];
	pEx->GetErrorMessage(sErrorMsg, 1024);
	CString sMsg = "An error occured! Please see the specified error message:\n\n";
	sMsg += sErrorMsg;
	MessageBox(NULL, sMsg, "Error", MB_OK | MB_ICONEXCLAMATION | MB_SETFOREGROUND);
	pEx->Delete();
}
