// SimuView.cpp : implementation of the CSimuView class
//

#include "stdafx.h"
#include "Simu.h"

#include "SimuDoc.h"
#include "SimuView.h"
#include "SimuSocket.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define INFINITY 999999999.     /* or close enough */


/////////////////////////////////////////////////////////////////////////////
// CSimuView

IMPLEMENT_DYNCREATE(CSimuView, CEditView)

BEGIN_MESSAGE_MAP(CSimuView, CEditView)
	//{{AFX_MSG_MAP(CSimuView)
	ON_WM_DESTROY()
	ON_COMMAND(ID_FILECOMM, OnFilecomm)
	ON_COMMAND(ID_SOCKETCOMM, OnSocketcomm)
	ON_UPDATE_COMMAND_UI(ID_SOCKETCOMM, OnUpdateSocketcomm)
	ON_UPDATE_COMMAND_UI(ID_FILECOMM, OnUpdateFilecomm)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_FILECHANGE, OnFileChange)
	ON_MESSAGE(WM_DATA, OnData)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimuView construction/destruction

CSimuView::CSimuView()
{
	m_pThreadInfo = new watchThreadInfo;
	m_SimuSocket = NULL;
	m_pThread = NULL;
	m_nCount = 2;
	m_bFirst = TRUE;

	/* NOTE 1: Change these to modify map size & resolution. */
	Rows   = 101;     /* Number of rows in each map. */
	Cols   = 101;     /* Number of columns in each map. */
	CellWd = 100.;    /* Cell width (E-W) in feet. */
	CellHt = 100.;    /* Cell height (N-S) in feet. */

	/* NOTE 2: Change these to set uniform burning conditions. */
	Model   = 1;      /* NFFL 1 */
	WindSpd = 2.;     /* mph */
	WindDir = 45.;     /* degrees clockwise from north */
	Slope   = 0.0;    /* fraction rise / reach */
	Aspect  = 0.0;    /* degrees clockwise from north */
	M1      = .10;    /* 1-hr dead fuel moisture */
	M10     = .10;    /* 10-hr dead fuel moisture */
	M100    = .10;    /* 100-hr dead fuel moisture */
	Mherb   = 1.00;   /* Live herbaceous fuel moisture */
	Mwood   = 1.50;   /* Live woody fuel moisture */

	nCol[0] =  0;
	nCol[1] = 1;
	nCol[2] = 1;
	nCol[3] = 1;
	nCol[4] = 0;
	nCol[5] = -1;
	nCol[6] = -1;
	nCol[7] = -1;

	nRow[0] =  1;
	nRow[1] = 1;
	nRow[2] = 0;
	nRow[3] = -1;
	nRow[4] = -1;
	nRow[5] = -1;
	nRow[6] = 0;
	nRow[7] = 1;

	ignMap   = NULL;
	flMap    = NULL;
	slpMap   = NULL;
	aspMap   = NULL;
	wspdMap  = NULL;
	wdirMap  = NULL;
	m1Map    = NULL;
	m10Map   = NULL;
	m100Map  = NULL;
	mherbMap = NULL;
	mwoodMap = NULL;
	fuelMap  = NULL;

	InitArrays();
}

CSimuView::~CSimuView()
{
	DeleteArrays();
	delete m_pThreadInfo;
}

BOOL CSimuView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CSimuView drawing

