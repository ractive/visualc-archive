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


// EricssonAT.h: interface for the CEricssonAT class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ERICSSONAT_H__4D371CD9_E321_4C4A_8BDC_B633B44B3D73__INCLUDED_)
#define AFX_ERICSSONAT_H__4D371CD9_E321_4C4A_8BDC_B633B44B3D73__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Serial.h"

class CEricssonAT : public CSerial  
{
public:
	void InfoBox(CString sText, int nNextState);
	static VOID CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime);
	void ListDlg(CString sTitle, int nInitialSelection, CStringArray &saMenuItems, int nNextState = 1);
	void FillPlayList();
	void InputDlg(CString sTitle, CString sPrompt, int nMaxLen, CString sInitialText = "", int nNextState = 1);
	void SetPosDlg();
	void SetErrorMode(BOOL bVerbose);
	void InfoDlg(CString sTitle, CString sText, int nNextState = 1);
	void PercentageDlg(CString sTitle, int nSteps, int nInitialStep, int nNextState = 1);
	void AddSubMenu(CString sTitle, int nSelectedItem, CStringArray &saMenuItems, int nNextState = 1);
	void AddAccessoryMenu(LPCTSTR sTitle);
	/*BOOL AddAccessoryMenu(LPCTSTR sTitle);
	BOOL InfoDlg(LPCTSTR sTitle, LPCTSTR sInfo, USHORT uNextState = 1);
	BOOL WaitDlg(LPCTSTR sTitle, USHORT uNextState = 1);
	BOOL PasswordInputDlg(LPCTSTR sTitle, LPCTSTR sPrompt, USHORT uMaxLength, USHORT uNextState = 1);
	BOOL StringInputDlg(LPCTSTR sTitle, LPCTSTR sPrompt, USHORT uMaxLength, LPCTSTR sInitialText = "", USHORT uNextState = 1);
	BOOL PhoneNrInputDlg(LPCTSTR sTitle, LPCTSTR sPrompt, LPCTSTR sInitialNumber = "", USHORT uNextState = 1);
	BOOL DateInputDlg(LPCTSTR sTitle, LPCTSTR sInitialDate = "", USHORT uNextState = 1);
	BOOL TimeInputDlg(LPCTSTR sTitle, LPCTSTR sInitialTime = "", USHORT uNextState = 1);
	BOOL ListDlg(LPCTSTR sTitle, USHORT uInitialSelection, USHORT uItemNum, char** saItems, USHORT uNextState = 1);
	BOOL SetAccessorySubMenu(LPCTSTR sTitle, USHORT uInitialSelection, USHORT uItemNum, char** saItems, USHORT uNextState = 1);
	BOOL OnOffDlg(LPCTSTR sTitle, BOOL bDefaultOn, USHORT uNextState = 1);
	BOOL PercentDlg(LPCTSTR sTitle,  USHORT uPercentSteps, USHORT uInitialPercentStep, USHORT uNextState = 1);
	BOOL NoDialog();
	BOOL SetVerboseErrorMode(BOOL bOn = TRUE);*/
	BOOL Receive(CString &sStatusText);
	void CheckForPhone();
	CEricssonAT();
	virtual ~CEricssonAT();
private:
	BOOL m_bSetPos;
	//enum EXPCTED {CHECKPHONE, MENU} m_expect;
	char * m_pInputBuf;
	char * m_sInputBuf;
protected:
	int m_nTimerID;
	int m_nPlayListPage;
	BOOL m_bErrorModeSet;
	void ShowMenu(int nInitialSelection = 1);
	CString GetMenuTitle();
	void ResetInputBuffer();

	static CEricssonAT * m_pPseudoThis;
};

#endif // !defined(AFX_ERICSSONAT_H__4D371CD9_E321_4C4A_8BDC_B633B44B3D73__INCLUDED_)
