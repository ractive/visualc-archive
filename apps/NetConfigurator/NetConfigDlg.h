#if !defined(AFX_NETCONFIGDLG_H__EEFEC942_17A0_4862_A91D_387BB2A42142__INCLUDED_)
#define AFX_NETCONFIGDLG_H__EEFEC942_17A0_4862_A91D_387BB2A42142__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetConfigDlg.h : header file
//

#include "IpAddressCtrlEx.h"

/////////////////////////////////////////////////////////////////////////////
// CNetConfigDlg dialog

class CNetConfigDlg : public CDialog
{
// Construction
public:
	BOOL m_bStaticDNS;
	BOOL m_bStaticIP;
	CNetConfigDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNetConfigDlg)
	enum { IDD = IDD_NETWORKCONFIG };
	CButton	m_DhcpIP;
	CButton	m_DhcpDNS;
	CButton	m_StaticIP;
	CButton	m_ManualDNS;

	CIPAddressCtrlEx	m_SubnetCtrl;
	CIPAddressCtrlEx	m_IPCtrl;
	CIPAddressCtrlEx	m_DNS2Ctrl;
	CIPAddressCtrlEx	m_DNS1Ctrl;
	CIPAddressCtrlEx	m_GatewayCtrl;
	//}}AFX_DATA

	CString m_sIP;
	CString m_sDNS1;
	CString m_sDNS2;
	CString m_sGW;
	CString m_sMask;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetConfigDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNetConfigDlg)
	virtual void OnOK();
	afx_msg void OnDhcpRadio();
	afx_msg void OnStaticRadio();
	afx_msg void OnDhcpdnsRadio();
	afx_msg void OnManualdnsRadio();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETCONFIGDLG_H__EEFEC942_17A0_4862_A91D_387BB2A42142__INCLUDED_)
