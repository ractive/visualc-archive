/************************************************************
Module name: FileLink.cpp
Written by: Armin Gerritsen
************************************************************/

#include "stdafx.h" //Useless, but VCC++ wants it unless I change the project-settings


//#define _WIN32_WINNT 0x0500 //NOT if we want to use it for NT 4 too

//#define STRICT
//#define offsetof(t,m) ((size_t) &(((t *) 0)->m))



#include <windows.h>
#include <stdio.h>
#include <winioctl.h>
#include <tchar.h>

#pragma comment( lib, "advapi32.lib" )

extern "C"
{
 typedef BOOL (__stdcall *DLLCreateHardLink)( LPCTSTR toFile, LPCTSTR fromFile, LPSECURITY_ATTRIBUTES sa );
}


/*
	//Internals
	BOOL  CreateLink(char*, char*, DWORD& ) ;
	BOOL  NT4CreateHardLink( char*, char*, DWORD& ) ;
	BOOL  EnablePrivs( DWORD& ) ;
*/
#include "Filelink.h"

/////////////////////////////////////////////////////////////



BOOL CreateLink(const char *szSource, const char *szTarget, DWORD &dwError )
{
 /* This function first tries if an API call exist (Windows NT 5),
    else it tries a manual link. */
 
 DLLCreateHardLink pfCreateHardLink  ;  // Pointer to the CreateHardLink() function if it exists
 
 // First load kernel-module
 HMODULE hKern32 = LoadLibrary( _T( "kernel32.dll" ) ) ;
 if ( hKern32 > (HMODULE)32 )		// Load succeded
 {
  pfCreateHardLink = (DLLCreateHardLink) GetProcAddress( hKern32, "CreateHardLinkA" ) ;
  if ( NULL != pfCreateHardLink )  	// API call exist
  {
   if ( !pfCreateHardLink( szSource, szTarget, NULL ) )
   {
    // API call failed
    dwError = GetLastError() ;
    FreeLibrary( hKern32 ) ;
    return FALSE ;
   }
   //API call succeded
   FreeLibrary( hKern32 ) ;
   return TRUE ;
  }
  else 					// No API call exists
  {
   // Do manual link, because API call doesn't exist
   if ( !NT4CreateHardLink( szTarget, szSource, dwError ) )
    return FALSE ;			// Manual link failed
   return TRUE ;			// Manual link succeded
  }
 }
 else					// Failed to load kernel32.dll
 {
  dwError = GetLastError() ;
  return FALSE ;
 }
}


BOOL NT4CreateHardLink( const char *szSource, const char *szTarget, DWORD &dwError )
{
 // Check if target exists. If so abort, even though link-creation could succede.
 // This is done to get the same behaviour as with the API CreateHardLink call.
 HANDLE fh = CreateFile( szTarget, 0, 0, NULL, OPEN_EXISTING, 0, NULL ) ;
 if ( fh != INVALID_HANDLE_VALUE )
 {
  CloseHandle( fh ) ;
  dwError = ERROR_ALREADY_EXISTS ; 	// =183
  return FALSE ;
 }
 
 
 // In case we aren't admin ...
 EnablePrivs( dwError ) ;
 
 
 //Open source file
 fh = CreateFile( szSource, GENERIC_READ, 0, NULL, OPEN_EXISTING, //not GENERIC_WRITE
                  FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_POSIX_SEMANTICS, NULL ) ;
 if ( fh == INVALID_HANDLE_VALUE )
 {
  dwError = GetLastError() ;
  return FALSE ;
 }
 
  
 // Do some preparations ...
 static char      buf1[MAX_PATH] ;
 static wchar_t   buf2[MAX_PATH * 2] ;
 WIN32_STREAM_ID  wsi ;
 char   	  *p ;
 
 GetFullPathName( szTarget, MAX_PATH, &buf1[0], &p ) ;
 wsi.dwStreamId         = BACKUP_LINK ;
 wsi.dwStreamAttributes = 0 ;
 wsi.dwStreamNameSize   = 0 ;
 MultiByteToWideChar( CP_ACP, 0, buf1, strlen( buf1 ) + 1, buf2, MAX_PATH ) ;
 wsi.Size.QuadPart = ( wcslen( buf2 ) + 1 ) * sizeof( wchar_t ) ;
 
 
 // Make link
 void  *ctx       = NULL ;
 DWORD numwritten = 0 ;
 if ( !BackupWrite( fh, (byte*) &wsi, offsetof( WIN32_STREAM_ID, cStreamName ), &numwritten, FALSE, FALSE, &ctx ) )
 {
  dwError = GetLastError() ;
  return FALSE ;
 }
 if ( numwritten != offsetof( WIN32_STREAM_ID, cStreamName ) )
 {
  dwError = GetLastError() ;
  return FALSE ;
 }
 if ( ! BackupWrite( fh, (byte *) buf2, wsi.Size.LowPart, &numwritten, FALSE, FALSE, &ctx ) )
 {
  dwError = GetLastError() ;
  return FALSE ;
 }
 if ( numwritten != wsi.Size.LowPart )
 {
  dwError = GetLastError() ;
  return FALSE ;
 }
 
 
 // Cleanup
 BackupWrite( fh, (byte *) &buf1[0], 0, &numwritten, TRUE, FALSE, &ctx ) ;
 CloseHandle( fh ) ;

 return TRUE ;
}


