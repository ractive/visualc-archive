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
#include "priv.h"
#include "ShellExt.h"
#include "HardLinker.h"

#include "Filelink.h"

#include <winbase.h>
#include <shlobj.h>
#include <shlguid.h>
#include "io.h"

// utilities
#include "ShUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*----------------------------------------------------------------

  FUNCTION: CShellExt::InvokeCommand(LPCMINVOKECOMMANDINFO)

  PURPOSE: Called by the shell after the user has selected on of the
           menu items that was added in QueryContextMenu(). This is 
           the function where you get to do your real work!!!

  PARAMETERS:
    lpcmi - Pointer to an CMINVOKECOMMANDINFO structure

  RETURN VALUE:


  COMMENTS:
 
----------------------------------------------------------------*/

STDMETHODIMP CShellExt::InvokeCommand(LPCMINVOKECOMMANDINFO lpcmi)
{
	// look at all the MFC stuff in here! call this to allow us to 
	// not blow up when we try to use it.
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

	HINSTANCE hInst = AfxGetInstanceHandle();

    ODS("CShellExt::InvokeCommand()\r\n");

	HWND hParentWnd = lpcmi->hwnd;
                                      
	HRESULT hr = NOERROR;

    //If HIWORD(lpcmi->lpVerb) then we have been called programmatically
    //and lpVerb is a command that should be invoked.  Otherwise, the shell
    //has called us, and LOWORD(lpcmi->lpVerb) is the menu ID the user has
    //selected.  Actually, it's (menu ID - idCmdFirst) from QueryContextMenu().
	UINT idCmd = 0;

   if (!HIWORD(lpcmi->lpVerb)) 
   {
		CString sError;
		// process it
		for (int i = 0; i < m_csaPaths.GetSize(); i++)
        {
			CFileFind finder;
			if (!finder.FindFile(m_csaPaths.GetAt(i))) {
				sError = TEXT("File ") + m_csaPaths.GetAt(i) + TEXT(" not found!");
				continue;
			}
			finder.FindNextFile();
			if (finder.IsDirectory()) {
				sError = m_csaPaths.GetAt(i) + TEXT(" is a direcory\n\nYou only can create hardlinks on normal files!");
				continue;
			}
			CString sFile = finder.GetFileName();
			
			CString sLinkName;
			if (m_sDropTarget.IsEmpty()) {
				m_sDropTarget = finder.GetFilePath();
				m_sDropTarget = m_sDropTarget.Left(m_sDropTarget.ReverseFind('\\'));
			}
			
			sLinkName = m_sDropTarget;
			
			if (!m_sDropTarget.IsEmpty() && (sLinkName.Right(1) != "\\"))
				sLinkName += "\\";
			int nPos = sFile.ReverseFind('.');
			CString sEnding;
			if (nPos != -1)
				sEnding = sFile.Mid(nPos);

			sLinkName += finder.GetFileTitle() + ".hlnk" + sEnding;

			// Ask the user for the name of the new file.
			OPENFILENAME openfilename;
			openfilename.lStructSize = sizeof(OPENFILENAME);
			openfilename.hwndOwner = lpcmi->hwnd;
			openfilename.hInstance = AfxGetInstanceHandle();
			openfilename.lpstrFilter = NULL;
			openfilename.lpstrCustomFilter = NULL;
			openfilename.nMaxCustFilter = 0;
			openfilename.nFilterIndex = 0;
			openfilename.lpstrFile = sLinkName.GetBuffer(_MAX_FNAME);;
			openfilename.nMaxFile = MAX_PATH;
			openfilename.lpstrFileTitle = NULL;
			openfilename.nMaxFileTitle = 0;
			openfilename.lpstrInitialDir = m_sDropTarget /*.GetBuffer(_MAX_DIR)*/;
			openfilename.lpstrTitle = "Hard link name ...";
			openfilename.Flags = OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY;
			openfilename.nFileOffset = 0;
			openfilename.nFileExtension = 0;
			openfilename.lpstrDefExt = sEnding.Mid(1)	;
			openfilename.lCustData = 0;
			openfilename.lpfnHook = NULL;
			openfilename.lpTemplateName = NULL;
			BOOL ans = GetSaveFileName(&openfilename);
            
			sLinkName.ReleaseBuffer();
			//m_sDropTarget.ReleaseBuffer();
			
			if (ans != IDOK)
            {
			 continue ;
			}
            

			// Now the big deal about all this :-)
			// Create the HardLink....
            DWORD dwError = 0 ;
            if ( !CreateLink( LPCTSTR(sLinkName), LPCTSTR(m_csaPaths.GetAt(i)), dwError) )
            {
             sError.Format("Could not create hard link!\n\nError: %d\n", dwError);
			 if (dwError == 1)
             {
			  sError += "You only can create hardlinks on NTFS volumes!" ;
			 }
			 else
             {
			  LPVOID lpMsgBuf;
			  FormatMessage( 
					        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
					        FORMAT_MESSAGE_FROM_SYSTEM | 
					        FORMAT_MESSAGE_IGNORE_INSERTS,
					        NULL,
					        dwError,
					        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
					        (LPTSTR) &lpMsgBuf,
					        0,
					        NULL 
			               );
                  
               // Display the string.
			   sError += "Correspoding Windows error message:\n\n";
			   sError += (LPCTSTR)lpMsgBuf;

			   // Free the buffer.
			   LocalFree( lpMsgBuf ) ;
			  }
			}
            
			if ( !sError.IsEmpty() )
            {
			 MessageBox(lpcmi->hwnd, sError, "ERROR", MB_OK | MB_ICONEXCLAMATION) ;
			 continue;
			}

		} //end for-loop

	}
   
   return hr;
}


