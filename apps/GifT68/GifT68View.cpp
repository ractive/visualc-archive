// GifT68View.cpp : implementation of the CGifT68View class
//

#include "stdafx.h"
#include "GifT68.h"

#include "GifT68Doc.h"
#include "GifT68View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGifT68View

IMPLEMENT_DYNCREATE(CGifT68View, CScrollView)

BEGIN_MESSAGE_MAP(CGifT68View, CScrollView)
	//{{AFX_MSG_MAP(CGifT68View)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGifT68View construction/destruction

CGifT68View::CGifT68View()
{
	// TODO: add construction code here

}

CGifT68View::~CGifT68View()
{
}

BOOL CGifT68View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGifT68View drawing

void CGifT68View::OnDraw(CDC* pDC)
{
	CGifT68Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// Check If a Picture File Was Opened
	if(pDoc->m_FilePathName != pDoc->m_FilePathNameLast)
		{
		m_Magnify = 0;
		m_FitToScreen = FALSE;
		// Update Title With FileName For Both Cases...
		m_FileName.Format("%s", pDoc->FileNameOnly(pDoc->m_FilePathName));
		pDoc->SetTitle(m_FileName); // Put Only The File Name On Title...
		if(pDoc->m_Picture.Load(pDoc->m_FilePathName)) // Load Picture Succeeded
			{
			pDoc->m_FilePathName = "";
			pDoc->m_FilePathNameLast = "";
			OnOptionsFitborderstopicture();
			Invalidate(TRUE);
			}
		else // Load Picture Failed
			{
			pDoc->m_FilePathName = "";
			pDoc->m_FilePathNameLast = "";
			pDoc->m_Picture.Load(IDR_DEFAULT, "JPG");
			OnOptionsFitborderstopicture(); // Show Here So It Will Appear
			Invalidate(TRUE);               // Before The Message Box...
			HWND hWnd = AfxGetApp()->GetMainWnd()->m_hWnd;
			MessageBoxEx(hWnd, "Picture data is not a known picture type\t\t\n(.BMP .DIB .EMF .GIF .ICO .JPG .WMF)\t\t\n(Default picture restored)\n\nFile may be CORRUPTED or MISSING\nFiles list of current directory was ReCreated\t", "Can not load picture", MB_OK | MB_ICONSTOP, LANG_ENGLISH);
			pDoc->SetTitle("Default"); // Set Default Title As We Load The Default Picture...
			// Try To Loading a "Good" Picture...
			if((m_ViewForward || m_ViewFirst) && (pDoc->m_FilesListPos != pDoc->m_FilesListCount)) OnButtonNext();
			else OnButtonPrev();
			}
		}
	else // Check If It Is The First Entry - Put Some "Default" Stuff
	if(m_ViewFirst)
		{
		if(m_FileName.IsEmpty()) pDoc->SetTitle("Default");
		OnOptionsFitborderstopicture();
		OnOptionsFitborderstopicture();
		m_ViewFirst = FALSE;
		Invalidate(TRUE);
		}
	
	GetClientRect(&m_ClientRect);
	pDoc->m_Picture.UpdateSizeOnDC(pDC); // Get Picture Dimentions In Pixels

	if(m_FitToScreen)
		{
		pDoc->m_Picture.Show(pDC, CRect(0,0, m_ClientRect.right, m_ClientRect.bottom));
		// Set Off Scrolls
		m_ScrollSizeTotal.cx = 0;
		m_ScrollSizeTotal.cy = 0;
		}
	else	
	{
	// Calculate Delta Width - To Center The Picture
	if(m_ClientRect.right - pDoc->m_Picture.m_Width > 0)
	m_DeltaX = (m_ClientRect.right - pDoc->m_Picture.m_Width)/2;
	else m_DeltaX = 0;
	// Calculate Delta Height - To Center The Picture
	if(m_ClientRect.bottom - pDoc->m_Picture.m_Height > 0)
	m_DeltaY = (m_ClientRect.bottom - pDoc->m_Picture.m_Height)/2;
	else m_DeltaY = 0;

	if(m_DeltaX + pDoc->m_Picture.m_Width*(m_Magnify+1) > m_ClientRect.right)
		{
		m_DeltaX = (m_ClientRect.right - pDoc->m_Picture.m_Width*(m_Magnify+1))/2;
		m_DeltaY = (m_ClientRect.bottom - pDoc->m_Picture.m_Height*(m_Magnify+1))/2;
		}

	if(m_Magnify >= 0) // Magnify Or Set Original Picture Dimentions
		{
		// Calculate New Dimentions For ScrollView
		m_ScrollSizeTotal.cx = pDoc->m_Picture.m_Width*(m_Magnify+1)-2;
		m_ScrollSizeTotal.cy = pDoc->m_Picture.m_Height*(m_Magnify+1)-2;
		// Center Picture (If We Have Enough Space)
		if(m_ClientRect.right - m_ScrollSizeTotal.cx <= 0) m_DeltaX = 0;
		if(m_ClientRect.bottom - m_ScrollSizeTotal.cy <= 0) m_DeltaY = 0;
		pDoc->m_Picture.Show(pDC, CPoint(m_DeltaX,m_DeltaY), CPoint(pDoc->m_Picture.m_Width, pDoc->m_Picture.m_Height), m_Magnify,m_Magnify);
		}
	else // Diminish Picture Dimentions
		{
		// Calculate New Dimentions For ScrollView
		m_ScrollSizeTotal.cx = pDoc->m_Picture.m_Width/(abs(m_Magnify-1));
		m_ScrollSizeTotal.cy = pDoc->m_Picture.m_Height/(abs(m_Magnify-1));
		// Center Picture (If We Have Enough Space)
		if(m_ClientRect.right - m_ScrollSizeTotal.cx > 1)
		m_DeltaX = (m_ClientRect.right - pDoc->m_Picture.m_Width/(abs(m_Magnify-1)))/2;
		else m_DeltaX = 0;
		if(m_ClientRect.bottom - m_ScrollSizeTotal.cy > 1)
		m_DeltaY = (m_ClientRect.bottom - pDoc->m_Picture.m_Height/(abs(m_Magnify-1)))/2;
		else m_DeltaY = 0;
		pDoc->m_Picture.Show(pDC, CRect(m_DeltaX,m_DeltaY, m_DeltaX + m_ScrollSizeTotal.cx, m_DeltaY + m_ScrollSizeTotal.cy));
		}
	} // !FitToScreen

	SetScrollSizes(MM_TEXT, m_ScrollSizeTotal);
}

void CGifT68View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CGifT68View diagnostics

#ifdef _DEBUG
void CGifT68View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CGifT68View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CGifT68Doc* CGifT68View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGifT68Doc)));
	return (CGifT68Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGifT68View message handlers
