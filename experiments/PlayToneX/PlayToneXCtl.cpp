// PlayToneXCtl.cpp : Implementation of the CPlayToneXCtrl ActiveX Control class.

#include "stdafx.h"
#include "PlayToneX.h"
#include "PlayToneXCtl.h"
#include "PlayToneXPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CPlayToneXCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CPlayToneXCtrl, COleControl)
	//{{AFX_MSG_MAP(CPlayToneXCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CPlayToneXCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CPlayToneXCtrl)
	DISP_STOCKPROP_BACKCOLOR()
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CPlayToneXCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CPlayToneXCtrl, COleControl)
	//{{AFX_EVENT_MAP(CPlayToneXCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CPlayToneXCtrl, 1)
	PROPPAGEID(CPlayToneXPropPage::guid)
END_PROPPAGEIDS(CPlayToneXCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CPlayToneXCtrl, "PLAYTONEX.PlayToneXCtrl.1",
	0xdfbaee2c, 0x2669, 0x489e, 0x83, 0x2e, 0x7f, 0xbf, 0x9f, 0x77, 0x1c, 0x35)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CPlayToneXCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DPlayToneX =
		{ 0x1268762e, 0xad7d, 0x43de, { 0x95, 0x9f, 0xcc, 0x43, 0x4d, 0xb8, 0x71, 0x42 } };
const IID BASED_CODE IID_DPlayToneXEvents =
		{ 0x5cd185b8, 0xd1bd, 0x4caa, { 0x98, 0x3b, 0xb5, 0x19, 0x1b, 0xea, 0x8a, 0xe4 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwPlayToneXOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CPlayToneXCtrl, IDS_PLAYTONEX, _dwPlayToneXOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CPlayToneXCtrl::CPlayToneXCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CPlayToneXCtrl

BOOL CPlayToneXCtrl::CPlayToneXCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_PLAYTONEX,
			IDB_PLAYTONEX,
			afxRegApartmentThreading,
			_dwPlayToneXOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CPlayToneXCtrl::CPlayToneXCtrl - Constructor

CPlayToneXCtrl::CPlayToneXCtrl()
{
	InitializeIIDs(&IID_DPlayToneX, &IID_DPlayToneXEvents);

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CPlayToneXCtrl::~CPlayToneXCtrl - Destructor

CPlayToneXCtrl::~CPlayToneXCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CPlayToneXCtrl::OnDraw - Drawing function

void CPlayToneXCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
    // Variables required for text output.
    CFont* pOldFont;
    TEXTMETRIC tm;
    char tText[30];
    CString strTime;
    CRect rc = rcBounds;
    CBrush bkBrush(TranslateColor(GetBackColor()));

    // Variables required for alarm handler.
    time_t aclock;     // elapsed time in seconds since 00:00:00 on
                       // 1/1/1970
    struct tm *now;    // time structure (contains useful time data)
    BOOL bTest;

    // Set the foreground color property and the transparent bk mode.
    pdc->SetTextColor(TranslateColor(GetForeColor()));
    pdc->SetBkMode(TRANSPARENT);

    // Paint the background using the BackColor property.
    pdc->FillRect(rcBounds, &bkBrush);

    // Retrieve the time, check the alarm, package a string
    // specifying the time.
    time(&aclock);    // retrieve elapsed time in seconds
    now = localtime(&aclock);    // convert elapsed seconds to
                                 // meaningful data

    // Examine the alarm properties.
    if ((now->tm_hour == m_alarmHour) && (now->tm_min == m_alarmMinute))
        if (bAlarm == TRUE)
    {
        bTest = PlaySound((const char*)IDR_WAVE3, AfxGetResourceHandle(),
                SND_RESOURCE);
        bAlarm = FALSE;
    }

    // Package time for rendering.
    sprintf(tText, "Current Time: %.8s\n", asctime(now)+11);
    strTime = tText;

    // Draw the time string.
    pOldFont = SelectStockFont(pdc);
    pdc->GetTextMetrics(&tm);
    pdc->SetTextAlign(TA_CENTER | TA_TOP);
    pdc->ExtTextOut((rc.left + rc.right) / 2, (rc.top + rc.bottom -
        tm.tmHeight) / 2, ETO_CLIPPED, rc, strTime, (strTime.GetLength())
        -1, NULL);

    // Reselect the old font and brush.
    pdc->SelectObject(pOldFont);

}


/////////////////////////////////////////////////////////////////////////////
// CPlayToneXCtrl::DoPropExchange - Persistence support

void CPlayToneXCtrl::DoPropExchange(CPropExchange* pPX)
{
    ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
    COleControl::DoPropExchange(pPX);

    long nInterval = m_interval;
    short sAlarmHr = m_alarmHour;
    short sAlarmMin = m_alarmMinute;

    PX_Long(pPX, _T("Interval"), m_interval, DEFAULT_INTERVAL);
    if (pPX->IsLoading())
    {
        if (nInterval != m_interval)
            OnIntervalChanged();
    }

    PX_Short(pPX, _T("AlarmHour"), m_alarmHour, DEFAULT_HOUR);
    if (pPX->IsLoading())
    {
        if (sAlarmHr != m_alarmHour)
            OnAlarmHourChanged();
    }

    PX_Short(pPX, _T("AlarmMinute"), m_alarmMinute, DEFAULT_MINUTE);
    if (pPX->IsLoading())
    {
        if (sAlarmMin != m_alarmMinute)
            OnAlarmMinuteChanged();
    }

}


/////////////////////////////////////////////////////////////////////////////
// CPlayToneXCtrl::OnResetState - Reset control to default state

void CPlayToneXCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CPlayToneXCtrl::AboutBox - Display an "About" box to the user

void CPlayToneXCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_PLAYTONEX);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CPlayToneXCtrl message handlers
