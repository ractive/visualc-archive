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

// ListToolBar.cpp : implementation file
//

#include "stdafx.h"
#include "LaPlaya.h"
#include "ListToolBar.h"
#include "LaPlayaDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListToolBar

IMPLEMENT_DYNCREATE(CListToolBar, CFormView)

CListToolBar::CListToolBar()
	: CFormView(CListToolBar::IDD)
{
	//{{AFX_DATA_INIT(CListToolBar)
	m_bAvi = TRUE;
	m_sFilter = _T("");
	m_bMov = TRUE;
	m_bMpg = TRUE;
	m_bRest = TRUE;
	//}}AFX_DATA_INIT
	m_bTracking = FALSE;
}

CListToolBar::~CListToolBar()
{
}

void CListToolBar::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CListToolBar)
	DDX_Check(pDX, IDC_AVI, m_bAvi);
	DDX_Text(pDX, IDC_FILTER, m_sFilter);
	DDX_Check(pDX, IDC_MOV, m_bMov);
	DDX_Check(pDX, IDC_MPG, m_bMpg);
	DDX_Check(pDX, IDC_REST, m_bRest);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CListToolBar, CFormView)
	//{{AFX_MSG_MAP(CListToolBar)
	ON_BN_CLICKED(IDC_AVI, OnAvi)
	ON_BN_CLICKED(IDC_MOV, OnMov)
	ON_BN_CLICKED(IDC_MPG, OnMpg)
	ON_BN_CLICKED(IDC_REST, OnRest)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_APPLYFILTER, OnApplyFilter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListToolBar diagnostics

#ifdef _DEBUG
void CListToolBar::AssertValid() const
{
	CFormView::AssertValid();
}

void CListToolBar::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CListToolBar message handlers

void CListToolBar::OnAvi() 
{
	UpdateData();	
	CLaPlayaDoc * pDoc = GetDocument();
	pDoc->m_bAvi = m_bAvi;
	pDoc->UpdateAllViews(this, NEW_TYPE);
}

void CListToolBar::OnMpg() 
{
	UpdateData();	
	CLaPlayaDoc * pDoc = GetDocument();
	pDoc->m_bMpg = m_bMpg;
	pDoc->UpdateAllViews(this, NEW_TYPE);
}

void CListToolBar::OnMov()
{
	UpdateData();	
	CLaPlayaDoc * pDoc = GetDocument();
	pDoc->m_bMov = m_bMov;
	pDoc->UpdateAllViews(this, NEW_TYPE);
}

void CListToolBar::OnRest() 
{
	UpdateData();	
	CLaPlayaDoc * pDoc = GetDocument();
	pDoc->m_bRest = m_bRest;
	pDoc->UpdateAllViews(this, NEW_TYPE);
	
}

void CListToolBar::OnMouseMove(UINT nFlags, CPoint point) 
{
	HINSTANCE hInst = AfxFindResourceHandle(MAKEINTRESOURCE(AFX_IDC_VSPLITBAR), RT_GROUP_CURSOR);
	HCURSOR hSplitCur = ::LoadCursor(hInst, MAKEINTRESOURCE(AFX_IDC_VSPLITBAR));
	::SetCursor(hSplitCur);
		
	if (m_bTracking) {
		CSplitterWnd * pSplitterWnd = (CSplitterWnd *)GetParent();
		int nHeight0 = 0, nMin0 = 0, nNewHeight = 0;

		pSplitterWnd->GetRowInfo(0, nHeight0, nMin0);

		nNewHeight = __max(nHeight0 + point.y - m_nHitOffset, nMin0);
		pSplitterWnd->SetRowInfo(0, nNewHeight, nMin0);
		
		pSplitterWnd->RecalcLayout();
	}
	CFormView::OnMouseMove(nFlags, point);
}

void CListToolBar::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SetCapture();
	m_nHitOffset = point.y;
	m_bTracking = TRUE;	
	CFormView::OnLButtonDown(nFlags, point);
}

void CListToolBar::OnLButtonUp(UINT nFlags, CPoint point) 
{
	ReleaseCapture();
	m_bTracking = FALSE;	
	CFormView::OnLButtonUp(nFlags, point);
}

void CListToolBar::OnApplyFilter() 
{
	UpdateData();
	CLaPlayaDoc * pDoc = GetDocument();
	pDoc->m_sFilter = m_sFilter;
	pDoc->UpdateAllViews(this, NEW_TYPE);
}

void CListToolBar::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	m_ToolTip.Create(this);
	m_ToolTip.Activate(TRUE);
	AddToolTip(IDC_AVI);
	AddToolTip(IDC_MPG);
	AddToolTip(IDC_MOV);
	AddToolTip(IDC_REST);
	AddToolTip(IDC_FILTER);
}

void CListToolBar::AddToolTip(UINT nControl)
{
	m_ToolTip.AddTool(GetDlgItem(nControl), nControl);
}

BOOL CListToolBar::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message== WM_LBUTTONDOWN || pMsg->message== WM_LBUTTONUP || pMsg->message== WM_MOUSEMOVE) {
		m_ToolTip.RelayEvent(pMsg);
	}
	
	return CFormView::PreTranslateMessage(pMsg);
}

void CListToolBar::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	
}
