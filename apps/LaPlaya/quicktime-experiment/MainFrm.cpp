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

// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "LaPlaya.h"

#include "MainFrm.h"
#include "ExploTreeView.h"
#include "ExploListView.h"
#include "MediaPlayerView.h"
#include "ListToolBar.h"
#include "SettingsDlg.h"
#include "LaPlayaDoc.h"
#include "MediaPlayer2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_SETTINGS, OnSettings)
	ON_COMMAND(ID_FULLSCREEN, OnFullscreen)
	ON_COMMAND(ID_WINDOWFIT, OnWindowfit)
	ON_UPDATE_COMMAND_UI(ID_WINDOWFIT, OnUpdateWindowfit)
	ON_COMMAND(ID_ORIGSIZE, OnOrigsize)
	ON_UPDATE_COMMAND_UI(ID_ORIGSIZE, OnUpdateOrigsize)
	ON_COMMAND(ID_DOUBLESIZE, OnDoublesize)
	ON_UPDATE_COMMAND_UI(ID_DOUBLESIZE, OnUpdateDoublesize)
	ON_COMMAND(ID_HALFSIZE, OnHalfsize)
	ON_UPDATE_COMMAND_UI(ID_HALFSIZE, OnUpdateHalfsize)
	ON_UPDATE_COMMAND_UI(ID_PAUSE, OnUpdatePause)
	ON_UPDATE_COMMAND_UI(ID_PLAY, OnUpdatePlay)
	ON_UPDATE_COMMAND_UI(ID_STOP, OnUpdateStop)
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI_RANGE(AFX_ID_VIEW_MINIMUM, AFX_ID_VIEW_MAXIMUM, OnUpdateViewStyles)
	ON_COMMAND_RANGE(AFX_ID_VIEW_MINIMUM, AFX_ID_VIEW_MAXIMUM, OnViewStyle)
	ON_COMMAND_RANGE(ID_FILE_MRU_FILE1, ID_FILE_MRU_FILE4, OnMRUDir)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_nState = STOP;
	m_bTracking = FALSE;

	m_pImageListLarge = NULL;
	m_pImageListSmall = NULL;
}

CMainFrame::~CMainFrame()
{
	if (m_pImageListLarge) {
		m_pImageListLarge->Detach();
		delete m_pImageListLarge;
	}

	if (m_pImageListSmall) {
		m_pImageListSmall->Detach();
		delete m_pImageListSmall;
	}

}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	if (!m_wndDlgBar.Create(this, IDR_MAINFRAME, 
		CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}

	if (!m_wndReBar.Create(this) ||
		!m_wndReBar.AddBar(&m_wndToolBar) ||
		!m_wndReBar.AddBar(&m_wndDlgBar))
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);

	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	// create splitter window
	/*if (!m_wndSplitter.CreateStatic(this, 1, 2))
		return FALSE;

	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CExploTreeView), CSize(300, 300), pContext) ||
		!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CExploListView), CSize(300, 300), pContext))
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}*/


    if (!m_wndSplitter.CreateStatic (this, 1, 2))
		return FALSE;

	if (!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CMediaPlayerView), CSize(400, 400), pContext)) {
		return FALSE;
	}

	if (!m_wndSplitter2.CreateStatic(&m_wndSplitter, 3, 1, WS_CHILD | WS_VISIBLE, m_wndSplitter.IdFromRowCol (0, 0))) {
		return FALSE;
	}
	
	if (!m_wndSplitter2.CreateView(0, 0, RUNTIME_CLASS (CExploTreeView), CSize (200, 200), pContext)) {
		return FALSE;
	}

	if (!m_wndSplitter2.CreateView(1, 0, RUNTIME_CLASS (CListToolBar), CSize (50, 50), pContext)) {
		return FALSE;
	}

	if (!m_wndSplitter2.CreateView(2, 0, RUNTIME_CLASS (CExploListView), CSize (200, 200), pContext)) {
		return FALSE;
	}

	/*if (!m_wndSplitter.CreateView (0, 0, RUNTIME_CLASS (CExploTreeView), CSize (160, 0), pContext) ||
        !m_wndSplitter2.Create (&m_wndSplitter, 2, 1, CSize (1, 1), pContext, WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | SPLS_DYNAMIC_SPLIT, m_wndSplitter.IdFromRowCol (0, 1)))

        return FALSE;*/

	SHFILEINFO  sfi;
	HIMAGELIST hImageListLarge = (HIMAGELIST)SHGetFileInfo( TEXT("C:\\"), 0,&sfi,sizeof(SHFILEINFO), SHGFI_SYSICONINDEX | SHGFI_LARGEICON);
	HIMAGELIST hImageListSmall = (HIMAGELIST)SHGetFileInfo( TEXT("C:\\"), 0,&sfi,sizeof(SHFILEINFO),SHGFI_SYSICONINDEX | SHGFI_SMALLICON);

	if (!m_pImageListLarge) {
		m_pImageListLarge = new CImageList;
		m_pImageListLarge->Attach(hImageListLarge);
	}

	if (!m_pImageListSmall) {
		m_pImageListSmall = new CImageList;
		m_pImageListSmall->Attach(hImageListSmall);
	}

	::SendMessage(m_wndSplitter2.GetPane(0, 0)->m_hWnd, TVM_SETIMAGELIST, (WPARAM)TVSIL_NORMAL, (LPARAM)hImageListSmall);

	::SendMessage(m_wndSplitter2.GetPane(2, 0)->m_hWnd, LVM_SETIMAGELIST, (WPARAM)LVSIL_SMALL, (LPARAM)hImageListSmall);
	::SendMessage(m_wndSplitter2.GetPane(2, 0)->m_hWnd, LVM_SETIMAGELIST, (WPARAM)LVSIL_NORMAL, (LPARAM)hImageListLarge);


	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

