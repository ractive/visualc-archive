// RecvCommand.h: interface for the CRecvCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECVCOMMAND_H__BF8799C8_5C44_4D1F_BBF1_D2500EF08036__INCLUDED_)
#define AFX_RECVCOMMAND_H__BF8799C8_5C44_4D1F_BBF1_D2500EF08036__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRecvCommand  
{
public:
	void Add(char c);
	BOOL IsComplete();
	CString GetCommand();
	CRecvCommand();
	virtual ~CRecvCommand();
protected:
	CString m_sBuffer;
	CString m_sCommand;
};

#endif // !defined(AFX_RECVCOMMAND_H__BF8799C8_5C44_4D1F_BBF1_D2500EF08036__INCLUDED_)
