// SimuDoc.h : interface of the CSimuDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIMUDOC_H__CE1EB5B7_8DB5_4D86_8538_80A5F4CE69F8__INCLUDED_)
#define AFX_SIMUDOC_H__CE1EB5B7_8DB5_4D86_8538_80A5F4CE69F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Afxtempl.h>

class CSimuDoc : public CDocument
{
protected: // create from serialization only
	CSimuDoc();
	DECLARE_DYNCREATE(CSimuDoc)

// Attributes
public:
	CObArray *m_pArTimeValues;
	CUIntArray m_HeightArray;
	int *m_HeightMap;
	CString m_sRecv;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimuDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	int GetHeight(int x, int y);
	void SetHeightValue(int x, int y, int nValue);
	void CreateHeightMap(int nWidth, int nHeight);
	int m_nMapWidth;
	int m_nMapHeight;

	virtual ~CSimuDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	

// Generated message map functions
protected:
	void DeleteHeightMap();
	//{{AFX_MSG(CSimuDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

inline void CSimuDoc::SetHeightValue(int x, int y, int nValue)
{
	if (!m_HeightMap) {
		return;
	}

	m_HeightMap[x + y * m_nMapHeight] = nValue;
}

inline int CSimuDoc::GetHeight(int x, int y)
{
	if (!m_HeightMap) {
		return -1;
	}
	else if (x > m_nMapWidth || y > m_nMapHeight) {
		return -1;
	}
	else if (x < 0 || y < 0) {
		return -1;
	}

	return m_HeightMap[x + y * m_nMapHeight];
}

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMUDOC_H__CE1EB5B7_8DB5_4D86_8538_80A5F4CE69F8__INCLUDED_)
