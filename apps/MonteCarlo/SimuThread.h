#if !defined(AFX_SIMUTHREAD_H__5BFDA472_DD25_43CF_887D_1E3B71A218D1__INCLUDED_)
#define AFX_SIMUTHREAD_H__5BFDA472_DD25_43CF_887D_1E3B71A218D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SimuThread.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CSimuThread thread

class CSimuThread : public CWinThread
{
	DECLARE_DYNCREATE(CSimuThread)
protected:
	CSimuThread();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimuThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

// Implementation
protected:
	double m_X;
	double m_Y;
	virtual ~CSimuThread();

	// Generated message map functions
	//{{AFX_MSG(CSimuThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMUTHREAD_H__5BFDA472_DD25_43CF_887D_1E3B71A218D1__INCLUDED_)
