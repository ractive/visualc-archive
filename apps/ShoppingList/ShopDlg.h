#if !defined(AFX_SHOPDLG_H__78135E72_E809_47E2_BB61_E02BC16B8798__INCLUDED_)
#define AFX_SHOPDLG_H__78135E72_E809_47E2_BB61_E02BC16B8798__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShopDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CShopDlg dialog

class CShopDlg : public CDialog
{
// Construction
public:
	CShopDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CShopDlg)
	enum { IDD = IDD_SHOPDIALOG };
	CString	m_sShop;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShopDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CShopDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOPDLG_H__78135E72_E809_47E2_BB61_E02BC16B8798__INCLUDED_)
