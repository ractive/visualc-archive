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

// ExploListView.cpp : implementation of the CExploListView class
//

#include "stdafx.h"
#include "LaPlaya.h"

#include "LaPlayaDoc.h"
#include "ExploListView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExploListView

IMPLEMENT_DYNCREATE(CExploListView, CListView)

BEGIN_MESSAGE_MAP(CExploListView, CListView)
	//{{AFX_MSG_MAP(CExploListView)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_COMMAND(ID_PAUSE, OnPause)
	ON_COMMAND(ID_PLAY, OnPlay)
	ON_COMMAND(ID_STOP, OnStop)
	ON_NOTIFY(HDN_ITEMCLICK, 0, OnHeaderClick)
	ON_COMMAND(ID_NEXT, OnNext)
	ON_UPDATE_COMMAND_UI(ID_NEXT, OnUpdateNext)
	ON_COMMAND(ID_PREVIOUS, OnPrevious)
	ON_UPDATE_COMMAND_UI(ID_PREVIOUS, OnUpdatePrevious)
	ON_COMMAND(ID_PLAYCONT, OnPlaycont)
	ON_UPDATE_COMMAND_UI(ID_PLAYCONT, OnUpdatePlaycont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExploListView construction/destruction

CExploListView::CExploListView()
{
	m_nSortedCol = 0;
	m_bSortAscending = TRUE;
	m_bContMode = FALSE;
	m_bOldAutoStart = FALSE;

}

CExploListView::~CExploListView()
{

}

BOOL CExploListView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style |= LVS_REPORT | LVS_SHOWSELALWAYS;

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CExploListView drawing

void CExploListView::OnDraw(CDC* pDC)
{
	CLaPlayaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CListCtrl& refCtrl = GetListCtrl();
	refCtrl.InsertItem(0, "Item!");
	// TODO: add draw code for native data here
}

void CExploListView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	CListCtrl &listCtrl = GetListCtrl();

	int nItem = 0;
	
	int nSubItem = 0;

	LV_COLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvc.fmt = LVCFMT_LEFT;
	lvc.iSubItem = nSubItem++;
	lvc.cx = 100;
	lvc.pszText = _T("Name");
	listCtrl.InsertColumn(0, &lvc);
	lvc.fmt = LVCFMT_RIGHT;
	lvc.iSubItem = nSubItem++;
	lvc.cx = 80;
	lvc.pszText = _T("Size");
	listCtrl.InsertColumn(1, &lvc);
	lvc.fmt = LVCFMT_RIGHT;
	lvc.iSubItem = nSubItem++;
	lvc.cx = 100;
	lvc.pszText = _T("Date/Time");
	listCtrl.InsertColumn(2, &lvc);

}

/////////////////////////////////////////////////////////////////////////////
// CExploListView diagnostics

#ifdef _DEBUG
void CExploListView::AssertValid() const
{
	CListView::AssertValid();
}

void CExploListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CLaPlayaDoc* CExploListView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLaPlayaDoc)));
	return (CLaPlayaDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExploListView message handlers
void CExploListView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//TODO: add code to react to the user changing the view style of your window
}

void CExploListView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if (lHint == END_STREAM && m_bContMode) {
		OnNext();
	}
	else if (lHint == NEW_DIR || lHint == NEW_TYPE) {
		ScanVideoFiles();
	}
}

int CExploListView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	
	if (!m_wndReBar.Create(this) ||
		!m_wndReBar.AddBar(&m_wndToolBar))	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}

	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);


	m_pics[AVI] = GetIcon("*.avi", FALSE);
	m_pics[MPG] = GetIcon("*.mpg", FALSE);
	m_pics[MOV] = GetIcon("*.mov", FALSE);
	m_pics[ASF] = GetIcon("*.asf", FALSE);
	m_pics[RM] = GetIcon("*.rm", FALSE);

	m_bOldAutoStart = GetDocument()->m_bAutoStart;

	return 0;
}

