// PicHolder.cpp : implementation file
//

#include "stdafx.h"
#include "GifT68.h"
#include "PicHolder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPicHolder

CPicHolder::CPicHolder()
{
}

CPicHolder::~CPicHolder()
{
}


BEGIN_MESSAGE_MAP(CPicHolder, CStatic)
	//{{AFX_MSG_MAP(CPicHolder)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPicHolder message handlers

void CPicHolder::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	//m_Picture.UpdateSizeOnDC(&dc); 

	CRect rc;
	GetClientRect(rc);
	m_Picture.Show(&dc, rc);


}

BOOL CPicHolder::Load(CString sFilePathName)
{
	if (!m_Picture.Load(sFilePathName)) {
		return FALSE;
	}

	CRect rc;
	GetWindowRect(rc);
	int m_nWidthX = m_Picture.m_Width > 131 ? 131 : m_Picture.m_Width;
	int m_nWidthY = m_Picture.m_Height > 131 ? 131 : m_Picture.m_Height;
	rc.right = rc.left + m_nWidthX;
	rc.bottom = rc.top + m_nWidthY;
	SetWindowPos(NULL, 0, 0, rc.right - rc.left, rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER | SWP_NOREPOSITION);

	return TRUE;
}

BOOL CPicHolder::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	return CStatic::OnEraseBkgnd(pDC);
}
