// FTPSyncView.cpp : implementation of the CFTPSyncView class
//

#include "stdafx.h"
#include "FTPSync.h"
#include "SyncProgressDlg.h"

#include "FTPSyncDoc.h"
#include "FTPSyncView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFTPSyncView

IMPLEMENT_DYNCREATE(CFTPSyncView, CListView)

BEGIN_MESSAGE_MAP(CFTPSyncView, CListView)
	//{{AFX_MSG_MAP(CFTPSyncView)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_UPDATE_COMMAND_UI(ID_SYNC, OnUpdateSync)
	ON_COMMAND(ID_SYNC, OnSync)
	ON_UPDATE_COMMAND_UI(ID_DELPAIR, OnUpdateDelpair)
	ON_COMMAND(ID_DELPAIR, OnDelpair)
	ON_UPDATE_COMMAND_UI(ID_EDITPAIR, OnUpdateDelpair)
	ON_COMMAND(ID_EDITPAIR, OnEditPair)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFTPSyncView construction/destruction

CFTPSyncView::CFTPSyncView()
{
	m_bInitialized = FALSE;
}

CFTPSyncView::~CFTPSyncView()
{
}

BOOL CFTPSyncView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL;

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFTPSyncView drawing

void CFTPSyncView::OnDraw(CDC* pDC)
{
	CFTPSyncDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CFTPSyncView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	if (!m_bInitialized) {
		m_ImageList.Create(16, 16, ILC_COLOR24 | ILC_MASK , 2, 0);

		HICON hIcon = AfxGetApp()->LoadIcon(IDI_FTPICON);
		if (hIcon) {
			m_ImageList.Add(hIcon);
		}

		m_ImageList.SetBkColor(GetSysColor(COLOR_WINDOW));

		CListCtrl &listCtrl = GetListCtrl();

		listCtrl.SetImageList(&m_ImageList, LVSIL_SMALL);


		DWORD dwStyle = listCtrl.GetExtendedStyle();

		listCtrl.SetExtendedStyle(dwStyle | LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT);

		AddHeaders();

		m_bInitialized = TRUE;
	}

	FillList();
}

/////////////////////////////////////////////////////////////////////////////
// CFTPSyncView diagnostics

#ifdef _DEBUG
void CFTPSyncView::AssertValid() const
{
	CListView::AssertValid();
}

void CFTPSyncView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CFTPSyncDoc* CFTPSyncView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFTPSyncDoc)));
	return (CFTPSyncDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFTPSyncView message handlers

void CFTPSyncView::AddHeaders()
{
	CListCtrl &listCtrl = GetListCtrl();

	int nItem = 0;
	
	int nSubItem = 0;

	LV_COLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvc.fmt = LVCFMT_LEFT;
	lvc.iSubItem = nSubItem++;
	lvc.cx = 250;
	lvc.pszText = _T("Local Folder");
	listCtrl.InsertColumn(0, &lvc);
	
	lvc.iSubItem = nSubItem++;
	lvc.pszText = _T("FTP site");
	lvc.cx = 250;
	listCtrl.InsertColumn(1, &lvc);

	lvc.fmt = LVCFMT_RIGHT;
	lvc.iSubItem = nSubItem++;
	lvc.pszText = _T("Port");
	lvc.cx = 50;
	listCtrl.InsertColumn(2, &lvc);
}

void CFTPSyncView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CListCtrl& ListCtrl = GetListCtrl();
	NMLISTVIEW* pNMListView = (NM_LISTVIEW *)pNMHDR;

	int nItem = -1;

	if ((nItem = ListCtrl.HitTest(pNMListView->ptAction)) == -1) {
		// The doubleclick was not on an item. Nothing to do!
		return;
	}
	
	GetDocument()->EditPair(ListCtrl.GetItemData(nItem));

	*pResult = 0;
}

void CFTPSyncView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	FillList();
}

void CFTPSyncView::OnUpdateSync(CCmdUI* pCmdUI) 
{
	// Enable the toolbar button if at least one item is checked in the list
	pCmdUI->Enable(FALSE);
	CListCtrl &listCtrl = GetListCtrl();
	
	int nItems = listCtrl.GetItemCount();
	for (int i = 0; i < nItems; i++) {
		if (listCtrl.GetCheck(i)) {
			pCmdUI->Enable(TRUE);
			break;
		}
	}
}

