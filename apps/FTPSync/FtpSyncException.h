// FtpSyncException.h: interface for the CFtpSyncException class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FTPSYNCEXCEPTION_H__A5AA5214_961E_4787_AE83_2D4639A178B6__INCLUDED_)
#define AFX_FTPSYNCEXCEPTION_H__A5AA5214_961E_4787_AE83_2D4639A178B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFtpSyncException : public CException  
{
public:
	CString GetErrorMessage();
	CFtpSyncException();
	virtual ~CFtpSyncException();
	typedef enum {CHANGEDIR, PUT, GET} ERRCODE;

	CFtpSyncException(ERRCODE errcode, CString sAddInfo = "", DWORD dwLocalError = 0);
	
	virtual BOOL GetErrorMessage( LPTSTR lpszError, UINT nMaxError, PUINT pnHelpContext = NULL );
	
	ERRCODE m_FtpError;
	DWORD m_LocalError;
	CString m_sAddInfo;
};

#endif // !defined(AFX_FTPSYNCEXCEPTION_H__A5AA5214_961E_4787_AE83_2D4639A178B6__INCLUDED_)
