// MyIPException.h: interface for the CMyIPException class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYIPEXCEPTION_H__7888B598_987D_4450_860A_D73D34525E28__INCLUDED_)
#define AFX_MYIPEXCEPTION_H__7888B598_987D_4450_860A_D73D34525E28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxinet.h>

class CMyIPException : public CException  
{

public:
	void GetErrorMessage(char * sErrorMsg, int nMaxLen);
	typedef enum {
		UNKNOWN, PARSEFILE, BADPWD, BADUSER, BADIP, BADEMAIL, BADHOSTNAME, BAD1MX, SYSERR, INVPWD, INVDOMAIN, NOCHANGE
	} ErrorCode;

	ErrorCode m_ErrorCode;

	CMyIPException(ErrorCode errCode);
	virtual ~CMyIPException();

};

#endif // !defined(AFX_MYIPEXCEPTION_H__7888B598_987D_4450_860A_D73D34525E28__INCLUDED_)
