// FtpSyncException.cpp: implementation of the CFtpSyncException class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FTPSync.h"
#include "FtpSyncException.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFtpSyncException::CFtpSyncException(CFtpSyncException::ERRCODE errcode, CString sAddInfo /* = "" */, DWORD dwLocalError /* = 0 */)
{
	m_FtpError = errcode;
	m_LocalError = dwLocalError;
	m_sAddInfo = sAddInfo;
}


CFtpSyncException::CFtpSyncException()
{

}

CFtpSyncException::~CFtpSyncException()
{

}

BOOL CFtpSyncException::GetErrorMessage( LPTSTR lpszError, UINT nMaxError, PUINT pnHelpContext /* = NULL */)
{
	switch (m_FtpError) {
	case CHANGEDIR:
		strncpy(lpszError, "The directory " + m_sAddInfo + " could not be accessed!", nMaxError);
		break;
	}

	return TRUE;
}

CString CFtpSyncException::GetErrorMessage()
{
	CString sSysError;
	if (m_LocalError != 0) {
		// There's a windows error code.
		// Convert that to a string and show it, too.
		LPVOID lpMsgBuf;
		FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			m_LocalError,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL 
		);

		// Add the string to the sError.
		sSysError += "\r\n\r\nThe Windows error message for this error is:\r\n\r\n";
		sSysError += (LPCTSTR)lpMsgBuf;
		
		// Free the buffer.
		LocalFree( lpMsgBuf );
	}

	CString sError;

	switch (m_FtpError) {
	case CHANGEDIR:
		sError = "The directory " + m_sAddInfo + " could not be accessed!";
		break;
	case PUT:
		sError = "The file\r\n" + m_sAddInfo + "\r\ncould not be uploaded!";
		break;
	case GET:
		sError = "The file\r\n     " + m_sAddInfo + "\r\ncould not be downloaded!";
		break;
	default:
		sError = "Unknown error!";
		break;
	}

	if (!sSysError.IsEmpty()) {
		sError += sSysError;
	}

	return sError;
}

