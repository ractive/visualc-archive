// PointList.cpp: implementation of the CPointList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MonteCarlo.h"
#include "PointList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPointList::CPointList()
{
	srand((unsigned)time(NULL));
}

CPointList::~CPointList()
{
	RemoveAll();
}

void CPointList::AddPoint(double x, double y)
{
	d_point p;
	p.x = x;
	p.y = y;
	Lock();
	AddTail(p);
	Unlock();
}

void CPointList::AddRandomPoint()
{
	double x = (double)((double)rand() / RAND_MAX * 2) - 1;
	double y = (double)((double)rand() / RAND_MAX * 2) - 1;
	AddPoint(x, y);
}


BOOL CPointList::GetHead(double &x, double &y)
{
	if (IsEmpty()) {
		return FALSE;
	}

	Lock();
	d_point p = RemoveHead();
	Unlock();

	x = p.x;
	y = p.y;

	return TRUE;
}

void CPointList::Lock()
{
	CSingleLock lock(&m_Lock);
	lock.Lock();
}

void CPointList::Unlock()
{
	CSingleLock lock(&m_Lock);
	lock.Unlock();
}