CExploListView* CMainFrame::GetRightPane()
{
	CWnd* pWnd = m_wndSplitter.GetPane(0, 1);
	CExploListView* pView = DYNAMIC_DOWNCAST(CExploListView, pWnd);
	return pView;
}

void CMainFrame::OnUpdateViewStyles(CCmdUI* pCmdUI)
{
	// TODO: customize or extend this code to handle choices on the
	// View menu.

	CExploListView* pView = GetRightPane(); 

	// if the right-hand pane hasn't been created or isn't a view,
	// disable commands in our range

	if (pView == NULL)
		pCmdUI->Enable(FALSE);
	else
	{
		DWORD dwStyle = pView->GetStyle() & LVS_TYPEMASK;

		// if the command is ID_VIEW_LINEUP, only enable command
		// when we're in LVS_ICON or LVS_SMALLICON mode

		if (pCmdUI->m_nID == ID_VIEW_LINEUP)
		{
			if (dwStyle == LVS_ICON || dwStyle == LVS_SMALLICON)
				pCmdUI->Enable();
			else
				pCmdUI->Enable(FALSE);
		}
		else
		{
			// otherwise, use dots to reflect the style of the view
			pCmdUI->Enable();
			BOOL bChecked = FALSE;

			switch (pCmdUI->m_nID)
			{
			case ID_VIEW_DETAILS:
				bChecked = (dwStyle == LVS_REPORT);
				break;

			case ID_VIEW_SMALLICON:
				bChecked = (dwStyle == LVS_SMALLICON);
				break;

			case ID_VIEW_LARGEICON:
				bChecked = (dwStyle == LVS_ICON);
				break;

			case ID_VIEW_LIST:
				bChecked = (dwStyle == LVS_LIST);
				break;

			default:
				bChecked = FALSE;
				break;
			}

			pCmdUI->SetRadio(bChecked ? 1 : 0);
		}
	}
}


void CMainFrame::OnViewStyle(UINT nCommandID)
{
	// TODO: customize or extend this code to handle choices on the
	// View menu.
	CExploListView* pView = GetRightPane();

	// if the right-hand pane has been created and is a CExploListView,
	// process the menu commands...
	if (pView != NULL)
	{
		DWORD dwStyle = -1;

		switch (nCommandID)
		{
		case ID_VIEW_LINEUP:
			{
				// ask the list control to snap to grid
				CListCtrl& refListCtrl = pView->GetListCtrl();
				refListCtrl.Arrange(LVA_SNAPTOGRID);
			}
			break;

		// other commands change the style on the list control
		case ID_VIEW_DETAILS:
			dwStyle = LVS_REPORT;
			break;

		case ID_VIEW_SMALLICON:
			dwStyle = LVS_SMALLICON;
			break;

		case ID_VIEW_LARGEICON:
			dwStyle = LVS_ICON;
			break;

		case ID_VIEW_LIST:
			dwStyle = LVS_LIST;
			break;
		}

		// change the style; window will repaint automatically
		if (dwStyle != -1)
			pView->ModifyStyle(LVS_TYPEMASK, dwStyle);
	}
}

