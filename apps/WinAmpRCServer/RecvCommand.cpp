// RecvCommand.cpp: implementation of the CRecvCommand class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WinAmpRC.h"
#include "RecvCommand.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRecvCommand::CRecvCommand()
{

}

CRecvCommand::~CRecvCommand()
{

}

BOOL CRecvCommand::IsComplete()
{
	BOOL bComplete = FALSE;
	if (m_sBuffer[0] != 0xA) {
		return FALSE;
	}

	int nFound = m_sBuffer.Find("\r\n", 0);
	if (nFound == -1) {
		return FALSE;
	}
	else {
		m_sCommand = m_sBuffer.Mid(1, nFound - 1);
		m_sBuffer.Delete(0, nFound + 2);
	}

	return TRUE;
}

void CRecvCommand::Add(char c)
{
	m_sBuffer += c;
}

CString CRecvCommand::GetCommand()
{
	return m_sCommand;
}
