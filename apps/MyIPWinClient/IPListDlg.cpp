// IPListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "myipwinclient.h"
#include "IPListDlg.h"
#include "MyIPWinClientDlg.h"
#include "MyIPHelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIPListDlg dialog


CIPListDlg::CIPListDlg(CWnd* pParent /*=NULL*/)
	: CToolTipDlg(CIPListDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIPListDlg)
	m_sRecordType = _T("");
	//}}AFX_DATA_INIT
}


void CIPListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIPListDlg)
	DDX_Control(pDX, IDC_RECORDTYPE, m_RecordCombo);
	DDX_Control(pDX, IDC_LIST, m_IPList);
	DDX_CBString(pDX, IDC_RECORDTYPE, m_sRecordType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIPListDlg, CDialog)
	//{{AFX_MSG_MAP(CIPListDlg)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnItemchangedList)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST, OnEndlabeleditList)
	ON_NOTIFY(LVN_BEGINLABELEDIT, IDC_LIST, OnBeginlabeleditList)
	ON_BN_CLICKED(IDC_IMPORT, OnImport)
	ON_CBN_SELCHANGE(IDC_RECORDTYPE, OnSelchangeRecordtype)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIPListDlg message handlers

BOOL CIPListDlg::OnInitDialog() 
{
	CToolTipDlg::OnInitDialog();

	AddTool(GetDlgItem(IDC_IMPORT), _T("Get your current settings from www.myip.org"));
	AddTool(GetDlgItem(IDC_LIST), _T("Choose a host to update"));
	AddTool(GetDlgItem(IDC_UPDATE), _T("Update the selected host in the list"));
	AddTool(GetDlgItem(IDC_RECORDTYPE), _T("Set the record type of the selected host in the list"));
	Activate(TRUE);

	DWORD dwExtStyle = m_IPList.GetExtendedStyle();
	m_IPList.SetExtendedStyle(dwExtStyle | LVS_EX_FULLROWSELECT);

	m_IPList.InsertColumn(0, _T("IP Address"), LVCFMT_LEFT, 100, 0);
	m_IPList.InsertColumn(1, _T("Hostname"), LVCFMT_LEFT, 100, 1);
	m_IPList.InsertColumn(2, _T("Record Type"), LVCFMT_LEFT, 100, 1);

	FillList();

	m_RecordCombo.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CIPListDlg::OnUpdate() 
{
	UpdateData();
	POSITION pos = m_IPList.GetFirstSelectedItemPosition();
	if (pos == NULL) {
		return;
	}
	int nItem = m_IPList.GetNextSelectedItem(pos);
	
	if (!m_pHostMgr->UpdateHost(m_IPList.GetItemText(nItem, 1), m_IPList.GetItemText(nItem, 0), m_sRecordType)) {
		return;
	}
}

void CIPListDlg::OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	hostEntry * entry = m_pHostMgr->GetHostEntry(pNMListView->iItem);
	m_RecordCombo.SetCurSel(m_RecordCombo.FindString(-1, entry->sRecordType));

	*pResult = 0;
}

void CIPListDlg::OnEndlabeleditList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	CString sRecordType = m_IPList.GetItemText(pDispInfo->item.iItem, 2);
	m_pHostMgr->SetHost(m_sEditedHost, pDispInfo->item.pszText, sRecordType);

	*pResult = 1;
}

void CIPListDlg::OnBeginlabeleditList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	m_sEditedHost = m_IPList.GetItemText(pDispInfo->item.iItem, 1);
	*pResult = 0;
}

void CIPListDlg::OnImport() 
{
	// Try to import the current settings form www.myip.org
	if (!m_pHostMgr->Import()) {
		return;
	}

	// If is was successful, we refill the list.
	m_IPList.DeleteAllItems();
	FillList();
	
}

void CIPListDlg::FillList()
{
	for (int i = 0; i < m_pHostMgr->GetSize(); i++) {
		hostEntry * entry = m_pHostMgr->GetHostEntry(i);
		LVITEM lvi;
		lvi.mask = LVIF_TEXT; 
		lvi.iItem = i;
		lvi.iSubItem = 0;
		lvi.cchTextMax = 128;
		if (entry->sIP.IsEmpty()) {
			entry->sIP = "unknown";
		}
		lvi.pszText = (LPTSTR)(LPCTSTR)entry->sIP;
		m_IPList.InsertItem(&lvi);
		lvi.iSubItem = 1;
		lvi.pszText = (LPTSTR)(LPCTSTR)entry->sHostName;
		m_IPList.SetItem(&lvi);
		lvi.iSubItem = 2;
		lvi.pszText = (LPTSTR)(LPCTSTR)entry->sRecordType;
		m_IPList.SetItem(&lvi);
	}

}

void CIPListDlg::OnSelchangeRecordtype() 
{
	UpdateData();
	POSITION pos = m_IPList.GetFirstSelectedItemPosition();
	if (pos == NULL) {
		return;
	}
	int nItem = m_IPList.GetNextSelectedItem(pos);
	LVITEM lvi;
	lvi.mask = LVIF_TEXT; 
	lvi.iItem = nItem;
	lvi.iSubItem = 2;
	lvi.pszText = (LPTSTR)(LPCTSTR)m_sRecordType;
	m_IPList.SetItem(&lvi);
		
}