void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if (!m_wndSplitter.CanActivateNext()) {
		return;
	}

	m_wndSplitter.SetColumnInfo(0, cx / 4, 50);
	int y = cy / 2 - 30;
	if (y < 0) y = 0;

	m_wndSplitter.SetRowInfo(0, y, 50);
	m_wndSplitter.RecalcLayout();

	m_wndSplitter2.SetRowInfo(0, cy / 3, 50);
	m_wndSplitter2.RecalcLayout();
}






void CMainFrame::OnSettings() 
{
	CLaPlayaDoc * pDoc = (CLaPlayaDoc *)GetActiveDocument();
	CSettingsDlg dlg;
	dlg.m_bAutoResize = pDoc->m_bAutoResize;
	dlg.m_bAutoStart = pDoc->m_bAutoStart;
	dlg.m_bShowControls = pDoc->m_bShowControls;
	if (dlg.DoModal() == IDOK) {
		pDoc->m_bAutoResize = dlg.m_bAutoResize;
		pDoc->m_bAutoStart = dlg.m_bAutoStart;
		pDoc->m_bShowControls = dlg.m_bShowControls;
		pDoc->UpdateAllViews(NULL, SETTINGS);
	}
}

void CMainFrame::OnWindowfit() 
{
	SetPlayerSize(WINDOWFIT);
}

void CMainFrame::OnUpdateWindowfit(CCmdUI* pCmdUI) 
{
	CLaPlayaDoc * pDoc = (CLaPlayaDoc *)GetActiveDocument();	
	pCmdUI->Enable(pDoc->m_bAutoResize);
	pCmdUI->SetRadio(m_nSize == WINDOWFIT);

}

void CMainFrame::OnOrigsize() 
{
	SetPlayerSize(ORIGINALSIZE);
}

void CMainFrame::OnUpdateOrigsize(CCmdUI* pCmdUI) 
{
	CLaPlayaDoc * pDoc = (CLaPlayaDoc *)GetActiveDocument();	
	pCmdUI->Enable(pDoc->m_bAutoResize);
	pCmdUI->SetRadio(m_nSize == ORIGINALSIZE);

}

void CMainFrame::OnDoublesize() 
{
	SetPlayerSize(DOUBLESIZE);
}

void CMainFrame::OnUpdateDoublesize(CCmdUI* pCmdUI) 
{
	CLaPlayaDoc * pDoc = (CLaPlayaDoc *)GetActiveDocument();	
	pCmdUI->Enable(pDoc->m_bAutoResize);
	pCmdUI->SetRadio(m_nSize == DOUBLESIZE);
}

void CMainFrame::OnFullscreen() 
{
	SetPlayerSize(FULLSCREEN);
}

void CMainFrame::OnHalfsize() 
{
	SetPlayerSize(HALFSIZE);
}

void CMainFrame::OnUpdateHalfsize(CCmdUI* pCmdUI) 
{
	CLaPlayaDoc * pDoc = (CLaPlayaDoc *)GetActiveDocument();	
	pCmdUI->Enable(pDoc->m_bAutoResize);
	pCmdUI->SetRadio(m_nSize == HALFSIZE);

}

void CMainFrame::SetPlayerSize(DISPLAY_SIZE nSize)
{
	CMediaPlayerView * pView = (CMediaPlayerView *)m_wndSplitter.GetPane(0, 1);
	if (pView && pView->m_pPlayer) {
		pView->m_pPlayer->SetDisplaySize(nSize);
		m_nSize = nSize;
	}	

}

void CMainFrame::OnUpdatePause(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(m_nState == PAUSE);	
}

void CMainFrame::OnUpdatePlay(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(m_nState == PLAY);	
}

void CMainFrame::OnUpdateStop(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(m_nState == STOP);	
}

void CMainFrame::OnMRUDir(UINT nID)
{
	CWaitCursor wait;

	CLaPlayaApp * pApp = (CLaPlayaApp *)AfxGetApp();
	pApp->SetMRUDirName(nID - ID_FILE_MRU_FILE1);
}
