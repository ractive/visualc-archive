// PlayToneXPpg.cpp : Implementation of the CPlayToneXPropPage property page class.

#include "stdafx.h"
#include "PlayToneX.h"
#include "PlayToneXPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CPlayToneXPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CPlayToneXPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CPlayToneXPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CPlayToneXPropPage, "PLAYTONEX.PlayToneXPropPage.1",
	0xfdb94d77, 0x5b63, 0x4bd3, 0x83, 0xd2, 0x6a, 0xa9, 0xab, 0xd1, 0xcd, 0xf7)


/////////////////////////////////////////////////////////////////////////////
// CPlayToneXPropPage::CPlayToneXPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CPlayToneXPropPage

BOOL CPlayToneXPropPage::CPlayToneXPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_PLAYTONEX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CPlayToneXPropPage::CPlayToneXPropPage - Constructor

CPlayToneXPropPage::CPlayToneXPropPage() :
	COlePropertyPage(IDD, IDS_PLAYTONEX_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CPlayToneXPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CPlayToneXPropPage::DoDataExchange - Moves data between page and properties

void CPlayToneXPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CPlayToneXPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CPlayToneXPropPage message handlers
