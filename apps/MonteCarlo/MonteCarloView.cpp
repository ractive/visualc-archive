// MonteCarloView.cpp : implementation of the CMonteCarloView class
//

#include "stdafx.h"
#include "MonteCarlo.h"

#include "MonteCarloDoc.h"
#include "MonteCarloView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMonteCarloView

IMPLEMENT_DYNCREATE(CMonteCarloView, CView)

BEGIN_MESSAGE_MAP(CMonteCarloView, CView)
	//{{AFX_MSG_MAP(CMonteCarloView)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMonteCarloView construction/destruction

CMonteCarloView::CMonteCarloView()
{
	// TODO: add construction code here

}

CMonteCarloView::~CMonteCarloView()
{
}

BOOL CMonteCarloView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMonteCarloView drawing

void CMonteCarloView::OnDraw(CDC* pDC)
{
	CMonteCarloDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	CRect cRect;

	GetClientRect(cRect);
	if (cRect.Width() > cRect.Height()) {
		cRect.right = cRect.Height();
	}
	else {
		cRect.bottom = cRect.Width();
	}
	
	int x = (int)((pDoc->m_X + 1) * cRect.Width() / 2);
	int y = (int)((pDoc->m_Y + 1) * cRect.Height() / 2);
	pDC->SetPixel(x, y, 0);
}

/////////////////////////////////////////////////////////////////////////////
// CMonteCarloView diagnostics

#ifdef _DEBUG
void CMonteCarloView::AssertValid() const
{
	CView::AssertValid();
}

void CMonteCarloView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMonteCarloDoc* CMonteCarloView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMonteCarloDoc)));
	return (CMonteCarloDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMonteCarloView message handlers

BOOL CMonteCarloView::OnEraseBkgnd(CDC* pDC) 
{
	CRect cRect;

	GetClientRect(cRect);

	if (cRect.Width() > cRect.Height()) {
		cRect.right = cRect.Height();
	}
	else {
		cRect.bottom = cRect.Width();
	}

	if (m_cRect.EqualRect(cRect)) {
		return TRUE;
	}

	BOOL bRet = CView::OnEraseBkgnd(pDC);
	if (!bRet) {
		return bRet;
	}

	m_cRect = cRect;


	CBrush brush(0x000000FF);
	pDC->FillRect(cRect, &brush);


	CPen pen(PS_INSIDEFRAME, 2, (COLORREF)0x00007700);
	pDC->SelectObject(&pen);
	pDC->Ellipse(&cRect);

	pDC->MoveTo(cRect.Width() / 2, 0);
	pDC->LineTo(cRect.Width() / 2, cRect.Height());
	pDC->MoveTo(0, cRect.Height() / 2);
	pDC->LineTo(cRect.Width(), cRect.Height() / 2);		

	return bRet;
}

void CMonteCarloView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if (lHint == 1) {
		m_cRect.SetRectEmpty();
		InvalidateRect(NULL);
		UpdateWindow();
	}

	if (GetDocument()->m_bDrawPoints) {
		InvalidateRect(NULL);
		UpdateWindow();
	}
}
