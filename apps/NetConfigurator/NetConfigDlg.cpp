// NetConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NetConfigurator.h"
#include "NetConfigDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetConfigDlg dialog


CNetConfigDlg::CNetConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNetConfigDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetConfigDlg)
	//}}AFX_DATA_INIT

	m_bStaticDNS = FALSE;
	m_bStaticIP = FALSE;
}


void CNetConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetConfigDlg)
	DDX_Control(pDX, IDC_DHCPIP, m_DhcpIP);
	DDX_Control(pDX, IDC_DHCPDNS, m_DhcpDNS);
	DDX_Control(pDX, IDC_MANUALDNS, m_ManualDNS);
	DDX_Control(pDX, IDC_STATICIP, m_StaticIP);

	DDX_Control(pDX, IDC_SUBNETMASK, m_SubnetCtrl);
	DDX_Control(pDX, IDC_IPADDRESS, m_IPCtrl);
	DDX_Control(pDX, IDC_DNS2, m_DNS2Ctrl);
	DDX_Control(pDX, IDC_DNS1, m_DNS1Ctrl);
	DDX_Control(pDX, IDC_GATEWAY, m_GatewayCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetConfigDlg, CDialog)
	//{{AFX_MSG_MAP(CNetConfigDlg)
	ON_BN_CLICKED(IDC_DHCPIP, OnDhcpRadio)
	ON_BN_CLICKED(IDC_STATICIP, OnStaticRadio)
	ON_BN_CLICKED(IDC_DHCPDNS, OnDhcpdnsRadio)
	ON_BN_CLICKED(IDC_MANUALDNS, OnManualdnsRadio)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetConfigDlg message handlers

void CNetConfigDlg::OnOK() 
{
	m_sIP =   m_IPCtrl.GetAddressString();
	m_sDNS1 = m_DNS1Ctrl.GetAddressString();
	m_sDNS2 = m_DNS2Ctrl.GetAddressString();
	m_sGW =   m_GatewayCtrl.GetAddressString();
	m_sMask = m_SubnetCtrl.GetAddressString();
	
	CDialog::OnOK();
}

void CNetConfigDlg::OnDhcpRadio() 
{
	m_DhcpDNS.EnableWindow(TRUE);

	m_IPCtrl.EnableWindow(FALSE);
	m_SubnetCtrl.EnableWindow(FALSE);	
	m_GatewayCtrl.EnableWindow(FALSE);
	m_bStaticIP= FALSE;
}

void CNetConfigDlg::OnStaticRadio() 
{
	OnManualdnsRadio();
	m_ManualDNS.SetCheck(TRUE);
	m_DhcpDNS.SetCheck(FALSE);

	m_bStaticDNS = FALSE;

	m_DhcpDNS.EnableWindow(FALSE);

	m_IPCtrl.EnableWindow();
	m_SubnetCtrl.EnableWindow();	
	m_GatewayCtrl.EnableWindow();
	m_bStaticIP= TRUE;
}

void CNetConfigDlg::OnDhcpdnsRadio() 
{
	m_DNS1Ctrl.EnableWindow(FALSE);
	m_DNS2Ctrl.EnableWindow(FALSE);
	m_bStaticDNS = FALSE;
	
}

void CNetConfigDlg::OnManualdnsRadio() 
{
	m_DNS1Ctrl.EnableWindow();
	m_DNS2Ctrl.EnableWindow();
	m_bStaticDNS = TRUE;
}

BOOL CNetConfigDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_DhcpIP.SetCheck(!m_bStaticIP);
	m_StaticIP.SetCheck(m_bStaticIP);

	m_DhcpDNS.SetCheck(!m_bStaticDNS);
	m_ManualDNS.SetCheck(m_bStaticDNS);

	if (!m_bStaticIP) {
		OnDhcpRadio();
	}
	if (!m_bStaticDNS) {
		OnDhcpdnsRadio();
	}

	m_IPCtrl.SetAddressString(m_sIP);
	m_DNS1Ctrl.SetAddressString(m_sDNS1);
	m_DNS2Ctrl.SetAddressString(m_sDNS2);
	m_GatewayCtrl.SetAddressString(m_sGW);
	m_SubnetCtrl.SetAddressString(m_sMask);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
