#if !defined(AFX_PROPERTYLIST_H__74205380_1B56_11D4_BC48_00105AA2186F__INCLUDED_)
#define AFX_PROPERTYLIST_H__74205380_1B56_11D4_BC48_00105AA2186F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropertyList.h : header file
//

#define PIT_COMBO	0  //PIT = property item type
#define PIT_EDIT	1
#define PIT_COLOR	2
#define PIT_FONT	3
#define PIT_FILE	4

#define IDC_PROPCMBBOX   712
#define IDC_PROPEDITBOX  713
#define IDC_PROPBTNCTRL  714


/////////////////////////////////////////////////////////////////////////////
//CPropertyList Items
class CPropertyItem
{
// Attributes
public:
	CString m_propName;
	CString m_curValue;
	int m_nItemType;
	CString m_cmbItems;

public:
	CPropertyItem() {};

	CPropertyItem(CString propName, CString curValue, int nItemType, CString cmbItems)
	{
		m_propName = propName;
		m_curValue = curValue;
		m_nItemType = nItemType;
		m_cmbItems = cmbItems;
	}

	virtual CString GetValue()
	{
		return m_curValue;
	}
	
	virtual void SetValue(CString sValue)
	{
		m_curValue = sValue;
	}

	virtual void SetValue(int v)
	{
		m_curValue.Format("%d", v);
	}
};

/////////////////////////////////////////////////////////////////////////////
//CPropertyList Items
class CPropertyItemInt : public CPropertyItem
{
// Attributes
public:
	int *m_pnValue;

public:
	CPropertyItemInt() {};

	CPropertyItemInt(CString propName, int *pValue, int nItemType, CString cmbItems)
	{
		m_propName = propName;
		m_pnValue = pValue;
		m_nItemType = nItemType;
		m_cmbItems = cmbItems;
	}

	virtual CString GetValue()
	{
		CString s;
		s.Format("%d", *m_pnValue);
		return s;
	}

	virtual void SetValue(CString sValue)
	{
		*m_pnValue = atoi(sValue);
	}

	virtual void SetValue(int v)
	{
		*m_pnValue = v;
	}
};

/////////////////////////////////////////////////////////////////////////////
//CPropertyList Items
class CPropertyItemStr : public CPropertyItem
{
// Attributes
public:
	LPTSTR m_str;

public:
	CPropertyItemStr() {};

	CPropertyItemStr(CString propName, LPCTSTR s, int nItemType, CString cmbItems)
	{
		m_propName = propName;
		m_str = (LPTSTR)s;
		m_nItemType = nItemType;
		m_cmbItems = cmbItems;
	}

	virtual CString GetValue()
	{
		return m_str;
	}

	virtual void SetValue(CString sValue)
	{
		sprintf(m_str, "%d", atoi(sValue));
	}

	virtual void SetValue(int v)
	{
		sprintf(m_str, "%d", v);
	}
};


/////////////////////////////////////////////////////////////////////////////
// CPropertyList window

class CPropertyList : public CListBox
{
// Construction
public:
	CPropertyList();

// Attributes
public:

// Operations
public:
	int AddItem(CString txt);
	int AddPropItem(CPropertyItem* pItem);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropertyList)
	public:
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PreSubclassWindow();
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

// Implementation
public:
	void InvalidateDataPart();
	virtual ~CPropertyList();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPropertyList)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSelchange();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg void OnKillfocusCmbBox();
	afx_msg void OnSelchangeCmbBox();
	afx_msg void OnKillfocusEditBox();
	afx_msg void OnChangeEditBox();
	afx_msg void OnButton();

	DECLARE_MESSAGE_MAP()

	void InvertLine(CDC* pDC,CPoint ptFrom,CPoint ptTo);
	void DisplayButton(CRect region);

	CComboBox m_cmbBox;
	CEdit m_editBox;
	CButton m_btnCtrl;
	CFont m_SSerif8Font;
	
	int m_curSel,m_prevSel;
	int m_nDivider;
	int m_nDivTop;
	int m_nDivBtm;
	int m_nOldDivX;
	int m_nLastBox;
	BOOL m_bTracking;
	BOOL m_bDivIsSet;
	HCURSOR m_hCursorArrow;
	HCURSOR m_hCursorSize;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTYLIST_H__74205380_1B56_11D4_BC48_00105AA2186F__INCLUDED_)
