// PointList.h: interface for the CPointList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POINTLIST_H__A59D9F8B_EB94_4CEC_87FF_EAF405705364__INCLUDED_)
#define AFX_POINTLIST_H__A59D9F8B_EB94_4CEC_87FF_EAF405705364__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct d_point {
	double x;
	double y;
};

class CPointList : public CList<d_point, d_point> 
{
public:
	BOOL GetHead(double &x, double &y);
	void AddRandomPoint();
	void AddPoint(double x, double y);
	CPointList();
	virtual ~CPointList();

protected:
	CMutex m_Lock;
	void Unlock();
	void Lock();
};

#endif // !defined(AFX_POINTLIST_H__A59D9F8B_EB94_4CEC_87FF_EAF405705364__INCLUDED_)
