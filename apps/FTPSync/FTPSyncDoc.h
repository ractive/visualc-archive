// FTPSyncDoc.h : interface of the CFTPSyncDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FTPSYNCDOC_H__99AB06C2_33CA_4470_8E9D_C06DB20ECAE8__INCLUDED_)
#define AFX_FTPSYNCDOC_H__99AB06C2_33CA_4470_8E9D_C06DB20ECAE8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSyncPair;

class CFTPSyncDoc : public CDocument
{
protected: // create from serialization only
	CFTPSyncDoc();
	DECLARE_DYNCREATE(CFTPSyncDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFTPSyncDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL CanCloseFrame(CFrameWnd* pFrame);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	void Load();
	void Save();
	void EditPair(UINT nData);
	void DelPair(UINT nData);
	void Sync(UINT nData, HWND hNotificationWnd, HANDLE hStop);
	void GetNextPair(POSITION &pos, CString &sLocalDir, CString &sFtp, UINT &nPort, UINT &nData);
	POSITION GetFirstPair();
	virtual ~CFTPSyncDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	CSyncPair * GetPtrFromData(UINT nData, POSITION &pos);
	//{{AFX_MSG(CFTPSyncDoc)
	afx_msg void OnAdd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CObList m_SyncPairs;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FTPSYNCDOC_H__99AB06C2_33CA_4470_8E9D_C06DB20ECAE8__INCLUDED_)
