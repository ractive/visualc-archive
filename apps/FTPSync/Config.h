// Config.h: interface for the CConfig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONFIG_H__3735CCA2_5AF2_4274_81B1_4FD99CE74450__INCLUDED_)
#define AFX_CONFIG_H__3735CCA2_5AF2_4274_81B1_4FD99CE74450__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CConfig : public CObject  
{
public:
	DECLARE_SERIAL(CConfig)

	BOOL m_bSyncFtp;
	BOOL m_bSyncLocal;

	BOOL m_bAskLocalOverwrite;
	
	BOOL m_bAskFtpOverwrite;

	BOOL m_bAskIfConflict;
	BOOL m_bUpload;

	void Serialize(CArchive &ar);

	CConfig();
	virtual ~CConfig();

};

#endif // !defined(AFX_CONFIG_H__3735CCA2_5AF2_4274_81B1_4FD99CE74450__INCLUDED_)
