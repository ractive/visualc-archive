// LandscapeView.h : interface of the CLandscapeView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LANDSCAPEVIEW_H__D8E67245_497C_4C2D_B8EC_7083C1F80202__INCLUDED_)
#define AFX_LANDSCAPEVIEW_H__D8E67245_497C_4C2D_B8EC_7083C1F80202__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define		MAP_SIZE	  1024							// Size Of Our .RAW Height Map (NEW)
#define		DELTA_S			16							// Width And Height Of Each Quad (NEW)
#define		HEIGHT_RATIO  1.5f							// Ratio That The Y Is Scaled According To The X And Z (NEW)


class CLandscapeView : public CView
{
protected: // create from serialization only
	CLandscapeView();
	DECLARE_DYNCREATE(CLandscapeView)

// Attributes
public:
	CLandscapeDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLandscapeView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	double m_fps;
	virtual ~CLandscapeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	BOOL m_bRender;
	HGLRC m_hRC;
	HDC m_hDC;
	GLvoid ReSizeGLScene(GLsizei width, GLsizei height);
	void LoadRawFile(LPSTR strName, int nSize, BYTE *pHeightMap);
	int Height(BYTE *pHeightMap, int X, int Y);
	int InitGL(GLvoid);
	void SetVertexColor(int h, int x, int y);
	void RenderHeightMap(BYTE pHeightMap[]);
	int DrawGLScene(GLvoid);
	void output_time( double time );
	double interval_time( LARGE_INTEGER startCount, LARGE_INTEGER endCount);
	void output_fps( double fps );
	int m_nFrames;

	LARGE_INTEGER timerFrequency;
	LARGE_INTEGER startCount;
	LARGE_INTEGER endCount;

	BYTE g_HeightMap[MAP_SIZE*MAP_SIZE];					// Holds The Height Map Data (NEW)
	float g_ColorMap[MAP_SIZE][MAP_SIZE][3];				// Holds The Height Map Data (NEW)

	float scaleValue;								// Scale Value For The Terrain (NEW)
	int pos_x;
	int pos_y;
	int pos_z;
	int view_x;
	int view_y;
	int view_z;
	int up_x;
	int up_y;
	int up_z;

	double color_offset;


	//{{AFX_MSG(CLandscapeView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRender();
	afx_msg void OnUpdateRender(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in LandscapeView.cpp
inline CLandscapeDoc* CLandscapeView::GetDocument()
   { return (CLandscapeDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LANDSCAPEVIEW_H__D8E67245_497C_4C2D_B8EC_7083C1F80202__INCLUDED_)