void CExploListView::ScanVideoFiles()
{
	CLaPlayaDoc * pDoc = GetDocument();
	CListCtrl &listCtrl = GetListCtrl();
	listCtrl.DeleteAllItems();


	CFileFind finder;
	BOOL bFound = FALSE;
	
	if (!pDoc->m_sFilter.IsEmpty()) {
		bFound = finder.FindFile(pDoc->GetPathName() + "\\" + pDoc->m_sFilter);
		while (bFound) {
			bFound = finder.FindNextFile();
			FILETIME ft;
			finder.GetLastWriteTime(&ft);
			AddMovie(finder.GetFileName(), finder.GetLength(), &ft, AVI);
		}
		finder.Close();
	}
	else {
		CString sWildCard = pDoc->GetPathName();
		if (sWildCard.Right(1) != "\\") {
			sWildCard += "\\";
		}
		sWildCard += "*.avi";
		if (pDoc->m_bAvi) {
			bFound = finder.FindFile(sWildCard);
			while (bFound) {
				bFound = finder.FindNextFile();
				FILETIME ft;
				finder.GetLastWriteTime(&ft);
				AddMovie(finder.GetFileName(), finder.GetLength(), &ft, AVI);
			}
			finder.Close();
		}

		if (pDoc->m_bMpg) {
			sWildCard = pDoc->GetPathName() + "\\*.mpg";
			bFound = finder.FindFile(sWildCard);
			while (bFound) {
				bFound = finder.FindNextFile();
				FILETIME ft;
				finder.GetLastWriteTime(&ft);
				AddMovie(finder.GetFileName(), finder.GetLength(), &ft, MPG);

			}
			finder.Close();


			sWildCard = pDoc->GetPathName() + "\\*.mpeg";
			bFound = finder.FindFile(sWildCard);
			while (bFound) {
				bFound = finder.FindNextFile();
				FILETIME ft;
				finder.GetLastWriteTime(&ft);
				AddMovie(finder.GetFileName(), finder.GetLength(), &ft, MPG);

			}
			finder.Close();
		}
		if (pDoc->m_bMov) {
			sWildCard = pDoc->GetPathName() + "\\*.mov";
			bFound = finder.FindFile(sWildCard);
			while (bFound) {
				bFound = finder.FindNextFile();
				FILETIME ft;
				finder.GetLastWriteTime(&ft);

				AddMovie(finder.GetFileName(), finder.GetLength(), &ft, MOV);

			}
			finder.Close();
		}

		if (pDoc->m_bRest) {
			sWildCard = pDoc->GetPathName() + "\\*.asf";
			bFound = finder.FindFile(sWildCard);
			while (bFound) {
				bFound = finder.FindNextFile();
				FILETIME ft;
				finder.GetLastWriteTime(&ft);

				AddMovie(finder.GetFileName(), finder.GetLength(), &ft, ASF);

			}
			finder.Close();


			sWildCard = pDoc->GetPathName() + "\\*.rm";
			bFound = finder.FindFile(sWildCard);
			while (bFound) {
				bFound = finder.FindNextFile();
				FILETIME ft;
				finder.GetLastWriteTime(&ft);

				AddMovie(finder.GetFileName(), finder.GetLength(), &ft, RM);

			}
			finder.Close();

			sWildCard = pDoc->GetPathName() + "\\*.wmv";
			bFound = finder.FindFile(sWildCard);
			while (bFound) {
				bFound = finder.FindNextFile();
				FILETIME ft;
				finder.GetLastWriteTime(&ft);

				AddMovie(finder.GetFileName(), finder.GetLength(), &ft, AVI);

			}
			finder.Close();

		}
	}
	SortItems(m_nSortedCol, m_bSortAscending, 0);

	if (listCtrl.GetItemCount() == 0) {
		listCtrl.InsertItem(0, "No movies in this directory", 3);
	}
}

