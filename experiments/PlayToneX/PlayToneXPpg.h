#if !defined(AFX_PLAYTONEXPPG_H__2425D0EE_54C0_4E55_A09E_5EE90D222D22__INCLUDED_)
#define AFX_PLAYTONEXPPG_H__2425D0EE_54C0_4E55_A09E_5EE90D222D22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// PlayToneXPpg.h : Declaration of the CPlayToneXPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CPlayToneXPropPage : See PlayToneXPpg.cpp.cpp for implementation.

class CPlayToneXPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CPlayToneXPropPage)
	DECLARE_OLECREATE_EX(CPlayToneXPropPage)

// Constructor
public:
	CPlayToneXPropPage();

// Dialog Data
	//{{AFX_DATA(CPlayToneXPropPage)
	enum { IDD = IDD_PROPPAGE_PLAYTONEX };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CPlayToneXPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYTONEXPPG_H__2425D0EE_54C0_4E55_A09E_5EE90D222D22__INCLUDED)
