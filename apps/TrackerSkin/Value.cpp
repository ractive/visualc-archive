// Value.cpp: implementation of the CValue class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TrackerSkin.h"
#include "Value.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CValue::CValue(CString &sValueName, CString &sParameter)
{
	m_sValueName = sValueName;

	CString sToken;
	int nOldStart = 0;
	int nStart = 0;

	// Process the comma separated list of parameters
	while((nStart = sParameter.Find(",", nOldStart)) != -1) {
		CString sToken = sParameter.Mid(nOldStart, nStart - nOldStart);

		AddToken(sToken);

		nOldStart = nStart;
		// Skip the comma itself
		nOldStart++;
	}

	sToken = sParameter.Mid(nOldStart);
	AddToken(sToken);

	if (sValueName == "BACKGROUND") {
		
	}
}

CValue::~CValue()
{

}

void CValue::AddToken(CString &sToken)
{
	sToken.TrimLeft(", \r\n");
	sToken.TrimRight(", \r\n");
	AddTail(sToken);
}