void CExploListView::AddMovie(const CString sFilePath, DWORD ulSize, FILETIME * ft, MOV_TYPE type)
{
	CListCtrl &listCtrl = GetListCtrl();
	LVITEM lvi;
	lvi.mask = LVIF_TEXT | LVIF_IMAGE;
	lvi.iItem = 0;
	lvi.iSubItem = 0;
	lvi.pszText = (LPTSTR)(LPCTSTR)sFilePath;
	lvi.cchTextMax = _MAX_PATH;
	lvi.iImage = m_pics[type];
	listCtrl.InsertItem(&lvi);
	CString sSize;
	lvi.iSubItem = 1;
	sSize.Format("%lu", ulSize);
	lvi.pszText = (LPTSTR)(LPCTSTR)sSize;
	listCtrl.SetItem(&lvi);
	SYSTEMTIME st;
	char sTime[15];
	char sDate[15];
	char sDateTime[31];
	sDateTime[0] = '\0';
	FileTimeToSystemTime(ft, &st);
	// Or use LOCALE_USER_DEFAULT???
	GetDateFormat(LOCALE_SYSTEM_DEFAULT, DATE_SHORTDATE, &st, NULL, sDate, 15);
	GetTimeFormat(LOCALE_SYSTEM_DEFAULT, TIME_NOSECONDS, &st, NULL, sTime, 15);
	strcpy(sDateTime, sDate);
	strcat(sDateTime, " ");
	strcat(sDateTime, sTime);
	lvi.iSubItem = 2;
	lvi.pszText = sDateTime;
	listCtrl.SetItem(&lvi);

}

int CExploListView::GetIcon(LPCTSTR sFile, bool bSelected)
{
	CLaPlayaDoc * pDoc = GetDocument();
	SHFILEINFO sfi;
	DWORD dwAttrib = SHGFI_SYSICONINDEX | SHGFI_SMALLICON | SHGFI_USEFILEATTRIBUTES ;
	SHGetFileInfo(sFile, FILE_ATTRIBUTE_NORMAL , &sfi, sizeof (SHFILEINFO), dwAttrib);

	return sfi.iIcon;
}

void CExploListView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CListCtrl& ListCtrl = GetListCtrl();
	NMLISTVIEW* pNMListView = (NM_LISTVIEW *)pNMHDR;
	if (ListCtrl.HitTest(pNMListView->ptAction) == -1) {
		// The doubleclick was not on an item. Nothing to do!
		return;
	}

	PlayFile(pNMListView->iItem);
	
	*pResult = 0;
}

void CExploListView::PlayFile(int nNo)
{
	CLaPlayaDoc * pDoc = GetDocument();
	CString sFile = GetListCtrl().GetItemText(nNo, 0);
	if (sFile == pDoc->GetTitle()) {
		// Don't open the same file again...
		return;
	}
	pDoc->SetTitle(sFile);
	pDoc->UpdateAllViews(this, NEW_FILE);
}

void CExploListView::OnPause() 
{
	GetDocument()->UpdateAllViews(this, PAUSE);
}

void CExploListView::OnPlay() 
{
	CListCtrl &list = GetListCtrl();
	POSITION pos = list.GetFirstSelectedItemPosition();
	if (pos) {
		int nPlay = list.GetNextSelectedItem(pos);
		PlayFile(nPlay);
	}

	GetDocument()->UpdateAllViews(this, PLAY);
}

void CExploListView::OnStop() 
{
	m_bContMode = FALSE;
	GetDocument()->m_bAutoStart = m_bOldAutoStart;
	GetDocument()->UpdateAllViews(this, STOP);
}

void CExploListView::OnHeaderClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	// TODO: Add your control notification handler code here
	
	m_nSortedCol = phdn->iItem;
	m_bSortAscending = !m_bSortAscending;
	Sort();
	
	*pResult = 0;
}

void CExploListView::Sort()
{
	CListCtrl& ListCtrl = GetListCtrl();
	//Determine how many subdirectories are shown

	// Sort files
	SortItems(m_nSortedCol, m_bSortAscending, 0);
}

