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

// ExploListView.h : interface of the CExploListView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXPLOLISTVIEW_H__9D58AEFB_3F27_4B16_BE67_2BCB063CF663__INCLUDED_)
#define AFX_EXPLOLISTVIEW_H__9D58AEFB_3F27_4B16_BE67_2BCB063CF663__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


typedef enum {MPG = 0, MPEG = 0, AVI, MOV, ASF, RM, RAM} MOV_TYPE;

class CExploListView : public CListView
{
protected: // create from serialization only
	CExploListView();
	DECLARE_DYNCREATE(CExploListView)
	CToolBar    m_wndToolBar;
	CReBar      m_wndReBar;
	int GetIcon(LPCTSTR sFile, bool bSelected);

// Attributes
public:
	CLaPlayaDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExploListView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CExploListView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	void AddMovie(const CString sFilePath, DWORD ulSize, FILETIME * ft, MOV_TYPE type);
	//{{AFX_MSG(CExploListView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPause();
	afx_msg void OnPlay();
	afx_msg void OnStop();
	afx_msg void OnHeaderClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNext();
	afx_msg void OnUpdateNext(CCmdUI* pCmdUI);
	afx_msg void OnPrevious();
	afx_msg void OnUpdatePrevious(CCmdUI* pCmdUI);
	afx_msg void OnPlaycont();
	afx_msg void OnUpdatePlaycont(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_MESSAGE_MAP()

private:
	void ScanVideoFiles();

	void PlayFile(int nNo);


	int m_pics[10];
	int m_nSortedCol;
	BOOL m_bSortAscending;
	void Sort();
	BOOL SortItems(int nCol, BOOL bAscending, int low, int high = -1);
	int CmpItems(CString cstL, CString cstR, int nCol);
	BOOL m_bContMode;
	BOOL m_bOldAutoStart;
};

#ifndef _DEBUG  // debug version in ExploListView.cpp
inline CLaPlayaDoc* CExploListView::GetDocument()
   { return (CLaPlayaDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXPLOLISTVIEW_H__9D58AEFB_3F27_4B16_BE67_2BCB063CF663__INCLUDED_)
