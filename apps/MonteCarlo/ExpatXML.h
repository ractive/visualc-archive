// ExpatXML.h: interface for the CExpatXML class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXPATXML_H__250015BB_C629_458D_8FCC_85CF1F9A93B6__INCLUDED_)
#define AFX_EXPATXML_H__250015BB_C629_458D_8FCC_85CF1F9A93B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ExpatImpl.h"

class CExpatXML : public CExpatImpl <CExpatXML>  
{
public:
	double y;
	double x;
	CExpatXML();
	virtual ~CExpatXML();
	
	void OnPostCreate ();
	

	void OnStartElement (const XML_Char *pszName, const XML_Char **papszAttrs);

	void OnEndElement (const XML_Char *pszName);

	void OnCharacterData (const XML_Char *pszData, int nLength);
protected:
	BOOL m_bFirstDouble;
	BOOL m_bInDouble;
};

#endif // !defined(AFX_EXPATXML_H__250015BB_C629_458D_8FCC_85CF1F9A93B6__INCLUDED_)