BOOL CExploListView::SortItems(int nCol, BOOL bAscending, int low, int high)
{
	CListCtrl& ListCtrl = GetListCtrl();

	if( nCol >= ((CHeaderCtrl*)GetDlgItem(0))->GetItemCount())
		return FALSE;
	if( high == -1 )
		high = ListCtrl.GetItemCount() - 1;
	int lo = low;
	int hi = high;
	CString midItem;
	if( hi <= lo )
		return FALSE;
	midItem = ListCtrl.GetItemText( (lo+hi)/2, nCol );
	// loop through the list until indices cross
	while( lo <= hi )	{
 		// rowText will hold all column text for one row 
		CStringArray rowText;
 		// find the first element that is greater than or equal to
 		// the partition element starting from the left Index.
		if( bAscending ) {
  			//while( ( lo < high ) && (atoi(GetItemText(lo, nCol)) < midItem ) )
			while( ( lo < high ) && ( CmpItems( ListCtrl.GetItemText(lo, nCol) , midItem, nCol) < 0 ) )
   				++lo;
		}
		else {
  			//while( ( lo < high ) && (atoi(GetItemText(lo, nCol)) > midItem ) )
			while( ( lo < high ) && ( CmpItems( ListCtrl.GetItemText(lo, nCol) , midItem, nCol) > 0 ) )
   				++lo;
		}
		// find an element that is smaller than or equal to
 		// the partition element starting from the right Index.
		if( bAscending ) {
  			//while( ( hi > low ) && (atoi(GetItemText(hi, nCol)) > midItem ) )
			while( ( hi > low ) && ( CmpItems(ListCtrl.GetItemText(hi, nCol) , midItem, nCol ) > 0 ) )
   				--hi;
		}
		else {
  			//while( ( hi > low ) && (atoi(GetItemText(hi, nCol)) < midItem ) )
			while( ( hi > low ) && ( CmpItems(ListCtrl.GetItemText(hi, nCol) , midItem, nCol ) < 0 ) )
   				--hi;
		}
		// if the indexes have not crossed, swap
 		// and if the items are not equal
		if( lo <= hi ) {
			// swap only if the items are not equal
			//if(atoi(GetItemText(lo, nCol)) != atoi(GetItemText(hi, nCol)) )			/*!!!*
			if( CmpItems (ListCtrl.GetItemText(lo, nCol) , ListCtrl.GetItemText(hi, nCol), nCol  ) != 0) {
	   			// swap the rows
				LV_ITEM lvitemlo, lvitemhi;
	   			int nColCount = ((CHeaderCtrl*)GetDlgItem(0))->GetItemCount();
	   			rowText.SetSize( nColCount );
				int i;
	   			for( i=0; i < nColCount; i++)
					rowText[i] = ListCtrl.GetItemText(lo, i);
	   			lvitemlo.mask = LVIF_IMAGE | LVIF_PARAM | LVIF_STATE;
	   			lvitemlo.iItem = lo;
				lvitemlo.iSubItem = 0;
	   			lvitemlo.stateMask = LVIS_CUT | LVIS_DROPHILITED |
	      					LVIS_FOCUSED |  LVIS_SELECTED |
	      					LVIS_OVERLAYMASK | LVIS_STATEIMAGEMASK;
				lvitemhi = lvitemlo;
	   			lvitemhi.iItem = hi;
				ListCtrl.GetItem( &lvitemlo );
	   			ListCtrl.GetItem( &lvitemhi );
				for( i=0; i< nColCount; i++)
	      			ListCtrl.SetItemText(lo, i, ListCtrl.GetItemText(hi, i) );
				lvitemhi.iItem = lo;
	   			ListCtrl.SetItem( &lvitemhi );
				for( i=0; i< nColCount; i++)
	      			ListCtrl.SetItemText(hi, i, rowText[i]);
				lvitemlo.iItem = hi;
	   			ListCtrl.SetItem( &lvitemlo );
			}	  		
			
			++lo;
			--hi;
		}
	}
	// If the right index has not reached the left side of array
	// must now sort the left partition.
	if( low < hi )
 		SortItems( nCol, bAscending , low, hi);
	// If the left index has not reached the right side of array
	// must now sort the right partition.
	if( lo < high )
 		SortItems( nCol, bAscending , lo, high );
	return TRUE;

}

