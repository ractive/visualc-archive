/*************************************************************************
  Bluesson
**************************************************************************

Copyright (C) June 2002 by Jean-Pierre Bergamin

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


// EricssonAT.cpp: implementation of the CEricssonAT class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Bluesson.h"
#include "EricssonAT.h"
#include "WinAmpControl.h"
#include "KeystrokeEngine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEricssonAT * CEricssonAT::m_pPseudoThis = NULL;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEricssonAT::CEricssonAT()
{
	m_sInputBuf = new TCHAR[1024];
	ResetInputBuffer();

	m_bSetPos = FALSE;

	m_nPlayListPage = 0;

	m_nTimerID = 0;

	m_pPseudoThis = this;
}

CEricssonAT::~CEricssonAT()
{
	delete [] m_sInputBuf;
}

BOOL CEricssonAT::Receive(CString &sStatus)
{
	Sleep(10);
	CWinAmpControl * pWACtrl = CWinAmpControl::GetInstance();

	
	BOOL bRet = TRUE;

	DWORD dwRead = ReadBufferFromCom(m_pInputBuf, InBufferLength());
	if (!dwRead) {
		UnleashDaemon();
		return FALSE;
	}

	m_pInputBuf += dwRead;

	TCHAR * pCursor = m_sInputBuf;
	CString sLine;

	// Add all received lines to a CStringList
	// This simplifies parsing
	CStringList saLines;
	while(*pCursor) {
		if (*pCursor == '\r') {
			if (!sLine.IsEmpty()) {
				saLines.AddTail(sLine);
				sLine.Empty();
			}

			while(*pCursor && (*pCursor == '\n' || *pCursor == '\r')) {
				pCursor++;
			}
			continue;
		}
		sLine += *pCursor++;
	}

	if (saLines.GetCount()) {
		TRACE("RECEIVED: %s\r\n", m_sInputBuf);

		CString sTail = saLines.GetTail();
		// Here we check if a complete answer was received
		if (sTail == "OK") {
			if (saLines.Find("ERICSSON  ")) {
				// The phone connected is an Ericsson.
				// Set the Accessory menu
				AddAccessoryMenu("MediaPlayer RC");
				sStatus += " - Phone found";
			}

			// Reset the input buffer for the next command
			ResetInputBuffer();
		}
		// Here we check if an error was received
		else if (sTail == "ERROR") {
			// Reset the input buffer for the next command
			ResetInputBuffer();

			bRet = FALSE;
		}
		else if (sTail == "*EAAI") {
			// The user entered the accessory menu
			ShowMenu();
			ResetInputBuffer();
		}
		else if (sTail.Left(6) == "*EAMI:") {
			// The user chose an item in the main accessory menu
			BOOL bShowMenu = TRUE;
			int nSel = 0;
			sscanf(sTail, "*EAMI: %d", &nSel);
			
			CKeystrokeEngine eng;
			eng.SetSendToWnd (TRUE);
			eng.SetCaseSensitive (FALSE);
			eng.SetExactMatch (TRUE);
			eng.SetPause (FALSE, 0);
			eng.SetReActivate (TRUE, 0);
			eng.SetWndClass ("WMPlayerApp");
			eng.SetWndTitle ("");

			switch (nSel) {
				case 1:
					// Volume --
					eng.SetKeys("<F9>");
					break;
				case 2:
					// Volume set
					eng.SetKeys("<F8>");
					break;
				case 3:
					// Volume ++
					eng.SetKeys("<F10>");
					break;
				case 4:
					// Previous
					eng.SetKeys("<CTRL>b");
					break;
				case 5: {
					//FullScreen
					eng.SetKeys("<ALT><ENTER>");
					break;
				}
				case 6:
					// Next
					eng.SetKeys("<CTRL>f");
					break;
				case 7:
					// Play
					eng.SetKeys("<CTRL>p");
					break;
				case 8:
					// Pause
					eng.SetKeys("<CTRL>p");
					break;
				case 9:
					// Stop
					eng.SetKeys("<CTRL>s");
					break;
			}
			
			eng.SendKeys();

			if (bShowMenu) {
				ShowMenu(nSel);
			}

			ResetInputBuffer();
		}
		else if (sTail.Left(6) == "*EAII:") {
			// The user replied on a dialog
			int nSel = 0, nType = 0;
			sscanf(sTail, "*EAII: %d,%d", &nType, &nSel);
			
			if (nType == 15) {
				// A change in the percentage setting was made
				if (m_bSetPos) {
					int nGoto = pWACtrl->GetSongLengthSeconds() * 10 * nSel;

					if (pWACtrl->JumpTo(nGoto) == 1 || nSel == 100) {
						pWACtrl->Next();
						SetPosDlg();
					}
				}
				else {
					pWACtrl->SetVolume((USHORT)(nSel * 2.55));
				}
			}

			ResetInputBuffer();

			if (nType == 4) {
				if (m_nTimerID != 0) {
					KillTimer(NULL, m_nTimerID);
					m_nTimerID = 0;
				}
				ShowMenu(m_bSetPos ? 14: 2);
			}
			else if (nType == 14) {
				ShowMenu(10);
			}
			else if (nType == 5) {
				if (nSel == 1 && m_nPlayListPage > 0) {
					m_nPlayListPage--;
					FillPlayList();
				}
				else if (nSel == 12) {
					m_nPlayListPage++;
					FillPlayList();
				}
				else {
					pWACtrl->SetPlaylistPos(nSel - 1 + m_nPlayListPage * 10);
					pWACtrl->Play();
				}
				ShowMenu(5);
			}
		}
		else if (sTail == "*EAAI") {
			ResetInputBuffer();
		}
		else {
			SetErrorMode(TRUE);
		}
	}

	UnleashDaemon();

	return bRet;
}

void CEricssonAT::CheckForPhone()
{
	TCHAR buf[] = "ATE0+CGMI\r\n";
	WriteBufferToCom(buf, strlen(buf));
}

void CEricssonAT::AddAccessoryMenu(LPCTSTR sTitle)
{
	TCHAR buf[32];
	sprintf(buf, "AT*EAM=\"%s\"\r\n", sTitle);
	WriteBufferToCom(buf, strlen(buf));
}

void CEricssonAT::ResetInputBuffer()
{
	memset(m_sInputBuf, 0, 1024);
	m_pInputBuf = m_sInputBuf;
}

void CEricssonAT::AddSubMenu(CString sTitle, int nSelectedItem, CStringArray &saMenuItems, int nNextState /* = 1 */)
{
	CString sATCommand;
	int nSize = saMenuItems.GetSize();

	sATCommand.Format("AT*EASM=\"%s\",%d,%d,%d", sTitle, nNextState, nSelectedItem, nSize);

	if (nSize) {
		sATCommand += ",";
		for (int i = 0; i < nSize - 1; i++) {
			sATCommand += "\"" + saMenuItems.GetAt(i).Left(15) + "\",";
		}
		
		sATCommand += "\"" + saMenuItems.GetAt(i).Left(15) + "\"";
	}

	sATCommand += "\r\n";

	WriteBufferToCom((LPTSTR)(LPCTSTR)sATCommand, sATCommand.GetLength());
}

