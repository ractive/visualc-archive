// MyIPException.cpp: implementation of the CMyIPException class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "myipwinclient.h"
#include "MyIPException.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyIPException::CMyIPException(ErrorCode errCode)
{
	m_ErrorCode = errCode;
}

CMyIPException::~CMyIPException()
{

}

void CMyIPException::GetErrorMessage(char *sErrorMsg, int nMaxLen)
{
	switch (m_ErrorCode) {
	case BADPWD:
		memcpy(sErrorMsg, "The password is not correct!", nMaxLen);
		break;
	case BADUSER:
		memcpy(sErrorMsg, "This user was not found on www.myip.org!", nMaxLen);
		break;
	case BADIP:
		memcpy(sErrorMsg, "You entered an invalid IP-Address\n\nOnly quad-dotted IPv4 addresses are supported.", nMaxLen);
		break;
	case BADEMAIL:
		memcpy(sErrorMsg, "Email address looks bogus.\nMust only contain a-zA-Z0-9.+-_@%!\nand be at least 6 chars wide (a@b.fr).", nMaxLen);
		break;
	case BAD1MX:
		memcpy(sErrorMsg, "Bad primary MX. It is not used.", nMaxLen);
		break;
	case SYSERR:
		memcpy(sErrorMsg, "A system error at www.myip.org occured.\nPlease report this bug to akg@recv.org", nMaxLen);
		break;
	case BADHOSTNAME:
		memcpy(sErrorMsg, "Hostname/login looks bogus. Must only be a-z0-9", nMaxLen);
		break;
	case INVPWD:
		memcpy(sErrorMsg, "You entered an invalid character in your password and/or username.\r\n\r\nPlease try another one...", nMaxLen);
		break;
	case INVDOMAIN:
		memcpy(sErrorMsg, "This is not a valid domain name you have choose.", nMaxLen);
		break;
	case PARSEFILE:
		memcpy(sErrorMsg, "The received data was unusable. Please try again.", nMaxLen);
		break;
	case NOCHANGE:
		memcpy(sErrorMsg, "The entry was not updated, because the settings were still the same", nMaxLen);
		break;
	default:
		memcpy(sErrorMsg, "An unkown error occured.", nMaxLen);
		break;
	}
}
