// NFOViewerView.cpp : implementation of the CNFOViewerView class
//

#include "stdafx.h"
#include "NFOViewer.h"

#include "NFOViewerDoc.h"
#include "NFOViewerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNFOViewerView

IMPLEMENT_DYNCREATE(CNFOViewerView, CScrollView)

BEGIN_MESSAGE_MAP(CNFOViewerView, CScrollView)
	//{{AFX_MSG_MAP(CNFOViewerView)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNFOViewerView construction/destruction

CNFOViewerView::CNFOViewerView()
{
	m_bkColor = RGB(0, 0, 0);
	m_textColor = RGB(200, 200, 200);


	LOGFONT lf;
	lf.lfCharSet = OEM_CHARSET;
	lf.lfClipPrecision = 0;
	lf.lfEscapement = 0;
	strcpy(lf.lfFaceName, "Terminal");
	lf.lfHeight = -12;
	lf.lfItalic = 0;
	lf.lfOrientation = 0;
	lf.lfOutPrecision = 0;
	lf.lfPitchAndFamily = 0;
	lf.lfQuality = 0;
	lf.lfStrikeOut = 0;
	lf.lfUnderline = 0;
	lf.lfWeight = 400;
	lf.lfWidth = 0;

	m_hTerminalFont = CreateFontIndirect(&lf);

	//m_Font.CreateFont(-12,0,0,0,400,0,0,0,255,1,2,1,49, "Terminal");
	
	m_nLines = 0;
	m_nCurPos = 0;
}

CNFOViewerView::~CNFOViewerView()
{
}

BOOL CNFOViewerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CNFOViewerView drawing

void CNFOViewerView::OnDraw(CDC* pDC)
{
	CNFOViewerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDC->SelectObject(m_hTerminalFont);

	RECT rt;

	pDC->SetTextColor(m_textColor);

	rt.top = 0;
	rt.left = 0;
	rt.bottom = pDoc->m_TextSize.cy;
	rt.right = pDoc->m_TextSize.cx;
	pDC->FillSolidRect(&rt, m_bkColor);
	pDC->DrawText(pDoc->m_sNFOContent, -1, &rt, DT_LEFT);
}

void CNFOViewerView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	//SetScrollSizes(MM_TEXT, sizeTotal);

	FitWindow();
}

/////////////////////////////////////////////////////////////////////////////
// CNFOViewerView diagnostics

#ifdef _DEBUG
void CNFOViewerView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CNFOViewerView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CNFOViewerDoc* CNFOViewerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNFOViewerDoc)));
	return (CNFOViewerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNFOViewerView message handlers

void CNFOViewerView::FitWindow()
{
	CNFOViewerDoc * pDoc = GetDocument();
	CDC * pDC = GetDC();

	pDC->SelectObject(m_hTerminalFont);

	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);

	// count the lines and calculate the
	// the extent of the biggest line
	LPTSTR s = (LPTSTR)(LPCTSTR)pDoc->m_sNFOContent;
	LPTSTR sTemp = NULL;
	int nMaxWidth = 0;
	m_nLines = 0;
	while (sTemp = strpbrk(s, "\n")) {
		int chars = sTemp - s;
		nMaxWidth = __max(nMaxWidth, chars * tm.tmAveCharWidth);
		s = sTemp + 1;
		m_nLines++;
	}

	m_nLines++;
	nMaxWidth++;

	m_nLineHeight = tm.tmHeight + tm.tmExternalLeading;
	pDoc->m_TextSize.cx = nMaxWidth;
	pDoc->m_TextSize.cy = m_nLineHeight * m_nLines;

	SetScrollSizes(MM_TEXT, pDoc->m_TextSize);
	pDC->SetBkMode(TRANSPARENT);
	
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit(FALSE);
}

void CNFOViewerView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	//FitWindow();	
}

BOOL CNFOViewerView::OnEraseBkgnd(CDC* pDC) 
{
	RECT cRect;
	GetClientRect(&cRect);
	pDC->FillSolidRect(&cRect, m_bkColor);
	return CScrollView::OnEraseBkgnd(pDC);
}
