// FTPSyncView.h : interface of the CFTPSyncView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FTPSYNCVIEW_H__B1F47FF6_8ABA_4300_852F_033CE83EFB7D__INCLUDED_)
#define AFX_FTPSYNCVIEW_H__B1F47FF6_8ABA_4300_852F_033CE83EFB7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSyncProgressDlg;

class CFTPSyncView : public CListView
{
protected: // create from serialization only
	CFTPSyncView();
	DECLARE_DYNCREATE(CFTPSyncView)

// Attributes
public:
	CFTPSyncDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFTPSyncView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	static UINT SyncThreadProc(LPVOID lParam);
	CSyncProgressDlg * m_pProgressDlg;
	virtual ~CFTPSyncView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CImageList m_ImageList;

// Generated message map functions
protected:
	void FillList();
	void AddHeaders();
	//{{AFX_MSG(CFTPSyncView)
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUpdateSync(CCmdUI* pCmdUI);
	afx_msg void OnSync();
	afx_msg void OnUpdateDelpair(CCmdUI* pCmdUI);
	afx_msg void OnDelpair();
	afx_msg void OnEditPair();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bInitialized;
};

#ifndef _DEBUG  // debug version in FTPSyncView.cpp
inline CFTPSyncDoc* CFTPSyncView::GetDocument()
   { return (CFTPSyncDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FTPSYNCVIEW_H__B1F47FF6_8ABA_4300_852F_033CE83EFB7D__INCLUDED_)
