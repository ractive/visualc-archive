// NFOViewerDoc.cpp : implementation of the CNFOViewerDoc class
//

#include "stdafx.h"
#include "NFOViewer.h"

#include "NFOViewerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNFOViewerDoc

IMPLEMENT_DYNCREATE(CNFOViewerDoc, CDocument)

BEGIN_MESSAGE_MAP(CNFOViewerDoc, CDocument)
	//{{AFX_MSG_MAP(CNFOViewerDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNFOViewerDoc construction/destruction

CNFOViewerDoc::CNFOViewerDoc()
{
	m_TextSize = CSize(0, 0);
}

CNFOViewerDoc::~CNFOViewerDoc()
{
}

BOOL CNFOViewerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CNFOViewerDoc serialization

void CNFOViewerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		m_sNFOContent.Empty();
		int nLength = ar.GetFile()->GetLength();
		ar.Read(m_sNFOContent.GetBuffer(nLength), nLength);
		m_sNFOContent.ReleaseBuffer();
		//UpdateAllViews(NULL, 1);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CNFOViewerDoc diagnostics

#ifdef _DEBUG
void CNFOViewerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CNFOViewerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNFOViewerDoc commands