int CExploListView::CmpItems(CString cstL, CString cstR, int nCol)
{
	if (nCol == 0) {
		return cstL.CompareNoCase(cstR);
	}
	// FIXME: Replace the call to isLocal() when we work in the
	// CFiler capability stuff in HPComm 3.1. (mjd)
	else if (nCol == 1) {
		if (cstR == cstL)
			return 0;
		else if (atol((LPCTSTR)cstL) < atol((LPCTSTR)cstR))
			return -1;
		else
			return 1;
	}
	else if (nCol == 2) {
		COleDateTime odtL;
		COleDateTime odtR;
		odtL.ParseDateTime(cstL);
		odtR.ParseDateTime(cstR);
		COleDateTimeSpan spanElapsed = odtL - odtR;
		if (spanElapsed.GetStatus() == COleDateTimeSpan::invalid) {
			return 0;
		}
		return (int)spanElapsed.GetTotalSeconds();

	}
	return 0;

}

void CExploListView::OnNext() 
{
	CListCtrl &list = GetListCtrl();

	LVFINDINFO lvfi = {0};
	lvfi.flags = LVFI_STRING;
	CLaPlayaDoc * pDoc = GetDocument();
	lvfi.psz = pDoc->GetTitle();
	int nNext = list.FindItem(&lvfi);
	if (nNext != -1) {
		if (nNext + 1 < list.GetItemCount()) {
			list.SetItemState(nNext++, !LVIS_SELECTED & !LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);

			pDoc->SetTitle(list.GetItemText(nNext, 0));
			list.SetItemState(nNext, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
			list.EnsureVisible(nNext, FALSE);
			pDoc->UpdateAllViews(this, NEW_FILE);
		}
	}
}

void CExploListView::OnUpdateNext(CCmdUI* pCmdUI) 
{
	CListCtrl &list = GetListCtrl();
	BOOL bEnable = FALSE;
	POSITION pos = list.GetFirstSelectedItemPosition();
	if (pos) {
		int nPlay = list.GetNextSelectedItem(pos);
		if (nPlay < list.GetItemCount() - 1) {
			bEnable = TRUE;
		}
	}	
	
	pCmdUI->Enable(bEnable);
}

void CExploListView::OnPrevious() 
{
	CListCtrl &list = GetListCtrl();

	LVFINDINFO lvfi = {0};
	lvfi.flags = LVFI_STRING;
	CLaPlayaDoc * pDoc = GetDocument();
	lvfi.psz = pDoc->GetTitle();
	int nNext = list.FindItem(&lvfi);
	if (nNext != -1) {
		if (nNext - 1 >= 0){
			list.SetItemState(nNext--, !LVIS_SELECTED & !LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);

			pDoc->SetTitle(list.GetItemText(nNext, 0));
			list.SetItemState(nNext, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
			list.EnsureVisible(nNext, FALSE);
			pDoc->UpdateAllViews(this, NEW_FILE);
		}
	}
	
}

void CExploListView::OnUpdatePrevious(CCmdUI* pCmdUI) 
{
	CListCtrl &list = GetListCtrl();
	BOOL bEnable = FALSE;
	POSITION pos = list.GetFirstSelectedItemPosition();
	if (pos) {
		int nPlay = list.GetNextSelectedItem(pos);
		if (nPlay != 0) {
			bEnable = TRUE;
		}
	}	
	
	pCmdUI->Enable(bEnable);
}

void CExploListView::OnPlaycont() 
{
	m_bContMode = TRUE;
	m_bOldAutoStart = GetDocument()->m_bAutoStart;
	GetDocument()->m_bAutoStart = TRUE;
	OnPlay();
}

void CExploListView::OnUpdatePlaycont(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(m_bContMode);	
}
