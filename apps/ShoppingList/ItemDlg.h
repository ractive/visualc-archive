#if !defined(AFX_ITEMDLG_H__60C634E8_91A9_473F_815F_A7378D00E8F4__INCLUDED_)
#define AFX_ITEMDLG_H__60C634E8_91A9_473F_815F_A7378D00E8F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ItemDlg.h : header file
//

class CShoppingListDoc;

/////////////////////////////////////////////////////////////////////////////
// CItemDlg dialog

class CItemDlg : public CDialog
{
// Construction
public:
	CItemDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CItemDlg)
	enum { IDD = IDD_ITEMDIALOG };
	CComboBox	m_ShopCtrl;
	BOOL	m_bInCart;
	CString	m_sName;
	CString	m_sShop;
	//}}AFX_DATA

	CString m_sCurrentShop;
	CShoppingListDoc * m_pDoc;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CItemDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CItemDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ITEMDLG_H__60C634E8_91A9_473F_815F_A7378D00E8F4__INCLUDED_)
