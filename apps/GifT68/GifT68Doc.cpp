// GifT68Doc.cpp : implementation of the CGifT68Doc class
//

#include "stdafx.h"
#include "GifT68.h"

#include "GifT68Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGifT68Doc

IMPLEMENT_DYNCREATE(CGifT68Doc, CDocument)

BEGIN_MESSAGE_MAP(CGifT68Doc, CDocument)
	//{{AFX_MSG_MAP(CGifT68Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGifT68Doc construction/destruction

CGifT68Doc::CGifT68Doc()
{
	// TODO: add one-time construction code here

}

CGifT68Doc::~CGifT68Doc()
{
}

BOOL CGifT68Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CGifT68Doc serialization

void CGifT68Doc::Serialize(CArchive& ar)
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
// CGifT68Doc diagnostics

#ifdef _DEBUG
void CGifT68Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGifT68Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGifT68Doc commands
