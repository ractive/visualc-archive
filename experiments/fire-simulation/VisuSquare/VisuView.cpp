// VisuView.cpp : implementation of the CVisuView class
//

#include "stdafx.h"
#include "Visu.h"

#include "VisuDoc.h"
#include "VisuView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVisuView

IMPLEMENT_DYNCREATE(CVisuView, CView)

BEGIN_MESSAGE_MAP(CVisuView, CView)
	//{{AFX_MSG_MAP(CVisuView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVisuView construction/destruction

CVisuView::CVisuView()
{
	// TODO: add construction code here

}

CVisuView::~CVisuView()
{
}

BOOL CVisuView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CVisuView drawing

void CVisuView::OnDraw(CDC* pDC)
{
	CVisuDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	int dx = 0;
	int dy = 0;
	COLORREF c;

	CRect rect;
	GetClientRect(&rect);

	dx = rect.Width() / pDoc->x;
	dy = rect.Height() / pDoc->y;

	srand( (unsigned)time( NULL ) );

	for(int i = 0; i < pDoc->x; i++) {
		for(int j = 0; j < pDoc->y; j++) {
			CRect fillrect(i * dx, dy * j,  dx * (i + 1), (j + 1) * dy);
			int r = (rand() * 255 / RAND_MAX);
			int g = (rand() * 255 / RAND_MAX);
			int b = (rand() * 255 / RAND_MAX);
			c = (COLORREF)((b << 10) + (g << 8) + r);
			CBrush brush(RGB(r, g, b));
			pDC->FillRect(&fillrect, &brush);
		}
	}


}

/////////////////////////////////////////////////////////////////////////////
// CVisuView diagnostics

#ifdef _DEBUG
void CVisuView::AssertValid() const
{
	CView::AssertValid();
}

void CVisuView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CVisuDoc* CVisuView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVisuDoc)));
	return (CVisuDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVisuView message handlers
