// LandscapeDoc.cpp : implementation of the CLandscapeDoc class
//

#include "stdafx.h"
#include "Landscape.h"

#include "LandscapeDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLandscapeDoc

IMPLEMENT_DYNCREATE(CLandscapeDoc, CDocument)

BEGIN_MESSAGE_MAP(CLandscapeDoc, CDocument)
	//{{AFX_MSG_MAP(CLandscapeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLandscapeDoc construction/destruction

CLandscapeDoc::CLandscapeDoc()
{
	// TODO: add one-time construction code here

}

CLandscapeDoc::~CLandscapeDoc()
{
}

BOOL CLandscapeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CLandscapeDoc serialization

void CLandscapeDoc::Serialize(CArchive& ar)
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
// CLandscapeDoc diagnostics

#ifdef _DEBUG
void CLandscapeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLandscapeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLandscapeDoc commands
