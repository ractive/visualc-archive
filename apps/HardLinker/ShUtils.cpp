/*************************************************************************
                          HardLinker
**************************************************************************

Copyright (C) June, 2000 Jean-Pierre Bergamin, james@ractive.ch

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

The original context menu code was found at CodeGuru and is from Chris
from Smaller Animals Software
"CtxMenu, Copyright 1999, Smaller Animals Software:
  This code may be modifed and distributed free of charge or restrictions.
  This code is provided as-is. If you use this code in any application,
any bugs in the code are your responsibility."

***************************************************************************/


#include "stdafx.h"
#include "resource.h"
#include "ShUtils.h"
#include "errno.h"
#include <direct.h>
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//CRITICAL_SECTION g_critSectionBreak;

////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////
void ShMsgPump()
{
	// if we do MFC stuff in an exported fn, call this first!
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

	DWORD dInitTime = GetTickCount();
	MSG m_msgCur;                   // current message
	CWinApp	*pWinApp = AfxGetApp();   
	while (::PeekMessage(&m_msgCur, NULL, NULL, NULL, PM_NOREMOVE)  &&
			(GetTickCount() - dInitTime < 200) )
	{
		pWinApp->PumpMessage();
	}
}

////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////
int WideCharToLocal(LPTSTR pLocal, LPWSTR pWide, DWORD dwChars)
{
	*pLocal = 0;

	#ifdef UNICODE
	lstrcpyn(pLocal, pWide, dwChars);
	#else
	WideCharToMultiByte( CP_ACP, 
						 0, 
						 pWide, 
						 -1, 
						 pLocal, 
						 dwChars, 
						 NULL, 
						 NULL);
	#endif

	return lstrlen(pLocal);
}

////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////
int LocalToWideChar(LPWSTR pWide, LPTSTR pLocal, DWORD dwChars)
{
	*pWide = 0;

	#ifdef UNICODE
	lstrcpyn(pWide, pLocal, dwChars);
	#else
	MultiByteToWideChar( CP_ACP, 
						 0, 
						 pLocal, 
						 -1, 
						 pWide, 
						 dwChars); 
	#endif

	return lstrlenW(pWide);
}

////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////
STDMETHODIMP CreateShellExtMenu(HMENU hMenu,
                                         UINT indexMenu,
                                         UINT idCmdFirst,
                                         UINT idCmdLast,
                                         UINT uFlags,
                                         HBITMAP hbmp)
{
   ODS("CShellExt::QueryContextMenu()\r\n");

   UINT idCmd = idCmdFirst;

   BOOL bAppendItems=TRUE;


   HINSTANCE hInst = AfxGetInstanceHandle();

   if ((uFlags & 0x000F) == CMF_NORMAL)  //Check == here, since CMF_NORMAL=0
   {
      ODS("CMF_NORMAL...\r\n");
   }
   else
   if (uFlags & CMF_VERBSONLY)
   {
      ODS("CMF_VERBSONLY...\r\n");
   }
   else
   if (uFlags & CMF_EXPLORE)
   {
      ODS("CMF_EXPLORE...\r\n");
   }
   else
   if (uFlags & CMF_DEFAULTONLY)
   {
      ODS("CMF_DEFAULTONLY...\r\n");
      bAppendItems = FALSE;
   }
   else
   {
      char szTemp[32];

      wsprintf(szTemp, "uFlags==>%d\r\n", uFlags);
      ODS("CMF_default...\r\ne");
      ODS(szTemp);
      bAppendItems = FALSE;
   }
   
   InsertMenu(hMenu, indexMenu++, MF_POPUP|MF_BYPOSITION, idCmd++, "Create hard-link");

   /*BOOL bPopUp = TRUE;

   if (bAppendItems)
   {
      HMENU hParentMenu;

      // add popup
      if (bPopUp)
      {
         hParentMenu = ::CreateMenu();
      }
      else
      {
         // or not
         hParentMenu = hMenu;
      }

      if (hParentMenu) 
      {
         // pop-up title
         if (bPopUp)
         {        
            InsertMenu(hMenu, indexMenu++, MF_POPUP|MF_BYPOSITION, (UINT)hParentMenu, "Create hard-link");
            SetMenuItemBitmaps(hMenu, indexMenu-1, MF_BITMAP | MF_BYPOSITION, hbmp, hbmp);
         }

         InsertMenu(hParentMenu, indexMenu++, MF_STRING|MF_BYPOSITION, idCmd++, "Operation 1 using "SHELLEXNAME);
         InsertMenu(hParentMenu, indexMenu++, MF_STRING|MF_BYPOSITION, idCmd++, "Operation 2 using "SHELLEXNAME);
      }
                       
      return ResultFromShort(idCmd-idCmdFirst); //Must return number of menu
      //items we added.
   }*/
   return ResultFromShort(idCmd-idCmdFirst); //Must return number of menu
   
   return NOERROR;
}

////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////
STDMETHODIMP GetSelectedFiles(LPCITEMIDLIST pIDFolder,
                                   LPDATAOBJECT &pDataObj,
                                   CStringArray &csaPaths, CString& sDropTarget)
{
   // get these paths into a CStringArray
	if (pIDFolder != NULL) {
		LPSHELLFOLDER lpsf = NULL;
		SHGetDesktopFolder(&lpsf);

		LPMALLOC pMalloc;
		SHGetMalloc(&pMalloc);


		STRRET str;

		HRESULT hr = lpsf->GetDisplayNameOf((LPITEMIDLIST)pIDFolder, SHGDN_NORMAL | SHGDN_FORPARSING | SHGDN_FORADDRESSBAR, &str);
		if (!SUCCEEDED(hr))
        {
		 int x = 2;
		}
		else
        {
			if (str.uType == STRRET_WSTR)
            {
				sDropTarget = str.pOleStr;
				pMalloc->Free(str.pOleStr);
				pMalloc->Release();
			}
			else
            {
				sDropTarget = str.cStr;
			}
		}
	}
   
   csaPaths.RemoveAll();
   
	// fetch all of the file names we're supposed to operate on
   if (pDataObj) 
   {
	   pDataObj->AddRef();

	   STGMEDIUM medium;
	   FORMATETC fe = { CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL};


	   HRESULT hr = pDataObj->GetData (&fe, &medium);
	   if (FAILED (hr))
	   {
		   return E_FAIL;
	   }

	   // buffer to receive filenames
	   char path[MAX_PATH];

	   // how many are there?
	   UINT fileCount = DragQueryFile((HDROP)medium.hGlobal, 0xFFFFFFFF,
	   path, MAX_PATH);

	   if (fileCount>0)
	   {
		   // avoid wasting mem when this thing gets filled in
		   csaPaths.SetSize(fileCount);

		   // stash the paths in our CStringArray
		   for (UINT i=0;i<fileCount;i++) 
         {
			   // clear old path
			   memset(path, 0, MAX_PATH);
			   // fetch new path
			   if (DragQueryFile((HDROP)medium.hGlobal, i, path, MAX_PATH)) 
            {
 		         csaPaths.SetAt(i, path);
		      }
	      }

         csaPaths.FreeExtra();
      }

      // free our path memory - we have the info in our CStringArray
      ReleaseStgMedium(&medium);
   }

   return NOERROR;
}
