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


// EditBox.cpp : implementation file
//

#include "stdafx.h"
#include "hexer.h"
#include "EditBox.h"
#include "HexerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditBox

CEditBox::CEditBox()
{
	m_pDropTarget = new CDropTarget(this);
	m_Base = decimal;
}

CEditBox::~CEditBox()
{
	delete m_pDropTarget;
}


BEGIN_MESSAGE_MAP(CEditBox, CEdit)
	//{{AFX_MSG_MAP(CEditBox)
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditBox message handlers

void CEditBox::SetBase(base base_)
{
	m_Base = base_;
}

BOOL CEditBox::Parse(unsigned __int64 * pRes, CString * psCont /* = NULL */, BOOL bSilent /* = FALSE */)
{
	CString sContent;
	*pRes = 0;

	if (psCont == NULL) {
		GetWindowText(sContent);
		psCont = &sContent;
	}

	if (psCont->IsEmpty()) {
		return FALSE;
	}

	// Remove all spaces
	psCont->Remove(' ');

	int i = 0;
	int nC = 0;

	BOOL bRet = TRUE;

	CString sMsg;
	int nLength;

	switch(m_Base) {
	case decimal:
		for (i = 0; i < psCont->GetLength(); i++) {
			// Is is a digit?
			if (!isdigit(psCont->GetAt(i))) {
				bRet = FALSE;
				sMsg = "Decimal number may only contain digits [0 - 9]";
				break;
			}
		}

		if (bRet) {
			sscanf(*psCont, "%I64u", pRes);
			Convert(pRes);
			CString sResult;
			sResult.Format("%I64u", *pRes);
			if (bRet == FALSE || sResult != *psCont) {
				sMsg = "Number too large!\r\n\r\nExceeding bit-range";
				bRet = FALSE;
				break;
			}
		}

		break;
	case dsigned:
		if (psCont->GetAt(0) == '-' && psCont->GetLength() == 1) {
			break;
		}
		for (i = 0; i < psCont->GetLength(); i++) {
			// Is is a digit?
			if (!isdigit(psCont->GetAt(i))) {
				if (!(i == 0 && psCont->GetAt(i) == '-')) {
					bRet = FALSE;
					sMsg = "Signed number may only contain digits [0 - 9]\r\nand a minus sign at the first position";
					break;
				}
			}
		}

		if (bRet) {
			sscanf(*psCont, "%I64d", pRes);
			Convert(pRes, TRUE);
			CString sResult;
			sResult.Format("%I64d", *pRes);
			if (bRet == FALSE || sResult != *psCont) {
				sMsg = "Number too large!\r\n\r\nExceeding bit-range";
				bRet = FALSE;
				break;
			}
		}

		break;

	case octal:
		for (i = 0; i < psCont->GetLength(); i++) {
			// Is the digit from 0 to 7?
			int n = psCont->GetAt(i) - '0';
			if (n > 7 || n < 0) {
				bRet = FALSE;
				sMsg = "Octal numbers numbers may only contain digits from 0 to 7";
				break;
			}
		}
		if (bRet) {
			sscanf(*psCont, "%I64o", pRes);
			Convert(pRes);
			CString sResult;
			sResult.Format("%I64o", *pRes);
			if (bRet == FALSE || sResult != *psCont) {
				sMsg = "Number too large!\r\n\r\nExceeding bit-range";
				bRet = FALSE;
				break;
			}
		}

		break;
	case binary:
		*pRes = 0;
		nLength = psCont->GetLength();
		if (nLength > *m_pnBit) {
			bRet = FALSE;
			sMsg = "Number too large!\r\n\r\nExceeding bit-range";
			break;
		}
		for (i = 0; i < nLength; i++) {
			// Is the digit 0 or 1?
			char ch = psCont->GetAt(nLength - i - 1);
			
			// ignore spaces
			if (ch == ' ') {
				continue;
			}
			
			if (!(ch == '0' || ch == '1')) {
				bRet = FALSE;
				sMsg = "Binary numbers numbers may only contain the digits 0 and 1";
				break;
			}
			
			if (ch == '1') {
				unsigned __int64 add = 0;
				if (nC >= 32 && nC < 62) {
					// We need two shift, because you only can shift max 32 bits
					add = Int64ShllMod32(1, 31);
					add = Int64ShllMod32(add, nC % 31);
				}
				else if (nC >= 62) {
					add = Int64ShllMod32(1, 31);
					add = Int64ShllMod32(add, 31);
					add = Int64ShllMod32(add, nC % 62);
				}
				else {
					add = Int64ShllMod32(1, nC);
				}
				*pRes += add;
			}

			nC++;
		}
		break;
	case hex:
		// Check if it begins with 0x
		// If yes, remove it.
		if (psCont->Left(2) == "0x") {
			*psCont = psCont->Mid(2);
		}
		if (psCont->GetLength() > *m_pnBit / 4) {
			sMsg = "Number is too large!\r\n\r\nExceeding bit-range";
			bRet = FALSE;
			break;
		}
		for (i = 0; i < psCont->GetLength(); i++) {
			// Is is a hex digit?
			if (!isxdigit(psCont->GetAt(i))) {
				bRet = FALSE;
				sMsg = "Hexadecimal numbers may only contain digits\nand the letters from a to f (lower and uppercase)!";
				break;
			}				
		}
		if (bRet) {
			sscanf(*psCont, "%I64x", pRes);
			Convert(pRes);
			CString sResult;
			sResult.Format("%I64x", *pRes);
			psCont->MakeLower();
			sResult.MakeLower();
			if (bRet == FALSE || sResult != *psCont) {
				sMsg = "Number too large!\r\n\r\nExceeding bit-range";
				bRet = FALSE;
				break;
			}
		}

		break;
	case ddouble:
		if (psCont->GetAt(0) == '.' && psCont->GetLength() == 1) {
			break;
		}
		for (i = 0; i < psCont->GetLength(); i++) {
			// Is is a digit?
			TCHAR ch = psCont->GetAt(i);
			if (!isdigit(ch) && ch != '.') {
				if (!(i == 0 && psCont->GetAt(i) == '-')) {
					bRet = FALSE;
					sMsg = "Double numbers may only contain digits [0 - 9]\r\nand the point as decimal separator";
					break;
				}
			}
		}

		if (bRet) {
			sscanf(*psCont, "%lf", pRes);
			Convert(pRes);
			/*CString sResult;
			sResult.Format("%lf", *pRes);
			if (bRet == FALSE || sResult != *psCont) {
				sMsg = "Number too large!\r\n\r\nMax. 64 bit numbers allowed!";
				bRet = FALSE;
				break;
			}*/
		}

		break;
	}
	if (!bSilent && !sMsg.IsEmpty() && (bRet == FALSE)) {
		MessageBox(sMsg, "Invalid Input", MB_OK | MB_ICONEXCLAMATION);
	}

	return bRet;
}

