// MonteCarloDoc.h : interface of the CMonteCarloDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MONTECARLODOC_H__00A43DB8_0024_4CEE_8C3D_EF98220A19D0__INCLUDED_)
#define AFX_MONTECARLODOC_H__00A43DB8_0024_4CEE_8C3D_EF98220A19D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PointList.h"

class CMonteCarloDoc : public CDocument
{
protected: // create from serialization only
	CMonteCarloDoc();
	DECLARE_DYNCREATE(CMonteCarloDoc)

// Attributes
public:
	BOOL m_bDrawPoints;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMonteCarloDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	UINT m_Method;
	BOOL NextPoint();
	void GetPoint(double &x, double &y);
	double GetDuration();
	double GetPi();
	BOOL m_bRun;
	static UINT Simulate(LPVOID lParam);
	static UINT GatherData(LPVOID lParam);
	double m_X;
	double m_Y;
	unsigned long m_nHits;
	unsigned long m_nPoints;
	
	virtual ~CMonteCarloDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	CWinThread * m_pSimuThread;
	CWinThread * m_pDataThread;
	void SetMethod(UINT nMethod);
	void Reset();
	CEvent m_DataAvailableEvt;
	CPointList m_PointList;

	clock_t m_Start;
	clock_t m_End;
	//{{AFX_MSG(CMonteCarloDoc)
	afx_msg void OnStart();
	afx_msg void OnStop();
	afx_msg void OnDrawpoints();
	afx_msg void OnUpdateDrawpoints(CCmdUI* pCmdUI);
	afx_msg void OnDirect();
	afx_msg void OnUpdateDirect(CCmdUI* pCmdUI);
	afx_msg void OnXml();
	afx_msg void OnUpdateXml(CCmdUI* pCmdUI);
	afx_msg void OnXmlrpc();
	afx_msg void OnUpdateXmlrpc(CCmdUI* pCmdUI);
	afx_msg void OnXmlpug();
	afx_msg void OnUpdateXmlpug(CCmdUI* pCmdUI);
	afx_msg void OnXMLite();
	afx_msg void OnUpdateXMLite(CCmdUI* pCmdUI);
	afx_msg void OnExpat();
	afx_msg void OnUpdateExpat(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	static CMonteCarloDoc * m_pPseudoThis;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MONTECARLODOC_H__00A43DB8_0024_4CEE_8C3D_EF98220A19D0__INCLUDED_)