void CSimuView::OnDraw(CDC* pDC)
{
	CSimuDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CSimuView diagnostics

#ifdef _DEBUG
void CSimuView::AssertValid() const
{
	CEditView::AssertValid();
}

void CSimuView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CSimuDoc* CSimuView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSimuDoc)));
	return (CSimuDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSimuView message handlers


UINT CSimuView::WatchChangeThreadProc(LPVOID pParam)
{
	LPWATCHTHREADINFO pInfo = (LPWATCHTHREADINFO)pParam;

	while (1) {
		HANDLE hFileNotification = ::FindFirstChangeNotification(pInfo->sDir, FALSE, FILE_NOTIFY_CHANGE_FILE_NAME);
		HANDLE ahHandles[3];
		ahHandles[0] = hFileNotification;
		ahHandles[1] = pInfo->hNewDir;
		ahHandles[2] = pInfo->hKillMe;

		DWORD dwRet = WaitForMultipleObjects(3, ahHandles, FALSE, INFINITE);
		if (dwRet - WAIT_OBJECT_0 == 0) {
			// hFileNotification was signaled
			
			// Now we eat up all other events that occur just shortly after.
			// Think about if the user copies 30 files to your folder, we'd get
			// 30 notification messages

			DWORD dwMilSecs = 500; // Wait 1/2 second to go on
			/*do {
				FindNextChangeNotification(hFileNotification);
				dwRet = WaitForSingleObject(hFileNotification, dwMilSecs);
			} while(dwRet == WAIT_OBJECT_0);*/

			// Post a notification message that something changed
			::PostMessage(pInfo->hWnd, WM_FILECHANGE, 0, 0);
		}
		else if (dwRet - WAIT_OBJECT_0 == 1) {
			// pInfo->hNewDir was signaled

			// Get a new filenotification handle
			if (hFileNotification) {
				FindCloseChangeNotification(hFileNotification);
			}
			
			hFileNotification = ::FindFirstChangeNotification(pInfo->sDir, FALSE, FILE_NOTIFY_CHANGE_FILE_NAME);

			// Reset the event and go on...
			ResetEvent(pInfo->hNewDir);
		}
		else if (dwRet - WAIT_OBJECT_0 == 2) {
			// pInfo->hKillMe was signaled
			// leave the loop to exit the thread
			if (hFileNotification) {
				FindCloseChangeNotification(hFileNotification);
			}
			break;
		}
		else {
			// Here we end i.e. if the directory doesn't exist any more
			continue;
		}
	}

	TRACE("Watch Thread ended gracefully!\r\n");

	return 0;
}

LRESULT CSimuView::OnData(WPARAM wParam, LPARAM lParam)
{
	int nFound = 0;

	CSimuDoc * pDoc = GetDocument();

	if (pDoc->m_sRecv.Left(3) == "MAP") {
		int nHeight = 0, nWidth = 0;

		sscanf(pDoc->m_sRecv, "MAP %d %d\r\n", &nHeight, &nWidth);

		int nOldStart = pDoc->m_sRecv.Find("\r\n");
		nOldStart += 2;

		while((nFound = pDoc->m_sRecv.Find("\r\n", nOldStart)) != -1) {
			int nRand = 0;
			int nOffset = 64;
			int nCounter = 0;
			int nStart = 0;
			int x = 0, y = 0;

			Rows = nHeight;
			Cols = nWidth;

			InitArrays();

			/* NOTE 5: set an ignition time & pattern (this ignites the middle cell). */
			srand( (unsigned)time( NULL ) );
			rand();
			int nX = Cols * rand() / RAND_MAX;
			int nY = Rows * rand() / RAND_MAX;
			//nX = 30;
			//nY = 30;
			cell = nX + nX * nY;
			//cell = Cols/2 + Cols*(Rows/4);
			ignMap[cell] = 1.0;


			/* NOTE 6: create a standard fuel model catalog and a flame length table. */
			catalog = Fire_FuelCatalogCreateStandard("Standard", 13);
			Fire_FlameLengthTable(catalog, 500, 0.1);

			/* Calculate distance across cell to each neighbor and its azimuth. */
			for ( n=0; n<8; n++ )
			{
				nDist[n] = sqrt ( nCol[n] * CellWd * nCol[n] * CellWd
								+ nRow[n] * CellHt * nRow[n] * CellHt );
				nAzm[n] = n * 45.;
			}

			/* NOTE 7: find the earliest (starting) ignition time. */
			for ( timeNext=INFINITY, cell=0; cell<cells; cell++ )
			{
				if ( ignMap[cell] < timeNext )
					timeNext = ignMap[cell];
			}

			pDoc->CreateHeightMap(nWidth, nHeight);

			while((nStart = pDoc->m_sRecv.Find(" ", nOldStart)) != -1) {
				if (nStart > nFound) {
					break;
				}

				UINT n = atoi(pDoc->m_sRecv.Mid(nOldStart, nStart));
			
				pDoc->SetHeightValue(x, y, n);

				nOldStart = nStart + 1;
				nCounter++;
				x++;
				if (x > nWidth) {
					x = 0;
					y++;
				}
			}

			FillSlopeMap();

			pDoc->m_sRecv.Delete(0, nFound + 2);
		}
	}
	else if (pDoc->m_sRecv.Left(6) == "VALUES") {
		float fTime = 0;
		sscanf(pDoc->m_sRecv, "VALUES %f\r\n", &fTime);
		int nLine = pDoc->m_sRecv.Find("\r\n");
		if (nLine != -1) {
			pDoc->m_sRecv.Delete(0, nLine + 2);
		}

		Simulate(fTime);
	}


	/*CUIntArray * arValues2 = NULL;
	CUIntArray * arValues = NULL;
		
	while((nFound = pDoc->m_sRecv.Find("\r\n")) != -1) {
		arValues = (CUIntArray *)pDoc->m_pArTimeValues->GetAt(m_nCount % 2);
		arValues2 = (CUIntArray *)pDoc->m_pArTimeValues->GetAt((m_nCount + 1) % 2);
		pDoc->m_HeightArray.RemoveAll();

		int nStart = 0;
		int nOldStart = 0;
		int nRand = 0;
		int nOffset = 64;
		char b[4];
		int nCounter = 0;
		CString sSendBuf = "[";

		while((nStart = pDoc->m_sRecv.Find(" ", nOldStart)) != -1) {
			if (nStart > nFound) {
				break;
			}

			UINT n = atoi(pDoc->m_sRecv.Mid(nOldStart, nStart));
		
			pDoc->m_HeightArray.Add(n);

			if (m_bFirst) {
				arValues->Add(0);
				arValues2->Add(0);
			}

			nOldStart = nStart + 1;
			nCounter++;
		}

		if (m_bFirst) {
			int nMapSize = (int)sqrt(nCounter) / 2;
			
			srand( (unsigned)time( NULL ) );
			//rand();

			int nX = nMapSize * rand() / RAND_MAX + nMapSize / 2;
			int nY = nMapSize * rand() / RAND_MAX + nMapSize / 2;
			//nY = 50;
			nX = 5;
			arValues->SetAt(nY * nMapSize + nX, 1);
			arValues2->SetAt(nY * nMapSize + nX, 1);
		}

		m_bFirst = FALSE;
		
		Simulate();

		int nSize = arValues->GetSize();
		
		for(int i = 0; i < nSize; i++) {

			sSendBuf += itoa(arValues->GetAt(i), b, 10);
			sSendBuf += ", ";
		}

		// Delete the last ", " separator
		sSendBuf.Delete(sSendBuf.GetLength() - 2, 2);
		sSendBuf += "]";

		//GetEditCtrl().SetWindowText(sSendBuf);

		// Send the data
		m_SimuSocket->SendData(sSendBuf, sSendBuf.GetLength());

		m_nCount++;

		pDoc->m_sRecv.Delete(0, nFound + 2);
	}*/

	return 0;
}

LRESULT CSimuView::OnFileChange(WPARAM wParam, LPARAM lParam)
{
	CFileFind finder;
	if (finder.FindFile("C:\\IPC\\ipc_out.lock")) {
		return 0;
	}
	finder.Close();

	// Let's see if we find the data file
	if (finder.FindFile("C:\\IPC\\ipc_in.dat")) {
		CFileFind LockFinder;

		if (LockFinder.FindFile("C:\\IPC\\ipc_in.lock")) {
			// If we find the lock file, the file is not ready yet
			finder.Close();
			LockFinder.Close();
			return 0;
		}
		// We found the data file, but not the lock file
		// Get the data and process it.
		GetData();
	}

	return 1;
}

void CSimuView::OnInitialUpdate() 
{
	CEditView::OnInitialUpdate();
	
	m_pThreadInfo->hKillMe = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_pThreadInfo->hNewDir = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_pThreadInfo->hWnd = m_hWnd;
	strcpy(m_pThreadInfo->sDir, "C:\\IPC");

	m_pThread = AfxBeginThread(WatchChangeThreadProc, m_pThreadInfo, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);
	m_pThread->m_bAutoDelete = FALSE;
}

void CSimuView::OnDestroy() 
{
	CEditView::OnDestroy();
	
	SetEvent(m_pThreadInfo->hKillMe);
	
	if (m_pThread) {
		// Give 3 sec. to exit the thread gracefully
		if (WaitForSingleObject(m_pThread->m_hThread, 3000) != WAIT_OBJECT_0) {
			// Kill the thread with brute force...
			TerminateThread(m_pThread->m_hThread, 0);
		}

		delete m_pThread;
		m_pThread = NULL;
	}

	delete m_SimuSocket;
	
}

void CSimuView::GetData()
{
	/*CSimuDoc * pDoc = GetDocument();
	int nFound = 0;

	CUIntArray * arValues2 = NULL;
	CUIntArray * arValues = NULL;

	CFile file;
	if (!file.Open("C:\\IPC\\ipc_in.dat", CFile::modeRead | CFile::shareDenyWrite)) {
		return;
	}

	DWORD dwFileLength = file.GetLength();

	char* buf = pDoc->m_sRecv.GetBuffer(dwFileLength + 1);

	DWORD dwRead = file.ReadHuge(buf, dwFileLength);
	if (dwRead == 0) {
		return;
	}
	buf[dwRead] = '\0';
	file.Close();

	pDoc->m_sRecv.ReleaseBuffer();

	pDoc->m_sRecv.TrimLeft("[");
	pDoc->m_sRecv.TrimRight("]");
	int nStart = 0;
	int nOldStart = 0;
	

	arValues = (CUIntArray *)pDoc->m_pArTimeValues->GetAt(m_nCount % 2);
	arValues2 = (CUIntArray *)pDoc->m_pArTimeValues->GetAt((m_nCount + 1) % 2);
	pDoc->m_HeightArray.RemoveAll();

	int nRand = 0;
	int nOffset = 64;
	int nCounter = 0;
	CString sSendBuf = "[";

	while((nStart = pDoc->m_sRecv.Find(", ", nOldStart)) != -1) {
		if (nStart > nFound) {
			break;
		}

		UINT n = atoi(pDoc->m_sRecv.Mid(nOldStart, nStart));
	
		pDoc->m_HeightArray.Add(n);

		if (m_bFirst) {
			arValues->Add(0);
			arValues2->Add(0);
		}

		nOldStart = nStart + 2;
		nCounter++;
	}

	if (m_bFirst) {
		int nMapSize = (int)sqrt(nCounter) / 2;
		
		srand( (unsigned)time( NULL ) );
		//rand();

		int nX = nMapSize * rand() / RAND_MAX + nMapSize / 2;
		int nY = nMapSize * rand() / RAND_MAX + nMapSize / 2;
		//nY = 50;
		nX = 5;
		arValues->SetAt(nY * nMapSize + nX, 1);
		arValues2->SetAt(nY * nMapSize + nX, 1);
	}

	m_bFirst = FALSE;
	
	Simulate();*/

	/*int nSize = arValues->GetSize();
	
	for(int i = 0; i < nSize; i++) {

		sSendBuf += itoa(arValues->GetAt(i), b, 10);
		sSendBuf += ", ";
	}

	// Delete the last ", " separator
	sSendBuf.Delete(sSendBuf.GetLength() - 2, 2);
	sSendBuf += "]";*/

	//GetEditCtrl().SetWindowText(sSendBuf);

	// Send the data
	//m_SimuSocket->SendData(sSendBuf, sSendBuf.GetLength());

	m_nCount++;

	//pDoc->m_sRecv.Delete(0, nFound + 2);



	/*Simulate();


	CFile outLockFile;
	CFile outFile;

	if (outLockFile.Open("C:\\IPC\\ipc_out.lock", CFile::modeCreate | CFile::shareExclusive)) {
		if (outFile.Open("C:\\IPC\\ipc_out.dat", CFile::modeWrite | CFile::modeCreate | CFile::shareExclusive)) {
	
			CUIntArray * pRes = (CUIntArray *)GetDocument()->m_pArTimeValues->GetAt(0);
			
			int nSize = pRes->GetSize();
			char b[5];
			
			CString sBuf;

			for(int i = 0; i < nSize; i++) {
				itoa(pRes->GetAt(i), b, 10);
				outFile.Write(b, strlen(b));
				sBuf += b;
				if (i + 1 < nSize) {
					outFile.Write(" ", 1);
					sBuf += " ";
				}
			}

			
			//GetEditCtrl().SetWindowText(sBuf);

			outFile.Close();
		}
		
		outLockFile.Close();
	}


	DeleteFile("C:\\IPC\\ipc_out.lock");

	DeleteFile("C:\\IPC\\ipc_in.dat");

	delete[] buf;*/
}

void CSimuView::Simulate(double toTime)
{
	toTime *= 120;
	if (timeNext >= toTime) {
		return;
	}

    /* NOTE 8: loop until no more cells can ignite or fire reaches an edge. */
    atEdge = 0;
    while ( timeNext < toTime && ! atEdge )
    {
        timeNow  = timeNext;
        timeNext = INFINITY;
        nTimes++;

        /* NOTE 9: examine each ignited cell in the fuel array. */
        for ( cell=0, row=0; row<Rows; row++ )
        {
            for ( col=0; col<Cols; col++, cell++ )
            {
                /* Skip this cell if it has not ignited. */
                if ( ignMap[cell] > timeNow )
                {
                    /* NOTE 12: first check if it is the next cell to ignite. */
                    if ( ignMap[cell] < timeNext )
                        timeNext = ignMap[cell];
                    continue;
                }

                /* NOTE 10: flag if the fire has reached the array edge. */
                if ( row==0 || row==Rows-1 || col==0 || col==Cols-1 )
                    atEdge = 1;

                /* NOTE 11: determine basic fire behavior within this cell. */
                modelNumber = fuelMap[cell];
                moisture[0] = m1Map[cell];
                moisture[1] = m10Map[cell];
                moisture[2] = m100Map[cell];
                moisture[3] = m100Map[cell];
                moisture[4] = mherbMap[cell];
                moisture[5] = mwoodMap[cell];
                Fire_SpreadNoWindNoSlope(catalog, modelNumber, moisture);
                Fire_SpreadWindSlopeMax(catalog, modelNumber, wspdMap[cell],
                    wdirMap[cell], slpMap[cell], aspMap[cell]);

                /* NOTE 12: examine each unignited neighbor. */
                for ( n=0; n<8; n++ )
                {
                    /* First find the neighbor's location. */
                    nrow = row + nRow[n];
                    ncol = col + nCol[n];
                    if ( nrow<0 || nrow>=Rows || ncol<0 || ncol>=Cols )
                        continue;
                    ncell = ncol + nrow*Cols;

                    /* Skip this neighbor if it is already ignited. */
                    if ( ignMap[ncell] <= timeNow )
                        continue;

                    /* Determine time to spread to this neighbor. */
                    Fire_SpreadAtAzimuth(catalog, modelNumber, nAzm[n], FIRE_NONE);
                    if ( (fpm = Fuel_SpreadAny(catalog, modelNumber)) > Smidgen)
                    {
                        minutes = nDist[n] / fpm;

                        /* Assign neighbor the earliest ignition time. */
                        if ( (ignTime = timeNow + minutes) < ignMap[ncell] )
                        {
                            ignMap[ncell] = ignTime;
                            Fire_FlameScorch(catalog, modelNumber, FIRE_FLAME);
                            flMap[ncell] = Fuel_FlameLength(catalog,modelNumber);
                        }

                        /* Keep track of next cell ignition time. */
                        if ( ignTime < timeNext )
                            timeNext = ignTime;
                    }
                }   /* next neighbor n */
            }   /* next source col */
        }   /* next source row */
    } /* next time */


	CString sSendBuf = "[";
	char b[32];

    for ( cell=0, row=0; row<Rows; row++ ) {
        for ( col=0; col<Cols; col++, cell++ ) {
			itoa((int)(40 * flMap[cell]), b, 10);

			sSendBuf += b;
			sSendBuf += ", ";
		}
	}

	// Delete the last ", " separator
	sSendBuf.Delete(sSendBuf.GetLength() - 2, 2);
	sSendBuf += "]";

	m_SimuSocket->SendData(sSendBuf, sSendBuf.GetLength());

	//GetEditCtrl().SetWindowText(sSendBuf);


	/*CSimuDoc * pDoc = GetDocument();
	CUIntArray * now = NULL;
	now = (CUIntArray *)pDoc->m_pArTimeValues->GetAt(m_nCount % 2);

	CUIntArray * last = NULL;
	if (m_nCount > 0) {
		last = (CUIntArray *)pDoc->m_pArTimeValues->GetAt((m_nCount - 1) % 2);
	}

	int nOffset = 32;
	int nSize = pDoc->m_HeightArray.GetSize();
	int nMapSize = (int)sqrt(nSize);
	int nRand = 0;
	int nNewVal = 0;
	int nNow = 0, nLast = 0, nT = 0, nB = 0, nL = 0, nR = 0;
	int nHeightDiff = 0;
	double dAngle = 0;
	int nHeight = 0;
	int nDelta = 1024 / nMapSize;

	for (int i = 0; i < nSize; i++) {
		
		int y = i / nMapSize;
		int x = i % nMapSize;
		int nHeight = pDoc->m_HeightArray.GetAt(i);

		nNow = 0, nLast = 0, nT = 0, nB = 0, nL = 0, nR = 0;

		nRand = nOffset * rand() / RAND_MAX;
		nNow = now->GetAt(i);
		if (last) {
			nLast = last->GetAt(i);
			if (x > 0) {
				nL = last->GetAt(i - 1);
				if (nL) {
					nHeightDiff = pDoc->m_HeightArray.GetAt(i - 1) - nHeight;
					dAngle = atan((double)nHeightDiff / nDelta);
					if (dAngle > 0) {
						nL = (int)(dAngle * 20 * nL) + 1;
					}
				}
			}
			if (x < nMapSize - 1) {
				nR = last->GetAt(i + 1);
				nHeightDiff = nHeight - pDoc->m_HeightArray.GetAt(i + 1);
				if (nR) {
					nHeightDiff = pDoc->m_HeightArray.GetAt(i + 1) - nHeight;
					dAngle = atan((double)nHeightDiff / nDelta);
					if (dAngle > 0) {
						nR = (int)(dAngle * 20 * nR) + 1;
					}
				}
			}
			if (y > 0) {
				nT = last->GetAt(i - nMapSize);
				nHeightDiff = nHeight - pDoc->m_HeightArray.GetAt(i - nMapSize);
				if (nT) {
					nHeightDiff = pDoc->m_HeightArray.GetAt(i - nMapSize) - nHeight;
					dAngle = atan((double)nHeightDiff / nDelta);
					if (dAngle > 0) {
						nT = (int)(dAngle * 20 * nT) + 1;
					}
				}
			}
			if (y < nMapSize - 1) {
				nB = last->GetAt(i + nMapSize);
				nHeightDiff = nHeight - pDoc->m_HeightArray.GetAt(i + nMapSize);
				if (nB) {
					nHeightDiff = pDoc->m_HeightArray.GetAt(i + nMapSize) - nHeight;
					dAngle = atan((double)nHeightDiff / nDelta);
					if (dAngle > 0) {
						nB = (int)(dAngle * 20 * nB) + 1;
					}
				}
			}

			nNewVal = 0;
			if (nL || nR || nT || nB || nLast) {
				
				nNewVal = (nLast + nL + nR + nT + nB);
				//nNewVal = nLast + __max(nL, __max(nR, __max(nT, __max(nB, nLast))));
				if (nNewVal > 16) {
					nNewVal /= 8;
				}
				
				//TRACE("X: %d, Y: %d, Val: %d\r\n", x, y, nNewVal);
			}
		}

		nNewVal = __max(nNewVal, 0);
		nNewVal = __min(nNewVal, 128);

		now->SetAt(i, nNewVal);
	}
	if (last) {
		for (i = 0; i < nSize; i++) {
			last->SetAt(i, now->GetAt(i));
		}
	}*/
}

void CSimuView::OnFilecomm() 
{
	m_pThread->ResumeThread();	
}

void CSimuView::OnSocketcomm() 
{
	InitSocket();
	
}

void CSimuView::OnUpdateSocketcomm(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CSimuView::OnUpdateFilecomm(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

int CSimuView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEditView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!InitSocket()) {
		return -1;
	}

	return 0;
}

BOOL CSimuView::InitSocket()
{
	if (m_SimuSocket) {
		delete m_SimuSocket;
	}

	m_SimuSocket = new CSimuSocket(m_hWnd);
	if (!m_SimuSocket->Create(1500)) {
		return FALSE;
	}

	m_SimuSocket->Bind(1500);

	return m_SimuSocket->Listen();
}

void CSimuView::InitArrays()
{
	DeleteArrays();

    /* NOTE 3: allocate all the maps. */
    cells = Rows * Cols;
    if ( (ignMap   = (double *) calloc(cells, sizeof(double))) == NULL
      || (flMap    = (double *) calloc(cells, sizeof(double))) == NULL
      || (slpMap   = (double *) calloc(cells, sizeof(double))) == NULL
      || (aspMap   = (double *) calloc(cells, sizeof(double))) == NULL
      || (wspdMap  = (double *) calloc(cells, sizeof(double))) == NULL
      || (wdirMap  = (double *) calloc(cells, sizeof(double))) == NULL
      || (m1Map    = (double *) calloc(cells, sizeof(double))) == NULL
      || (m10Map   = (double *) calloc(cells, sizeof(double))) == NULL
      || (m100Map  = (double *) calloc(cells, sizeof(double))) == NULL
      || (mherbMap = (double *) calloc(cells, sizeof(double))) == NULL
      || (mwoodMap = (double *) calloc(cells, sizeof(double))) == NULL
      || (fuelMap  = (size_t *) calloc(cells, sizeof(size_t))) == NULL )
    {
        fprintf(stderr, "Unable to allocate maps with %d cols and %d rows.\n",
            Cols, Rows);
        return ;
    }

    /* NOTE 4: initialize all the maps -- modify them as you please. */
    for ( cell=0; cell<cells; cell++ )
    {
        fuelMap[cell]  = Model;
        slpMap[cell]   = Slope;
        aspMap[cell]   = Aspect;
        wspdMap[cell]  = 88. * WindSpd;     /* convert mph into ft/min */
        wdirMap[cell]  = WindDir;
        m1Map[cell]    = M1;
        m10Map[cell]   = M10;
        m100Map[cell]  = M100;
        mherbMap[cell] = Mherb;
        mwoodMap[cell] = Mwood;
        ignMap[cell]   = INFINITY;
        flMap[cell]    = 0.;
    }
}

void CSimuView::DeleteArrays()
{
	if (ignMap) {
		free(ignMap);
		ignMap   = NULL;
	}
	if (flMap) {
		free(flMap);
		flMap   = NULL;
	}
	if (slpMap) {
		free(slpMap);
		slpMap   = NULL;
	}
	if (aspMap) {
		free(aspMap);
		aspMap   = NULL;
	}
	if (wspdMap) {
		free(wspdMap);
		wspdMap   = NULL;
	}
	if (wdirMap) {
		free(wdirMap);
		wdirMap   = NULL;
	}
	if (m1Map) {
		free(m1Map);
		m1Map   = NULL;
	}
	if (m10Map) {
		free(m10Map);
		m10Map   = NULL;
	}
	if (m100Map) {
		free(m100Map);
		m100Map   = NULL;
	}
	if (mherbMap) {
		free(mherbMap);
		mherbMap   = NULL;
	}

	if (mwoodMap) {
		free(mwoodMap);
		mwoodMap   = NULL;
	}
	if (fuelMap) {
		free(fuelMap);
		fuelMap   = NULL;
	}
}

void CSimuView::FillSlopeMap()
{
	CSimuDoc * pDoc = GetDocument();
	
	int cell = 0;

	for(int x = 0; x < Cols; x++) {
		for (int y = 0; y < Rows; y++, cell++) {
			int nHeight = pDoc->GetHeight(x, y);

		}
	}
}
