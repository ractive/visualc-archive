#if !defined(AFX_LINKSDLG_H__353333A6_B7E6_4904_9DA1_8A0F6C62A4D6__INCLUDED_)
#define AFX_LINKSDLG_H__353333A6_B7E6_4904_9DA1_8A0F6C62A4D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LinksDlg.h : header file
//

#include "HyperLink.h"

/////////////////////////////////////////////////////////////////////////////
// CLinksDlg dialog

class CLinksDlg : public CDialog
{
// Construction
public:
	CLinksDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLinksDlg)
	enum { IDD = IDD_LINKSDLG };
	CHyperLink	m_EmelodyUrl;
	CHyperLink	m_MailUrl;
	CHyperLink	m_MobileHitsUrl;
	CHyperLink	m_EricssonUrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLinksDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLinksDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINKSDLG_H__353333A6_B7E6_4904_9DA1_8A0F6C62A4D6__INCLUDED_)
