/*************************************************************************
                     Hexer
**************************************************************************

Copyright (C) April, 2000 Jean-Pierre Bergamin, james@ractive.ch

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


#if !defined(AFX_EDITBOX_H__182344CD_36E9_4864_98BC_DE0C9F599A01__INCLUDED_)
#define AFX_EDITBOX_H__182344CD_36E9_4864_98BC_DE0C9F599A01__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditBox.h : header file
//

#include "DropTarget.h"

/////////////////////////////////////////////////////////////////////////////
// CEditBox window

class CEditBox : public CEdit
{
// Construction
public:
	CEditBox();
	unsigned short * m_pnBit;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL Parse(unsigned __int64 * pRes, CString * psCont = NULL, BOOL bSilent = FALSE);
	void SetBase(base base_);
	virtual ~CEditBox();
	CDropTarget * m_pDropTarget;
	BOOL Paste(LPDATAOBJECT pIDataObject);
	void Convert(unsigned __int64 * pVal, BOOL bSigned = FALSE);

	// Generated message map functions
protected:
	//{{AFX_MSG(CEditBox)
	afx_msg void OnChange();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	
	base m_Base;
private:
	CString m_sOldContent;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITBOX_H__182344CD_36E9_4864_98BC_DE0C9F599A01__INCLUDED_)
