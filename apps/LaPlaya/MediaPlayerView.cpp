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

// MediaPlayerView.cpp : implementation file
//

#include "stdafx.h"
#include "LaPlaya.h"
#include "MediaPlayerView.h"
#include "LaPlayaDoc.h"
#include "ExploListView.h"
#include "MediaPlayer2.h"
#include "MainFrm.h"

importlib("stdole32.tlb");

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMediaPlayerView

IMPLEMENT_DYNCREATE(CMediaPlayerView, CView)

CMediaPlayerView::CMediaPlayerView()
{
	m_pPlayer = NULL;
}

CMediaPlayerView::~CMediaPlayerView()
{
}


BEGIN_MESSAGE_MAP(CMediaPlayerView, CView)
	//{{AFX_MSG_MAP(CMediaPlayerView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_PLAY, OnPlay)
	ON_COMMAND(ID_PAUSE, OnPause)
	ON_COMMAND(ID_STOP, OnStop)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CMediaPlayerView, CView)
    //{{AFX_EVENTSINK_MAP(CMediaPlayerTestDlg)
	//}}AFX_EVENTSINK_MAP
	ON_EVENT(CMediaPlayerView, ID_MEDIAPLAYER, 3002 /* EndOfStream */, OnEndOfStream, VTS_I4)
	ON_EVENT(CMediaPlayerView, ID_MEDIAPLAYER, 3011 /* OpenStateChange */, OnOpenStateChange, VTS_I4 VTS_I4)
	ON_EVENT(CMediaPlayerView, ID_MEDIAPLAYER, 3012 /* PlayStateChange */, OnPlayStateChange, VTS_I4 VTS_I4)
	ON_EVENT(CMediaPlayerView, ID_MEDIAPLAYER, 3010 /* Error */, OnError, VTS_NONE)
	ON_EVENT(CMediaPlayerView, ID_MEDIAPLAYER, 3009 /* Warning */, OnWarning, VTS_I4 VTS_I4 VTS_BSTR)
	ON_EVENT(CMediaPlayerView, ID_MEDIAPLAYER, 2 /* PositionChange */, OnPositionChange, VTS_R8 VTS_R8)
	ON_EVENT(CMediaPlayerView, ID_MEDIAPLAYER, -609 /* ReadyStateChange */, OnReadyStateChange, VTS_I4)
END_EVENTSINK_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMediaPlayerView drawing

void CMediaPlayerView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CMediaPlayerView diagnostics

#ifdef _DEBUG
void CMediaPlayerView::AssertValid() const
{
	CView::AssertValid();
}

void CMediaPlayerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMediaPlayerView message handlers

int CMediaPlayerView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	InitMediaPlayer();	

	return 0;
}

void CMediaPlayerView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if (lHint == SETTINGS) {
		InitMediaPlayer();
		InvalidateRect(NULL);
		UpdateWindow();
	}


	if (lHint == NEW_FILE || lHint == SETTINGS) {
		CLaPlayaDoc * pDoc = GetDocument();
		if (pSender && pSender->IsKindOf(RUNTIME_CLASS(CExploListView))) {
			if (pDoc->GetTitle().IsEmpty()) {
				return;
			}
			
			FitToWindow();

			m_pPlayer->SetAutoStart(pDoc->m_bAutoStart); // Disables the automatic play on open 

			CString sPath = pDoc->GetPathName();
			AfxGetApp()->AddToRecentFileList(sPath);
			if (sPath.Right(1) != "\\") {
				sPath += "\\";
			}
		

			m_pPlayer->SetFileName(sPath + pDoc->GetTitle());
			((CMainFrame *)AfxGetMainWnd())->m_nState = PLAY;
		}
	}

	else if (lHint == PLAY) {
		OnPlay();
	}
	else if (lHint == STOP) {
		OnStop();
	}
	else if (lHint == PAUSE) {
		OnPause();
	}

}

void CMediaPlayerView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	if (m_pPlayer && GetDocument()->m_bAutoResize) {
		m_pPlayer->MoveWindow(0, 0, cx, cy, TRUE);
	}
}

void CMediaPlayerView::OnPlay() 
{
	m_pPlayer->Play();
	((CMainFrame *)AfxGetMainWnd())->m_nState = PLAY;
}

void CMediaPlayerView::OnPause() 
{
	m_pPlayer->Pause();
	((CMainFrame *)AfxGetMainWnd())->m_nState = PAUSE;
}

void CMediaPlayerView::OnStop() 
{
	m_pPlayer->Stop();
	m_pPlayer->SetCurrentPosition(0);
	((CMainFrame *)AfxGetMainWnd())->m_nState = STOP;
}

void CMediaPlayerView::OnEndOfStream(long Result) 
{
	GetDocument()->UpdateAllViews(this, END_STREAM);
}

void CMediaPlayerView::OnOpenStateChange(long OldState, long NewState) 
{
	// TODO: Add your control notification handler code here
	
}

void CMediaPlayerView::OnPlayStateChange(long OldState, long NewState) 
{
	((CMainFrame *)AfxGetMainWnd())->m_nState = (PLAY_STATE)NewState;			
}

void CMediaPlayerView::OnError() 
{
	// TODO: Add your control notification handler code here
	DWORD dwError = GetLastError();
}

void CMediaPlayerView::OnWarning(long WarningType, long Param, LPCTSTR Description) 
{
	// TODO: Add your control notification handler code here
	
}

void CMediaPlayerView::OnPositionChange(double oldPosition, double newPosition) 
{
}

void CMediaPlayerView::OnReadyStateChange(long ReadyState) 
{
	// TODO: Add your control notification handler code here
	
}


void CMediaPlayerView::InitMediaPlayer()
{
	if (m_pPlayer) {
		delete m_pPlayer;
		m_pPlayer = NULL;
	}

	RECT rect;
	GetClientRect(&rect);
	m_pPlayer = new CMediaPlayer2;
	m_pPlayer->Create("Media Player", WS_CHILD, rect, this, ID_MEDIAPLAYER);

	CLaPlayaDoc * pDoc = GetDocument();

	m_pPlayer->SetAllowChangeDisplaySize(TRUE);
	m_pPlayer->SetTransparentAtStart(TRUE);
	m_pPlayer->SetSendErrorEvents(TRUE);
	m_pPlayer->SetSendOpenStateChangeEvents(TRUE);
	m_pPlayer->SetSendPlayStateChangeEvents(TRUE);
	m_pPlayer->SetSendWarningEvents(TRUE);
	m_pPlayer->SetShowCaptioning(TRUE);
	m_pPlayer->SetEnableFullScreenControls(TRUE);
	m_pPlayer->SetEnablePositionControls(TRUE);
	m_pPlayer->SetEnableTracker(TRUE);
	m_pPlayer->SetAutoSize(!pDoc->m_bAutoResize); // Control automatically sizes to the video size 
	m_pPlayer->SetAllowChangeDisplaySize(pDoc->m_bAutoResize);
	m_pPlayer->SetShowControls(pDoc->m_bShowControls); // Turns off the control panel
}

void CMediaPlayerView::OnDestroy() 
{
	CView::OnDestroy();
	
	if (m_pPlayer) {
		delete m_pPlayer;
		m_pPlayer = NULL;
	}

}

void CMediaPlayerView::FitToWindow()
{
	CLaPlayaDoc * pDoc = GetDocument();

	if (pDoc->m_bAutoResize) {
		RECT rect;
		GetClientRect(&rect);
		m_pPlayer->MoveWindow(&rect, TRUE);
	}
}
