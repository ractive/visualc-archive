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

// LaPlayaDoc.h : interface of the CLaPlayaDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LAPLAYADOC_H__487FBC61_440A_4640_8060_A50C467FD721__INCLUDED_)
#define AFX_LAPLAYADOC_H__487FBC61_440A_4640_8060_A50C467FD721__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RegBinding.h"

class CLaPlayaDoc : public CDocument
{
protected: // create from serialization only
	CLaPlayaDoc();
	DECLARE_DYNCREATE(CLaPlayaDoc)

// Attributes
public:

	BOOL m_bAvi;
	BOOL m_bMpg;
	BOOL m_bMov;
	BOOL m_bRest;

	BOOL m_bAutoResize;
	BOOL m_bAutoStart;
	BOOL m_bShowControls;

	CString m_sFilter;

	CRegBinding rb;


	// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLaPlayaDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLaPlayaDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLaPlayaDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LAPLAYADOC_H__487FBC61_440A_4640_8060_A50C467FD721__INCLUDED_)
