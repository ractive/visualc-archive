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

#if !defined(AFX_LISTTOOLBAR_H__7308E846_5C60_4B6E_ACCD_E3D79C154CFA__INCLUDED_)
#define AFX_LISTTOOLBAR_H__7308E846_5C60_4B6E_ACCD_E3D79C154CFA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListToolBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListToolBar form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CLaPlayaDoc;

class CListToolBar : public CFormView
{
protected:
	CListToolBar();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CListToolBar)

// Form Data
public:
	//{{AFX_DATA(CListToolBar)
	enum { IDD = IDD_LISTTOOLBAR };
	BOOL	m_bAvi;
	CString	m_sFilter;
	BOOL	m_bMov;
	BOOL	m_bMpg;
	BOOL	m_bRest;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	CLaPlayaDoc* GetDocument();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListToolBar)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CListToolBar();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CListToolBar)
	afx_msg void OnAvi();
	afx_msg void OnMov();
	afx_msg void OnMpg();
	afx_msg void OnRest();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnApplyFilter();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void AddToolTip(UINT nControl);
	CToolTipCtrl m_ToolTip;
	int m_nHitOffset;
	BOOL m_bTracking;
};

inline CLaPlayaDoc* CListToolBar::GetDocument()
   { return (CLaPlayaDoc*)m_pDocument; }
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTTOOLBAR_H__7308E846_5C60_4B6E_ACCD_E3D79C154CFA__INCLUDED_)
