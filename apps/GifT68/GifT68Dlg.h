// GifT68Dlg.h : header file
//

#if !defined(AFX_GIFT68DLG_H__DF6E5AF0_84EF_4BDB_87B2_AF252316C92B__INCLUDED_)
#define AFX_GIFT68DLG_H__DF6E5AF0_84EF_4BDB_87B2_AF252316C92B__INCLUDED_

#include "Picture.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CGifT68Dlg dialog

#include "PicHolder.h"

class CGifT68Dlg : public CDialog
{
// Construction
public:
	CGifT68Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGifT68Dlg)
	enum { IDD = IDD_GIFT68_DIALOG };
	CPicHolder  m_ConvertedGif;
	CPicHolder	m_GifImage;
	CString	m_sInputFile;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGifT68Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CPicture m_Picture;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGifT68Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GIFT68DLG_H__DF6E5AF0_84EF_4BDB_87B2_AF252316C92B__INCLUDED_)
