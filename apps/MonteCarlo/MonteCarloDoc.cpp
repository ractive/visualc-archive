// MonteCarloDoc.cpp : implementation of the CMonteCarloDoc class
//

#include "stdafx.h"
#include "MonteCarlo.h"
#include "MonteCarloDoc.h"
#include "Markup.h"
#include "pugxml.h"
#include "XMLite.h"
#include "ExpatXML.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMonteCarloDoc

CMonteCarloDoc * CMonteCarloDoc::m_pPseudoThis = NULL;

IMPLEMENT_DYNCREATE(CMonteCarloDoc, CDocument)

BEGIN_MESSAGE_MAP(CMonteCarloDoc, CDocument)
	//{{AFX_MSG_MAP(CMonteCarloDoc)
	ON_COMMAND(ID_START, OnStart)
	ON_COMMAND(ID_STOP, OnStop)
	ON_COMMAND(ID_DRAWPOINTS, OnDrawpoints)
	ON_UPDATE_COMMAND_UI(ID_DRAWPOINTS, OnUpdateDrawpoints)
	ON_COMMAND(ID_DIRECT, OnDirect)
	ON_UPDATE_COMMAND_UI(ID_DIRECT, OnUpdateDirect)
	ON_COMMAND(ID_XML, OnXml)
	ON_UPDATE_COMMAND_UI(ID_XML, OnUpdateXml)
	ON_COMMAND(ID_XMLRPC, OnXmlrpc)
	ON_UPDATE_COMMAND_UI(ID_XMLRPC, OnUpdateXmlrpc)
	ON_COMMAND(ID_XMLPUG, OnXmlpug)
	ON_UPDATE_COMMAND_UI(ID_XMLPUG, OnUpdateXmlpug)
	ON_COMMAND(ID_XMLite, OnXMLite)
	ON_UPDATE_COMMAND_UI(ID_XMLite, OnUpdateXMLite)
	ON_COMMAND(ID_EXPAT, OnExpat)
	ON_UPDATE_COMMAND_UI(ID_EXPAT, OnUpdateExpat)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMonteCarloDoc construction/destruction

CMonteCarloDoc::CMonteCarloDoc()
{
	// TODO: add one-time construction code here
	m_pPseudoThis = this;
	m_bDrawPoints = TRUE;
	m_Method = ID_DIRECT;
	m_pSimuThread = NULL;
	m_pDataThread = NULL;
}

CMonteCarloDoc::~CMonteCarloDoc()
{
}

BOOL CMonteCarloDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMonteCarloDoc serialization

void CMonteCarloDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMonteCarloDoc diagnostics

#ifdef _DEBUG
void CMonteCarloDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMonteCarloDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMonteCarloDoc commands


UINT CMonteCarloDoc::Simulate(LPVOID lParam)
{
	m_pPseudoThis->m_nHits = 0;
	m_pPseudoThis->m_nPoints = 0;
	while(m_pPseudoThis->m_bRun) {
		
		//m_pPseudoThis->m_PointList.AddRandomPoint();

		while(!m_pPseudoThis->NextPoint()) {
			WaitForSingleObject(m_pPseudoThis->m_DataAvailableEvt, INFINITE);
			m_pPseudoThis->m_DataAvailableEvt.ResetEvent();
			continue;
		}

		m_pPseudoThis->m_nPoints++;
		
		if (sqrt(m_pPseudoThis->m_X * m_pPseudoThis->m_X + m_pPseudoThis->m_Y * m_pPseudoThis->m_Y) <= 1) {
			m_pPseudoThis->m_nHits++;
		}
		
		SendMessage(AfxGetMainWnd()->m_hWnd, WM_PROGRESS, 0, 0);
	}

	return 0;
}

