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


#ifndef SHELLEXTDEFSH
#define SHELLEXTDEFSH

// this class factory object creates context menu handlers for Windows 95 shell
class CShellExtClassFactory : public IClassFactory
{
protected:
	ULONG        m_cRef;


public:
	CShellExtClassFactory();
	~CShellExtClassFactory();

	//IUnknown members
	STDMETHODIMP			QueryInterface(REFIID, LPVOID FAR *);
	STDMETHODIMP_(ULONG)	AddRef();
	STDMETHODIMP_(ULONG)	Release();

	//IClassFactory members
	STDMETHODIMP		CreateInstance(LPUNKNOWN, REFIID, LPVOID FAR *);
	STDMETHODIMP		LockServer(BOOL);

};
typedef CShellExtClassFactory *LPCSHELLEXTCLASSFACTORY;

// this is the actual OLE Shell context menu handler
class CShellExt : public IContextMenu, 
                         IShellExtInit
{
public:
  

protected:
	ULONG			   m_cRef;
	LPDATAOBJECT	m_pDataObj;

   // CShellExt::Initialize fills this with the paths to the
   // files that were selected when the user chose our menu item.
	CStringArray	m_csaPaths;
	CString			m_sDropTarget;

   // our menu bitmap
   CBitmap        m_menuBmp;
	//////////////////////////////////////////////////////////////////

protected:

public:
	// generic shell ext functions
	CShellExt();
	~CShellExt();

	//IUnknown members
	STDMETHODIMP			QueryInterface(REFIID, LPVOID FAR *);
	STDMETHODIMP_(ULONG)	AddRef();
	STDMETHODIMP_(ULONG)	Release();

   //IShellExtInit methods
	STDMETHODIMP		    Initialize(LPCITEMIDLIST pIDFolder, 
                                          LPDATAOBJECT pDataObj, 
                                          HKEY hKeyID);

	//IShell members

   //////////////////////////////////////////////////////////////
   //
   // These are the only functions you really need to modify. They
   // are all in ShellCtxMenu.cpp
   
   //
   // called to get menu item strings for Explorer
   //
	STDMETHODIMP			QueryContextMenu(HMENU hMenu,
                                          UINT indexMenu, 
                                          UINT idCmdFirst,
                                          UINT idCmdLast, 
                                          UINT uFlags);
   //
   // called after a menu item has been selected
   //
	STDMETHODIMP			InvokeCommand(LPCMINVOKECOMMANDINFO lpcmi);

   //
   // fetch various strings for Explorer
   //
	STDMETHODIMP			GetCommandString(UINT idCmd, 
                                          UINT uFlags, 
                                          UINT FAR *reserved, 
                                          LPSTR pszName, 
                                          UINT cchMax);

   //
   //
   //////////////////////////////////////////////////////////////
   
};
typedef CShellExt *LPCSHELLEXT;


#endif