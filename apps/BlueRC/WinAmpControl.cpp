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


// WinAmpControl.cpp: implementation of the CWinAmpControl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Bluesson.h"
#include "FRONTEND.H"
#include "WinAmpControl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWinAmpControl * CWinAmpControl::m_pInstance = NULL;

CWinAmpControl * CWinAmpControl::GetInstance()
{
	if (m_pInstance == NULL) {
		m_pInstance = new CWinAmpControl();
	}

	return m_pInstance;
}

void CWinAmpControl::Destroy()
{
	if (m_pInstance != NULL) {
		delete m_pInstance;
		m_pInstance = NULL;
	}
}


CWinAmpControl::CWinAmpControl()
{
	m_hWinAmpWnd = NULL;
	GetWinampWnd();
}

CWinAmpControl::~CWinAmpControl()
{

}

void CWinAmpControl::Play()
{
	GetWinampWnd();
	SendMessage(m_hWinAmpWnd, WM_COMMAND, WINAMP_PLAY, 0);
}

void CWinAmpControl::PlayFile(LPCTSTR sFile)
{
	GetWinampWnd();

	if (m_hWinAmpWnd == NULL) {
		// If winamp is not started, we use Shell Execute to start it
		ShellExecute(NULL, "open", sFile, NULL, NULL, SW_SHOWNORMAL);	
	}
	else {
		COPYDATASTRUCT cds;
		cds.dwData = IPC_PLAYFILE;
		cds.lpData = (LPVOID)sFile;
		cds.cbData = strlen((char *) cds.lpData)+1; // include space for null char
		SendMessage(m_hWinAmpWnd,WM_COPYDATA,(WPARAM)NULL,(LPARAM)&cds);
	}
}

void CWinAmpControl::SetVolume(unsigned short nVol)
{
	GetWinampWnd();
	SendMessage(m_hWinAmpWnd, WM_WA_IPC, nVol, IPC_SETVOLUME);
}

void CWinAmpControl::SetPlaylistPos(int nPos)
{
	GetWinampWnd();
	SendMessage(m_hWinAmpWnd, WM_WA_IPC, nPos, IPC_SETPLAYLISTPOS);
}

void CWinAmpControl::AddToPlaylist(LPCTSTR sFile)
{
	GetWinampWnd();
	COPYDATASTRUCT cds;
	cds.dwData = IPC_PLAYFILE;
	cds.cbData = lstrlen(sFile) + 1;
	cds.lpData = (void *)sFile;
	SendMessage(m_hWinAmpWnd, WM_COPYDATA, (WPARAM)NULL, (LPARAM)&cds);
}

void CWinAmpControl::ChangeDir(LPCTSTR sDir)
{
	GetWinampWnd();
	COPYDATASTRUCT cds;
	cds.dwData = IPC_CHDIR;
	cds.lpData = (void *)sDir;
	cds.cbData = strlen((char *) cds.lpData)+1; // include space for null char
	SendMessage(m_hWinAmpWnd, WM_COPYDATA, (WPARAM)NULL, (LPARAM)&cds);
}

void CWinAmpControl::VolumeUp()
{
	GetWinampWnd();
	SendMessage(m_hWinAmpWnd, WM_COMMAND, WINAMP_VOLUMEUP, 0);
}

void CWinAmpControl::VolumeDown()
{
	GetWinampWnd();
	SendMessage(m_hWinAmpWnd, WM_COMMAND, WINAMP_VOLUMEDOWN, 0);
}

void CWinAmpControl::Previous()
{
	GetWinampWnd();
	SendMessage(m_hWinAmpWnd, WM_COMMAND, WINAMP_PREV, 0);
}

void CWinAmpControl::Next()
{
	GetWinampWnd();
	SendMessage(m_hWinAmpWnd, WM_COMMAND, WINAMP_NEXT, 0);
}

void CWinAmpControl::Pause()
{
	GetWinampWnd();
	SendMessage(m_hWinAmpWnd, WM_COMMAND, WINAMP_PAUSE, 0);
}

void CWinAmpControl::Stop()
{
	GetWinampWnd();
	SendMessage(m_hWinAmpWnd, WM_COMMAND, WINAMP_STOP, 0);
}

void CWinAmpControl::GetWinampWnd()
{
	if (m_hWinAmpWnd == NULL || !::IsWindow(m_hWinAmpWnd)) {
		m_hWinAmpWnd = FindWindow("Winamp v1.x",NULL);
	}
}

void CWinAmpControl::PlayLastSong()
{
	int winampPlayMode;
	int playListLen = 0;

	winampPlayMode = SendMessage(m_hWinAmpWnd, WM_USER, 0, 104);

	//if winampPlayMode is 3 than winamp is paused, so we need to start it
	if( winampPlayMode == 3 ) {
		// start it playing where it currently is (it has to be in play mode for the 
		// play list pointer to be moved right, or so it seems)
		SendMessage(m_hWinAmpWnd, WM_WA_IPC, 0, IPC_STARTPLAY ); 
	}

	// figure out how big the play list is
	playListLen = SendMessage(m_hWinAmpWnd, WM_WA_IPC, 0, IPC_GETLISTLENGTH );

	// move to the end of the list
	SendMessage(m_hWinAmpWnd, WM_WA_IPC, playListLen, IPC_SETPLAYLISTPOS );

	// and hit play
	SendMessage(m_hWinAmpWnd, WM_COMMAND, WINAMP_PLAY, 0 ); // play button
}

void CWinAmpControl::ClearPlayList()
{
	GetWinampWnd();

	SendMessage(m_hWinAmpWnd, WM_WA_IPC, 0, IPC_DELETE);	
}

