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


// DropTarget.h: interface for the CDropTarget class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DROPTARGET_H__33BD7800_3547_4802_9D33_82A8601ED1D1__INCLUDED_)
#define AFX_DROPTARGET_H__33BD7800_3547_4802_9D33_82A8601ED1D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef enum {decimal, hex, octal, binary, dsigned, ddouble} base;

//#include "EditBox.h"
class CEditBox;

class CDropTarget : public IDropTarget  
{
public:
	void GetText(LPDATAOBJECT pIDataSource, CString& sText);
	CDropTarget(CEditBox * pWnd);
	virtual ~CDropTarget();

	STDMETHODIMP QueryInterface(REFIID, VOID**);
	STDMETHODIMP_(ULONG) AddRef(void);
	STDMETHODIMP_(ULONG) Release(void);

	STDMETHODIMP DragEnter(LPDATAOBJECT, DWORD, POINTL, LPDWORD);
	STDMETHODIMP DragOver(DWORD, POINTL, LPDWORD);
	STDMETHODIMP DragLeave(void);
	STDMETHODIMP Drop(LPDATAOBJECT, DWORD, POINTL, LPDWORD);
protected:
	CEditBox* m_pWnd;
	ULONG m_cRef;
	LPDATAOBJECT m_pIDataObject;
private:
	BOOL m_bValidData;
};

#endif // !defined(AFX_DROPTARGET_H__33BD7800_3547_4802_9D33_82A8601ED1D1__INCLUDED_)