BOOL EnablePrivs( DWORD &dwError )
{
 HANDLE hToken ;
 byte buf[sizeof TOKEN_PRIVILEGES * 2] ;
 TOKEN_PRIVILEGES & tkp = *( (TOKEN_PRIVILEGES *) buf ) ;
 
 if ( ! OpenProcessToken( GetCurrentProcess(),
	TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken ) )
 {
  dwError = GetLastError() ;
  return FALSE ;
 }

 // Enable SeBackupPrivilege, SeRestorePrivilege
 if ( !LookupPrivilegeValue( NULL, SE_BACKUP_NAME, &tkp.Privileges[0].Luid ) )
 {
  dwError = GetLastError() ;
  return FALSE ;
 }
 if ( !LookupPrivilegeValue( NULL, SE_RESTORE_NAME, &tkp.Privileges[1].Luid ) )
 {
  dwError = GetLastError() ;
  return FALSE ;
 }
 
 // Now adjust it
 tkp.PrivilegeCount = 2;
 tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
 tkp.Privileges[1].Attributes = SE_PRIVILEGE_ENABLED;
 if ( ! AdjustTokenPrivileges( hToken, FALSE, &tkp, sizeof tkp, NULL, NULL ) )
 {
  dwError = GetLastError() ;
  return FALSE ;
 }

 return TRUE ;
}

BOOL RemoveJunctionPoint(PTCHAR pszLink)
{
	BOOL bResult = FALSE;
	TCHAR szLink[MAX_PATH];
	PTCHAR pszFilePart;
	char reparseBuffer[1024];
	PREPARSE_DATA_BUFFER reparseInfo = (PREPARSE_DATA_BUFFER)reparseBuffer;

	if (GetFullPathName(pszLink, MAX_PATH, szLink, &pszFilePart))
	{
		HANDLE hFile;

		hFile = CreateFile(szLink, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_OPEN_REPARSE_POINT | FILE_FLAG_BACKUP_SEMANTICS, NULL);
		if (hFile != INVALID_HANDLE_VALUE)
		{
			DWORD	dwLength = 0;

			ZeroMemory(reparseBuffer, sizeof(reparseBuffer));
			reparseInfo->ReparseTag = IO_REPARSE_TAG_MOUNT_POINT;
			reparseInfo->ReparseDataLength = 0;
			reparseInfo->Reserved = 0;

			if (DeviceIoControl(hFile, FSCTL_DELETE_REPARSE_POINT, (LPVOID)reparseInfo, REPARSE_GUID_DATA_BUFFER_HEADER_SIZE, NULL, 0, &dwLength, NULL))
			{
				bResult = TRUE;
			}

			CloseHandle(hFile);

			if (bResult) RemoveDirectory(pszLink);
		}
	}

	return bResult;
}

BOOL CreateJunction(PTCHAR pszLink, PTCHAR pszTarget)
{
	BOOL bResult = FALSE;
	TCHAR szTarget[MAX_PATH];
	TCHAR szLink[MAX_PATH];
	WCHAR wszTargetNativeFilename[MAX_PATH];
	PTCHAR pszFilePart;
	char reparseBuffer[1024];
	PREPARSE_DATA_BUFFER reparseInfo = (PREPARSE_DATA_BUFFER)reparseBuffer;
	int nDestBytes;

	ZeroMemory(&wszTargetNativeFilename, sizeof(wszTargetNativeFilename));
	if (GetFullPathName(pszTarget, MAX_PATH, szTarget, &pszFilePart))
	{
		if (GetFullPathName(pszLink, MAX_PATH, szLink, &pszFilePart))
		{
			HANDLE hFile;

			CreateDirectory(szLink, NULL);
			hFile = CreateFile(szLink, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_OPEN_REPARSE_POINT | FILE_FLAG_BACKUP_SEMANTICS, NULL);
			if (hFile != INVALID_HANDLE_VALUE)
			{
				DWORD	dwLength = 0;

				wsprintfW(wszTargetNativeFilename, L"\\??\\%s", CString(szTarget));
				nDestBytes = lstrlenW(wszTargetNativeFilename) * sizeof(WCHAR);
				ZeroMemory(reparseBuffer, sizeof(reparseBuffer));
				reparseInfo->ReparseTag = IO_REPARSE_TAG_MOUNT_POINT;
				reparseInfo->ReparseDataLength = nDestBytes + 12;
				reparseInfo->Reserved = 0;
				reparseInfo->SymbolicLinkReparseBuffer.SubstituteNameOffset = 0;
				reparseInfo->SymbolicLinkReparseBuffer.SubstituteNameLength = nDestBytes;
				reparseInfo->SymbolicLinkReparseBuffer.PrintNameOffset = nDestBytes + 2;
				reparseInfo->SymbolicLinkReparseBuffer.PrintNameLength = 0;
				lstrcpyW(reparseInfo->SymbolicLinkReparseBuffer.PathBuffer, wszTargetNativeFilename);

				if (DeviceIoControl(hFile, FSCTL_SET_REPARSE_POINT, (LPVOID)reparseInfo, reparseInfo->ReparseDataLength + REPARSE_DATA_BUFFER_HEADER_SIZE, NULL, 0, &dwLength, NULL))
				{
					bResult = TRUE;
				}
				CloseHandle(hFile);
			}
		}
	}

	return bResult;
}
