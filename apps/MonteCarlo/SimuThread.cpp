// SimuThread.cpp : implementation file
//

#include "stdafx.h"
#include "MonteCarlo.h"
#include "SimuThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSimuThread

IMPLEMENT_DYNCREATE(CSimuThread, CWinThread)

CSimuThread::CSimuThread()
{
}

CSimuThread::~CSimuThread()
{
}

BOOL CSimuThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CSimuThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CSimuThread, CWinThread)
	//{{AFX_MSG_MAP(CSimuThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimuThread message handlers

int CSimuThread::Run() 
{
	srand((unsigned)time(NULL));
	CFrameWnd * pFrame = (CFrameWnd *)(AfxGetApp()->m_pMainWnd);

	CView * pView = pFrame->GetActiveView();

	if ( !pView )
		return 1;

	// Fail if view is of wrong kind
	// (this could occur with splitter windows, or additional
	// views on a single document
//	if ( ! pView->IsKindOf( RUNTIME_CLASS(CMonteCarloView) ) )
//		return 1;


	for(int i = 0; i < 100000; i++) {
		m_X = (double)((double)rand() / RAND_MAX * 2) - 1;
		m_Y = (double)((double)rand() / RAND_MAX * 2) - 1;
		
		SendMessage(pView->m_hWnd, WM_PAINT, 0, 0);
	}

	return CWinThread::Run();
}
