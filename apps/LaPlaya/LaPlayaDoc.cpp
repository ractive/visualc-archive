/*************************************************************************
                     LaPlaya
**************************************************************************

Copyright (C) June, 2001 Jean-Pierre Bergamin, james@ractive.ch

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
***************************************************************************/

// LaPlayaDoc.cpp : implementation of the CLaPlayaDoc class
//

#include "stdafx.h"
#include "LaPlaya.h"

#include "LaPlayaDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLaPlayaDoc

IMPLEMENT_DYNCREATE(CLaPlayaDoc, CDocument)

BEGIN_MESSAGE_MAP(CLaPlayaDoc, CDocument)
	//{{AFX_MSG_MAP(CLaPlayaDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLaPlayaDoc construction/destruction

CLaPlayaDoc::CLaPlayaDoc() : rb("Settings")
{
	// TODO: add one-time construction code here
	m_bAvi = TRUE;
	m_bMpg = TRUE;
	m_bMov = TRUE;
	m_bRest = TRUE;

	m_bAutoResize = FALSE;
	m_bAutoStart = FALSE;
	m_bShowControls = FALSE;
	rb.Bind(m_bAutoResize, "AutoResize", TRUE);
	rb.Bind(m_bAutoStart, "AutoStart", FALSE);
	rb.Bind(m_bShowControls, "Show controls", FALSE);

}

CLaPlayaDoc::~CLaPlayaDoc()
{
}

BOOL CLaPlayaDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CLaPlayaDoc serialization

void CLaPlayaDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CLaPlayaDoc diagnostics

#ifdef _DEBUG
void CLaPlayaDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLaPlayaDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLaPlayaDoc commands

BOOL CLaPlayaDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// Don't allow saving
	return FALSE;	
	//return CDocument::OnSaveDocument(lpszPathName);
}

BOOL CLaPlayaDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	
	return TRUE;
}
