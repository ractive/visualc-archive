/*************************************************************************
                     JAGS
**************************************************************************

Copyright (C) July, 2001 Jean-Pierre Bergamin, james@ractive.ch

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

// DirectoryPicker.cpp: implementation of the CDirectoryPicker class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DirectoryPicker.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CString * CDirectoryPicker::m_sDirectory = NULL;

CDirectoryPicker::CDirectoryPicker(HWND hWnd, CString * sStartDir)
{
	m_sDirectory = sStartDir;
	m_hWnd = hWnd;
	BrowseFolder();
}

CDirectoryPicker::~CDirectoryPicker()
{

}

void CDirectoryPicker::BrowseFolder()
{
	LPMALLOC pMalloc;
            	
	LPITEMIDLIST pidl;
	// Get some memory for the ID-List SHBrowseForFolder will return
	if (SUCCEEDED(SHGetMalloc(&pMalloc))) {
		
		// The directory name will be in there.
		TCHAR szDisplayName[MAX_PATH] = "";
		BROWSEINFO binfo = {0};
		binfo.hwndOwner = m_hWnd; 
		// NULL means that the Desktop is the root.
		binfo.pidlRoot = NULL; 
		binfo.pszDisplayName = szDisplayName; 
		binfo.lpszTitle = "Please choose the folder that will be synchronized with the FTP-site"; 

		// BIF_RETURNONLYFSDIRS:	The OK button is only activated if we choose
		//							a filesystem directory
		// BIF_STATUSTEXT:			Show a status text.
		binfo.ulFlags = BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT; 

		// Set the callback function.
		binfo.lpfn = NULL; 
		binfo.lParam = 0;
		
		// Now display the dialog box where the user can choose the directory.
		pidl = SHBrowseForFolder(&binfo);

		if (pidl) {
			SHGetPathFromIDList(pidl,szDisplayName);
			*m_sDirectory = szDisplayName;
			pMalloc->Free(pidl);
			pMalloc->Release();
		}
		else {
			m_sDirectory->Empty();
		}
		
	}

}
