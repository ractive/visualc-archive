// ExpatXML.cpp: implementation of the CExpatXML class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MonteCarlo.h"
#include "ExpatXML.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CExpatXML::CExpatXML()
{
	m_bFirstDouble = TRUE;
	m_bInDouble = FALSE;
	x = 0;
	y = 0;
}

CExpatXML::~CExpatXML()
{

}

// Invoked by CExpatImpl after the parser is created

void CExpatXML::OnPostCreate ()
{
	// Enable all the event routines we want
	EnableStartElementHandler ();
	EnableEndElementHandler ();
	// Note: EnableElementHandler will do both start and end
	EnableCharacterDataHandler ();
}

// Start element handler

void CExpatXML::OnStartElement (const XML_Char *pszName, const XML_Char **papszAttrs)
{
	if (strcmp(pszName, "double") == 0) {
		m_bInDouble = TRUE;
	}
		
	return;
}

// End element handler

void CExpatXML::OnEndElement (const XML_Char *pszName)
{
	if (strcmp(pszName, "double") == 0) {
		m_bInDouble = FALSE;
	}

	return;
}

// Character data handler

void CExpatXML::OnCharacterData (const XML_Char *pszData, int nLength)
{
	if (m_bInDouble) {
		if (m_bFirstDouble) {
			x = atof(pszData);
		}
		else {
			y = atof(pszData);
		}

		m_bFirstDouble = !m_bFirstDouble;
	}
	return;
}