int CWinAmpControl::GetListLength()
{
	GetWinampWnd();

	return SendMessage(m_hWinAmpWnd, WM_WA_IPC, 0, IPC_GETLISTLENGTH);
}

char* CWinAmpControl::GetListTitle(int nIndex)
{
	GetWinampWnd();

	return (char *)SendMessage(m_hWinAmpWnd, WM_WA_IPC, nIndex, IPC_GETPLAYLISTTITLE);
}

int CWinAmpControl::GetListPos()
{
	GetWinampWnd();

	return SendMessage(m_hWinAmpWnd, WM_WA_IPC, 0, IPC_GETLISTPOS);
}

BOOL CWinAmpControl::IsPlaying()
{
	GetWinampWnd();

	return SendMessage(m_hWinAmpWnd,WM_WA_IPC,0,IPC_ISPLAYING) == 1;
}

BOOL CWinAmpControl::IsPaused()
{
	GetWinampWnd();

	return SendMessage(m_hWinAmpWnd,WM_WA_IPC,0,IPC_ISPLAYING) == 3;
}

BOOL CWinAmpControl::IsStopped()
{
	GetWinampWnd();

	return SendMessage(m_hWinAmpWnd,WM_WA_IPC,0,IPC_ISPLAYING) == 0;
}

CString CWinAmpControl::GetCurrentSong(CString * psArtist /* = NULL */)
{
	GetWinampWnd();
	SendMessage(m_hWinAmpWnd, WM_WA_IPC, 0, IPC_UPDTITLE);
	CString sTitle;
	GetWindowText(m_hWinAmpWnd, sTitle.GetBuffer(512), 512);
	sTitle.ReleaseBuffer();
	sTitle = sTitle.Left(sTitle.Find(" - Winamp"));
	sTitle = sTitle.Mid(sTitle.Find(" ") + 1);
	int nPos = sTitle.Find(" - ") + 3;
	if (nPos < sTitle.GetLength()) {
		if (psArtist != NULL && nPos - 3 > 1) {
			*psArtist = sTitle.Left(nPos - 3);
			psArtist->TrimLeft();
			psArtist->TrimRight();
		}
		sTitle = sTitle.Mid(nPos);
	}
	return sTitle;
}


BOOL CWinAmpControl::IsRunning()
{
	GetWinampWnd();

	return m_hWinAmpWnd != NULL;
}

void CWinAmpControl::Close()
{
	GetWinampWnd();
	
	SendMessage(m_hWinAmpWnd, WM_COMMAND, WINAMP_CLOSE, 0);
}


int CWinAmpControl::GetSampleRate()
{
	GetWinampWnd();
	
	return SendMessage(m_hWinAmpWnd, WM_WA_IPC, 0, IPC_GETINFO);
}

int CWinAmpControl::GetBitRate()
{
	GetWinampWnd();
	
	return SendMessage(m_hWinAmpWnd, WM_WA_IPC, 1, IPC_GETINFO);
}

int CWinAmpControl::GetChannels()
{
	GetWinampWnd();
	
	return SendMessage(m_hWinAmpWnd, WM_WA_IPC, 2, IPC_GETINFO);
}

void CWinAmpControl::GotoStartPlaylist()
{
	GetWinampWnd();

	SendMessage(m_hWinAmpWnd, WM_COMMAND, WINAMP_START_PLAYLIST, 0 );
}

CString CWinAmpControl::GetSongLength()
{
	GetWinampWnd();
	
	int nSeconds = GetSongLengthSeconds();
	if (nSeconds == -1) {
		return "????";
	}
	
	CString sLength;
	sLength.Format("%02d:%02d", nSeconds / 60, nSeconds % 60);

	return sLength;
}

int CWinAmpControl::GetSongLengthSeconds()
{
	GetWinampWnd();
	
	return SendMessage(m_hWinAmpWnd, WM_WA_IPC, 1, IPC_GETOUTPUTTIME);
}


int CWinAmpControl::GetCurrentPosition()
{
	GetWinampWnd();
	
	return SendMessage(m_hWinAmpWnd, WM_WA_IPC, 0, IPC_GETOUTPUTTIME);
}

void CWinAmpControl::FFWD()
{
	GetWinampWnd();

	SendMessage(m_hWinAmpWnd, WM_COMMAND, WINAMP_FFWD, 0 );
}

void CWinAmpControl::FREW()
{
	GetWinampWnd();

	SendMessage(m_hWinAmpWnd, WM_COMMAND, WINAMP_FREW, 0 );

}

int CWinAmpControl::JumpTo(int nMilliSeconds)
{
	GetWinampWnd();
	
	return SendMessage(m_hWinAmpWnd, WM_WA_IPC, nMilliSeconds, IPC_JUMPTOTIME);
}

BOOL CWinAmpControl::IsShuffleSet()
{
	GetWinampWnd();
	
	return SendMessage(m_hWinAmpWnd, WM_WA_IPC, 0, IPC_GET_SHUFFLE);
}

BOOL CWinAmpControl::IsRepeatSet()
{
	GetWinampWnd();
	
	return SendMessage(m_hWinAmpWnd, WM_WA_IPC, 0, IPC_GET_REPEAT);
}

void CWinAmpControl::SetShuffle(BOOL bSet)
{
	GetWinampWnd();
	
	SendMessage(m_hWinAmpWnd, WM_WA_IPC, bSet, IPC_SET_SHUFFLE);
}

void CWinAmpControl::SetRepeat(BOOL bSet)
{
	GetWinampWnd();
	
	SendMessage(m_hWinAmpWnd, WM_WA_IPC, bSet, IPC_SET_REPEAT);
}
