// SimuDoc.cpp : implementation of the CSimuDoc class
//

#include "stdafx.h"
#include "Simu.h"

#include "SimuDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSimuDoc

IMPLEMENT_DYNCREATE(CSimuDoc, CDocument)

BEGIN_MESSAGE_MAP(CSimuDoc, CDocument)
	//{{AFX_MSG_MAP(CSimuDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimuDoc construction/destruction

CSimuDoc::CSimuDoc()
{
	// TODO: add one-time construction code here
	m_pArTimeValues = new CObArray;
	m_pArTimeValues->Add(new CUIntArray);
	m_pArTimeValues->Add(new CUIntArray);

	m_HeightMap = NULL;
}

CSimuDoc::~CSimuDoc()
{
	int nSize = m_pArTimeValues->GetSize();
	if (nSize > 0) {
		for (int i = 0; i < nSize; i++) {
			delete (CUIntArray *)m_pArTimeValues->GetAt(i);
		}
		
		m_pArTimeValues->RemoveAll();
	}

	delete m_pArTimeValues;

	DeleteHeightMap();
}

BOOL CSimuDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	((CEditView*)m_viewList.GetHead())->SetWindowText(NULL);

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	DeleteFile("C:\\IPC\\ipc_out.dat");
	DeleteFile("C:\\IPC\\ipc_out.lock");
	DeleteFile("C:\\IPC\\ipc_in.dat");
	DeleteFile("C:\\IPC\\ipc_in.lock");


	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSimuDoc serialization

void CSimuDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CSimuDoc diagnostics

#ifdef _DEBUG
void CSimuDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSimuDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSimuDoc commands

void CSimuDoc::CreateHeightMap(int nWidth, int nHeight)
{
	DeleteHeightMap();
	
	m_nMapHeight = nHeight;
	m_nMapWidth = nWidth;

	m_HeightMap = new int[nWidth * nHeight];
}

void CSimuDoc::DeleteHeightMap()
{
	if (m_HeightMap) {
		delete [] m_HeightMap;
		m_HeightMap = NULL;
	}

	m_nMapHeight = 0;
	m_nMapWidth = 0;
}

