// TrackerSkinDlg.h : header file
//

#if !defined(AFX_TRACKERSKINDLG_H__A0F0486F_0538_4806_81AB_88B4BE2C079B__INCLUDED_)
#define AFX_TRACKERSKINDLG_H__A0F0486F_0538_4806_81AB_88B4BE2C079B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BitmapHolder.h"
#include "PropertyList.h"
/////////////////////////////////////////////////////////////////////////////
// CTrackerSkinDlg dialog

class CTrackerSkinDlg : public CDialog
{
// Construction
public:
	CTrackerSkinDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTrackerSkinDlg)
	enum { IDD = IDD_TRACKERSKIN_DIALOG };
	CStatic	m_Frame;
	CTabCtrl	m_Desktops;
	CPropertyList	m_propList;
	CBitmapHolder m_Screen;
	int		m_nTest;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrackerSkinDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTrackerSkinDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRACKERSKINDLG_H__A0F0486F_0538_4806_81AB_88B4BE2C079B__INCLUDED_)
