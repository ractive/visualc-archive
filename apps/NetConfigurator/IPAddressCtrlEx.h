#if !defined(AFX_IPADDRESSCTRLEX_H__C1654190_B134_4F32_A52C_9775956BE789__INCLUDED_)
#define AFX_IPADDRESSCTRLEX_H__C1654190_B134_4F32_A52C_9775956BE789__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IPAddressCtrlEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIPAddressCtrlEx window

class CIPAddressCtrlEx : public CIPAddressCtrl
{
// Construction
public:
	CIPAddressCtrlEx();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIPAddressCtrlEx)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetAddressString(CString sIP);
	CString GetAddressString();
	virtual ~CIPAddressCtrlEx();

	// Generated message map functions
protected:
	//{{AFX_MSG(CIPAddressCtrlEx)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IPADDRESSCTRLEX_H__C1654190_B134_4F32_A52C_9775956BE789__INCLUDED_)
