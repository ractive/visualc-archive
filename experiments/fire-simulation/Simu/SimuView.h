// SimuView.h : interface of the CSimuView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIMUVIEW_H__5992C6DB_8D60_4177_9EB2_2C4332FD774C__INCLUDED_)
#define AFX_SIMUVIEW_H__5992C6DB_8D60_4177_9EB2_2C4332FD774C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "fireLib.h"

class CSimuSocket;

class CSimuView : public CEditView
{
	struct watchThreadInfo {
		TCHAR sDir[MAX_PATH];
		HWND hWnd;
		HANDLE hNewDir;
		HANDLE hKillMe;
	};
	
	typedef watchThreadInfo * LPWATCHTHREADINFO;

protected: // create from serialization only
	CSimuView();
	DECLARE_DYNCREATE(CSimuView)

// Attributes
public:
	CSimuDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimuView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	void Simulate(double toTime);
	virtual ~CSimuView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	static UINT WatchChangeThreadProc(LPVOID pParam);
	LPWATCHTHREADINFO m_pThreadInfo;
	CWinThread * m_pThread;

	CSimuSocket * m_SimuSocket;



    /* neighbor's address*/     /* N  NE   E  SE   S  SW   W  NW */
    int nCol[8];
    int nRow[8];
    int nTimes;      /* counter for number of time steps */
    FuelCatalogPtr catalog;     /* fuel catalog handle */
    double nDist[8];            /* distance to each neighbor */
    double nAzm[8];             /* compass azimuth to each neighbor (0=N) */
    double timeNow;             /* current time (minutes) */
    double timeNext;            /* time of next cell ignition (minutes) */
    int    row, col, cell;      /* row, col, and index of current cell */
    int    nrow, ncol, ncell;   /* row, col, and index of neighbor cell */
    int    n, cells;            /* neighbor index, total number of map cells */
    size_t modelNumber;         /* fuel model number at current cell */
    double moisture[6];         /* fuel moisture content at current cell */
    double fpm;                 /* spread rate in direction of neighbor */
    double minutes;             /* time to spread from cell to neighbor */
    double ignTime;             /* time neighbor is ignited by current cell */
    int    atEdge;              /* flag indicating fire has reached edge */
    size_t *fuelMap;            /* ptr to fuel model map */
    double *ignMap;             /* ptr to ignition time map (minutes) */
    double *flMap;              /* ptr to flame length map (feet) */
    double *slpMap;             /* ptr to slope map (rise/reach) */
    double *aspMap;             /* ptr to aspect map (degrees from north) */
    double *wspdMap;            /* ptr to wind speed map (ft/min) */
    double *wdirMap;            /* ptr to wind direction map (deg from north) */
    double *m1Map;              /* ptr to 1-hr dead fuel moisture map */
    double *m10Map;             /* ptr to 10-hr dead fuel moisture map */
    double *m100Map;            /* ptr to 100-hr dead fuel moisture map */
    double *mherbMap;           /* ptr to live herbaceous fuel moisture map */
    double *mwoodMap;           /* ptr to live stem fuel moisture map */

	/* NOTE 1: Change these to modify map size & resolution. */
	int    Rows;     /* Number of rows in each map. */
	int    Cols;     /* Number of columns in each map. */
	double CellWd;    /* Cell width (E-W) in feet. */
	double CellHt;    /* Cell height (N-S) in feet. */

	/* NOTE 2: Change these to set uniform burning conditions. */
	size_t Model;      /* NFFL 1 */
	double WindSpd;     /* mph */
	double WindDir;     /* degrees clockwise from north */
	double Slope;    /* fraction rise / reach */
	double Aspect;    /* degrees clockwise from north */
	double M1;    /* 1-hr dead fuel moisture */
	double M10;    /* 10-hr dead fuel moisture */
	double M100;    /* 100-hr dead fuel moisture */
	double Mherb;   /* Live herbaceous fuel moisture */
	double Mwood;   /* Live woody fuel moisture */

// Generated message map functions
protected:
	void FillSlopeMap();
	void DeleteArrays();
	void InitArrays();
	BOOL m_bFirst;
	UINT m_nCount;
	BOOL InitSocket();
	void GetData();
	//{{AFX_MSG(CSimuView)
	afx_msg void OnDestroy();
	afx_msg void OnFilecomm();
	afx_msg void OnSocketcomm();
	afx_msg void OnUpdateSocketcomm(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilecomm(CCmdUI* pCmdUI);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	
	afx_msg LRESULT OnFileChange(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnData(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SimuView.cpp
inline CSimuDoc* CSimuView::GetDocument()
   { return (CSimuDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMUVIEW_H__5992C6DB_8D60_4177_9EB2_2C4332FD774C__INCLUDED_)

