// MelodyEdit.cpp : implementation file
//

#include "stdafx.h"
#include "EMelodyLab.h"
#include "MelodyEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMelodyEdit

CMelodyEdit::CMelodyEdit()
{
}

CMelodyEdit::~CMelodyEdit()
{
}


BEGIN_MESSAGE_MAP(CMelodyEdit, CEdit)
	//{{AFX_MSG_MAP(CMelodyEdit)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMelodyEdit message handlers



void CMelodyEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);

	if (nChar == VK_RIGHT) {
		int nStart = 0;
		int nEnd = 0;
		GetSel(nStart, nEnd);
		
		::SendMessage(GetParent()->GetSafeHwnd(), WM_PLAYTONE, nStart, nEnd);
	}
}
