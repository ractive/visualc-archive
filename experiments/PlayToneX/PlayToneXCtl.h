#if !defined(AFX_PLAYTONEXCTL_H__D5FC41A8_320E_436F_B21C_B76885394E36__INCLUDED_)
#define AFX_PLAYTONEXCTL_H__D5FC41A8_320E_436F_B21C_B76885394E36__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// PlayToneXCtl.h : Declaration of the CPlayToneXCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CPlayToneXCtrl : See PlayToneXCtl.cpp for implementation.

class CPlayToneXCtrl : public COleControl
{
	DECLARE_DYNCREATE(CPlayToneXCtrl)

// Constructor
public:
	CPlayToneXCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlayToneXCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CPlayToneXCtrl();

	DECLARE_OLECREATE_EX(CPlayToneXCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CPlayToneXCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CPlayToneXCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CPlayToneXCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CPlayToneXCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CPlayToneXCtrl)
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CPlayToneXCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CPlayToneXCtrl)
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYTONEXCTL_H__D5FC41A8_320E_436F_B21C_B76885394E36__INCLUDED)