CString CEricssonAT::GetMenuTitle()
{
	CWinAmpControl * pWACtrl = CWinAmpControl::GetInstance();

	CString sTitle;

	sTitle.Format("%d.%s", pWACtrl->GetListPos() + 1, pWACtrl->GetCurrentSong());

	return sTitle.Left(15);
}

void CEricssonAT::PercentageDlg(CString sTitle, int nSteps, int nInitialStep, int nNextState)
{
	CString sATCommand;
	sATCommand.Format("AT*EAID=4,%d,\"%s\",%d,%d\r\n", nNextState, sTitle.Left(15), nSteps, nInitialStep);
	WriteBufferToCom((LPTSTR)(LPCTSTR)sATCommand, sATCommand.GetLength());
}

void CEricssonAT::ShowMenu(int nInitialSelection /* = 1 */)
{
	if (m_nTimerID != 0) {
		KillTimer(NULL, m_nTimerID);
		m_nTimerID = 0;
	}

	CWinAmpControl * pWACtrl = CWinAmpControl::GetInstance();

	CStringArray saMenu;

	saMenu.Add("Volume -");
	saMenu.Add("Mute");
	saMenu.Add("Volume +");

	saMenu.Add("Previous");
	saMenu.Add("Fullscreen");
	saMenu.Add("Next");
	saMenu.Add("Play");
	saMenu.Add("Pause");
	saMenu.Add("Stop");

	saMenu.Add("Song info");

	AddSubMenu("Media Player", nInitialSelection, saMenu);
}


void CEricssonAT::InfoDlg(CString sTitle, CString sText, int nNextState)
{
	CString sATCommand;
	sATCommand.Format("AT*EAID=14,%d,\"%s\",\"%s\"\r\n", nNextState, sTitle.Left(15), sText);
	//sATCommand = "AT*EAID=11,1,\"Titel\",\"Enter:\",20\r\n";
	WriteBufferToCom((LPTSTR)(LPCTSTR)sATCommand, sATCommand.GetLength());	
}

