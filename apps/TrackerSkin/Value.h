// Value.h: interface for the CValue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VALUE_H__0861C9FC_F00E_4031_B4B5_92C36D7D150F__INCLUDED_)
#define AFX_VALUE_H__0861C9FC_F00E_4031_B4B5_92C36D7D150F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CValue : public CStringList  
{
public:
	CValue(CString &sValueName, CString &sParameter);
	virtual ~CValue();
	CString m_sValueName;
protected:
	void AddToken(CString &sToken);
};

#endif // !defined(AFX_VALUE_H__0861C9FC_F00E_4031_B4B5_92C36D7D150F__INCLUDED_)