void CEditBox::OnChange() 
{
	unsigned __int64 nRes;
	if (Parse(&nRes) == FALSE) {
		// If the user entered an invalid character we remove the last
		// character from the edit control that has the focus.
		/*CString sWndText;
		GetWindowText(sWndText);
		sWndText = sWndText.Left(sWndText.GetLength() - 1);
		SetWindowText(sWndText);
		// Set the caret to the last position
		SetSel(0xFFFF, 0xFFFF);*/
		SetWindowText(m_sOldContent);
	}
	else {
		GetWindowText(m_sOldContent);
	}
}

BOOL CEditBox::Paste(LPDATAOBJECT pIDataObject)
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
	
	LPSTR sClipboard = (LPSTR)GlobalLock(stm.hGlobal);
	SetWindowText(sClipboard);
	GlobalUnlock(stm.hGlobal);

	if (stm.hGlobal != NULL) {         
		ReleaseStgMedium(&stm);         
	}
	
	CHexerDlg * pHexerDlg = (CHexerDlg *)GetParent();
	pHexerDlg->m_Base = m_Base;
	pHexerDlg->Calculate();

	return fRet;     
}

void CEditBox::Convert(unsigned __int64 *pVal, BOOL bSigned /* = FALSE */)
{
	switch(*m_pnBit) {
	case 8:
		if (bSigned)
			*pVal = (signed __int8)*pVal;
		else
			*pVal = (unsigned __int8)*pVal;
		break;
	case 16:
		if (bSigned)
			*pVal = (signed __int16)*pVal;
		else
			*pVal = (unsigned __int16)*pVal;
		break;
	case 32:
		if (bSigned)
			*pVal = (signed __int32)*pVal;
		else
			*pVal = (unsigned __int32)*pVal;
		break;
	case 64:
		if (bSigned)
			*pVal = (signed __int64)*pVal;
		else
			*pVal = (unsigned __int64)*pVal;
		break;
	default:
		ASSERT(FALSE);
	}
}
