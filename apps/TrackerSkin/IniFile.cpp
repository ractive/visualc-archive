// IniFile.cpp: implementation of the CIniFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TrackerSkin.h"
#include "IniFile.h"
#include "Value.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIniFile::CIniFile(const LPCTSTR sBaseDir, const LPCTSTR sFileName)
{
	m_sBaseDir = sBaseDir;
	if (m_sBaseDir.Right(1) != "\\") {
		m_sBaseDir += "\\";
	}
	m_sFileName = sFileName;
}

CIniFile::~CIniFile()
{
	Close();
	DeleteValues();
}

BOOL CIniFile::ParseFile()
{
	Open(m_sBaseDir + m_sFileName, CFile::modeRead);

	// Read the whole file into sContent...
	CString sContent;
	UINT nLength = GetLength();
	LPTSTR sBuf = sContent.GetBuffer(nLength);
	if (Read(sBuf, nLength) != nLength) {
		return FALSE;
	}
	sContent.ReleaseBuffer();

	// Get the single lines
	CString sLine;
	int nOldStart = 0;
	int nStart = 0;

	while((nStart = sContent.Find("\r\n", nOldStart)) != -1) {
		CString sLine = sContent.Mid(nOldStart, nStart - nOldStart);
		nOldStart = nStart;
		nOldStart += 2;
	
		ProcessLine(sLine);
	}

	sLine = sContent.Mid(nOldStart);
	ProcessLine(sLine);

	Close();

	return TRUE;
}

void CIniFile::ProcessLine(CString &sLine)
{
	sLine.TrimLeft();
	sLine.TrimRight();
	if (sLine.IsEmpty() || sLine.GetAt(0) == ';') {
		// Ignore comments and empty lines
		return;
	}

	int nFind = sLine.Find("=");
	if (nFind == -1) {
		return;
	}

	CString sName = sLine.Left(nFind);
	CString sParameter = sLine.Mid(nFind + 1);
	CValue *pValue = new CValue(sName, sParameter);
	m_ValueList.AddTail(pValue);
}

void CIniFile::WriteFile()
{
	Open(m_sBaseDir + m_sFileName, CFile::modeWrite | CFile::modeCreate);

	POSITION pos = NULL;
	
	CValue * pValue = NULL;

	for(pos = m_ValueList.GetHeadPosition(); pos != NULL;) {
		pValue = (CValue *)m_ValueList.GetNext(pos);
		POSITION vpos = pValue->GetHeadPosition();
		CString sParameter = pValue->m_sValueName + "=";
		LPCTSTR s;
		for( vpos = pValue->GetHeadPosition(); vpos != NULL; ) {
			s = (LPCTSTR)pValue->GetNext(vpos);
			sParameter += s;
			sParameter += ", ";
		}
		// Delete the last ", "
		sParameter.Delete(sParameter.GetLength() - 2, 2);
		sParameter += "\r\n";

		Write(sParameter, sParameter.GetLength());
	}
}

void CIniFile::DeleteValues()
{
	POSITION pos = NULL;
	CValue * pValue = NULL;
	for(pos = m_ValueList.GetHeadPosition(); pos != NULL;) {
		pValue = (CValue *)m_ValueList.GetNext(pos);
		delete pValue;
	}
}
