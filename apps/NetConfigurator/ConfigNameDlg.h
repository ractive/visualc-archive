#if !defined(AFX_CONFIGNAMEDLG_H__D1705CD9_74E6_420A_9748_6F69E7BF27B5__INCLUDED_)
#define AFX_CONFIGNAMEDLG_H__D1705CD9_74E6_420A_9748_6F69E7BF27B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigNameDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigNameDlg dialog

class CConfigNameDlg : public CDialog
{
// Construction
public:
	CConfigNameDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigNameDlg)
	enum { IDD = IDD_CONFIGNAME };
	CString	m_sName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigNameDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigNameDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGNAMEDLG_H__D1705CD9_74E6_420A_9748_6F69E7BF27B5__INCLUDED_)
