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

// HexerDlg.h : header file
//

#if !defined(AFX_HEXERDLG_H__E24D41F4_B949_4069_A963_5DEA68CFE24C__INCLUDED_)
#define AFX_HEXERDLG_H__E24D41F4_B949_4069_A963_5DEA68CFE24C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "DropTarget.h"
#include "EditBox.h"
#include "colorbtn.h"
/////////////////////////////////////////////////////////////////////////////
// CHexerDlg dialog

class CHexerDlg : public CDialog
{
// Construction
public:
	void Calculate();
	CHexerDlg(CWnd* pParent = NULL);	// standard constructor
	base m_Base;

// Dialog Data
	//{{AFX_DATA(CHexerDlg)
	enum { IDD = IDD_HEXER_DIALOG };
	CComboBox	m_BitCombo;
	CSpinButtonCtrl	m_Spin;
	CEditBox	m_DoubleBox;
	CEditBox	m_SignedBox;
	CEditBox	m_OctalBox;
	CEditBox	m_HexBox;
	CEditBox	m_DecimalBox;
	CEditBox	m_BinaryBox;
	CString		m_sDecimal;
	CString		m_sBinary;
	CString		m_sOctal;
	CString		m_sHex;
	CString	m_sSigned;
	CString	m_sDouble;
	BOOL	m_bTopMost;
	UINT	m_unPrecision;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHexerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHexerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCalculate();
	afx_msg void OnSetfocusDecimal();
	afx_msg void OnSetfocusHex();
	afx_msg void OnSetfocusBinary();
	afx_msg void OnSetfocusOctal();
	afx_msg void OnSetfocusSigned();
	afx_msg void OnSetfocusDouble();
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColorButton();
	afx_msg void OnAlwaysontop();
	afx_msg void OnSelchangeBitcombo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CColorButton	m_Color;

private:
	unsigned short m_nBit;
	void FillBitCombo();
	void SetOnTopIcon();
	void SwitchOnTop();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HEXERDLG_H__E24D41F4_B949_4069_A963_5DEA68CFE24C__INCLUDED_)
