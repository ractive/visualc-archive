// VisuDoc.cpp : implementation of the CVisuDoc class
//

#include "stdafx.h"
#include "Visu.h"

#include "VisuDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVisuDoc

IMPLEMENT_DYNCREATE(CVisuDoc, CDocument)

BEGIN_MESSAGE_MAP(CVisuDoc, CDocument)
	//{{AFX_MSG_MAP(CVisuDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVisuDoc construction/destruction

CVisuDoc::CVisuDoc()
{
	// TODO: add one-time construction code here
	x = 50;
	y = 50;
}

CVisuDoc::~CVisuDoc()
{
}

BOOL CVisuDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CVisuDoc serialization

void CVisuDoc::Serialize(CArchive& ar)
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
// CVisuDoc diagnostics

#ifdef _DEBUG
void CVisuDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CVisuDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVisuDoc commands