void CEricssonAT::SetErrorMode(BOOL bVerbose)
{
	if (m_bErrorModeSet) {
		return;
	}

	CString sATCommand;
	sATCommand.Format("AT+CMEE=");
	sATCommand += bVerbose ? "2" : "0";
	sATCommand += "\r\n";
	WriteBufferToCom((LPTSTR)(LPCTSTR)sATCommand, sATCommand.GetLength());

	m_bErrorModeSet = TRUE;
}

void CEricssonAT::SetPosDlg()
{
	CWinAmpControl * pWACtrl = CWinAmpControl::GetInstance();
	int nLen = pWACtrl->GetSongLengthSeconds();
	int nPos = pWACtrl->GetCurrentPosition() / 1000;
	if (m_nTimerID == 0) {
		m_nTimerID = SetTimer(NULL, 1, nLen  * 100, TimerProc);
	}

	PercentageDlg("Set position", 10, (10 * nPos / nLen));
	m_bSetPos = TRUE;
}

void CEricssonAT::InputDlg(CString sTitle, CString sPrompt, int nMaxLen, CString sInitialText, int nNextState)
{
	CString sATCommand;
	sATCommand.Format("AT*EAID=11,%d,\"%s\",\"%s\",%d,\"%s\"\r\n", nNextState, sTitle.Left(15), sPrompt, nMaxLen, sInitialText);
	WriteBufferToCom((LPTSTR)(LPCTSTR)sATCommand, sATCommand.GetLength());	
}


void CEricssonAT::InfoBox(CString sText, int nNextState)
{
	CString sATCommand;
	sATCommand.Format("AT*EAID=1,%d,\"%s\"\r\n", nNextState, sText);
	WriteBufferToCom((LPTSTR)(LPCTSTR)sATCommand, sATCommand.GetLength());	

}

void CEricssonAT::FillPlayList()
{
	CWinAmpControl * pWACtrl = CWinAmpControl::GetInstance();
	
	int nCurPos = pWACtrl->GetListPos();

	pWACtrl->Stop();
	pWACtrl->GotoStartPlaylist();

	int nListLength = pWACtrl->GetListLength();
	
	CStringArray saPlaylist;

	int nAdd = 0;

	// Skip the songs that are not on the current page...
	int nSkip = m_nPlayListPage * 10;
	if (m_nPlayListPage > 0) {
		nSkip++;
	}

	nSkip--;

	for (int i = 0; i < nSkip; i++) {
		pWACtrl->Next();	
	}

	i++;

	int nCounter = 0;
	for(; nCounter < 12 && i <= nListLength; i++) {
		CString sCurSong;
		if (nListLength > 12 && i >= 11 && nCounter % 12 == 0) {
			sCurSong = "Previous Page";
		}
		else if (nListLength > 12 && nCounter % 12 == 11) {
			sCurSong = "NextPage";
		}
		else {
			sCurSong.Format("%02d.%s", i - nAdd, pWACtrl->GetCurrentSong());
		}
		saPlaylist.Add(sCurSong);
		pWACtrl->Next();
		nCounter++;
	}

	CString sTitle;
	sTitle.Format("Playlist (%d)", nListLength);
	int nInitialSelection = nCurPos - 1 - 10 * m_nPlayListPage;
	if (m_nPlayListPage == 0) {
		nInitialSelection--;
	}
	ListDlg(sTitle, nInitialSelection, saPlaylist);

}

void CEricssonAT::ListDlg(CString sTitle, int nInitialSelection, CStringArray &saMenuItems, int nNextState)
{
	CString sATCommand;
	int nSize = saMenuItems.GetSize();

	if (nInitialSelection > nSize) {
		nInitialSelection = 1;
	}

	sATCommand.Format("AT*EAID=5,%d,\"%s\",%d,%d", nNextState, sTitle, nInitialSelection, nSize);

	if (nSize) {
		sATCommand += ",";
		for (int i = 0; i < nSize - 1; i++) {
			sATCommand += "\"" + saMenuItems.GetAt(i).Left(15) + "\",";
		}
		
		sATCommand += "\"" + saMenuItems.GetAt(i).Left(15) + "\"";
	}

	sATCommand += "\r\n";

	WriteBufferToCom((LPTSTR)(LPCTSTR)sATCommand, sATCommand.GetLength());
}

VOID CALLBACK CEricssonAT::TimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	m_pPseudoThis->SetPosDlg();
}
