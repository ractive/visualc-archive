#if !defined(AFX_UPDATEDLG_H__6B21A2C6_E242_49F3_9A13_07CC42843F1B__INCLUDED_)
#define AFX_UPDATEDLG_H__6B21A2C6_E242_49F3_9A13_07CC42843F1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UpdateDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUpdateDlg dialog

class CUpdateDlg : public CDialog
{
// Construction
public:
	BOOL Pump();
	static void UpdateDlg(DWORD dwStatus, void* pStatusInfo, DWORD dwInfoLen);
	CUpdateDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUpdateDlg)
	enum { IDD = IDD_UPDATEDLG };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUpdateDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	static CUpdateDlg * pPseudoThis;
	// Generated message map functions
	//{{AFX_MSG(CUpdateDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UPDATEDLG_H__6B21A2C6_E242_49F3_9A13_07CC42843F1B__INCLUDED_)