void CFTPSyncView::FillList()
{
	CListCtrl &listCtrl = GetListCtrl();

	listCtrl.DeleteAllItems();

	CFTPSyncDoc * pDoc = GetDocument();
	
	POSITION pos = pDoc->GetFirstPair();
	while(pos) {
		CString sLocalDir;
		CString sFtp;
		
		UINT nPort = 0;
		UINT nData = 0;

		pDoc->GetNextPair(pos, sLocalDir, sFtp, nPort, nData);
		LVITEM lvi;
		lvi.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
		lvi.lParam = nData;
		lvi.iItem = 0;
		lvi.iSubItem = 0;
		lvi.pszText = (LPTSTR)(LPCTSTR)sLocalDir;
		lvi.cchTextMax = _MAX_PATH;
		lvi.iImage = 0;

		int nIns = listCtrl.InsertItem(&lvi);
		
		//listCtrl.SetItemData(nIns, dwParam);
		lvi.mask = LVIF_TEXT;
		lvi.iSubItem = 1;
		lvi.pszText = (LPTSTR)(LPCTSTR)sFtp;
		listCtrl.SetItem(&lvi);

		lvi.iSubItem = 2;
		CString sPort;
		sPort.Format("%d", nPort);
		lvi.pszText = (LPTSTR)(LPCTSTR)sPort;
		listCtrl.SetItem(&lvi);	
	}

}

void CFTPSyncView::OnUpdateDelpair(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetListCtrl().GetSelectedCount());
}

void CFTPSyncView::OnDelpair() 
{
	CListCtrl &listCtrl = GetListCtrl();

	CFTPSyncDoc * pDoc = GetDocument();

	POSITION pos = listCtrl.GetFirstSelectedItemPosition();
	if (pos) {
		int nSel = listCtrl.GetNextSelectedItem(pos);
		pDoc->DelPair(listCtrl.GetItemData(nSel));

		int nNewSel = nSel - 1;
		if (nNewSel == -1) {
			nNewSel = 0;
		}

		listCtrl.SetItemState(nNewSel, LVIS_SELECTED, LVIS_SELECTED);
	}
}

void CFTPSyncView::OnEditPair() 
{
	CListCtrl &listCtrl = GetListCtrl();

	CFTPSyncDoc * pDoc = GetDocument();

	POSITION pos = listCtrl.GetFirstSelectedItemPosition();
	if (pos) {
		int nSel = listCtrl.GetNextSelectedItem(pos);
		pDoc->EditPair(listCtrl.GetItemData(nSel));
	}
}

void CFTPSyncView::OnSync() 
{
	//DWORD exit;
	m_pProgressDlg = new CSyncProgressDlg;
	m_pProgressDlg->Create(IDD_SYNCPROGRESSDLG);

	m_pProgressDlg->m_hStop = CreateEvent(NULL, TRUE, FALSE, NULL);


	CWinThread * pThread = AfxBeginThread(SyncThreadProc, this, 0, CREATE_SUSPENDED, NULL);
	pThread->m_bAutoDelete = false;
	pThread->ResumeThread();

	// Hmm, not sure but here could occur a "deadlock". If the Window gets not messages
	// any more and we call Pump at the wrong time, Pump will wait will a new
	// message arrives. Very unlikely, but possible.
	DWORD dwSigHandle;
	while (dwSigHandle = WaitForSingleObject(pThread->m_hThread, 100)) {
		if (dwSigHandle == WAIT_TIMEOUT) {
			CSyncProgressDlg::Pump();
			continue;
		}
		else if (dwSigHandle - WAIT_OBJECT_0 == 1) {
			//m_bCancel = true;
			continue;
		}
		else if (dwSigHandle - WAIT_OBJECT_0 == 0) {
			break;
		}
	}

	WaitForSingleObject(pThread->m_hThread, 1000);


	/*if (!::GetExitCodeThread(pThread->m_hThread, &exit)) {
		ThrowProtException(CProtException::UNKNOWN, GetLastError());
	}*/
	
	m_pProgressDlg->DestroyWindow();

	CloseHandle(m_pProgressDlg->m_hStop);

	delete m_pProgressDlg;

	delete pThread;
}

UINT CFTPSyncView::SyncThreadProc(LPVOID lParam)
{
	CFTPSyncView * pThis = (CFTPSyncView *)lParam;
	CListCtrl &listCtrl = pThis->GetListCtrl();

	CFTPSyncDoc * pDoc = pThis->GetDocument();

	AfxGetMainWnd()->EnableWindow(FALSE);


	int nItems = listCtrl.GetItemCount();
	for (int i = 0; i < nItems; i++) {
		if (listCtrl.GetCheck(i)) {
			if (WaitForSingleObject(pThis->m_pProgressDlg->m_hStop, 0) == WAIT_OBJECT_0) {
				// End the thread
				return 1;
			}
			UINT nData = listCtrl.GetItemData(i);
			pDoc->Sync(nData, pThis->m_pProgressDlg->m_hWnd, pThis->m_pProgressDlg->m_hStop);
		}
	}	

	AfxGetMainWnd()->EnableWindow(TRUE);

	return 0;
}
