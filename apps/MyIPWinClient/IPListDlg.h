#if !defined(AFX_IPLISTDLG_H__70F4EF1C_EF9D_42EF_BD52_D2CA0B8D84C9__INCLUDED_)
#define AFX_IPLISTDLG_H__70F4EF1C_EF9D_42EF_BD52_D2CA0B8D84C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IPListDlg.h : header file
//

#include "ToolTipDlg.h"
#include "HostMgr.h"

/////////////////////////////////////////////////////////////////////////////
// CIPListDlg dialog

class CIPListDlg : public CToolTipDlg
{
// Construction
public:
	CHostMgr * m_pHostMgr;
	CIPListDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CIPListDlg)
	enum { IDD = IDD_IPLIST };
	CComboBox	m_RecordCombo;
	CListCtrl	m_IPList;
	CString	m_sRecordType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIPListDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CIPListDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnUpdate();
	afx_msg void OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndlabeleditList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBeginlabeleditList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnImport();
	afx_msg void OnSelchangeRecordtype();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void FillList();
	CString m_sEditedHost;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IPLISTDLG_H__70F4EF1C_EF9D_42EF_BD52_D2CA0B8D84C9__INCLUDED_)
