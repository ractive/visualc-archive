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

#if !defined(AFX_MEDIAPLAYERVIEW_H__150F5370_94F7_4704_8D46_A3FE450723AD__INCLUDED_)
#define AFX_MEDIAPLAYERVIEW_H__150F5370_94F7_4704_8D46_A3FE450723AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MediaPlayerView.h : header file
//

class CLaPlayaDoc;
class CMediaPlayer2;

/////////////////////////////////////////////////////////////////////////////
// CMediaPlayerView view

class CMediaPlayerView : public CView
{
protected:
	CMediaPlayerView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMediaPlayerView)

// Attributes
public:
	CMediaPlayer2 * m_pPlayer;

// Operations
public:
	void FitToWindow();

// Overrides
	CLaPlayaDoc* GetDocument();
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMediaPlayerView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMediaPlayerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CMediaPlayerView)
	afx_msg void OnDestroy();
	//}}AFX_MSG
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPlay();
	afx_msg void OnPause();
	afx_msg void OnStop();
	afx_msg void OnEndOfStream(long Result);
	afx_msg void OnOpenStateChange(long OldState, long NewState);
	afx_msg void OnPlayStateChange(long OldState, long NewState);
	afx_msg void OnError();
	afx_msg void OnWarning(long WarningType, long Param, LPCTSTR Description);
	afx_msg void OnPositionChange(double oldPosition, double newPosition);
	afx_msg void OnReadyStateChange(long ReadyState);
	DECLARE_EVENTSINK_MAP()
	DECLARE_MESSAGE_MAP()
private:
	void InitMediaPlayer();
};

inline CLaPlayaDoc* CMediaPlayerView::GetDocument()
   { return (CLaPlayaDoc*)m_pDocument; }

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEDIAPLAYERVIEW_H__150F5370_94F7_4704_8D46_A3FE450723AD__INCLUDED_)
