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


// DropTarget.cpp: implementation of the CDropTarget class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "hexer.h"
#include "DropTarget.h"
#include "EditBox.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDropTarget::CDropTarget(CEditBox * pWnd)
{
	m_cRef=0;     
	m_pIDataObject=NULL;
	m_pWnd = pWnd;
	return;     
}

CDropTarget::~CDropTarget()
{

}

STDMETHODIMP CDropTarget::QueryInterface(REFIID riid, VOID** ppv)   
{     
	*ppv=NULL;      
	if (IID_IUnknown==riid || IID_IDropTarget==riid)         
		*ppv=this;      
	if (NULL!=*ppv) {         
		((LPUNKNOWN)*ppv)->AddRef();         
		return NOERROR;         
	}      
	return ResultFromScode(E_NOINTERFACE);
}   

STDMETHODIMP_(ULONG) CDropTarget::AddRef(void)     
{     
	return ++m_cRef;     
}  

STDMETHODIMP_(ULONG) CDropTarget::Release(void)   
{      
	if (0!=--m_cRef)         
		return m_cRef;      
	delete this;     
	return 0;     
}      

STDMETHODIMP CDropTarget::DragEnter(LPDATAOBJECT pIDataSource , DWORD grfKeyState, POINTL pt, LPDWORD pdwEffect)    
{     
	m_pIDataObject=NULL;
	CString sText;
	GetText(pIDataSource, sText);
	unsigned __int64 nRet;
	if (m_pWnd->Parse(&nRet, &sText, TRUE) != -1) {
		*pdwEffect=DROPEFFECT_COPY;
		m_bValidData = TRUE;
	}
	else {
		*pdwEffect=DROPEFFECT_NONE;
		m_bValidData = FALSE;
	}

	m_pIDataObject=pIDataSource;     
	m_pIDataObject->AddRef();      
	
	return NOERROR;     
}       

STDMETHODIMP CDropTarget::DragOver(DWORD grfKeyState, POINTL pt, LPDWORD pdwEffect)   
{     

	if (NULL==m_pIDataObject) {         
		*pdwEffect=DROPEFFECT_NONE;         
	}
	else {
		if (m_bValidData) {
			*pdwEffect=DROPEFFECT_COPY;
		}
		else {
			*pdwEffect=DROPEFFECT_NONE;         
		}
	}

	return NOERROR;     
}       

STDMETHODIMP CDropTarget::DragLeave(void)     
{     
	m_pIDataObject->Release();
	m_bValidData = FALSE;
	return NOERROR;     
}      

STDMETHODIMP CDropTarget::Drop(LPDATAOBJECT pIDataSource, DWORD grfKeyState, POINTL pt, LPDWORD pdwEffect)     
{     
	BOOL        fRet=TRUE;      
	*pdwEffect=DROPEFFECT_NONE;      
	if (NULL==m_pIDataObject)         
		return ResultFromScode(E_FAIL);

	DragLeave();      
	
	m_pWnd->Paste(pIDataSource);

	*pdwEffect=DROPEFFECT_COPY;      

	return NOERROR;     
} 


 

void CDropTarget::GetText(LPDATAOBJECT pIDataObject, CString& sText)
{
    FORMATETC       fe;     
	STGMEDIUM       stm;     
	BOOL			fRet;

	// Let's get the text from the "clipboard"
 	fe.cfFormat = CF_TEXT;
	fe.dwAspect = DVASPECT_CONTENT;
	fe.lindex = -1;
	fe.ptd = NULL;
	fe.tymed = TYMED_HGLOBAL;

	fRet=SUCCEEDED(pIDataObject->GetData(&fe, &stm));
	
	sText = (LPSTR)GlobalLock(stm.hGlobal);
	GlobalUnlock(stm.hGlobal);

	if (stm.hGlobal != NULL) {         
		ReleaseStgMedium(&stm);         
	}
}
