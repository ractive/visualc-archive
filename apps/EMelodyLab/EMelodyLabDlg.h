// EMelodyLabDlg.h : header file
//

#if !defined(AFX_EMELODYLABDLG_H__6AF5B3C3_5F2E_4032_A585_82345809847B__INCLUDED_)
#define AFX_EMELODYLABDLG_H__6AF5B3C3_5F2E_4032_A585_82345809847B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CEMelodyLabDlg dialog

#define WM_POS (WM_USER + 1)
#define WM_THREADEND (WM_USER + 3)
#include "MelodyEdit.h"
#include "HyperLink.h"

class CEMelodyLabDlg : public CDialog
{
// Construction
public:
	CEMelodyLabDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CEMelodyLabDlg)
	enum { IDD = IDD_EMELODYLAB_DIALOG };
	CButton	m_StopCtrl;
	CButton	m_PlayCtrl;
	CHyperLink	m_UploadUrl;
	CMelodyEdit	m_MelodyCtrl;
	UINT	m_nSpeed;
	CString	m_sAvailable;
	BOOL	m_bPlayRight;
	//}}AFX_DATA
	static BOOL	m_bLoop;
	static CString	m_sMelody;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEMelodyLabDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL CheckSaveState();
	BOOL m_bModified;
	BOOL GetSaveName();
	void SaveMelody();
	CString m_sFileName;
	static int m_nStart;
	static int m_nStop;
	int CountTones();
	int m_nChars;
	int m_nTones;
	static int m_nDuration;
	static UINT PlayThread(LPVOID lParam);
	static int GetFrequency(CString s, BOOL bHighOctave);
	static HANDLE m_hStop;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CEMelodyLabDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnPlay();
	afx_msg void OnStop();
	afx_msg void OnChangeMelody();
	afx_msg void OnOpen();
	afx_msg void OnSave();
	afx_msg void OnSaveAs();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClear();
	afx_msg void OnNew();
	afx_msg void OnHelp();
	afx_msg void OnLinks();
	afx_msg void OnRewind();
	afx_msg void OnLoop();
	//}}AFX_MSG
	afx_msg LRESULT OnPos(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnPlayTone(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnThreadEnd(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EMELODYLABDLG_H__6AF5B3C3_5F2E_4032_A585_82345809847B__INCLUDED_)