////////////////////////////////////////////////////////////////////////
//
//  FUNCTION: CShellExt::GetCommandString(...)
//
//  PURPOSE: Retrieve various text strinsg associated with the context menu
//
//	Param			Type			Use
//	-----			----			---
//	idCmd			UINT			ID of the command
//	uFlags			UINT			which type of info are we requesting
//	reserved		UINT *			must be NULL
//	pszName			LPSTR			output buffer
//	cchMax			UINT			max chars to copy to pszName
//
////////////////////////////////////////////////////////////////////////

STDMETHODIMP CShellExt::GetCommandString(UINT idCmd,
                                         UINT uFlags,
                                         UINT FAR *reserved,
                                         LPSTR pszName,
                                         UINT cchMax)
{
   ODS("CShellExt::GetCommandString()\r\n");
	
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

	HINSTANCE hInst = AfxGetInstanceHandle();

	switch (uFlags) 
   {
	case GCS_HELPTEXT:		// fetch help text for display at the bottom of the 
							// explorer window
		switch (idCmd)
		{
			case 0:
            strncpy(pszName, "Do something to the selected file(s)", cchMax);
				break;
			case 1:
            strncpy(pszName, "Do something else to the selected file(s)", cchMax);
				break;
         default:
            strncpy(pszName, SHELLEXNAME, cchMax);
				break;
		}
		break;

	case GCS_VALIDATE:
		break;

	case GCS_VERB:			// language-independent command name for the menu item 
		switch (idCmd)
		{
			case 0:
            strncpy(pszName, "Operation1", cchMax);
				break;
			case 1:
            strncpy(pszName, "Operation2", cchMax);
				break;
         default:
            strncpy(pszName, SHELLEXNAME, cchMax);
				break;
		}

		break;
	}
    return NOERROR;
}

///////////////////////////////////////////////////////////////////////////
//
//  FUNCTION: CShellExt::QueryContextMenu(HMENU, UINT, UINT, UINT, UINT)
//
//  PURPOSE: Called by the shell just before the context menu is displayed.
//           This is where you add your specific menu items.
//
//  PARAMETERS:
//    hMenu      - Handle to the context menu
//    indexMenu  - Index of where to begin inserting menu items
//    idCmdFirst - Lowest value for new menu ID's
//    idCmtLast  - Highest value for new menu ID's
//    uFlags     - Specifies the context of the menu event
//
//  RETURN VALUE:
//
//
//  COMMENTS:
//
///////////////////////////////////////////////////////////////////////////

STDMETHODIMP CShellExt::QueryContextMenu(HMENU hMenu,
                                         UINT indexMenu,
                                         UINT idCmdFirst,
                                         UINT idCmdLast,
                                         UINT uFlags)
{
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   return CreateShellExtMenu(hMenu, 
                              indexMenu, 
                              idCmdFirst, 
                              idCmdLast, 
                              uFlags, 
                              (HBITMAP)m_menuBmp.GetSafeHandle());
}