UINT CMonteCarloDoc::GatherData(LPVOID lParam)
{
	char response[512];
	double x, y;

	CMarkup xml;
	CPugXmlParser pug;
	XNode xmlite;
	CExpatXML expat;
	expat.Create();

	sprintf(response, ""
			"%s"
			"<methodResponse>"
				"<params>"
					"<param>"
						"<value>"
						   "<double>"
							   "%f"
						   "</double>"
						"</value>"
					"</param>"
					"<param>"
						"<value>"
						   "<double>"
							   "%f"
						   "</double>"
						"</value>"
					"</param>"
					"</params> </methodResponse>", m_pPseudoThis->m_Method != ID_XMLite ? "<?xml version=\"1.0\"?>" : "", (double)((double)rand() / RAND_MAX * 2) - 1, (double)((double)rand() / RAND_MAX * 2) - 1);


	while(m_pPseudoThis->m_bRun) {

		if (m_pPseudoThis->m_Method == ID_DIRECT) {
			m_pPseudoThis->m_PointList.AddRandomPoint();		
		}
		else if (m_pPseudoThis->m_Method == ID_XML) {
			

			xml.SetDoc(response);
			xml.ResetPos();

			if (xml.FindElem("methodResponse")) {
				if (xml.FindChildElem("params")) {
					xml.IntoElem();
					if (xml.FindChildElem("param")) {
						xml.IntoElem();
						xml.FindChildElem("value");
						xml.IntoElem();
						xml.FindChildElem("double");
						x = atof(xml.GetChildData());
						xml.OutOfElem();
						xml.OutOfElem();
					}
					if (xml.FindChildElem("param")) {
						xml.IntoElem();
						xml.FindChildElem("value");
						xml.IntoElem();
						xml.FindChildElem("double");
						y = atof(xml.GetChildData());
						xml.OutOfElem();
						xml.OutOfElem();
					}
				}

			}
			
			m_pPseudoThis->m_PointList.AddPoint(x, y);
		}
		else if (m_pPseudoThis->m_Method == ID_XMLPUG) {
			


			pug.Parse(response);

			CPugXmlBranch cEntry = pug.GetRoot().FindFirstElement("double");
			TRACE(cEntry.GetData());

			CPugXmlBranchArray rFound;
			
			pug.GetRoot().FindAllElements("double", rFound);

			if (rFound.GetCount() == 2) {
				CPugXmlBranch branch = rFound.GetAt(0);
				
				x = atof(branch.GetChildAt(0).GetData());
				branch = rFound.GetAt(1);
				y = atof(branch.GetChildAt(0).GetData());
			}

			m_pPseudoThis->m_PointList.AddPoint(x, y);

			pug.Clear();
		}
		else if (m_pPseudoThis->m_Method == ID_XMLite) {
			

			xmlite.Load( response );

			LPXNode params = xmlite.GetChild(0);
			x = atof(params->GetChild(0)->GetChild(0)->GetChildValue("double"));
			y = atof(params->GetChild(1)->GetChild(0)->GetChildValue("double"));
			
			m_pPseudoThis->m_PointList.AddPoint(x, y);
		}
		else if (m_pPseudoThis->m_Method == ID_EXPAT) {

			
			
			// Send this simple string to the parser
			expat.Create();
			if (expat.Parse(response)) {
				m_pPseudoThis->m_PointList.AddPoint(expat.x, expat.y);
				expat.Destroy();
			}
		}
		else if (m_pPseudoThis->m_Method == ID_XMLRPC) {
		
		}

		m_pPseudoThis->m_DataAvailableEvt.SetEvent();
	}

	return 0;
}

void CMonteCarloDoc::OnStart() 
{
	m_Start = clock();

	m_bRun = TRUE;
	m_pSimuThread = AfxBeginThread(Simulate, NULL);

	m_pDataThread = AfxBeginThread(GatherData, NULL);

}


void CMonteCarloDoc::OnStop() 
{
	m_bRun = FALSE;
}

double CMonteCarloDoc::GetPi()
{
	return (double) m_pPseudoThis->m_nHits * 4 / m_pPseudoThis->m_nPoints;
}

double CMonteCarloDoc::GetDuration()
{
	m_End = clock();
	return (double)(m_End - m_Start) / CLOCKS_PER_SEC;
}

void CMonteCarloDoc::GetPoint(double &x, double &y)
{
	x = m_X;
	y = m_Y;
}

BOOL CMonteCarloDoc::NextPoint()
{
	return m_PointList.GetHead(m_X, m_Y);
}

void CMonteCarloDoc::OnDrawpoints() 
{
	m_bDrawPoints = !m_bDrawPoints;
	Reset();
}

void CMonteCarloDoc::OnUpdateDrawpoints(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bDrawPoints);	
}

void CMonteCarloDoc::OnDirect() 
{
	SetMethod(ID_DIRECT);
}

void CMonteCarloDoc::OnUpdateDirect(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_Method == ID_DIRECT);	
}

void CMonteCarloDoc::OnXml() 
{
	SetMethod(ID_XML);
}

void CMonteCarloDoc::OnUpdateXml(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_Method == ID_XML);		
}

void CMonteCarloDoc::OnXmlrpc() 
{
	SetMethod(ID_XMLRPC);
}

void CMonteCarloDoc::OnUpdateXmlrpc(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_Method == ID_XMLRPC);	
}

void CMonteCarloDoc::Reset()
{
	m_nPoints = 0;
	m_nHits = 0;
	m_Start = clock();
	UpdateAllViews(NULL, 1);
}

void CMonteCarloDoc::OnXmlpug() 
{
	SetMethod(ID_XMLPUG);
	
}

void CMonteCarloDoc::OnUpdateXmlpug(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_Method == ID_XMLPUG);	
}

void CMonteCarloDoc::OnXMLite() 
{
	SetMethod(ID_XMLite);
}

void CMonteCarloDoc::OnUpdateXMLite(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_Method == ID_XMLite);	
	
}

void CMonteCarloDoc::SetMethod(UINT nMethod)
{
	if (m_Method == nMethod) {
		return;
	}

	m_Method = nMethod;
	Reset();
}

void CMonteCarloDoc::OnCloseDocument() 
{
	m_bRun = FALSE;
	if (m_pSimuThread) {
		WaitForSingleObject(m_pSimuThread->m_hThread, 1000);
	}

	CDocument::OnCloseDocument();
}

void CMonteCarloDoc::OnExpat() 
{
	SetMethod(ID_EXPAT);
}

void CMonteCarloDoc::OnUpdateExpat(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_Method == ID_EXPAT);	
}
