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

// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__013B7B0E_4551_4429_A161_75100A2B7408__INCLUDED_)
#define AFX_MAINFRM_H__013B7B0E_4551_4429_A161_75100A2B7408__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CExploListView;
#include "ToolSplitterWnd.h"

typedef enum {ORIGINALSIZE=0, HALFSIZE=1, DOUBLESIZE=2, FULLSCREEN=3, WINDOWFIT=7} DISPLAY_SIZE;

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
protected:
	CSplitterWnd m_wndSplitter;
	CToolSplitterWnd m_wndSplitter2;
public:
	PLAY_STATE m_nState;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
	CExploListView* GetRightPane();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CReBar      m_wndReBar;
	CDialogBar      m_wndDlgBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSettings();
	afx_msg void OnFullscreen();
	afx_msg void OnWindowfit();
	afx_msg void OnUpdateWindowfit(CCmdUI* pCmdUI);
	afx_msg void OnOrigsize();
	afx_msg void OnUpdateOrigsize(CCmdUI* pCmdUI);
	afx_msg void OnDoublesize();
	afx_msg void OnUpdateDoublesize(CCmdUI* pCmdUI);
	afx_msg void OnHalfsize();
	afx_msg void OnUpdateHalfsize(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePause(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePlay(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStop(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnUpdateViewStyles(CCmdUI* pCmdUI);
	afx_msg void OnViewStyle(UINT nCommandID);
	afx_msg void OnMRUDir(UINT nID);

	DECLARE_MESSAGE_MAP()
private:
	CImageList * m_pImageListSmall;
	CImageList * m_pImageListLarge;

	BOOL m_bTracking;
	void SetPlayerSize(DISPLAY_SIZE nSize);
	DISPLAY_SIZE m_nSize;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__013B7B0E_4551_4429_A161_75100A2B7408__INCLUDED_)
