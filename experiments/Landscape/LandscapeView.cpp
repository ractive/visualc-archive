// LandscapeView.cpp : implementation of the CLandscapeView class
//

#include "stdafx.h"
#include "Landscape.h"

#include "LandscapeDoc.h"
#include "LandscapeView.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CLandscapeView

IMPLEMENT_DYNCREATE(CLandscapeView, CView)

BEGIN_MESSAGE_MAP(CLandscapeView, CView)
	//{{AFX_MSG_MAP(CLandscapeView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_COMMAND(ID_RENDER, OnRender)
	ON_UPDATE_COMMAND_UI(ID_RENDER, OnUpdateRender)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLandscapeView construction/destruction

CLandscapeView::CLandscapeView()
{

	scaleValue = 0.15f;								// Scale Value For The Terrain (NEW)
	pos_x = 212;
	pos_y = 60;
	pos_z = 194;
	view_x = 176;
	view_y = 55;
	view_z = 171;
	up_x = 0;
	up_y = 1;
	up_z = 0;

	color_offset = 0;

	m_bRender = FALSE;

	m_nFrames = 0;
}

CLandscapeView::~CLandscapeView()
{
}

BOOL CLandscapeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLandscapeView drawing

void CLandscapeView::OnDraw(CDC* pDC)
{
	CLandscapeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	m_nFrames++;
	if (m_nFrames > 50)
	{
		QueryPerformanceCounter(&endCount);  // Stop timer
		double time = interval_time( startCount, endCount );
		m_fps = ((double) m_nFrames)/time;
		output_fps( m_fps );
		m_nFrames = 0;
		QueryPerformanceCounter(&startCount);
	}

	
	wglMakeCurrent(pDC->m_hDC, m_hRC);
	DrawGLScene();
	wglMakeCurrent(pDC->m_hDC, NULL);

	SwapBuffers(pDC->m_hDC);

	if (m_bRender) {
		Invalidate(FALSE);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CLandscapeView diagnostics

#ifdef _DEBUG
void CLandscapeView::AssertValid() const
{
	CView::AssertValid();
}

void CLandscapeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLandscapeDoc* CLandscapeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLandscapeDoc)));
	return (CLandscapeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLandscapeView message handlers

int CLandscapeView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	/*PIXELFORMATDESCRIPTOR pfd ={
		sizeof(PIXELFORMATDESCRIPTOR), // Structure size
		1,// Structure version number
		PFD_DRAW_TO_WINDOW |// Property flags
		PFD_SUPPORT_OPENGL,
		PFD_TYPE_RGBA,
		24,// 24-bit color
		0,0,0,0,0,0,// Not concerned with these
		0,0,0,0,0,0,0,// No alpha or accumbuffer
		32,// 32-bit depth buffer
		0,0,// No stencil or aux buffer
		PFD_MAIN_PLANE,// Main layer type
		0,// Reserved
		0,0,0// Unsupported
	};*/

	PIXELFORMATDESCRIPTOR pfd ={
		sizeof(PIXELFORMATDESCRIPTOR),					// Size Of This Pixel Format Descriptor
		1,												// Version Number
		PFD_DRAW_TO_WINDOW |							// Format Must Support Window
		PFD_SUPPORT_OPENGL |							// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,								// Must Support Double Buffering
		PFD_TYPE_RGBA,									// Request An RGBA Format
		16,											// Select Our Color Depth
		0, 0, 0, 0, 0, 0,								// Color Bits Ignored
		0,												// No Alpha Buffer
		0,												// Shift Bit Ignored
		0,												// No Accumulation Buffer
		0, 0, 0, 0,										// Accumulation Bits Ignored
		16,												// 16Bit Z-Buffer (Depth Buffer)  
		0,												// No Stencil Buffer
		0,												// No Auxiliary Buffer
		PFD_MAIN_PLANE,									// Main Drawing Layer
		0,												// Reserved
		0, 0, 0	
	};

	CClientDC clientDC(this);
	int pixelFormat= ChoosePixelFormat(clientDC.m_hDC, &pfd);
	BOOL success = SetPixelFormat(clientDC.m_hDC, pixelFormat, &pfd);
	m_hRC = wglCreateContext(clientDC.m_hDC);// Create rendering context
	m_hDC = ::GetDC(m_hWnd);
	InitGL();

	QueryPerformanceFrequency(&timerFrequency);	// Initialize timer
	QueryPerformanceCounter(&startCount);		// Start timer

	return 0;
}


GLvoid CLandscapeView::ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height==0)										// Prevent A Divide By Zero By
		height=1;										// Making Height Equal One

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window.  Farthest Distance Changed To 500.0f (NEW)
	gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 500.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

void CLandscapeView::OnDestroy() 
{
	CView::OnDestroy();
	
	wglDeleteContext(m_hRC);	
}

void CLandscapeView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	CClientDC clientDC(this);
	wglMakeCurrent(clientDC.m_hDC, m_hRC);
	
	ReSizeGLScene(cx, cy);

	wglMakeCurrent(NULL, NULL);	
}


// Loads The .RAW File And Stores It In pHeightMap
void CLandscapeView::LoadRawFile(LPSTR strName, int nSize, BYTE *pHeightMap)
{
	FILE *pFile = NULL;

	// Open The File In Read / Binary Mode.
	pFile = fopen( strName, "rb" );

	// Check To See If We Found The File And Could Open It
	if ( pFile == NULL )	
	{
		// Display Error Message And Stop The Function
		MessageBox("Can't Find The Height Map!", "Error", MB_OK);
		return;
	}

	fread( pHeightMap, 1, nSize, pFile );

	// After We Read The Data, It's A Good Idea To Check If Everything Read Fine
	int result = ferror( pFile );

	// Check If We Received An Error
	if (result)
	{
		MessageBox("Failed To Get Data!", "Error", MB_OK);
	}

	// Close The File.
	fclose(pFile);
}



int CLandscapeView::Height(BYTE *pHeightMap, int X, int Y)				// This Returns The Height From A Height Map Index
{
	int x = X % MAP_SIZE;								// Error Check Our x Value
	int y = Y % MAP_SIZE;								// Error Check Our y Value

	if(!pHeightMap) return 0;							// Make Sure Our Data Is Valid

	return pHeightMap[x + (y * MAP_SIZE)];				// Index Into Our Height Array And Return The Height
}

int CLandscapeView::InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	int X = 0;
	int Y = 0;

	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	LoadRawFile("Data/Terrain.raw", MAP_SIZE * MAP_SIZE, g_HeightMap);	// (NEW)

	for ( X = 0; X < MAP_SIZE; X += DELTA_S ) {
		for ( Y = 0; Y < MAP_SIZE; Y += DELTA_S ) {
			g_ColorMap[X][Y][0] = 0;
			g_ColorMap[X][Y][1] = 0;
			g_ColorMap[X][Y][2] = -0.15f + (Height(g_HeightMap, X, Y) / 256.0f);;
		}
	}

	return TRUE;										// Initialization Went OK
}
														
void CLandscapeView::SetVertexColor(int h, int x, int y)		// Sets The Color Value For A Particular Index, Depending On The Height Index
{
	//if(!pHeightMap) return;								// Make Sure Our Height Data Is Valid

	//int h = Height(pHeightMap, x, y );

	float fColor = -0.15f + (h / 256.0f);
	float fColorx = 0;
	float fColory = 0;
	// Assign This Blue Shade To The Current Vertex

	int n = (int)(0.5 * (rand() / RAND_MAX));

	fColorx = (float)sin((h + color_offset) / ( 70)) + (float)cos((x + color_offset - n) / (130)) - n;
	fColorx = (float)sin((x + color_offset) / (100)) + (float)cos((y + color_offset - n) / (100)) - n;
	fColory = (float)sin((y + color_offset) / (130)) + (float)cos((h + color_offset - n) / (70))  - n;

	
	/*fColorx = g_ColorMap[x][y][0];
	fColory = g_ColorMap[x][y][1];
	fColor = g_ColorMap[x][y][2];*/
	glColor3f(fColorx, fColory, fColor);

	color_offset += 0.0001f;
}

void CLandscapeView::RenderHeightMap(BYTE pHeightMap[])					// This Renders The Height Map As Quads
{
	int X = 0, Y = 0;									// Create Some Variables To Walk The Array With.
	int x, y, z;										// Create Some Variables For Readability

	if(!pHeightMap) return;								// Make Sure Our Height Data Is Valid

	if(m_bRender)											// What We Want To Render
		glBegin( GL_QUADS );							// Render Polygons
	else 
		glBegin( GL_LINES );							// Render Lines Instead

	for ( X = 0; X < MAP_SIZE; X += DELTA_S )
		for ( Y = 0; Y < MAP_SIZE; Y += DELTA_S )
		{
			// Get The (X, Y, Z) Value For The Bottom Left Vertex
			x = X;							
			y = Height(pHeightMap, X, Y );	
			z = Y;							
			
			// Set The Color Value Of The Current Vertex
			SetVertexColor(y, x, z);

			glVertex3i(x, y, z);						// Send This Vertex To OpenGL To Be Rendered (Integer Points Are Faster)

			// Get The (X, Y, Z) Value For The Top Left Vertex
			x = X;										
			y = Height(pHeightMap, X, Y + DELTA_S );  
			z = Y + DELTA_S ;							
			
			// Set The Color Value Of The Current Vertex
			SetVertexColor(y, x, z);

			glVertex3i(x, y, z);						// Send This Vertex To OpenGL To Be Rendered

			// Get The (X, Y, Z) Value For The Top Right Vertex
			x = X + DELTA_S; 
			y = Height(pHeightMap, X + DELTA_S, Y + DELTA_S ); 
			z = Y + DELTA_S ;

			// Set The Color Value Of The Current Vertex
			SetVertexColor(y, x, z);
			
			glVertex3i(x, y, z);						// Send This Vertex To OpenGL To Be Rendered

			// Get The (X, Y, Z) Value For The Bottom Right Vertex
			x = X + DELTA_S; 
			y = Height(pHeightMap, X + DELTA_S, Y ); 
			z = Y;

			// Set The Color Value Of The Current Vertex
			SetVertexColor(y, x, z);

			glVertex3i(x, y, z);						// Send This Vertex To OpenGL To Be Rendered
		}

	glEnd();

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);					// Reset The Color
}

int CLandscapeView::DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
	glLoadIdentity();									// Reset The Matrix
	
	// 			 Position	      View		Up Vector
	//gluLookAt(212, 60, 194,  176, 55, 171,  0, 1, 0);	// This Determines Where The Camera's Position And View Is

	gluLookAt(pos_x, pos_y, pos_z,  view_x, view_y, view_z,  up_x, up_y, up_z);

	glScalef(scaleValue, scaleValue * HEIGHT_RATIO, scaleValue);

	RenderHeightMap(g_HeightMap);						// Render The Height Map

	return TRUE;										// Keep Going
}

/*GLvoid CLandscapeView::KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL",hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// Set hInstance To NULL
	}
}*/

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *	title			- Title To Appear At The Top Of The Window				*
 *	width			- Width Of The GL Window Or Fullscreen Mode				*
 *	height			- Height Of The GL Window Or Fullscreen Mode			*
 *	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
 *	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/
 
/*BOOL CLandscapeView::CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;							// Holds The Results After Searching For A Match
	WNDCLASS	wc;										// Windows Class Structure
	DWORD		dwExStyle;								// Window Extended Style
	DWORD		dwStyle;								// Window Style
	RECT		WindowRect;								// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;							// Set Left Value To 0
	WindowRect.right=(long)width;						// Set Right Value To Requested Width
	WindowRect.top=(long)0;								// Set Top Value To 0
	WindowRect.bottom=(long)height;						// Set Bottom Value To Requested Height

	fullscreen=fullscreenflag;							// Set The Global Fullscreen Flag

	hInstance			= GetModuleHandle(NULL);		// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;			// WndProc Handles Messages
	wc.cbClsExtra		= 0;							// No Extra Window Data
	wc.cbWndExtra		= 0;							// No Extra Window Data
	wc.hInstance		= hInstance;					// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);	// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);	// Load The Arrow Pointer
	wc.hbrBackground	= NULL;							// No Background Required For GL
	wc.lpszMenuName		= NULL;							// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";						// Set The Class Name

	if (!RegisterClass(&wc))							// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}
	
	if (fullscreen)										// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;						// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);	// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= width;		// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;		// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= bits;			// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;						// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;							// Return FALSE
			}
		}
	}

	if (fullscreen)										// Are We Still In Fullscreen Mode?
	{
		dwExStyle=WS_EX_APPWINDOW;						// Window Extended Style
		dwStyle=WS_POPUP;								// Windows Style
		ShowCursor(FALSE);								// Hide Mouse Pointer
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;	// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;					// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);	// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,				// Extended Style For The Window
								"OpenGL",				// Class Name
								title,					// Window Title
								dwStyle |				// Defined Window Style
								WS_CLIPSIBLINGS |		// Required Window Style
								WS_CLIPCHILDREN,		// Required Window Style
								0, 0,					// Window Position
								WindowRect.right-WindowRect.left,	// Calculate Window Width
								WindowRect.bottom-WindowRect.top,	// Calculate Window Height
								NULL,					// No Parent Window
								NULL,					// No Menu
								hInstance,				// Instance
								NULL)))					// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();									// Reset The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd=					// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),					// Size Of This Pixel Format Descriptor
		1,												// Version Number
		PFD_DRAW_TO_WINDOW |							// Format Must Support Window
		PFD_SUPPORT_OPENGL |							// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,								// Must Support Double Buffering
		PFD_TYPE_RGBA,									// Request An RGBA Format
		bits,											// Select Our Color Depth
		0, 0, 0, 0, 0, 0,								// Color Bits Ignored
		0,												// No Alpha Buffer
		0,												// Shift Bit Ignored
		0,												// No Accumulation Buffer
		0, 0, 0, 0,										// Accumulation Bits Ignored
		16,												// 16Bit Z-Buffer (Depth Buffer)  
		0,												// No Stencil Buffer
		0,												// No Auxiliary Buffer
		PFD_MAIN_PLANE,									// Main Drawing Layer
		0,												// Reserved
		0, 0, 0											// Layer Masks Ignored
	};

	if (!(hDC=GetDC(hWnd)))								// Did We Get A Device Context?
	{
		KillGLWindow();									// Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))		// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();									// Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))			// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();									// Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))					// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();									// Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))						// Try To Activate The Rendering Context
	{
		KillGLWindow();									// Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}

	ShowWindow(hWnd,SW_SHOW);							// Show The Window
	SetForegroundWindow(hWnd);							// Slightly Higher Priority
	SetFocus(hWnd);										// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);						// Set Up Our Perspective GL Screen

	if (!InitGL())										// Initialize Our Newly Created GL Window
	{
		KillGLWindow();									// Reset The Display
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}

	return TRUE;										// Success
}

LRESULT CALLBACK WndProc(	HWND	hWnd,				// Handle For This Window
							UINT	uMsg,				// Message For This Window
							WPARAM	wParam,				// Additional Message Information
							LPARAM	lParam)				// Additional Message Information
{
	switch (uMsg)										// Check For Windows Messages
	{
		case WM_ACTIVATE:								// Watch For Window Activate Message
		{
			if (!HIWORD(wParam))						// Check Minimization State
			{
				active=TRUE;							// Program Is Active
			}
			else
			{
				active=FALSE;							// Program Is No Longer Active
			}

			return 0;									// Return To The Message Loop
		}

		case WM_SYSCOMMAND:								// Intercept System Commands
		{
			switch (wParam)								// Check System Calls
			{
				case SC_SCREENSAVE:						// Screensaver Trying To Start?
				case SC_MONITORPOWER:					// Monitor Trying To Enter Powersave?
				return 0;								// Prevent From Happening
			}
			break;										// Exit
		}

		case WM_CLOSE:									// Did We Receive A Close Message?
		{
			PostQuitMessage(0);							// Send A Quit Message
			return 0;									// Jump Back
		}

		case WM_LBUTTONDOWN:							// Did We Receive A Left Mouse Click?
		{
			bRender = !bRender;							// Change The Rendering State Between Fill And Wire Frame
			return 0;									// Jump Back
		}

		case WM_KEYDOWN:								// Is A Key Being Held Down?
		{
			keys[wParam] = TRUE;						// If So, Mark It As TRUE
			return 0;									// Jump Back
		}

		case WM_KEYUP:									// Has A Key Been Released?
		{
			keys[wParam] = FALSE;						// If So, Mark It As FALSE
			return 0;									// Jump Back
		}

		case WM_SIZE:									// Resize The OpenGL Window
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;									// Jump Back
		}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

int WINAPI WinMain(	HINSTANCE	hInstance,				// Instance
					HINSTANCE	hPrevInstance,			// Previous Instance
					LPSTR		lpCmdLine,				// Command Line Parameters
					int			nCmdShow)				// Window Show State
{
	MSG		msg;										// Windows Message Structure
	BOOL	done=FALSE;									// Bool Variable To Exit Loop

	// Ask The User Which Screen Mode They Prefer
	if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen=FALSE;								// Windowed Mode
	}

	// Create Our OpenGL Window
	if (!CreateGLWindow("IPODLAS - Visu", 640, 480, 16, fullscreen))
	{
		return 0;										// Quit If Window Was Not Created
	}

	while(!done)										// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))		// Is There A Message Waiting?
		{
			if (msg.message==WM_QUIT)					// Have We Received A Quit Message?
			{
				done=TRUE;								// If So done=TRUE
			}
			else										// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);					// Translate The Message
				DispatchMessage(&msg);					// Dispatch The Message
			}
		}
		else											// If There Are No Messages
		{
			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
			if ((active && !DrawGLScene()) || keys[VK_ESCAPE])	// Active?  Was There A Quit Received?
			{
				done=TRUE;								// ESC or DrawGLScene Signalled A Quit
			}
			else if (active)							// Not Time To Quit, Update Screen
			{
				SwapBuffers(hDC);						// Swap Buffers (Double Buffering)
			}

			if (keys[VK_F1])							// Is F1 Being Pressed?
			{
				keys[VK_F1]=FALSE;						// If So Make Key FALSE
				KillGLWindow();							// Kill Our Current Window
				fullscreen=!fullscreen;					// Toggle Fullscreen / Windowed Mode
				// Recreate Our OpenGL Window
				if (!CreateGLWindow("NeHe & Ben Humphrey's Height Map Tutorial", 640, 480, 16, fullscreen))
				{
					return 0;							// Quit If Window Was Not Created
				}
			}

			if (keys[VK_UP])							// Is the UP ARROW key Being Pressed?
				scaleValue += 0.001f;					// Increase the scale value to zoom in

			if (keys[VK_DOWN])							// Is the DOWN ARROW key Being Pressed?
				scaleValue -= 0.001f;					// Decrease the scale value to zoom out

			if (keys[VK_LEFT])
				view_z += 1;

			if (keys[VK_RIGHT])
				view_z -= 1;
		}
	}

	// Shutdown
	KillGLWindow();										// Kill The Window
	return (msg.wParam);								// Exit The Program
}
*/

void CLandscapeView::OnRender() 
{
	m_bRender = !m_bRender;
	Invalidate(FALSE);
	
}

void CLandscapeView::OnUpdateRender(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bRender);
	if (m_bRender) {
		Invalidate(TRUE);
	}
}

void CLandscapeView::output_time( double time )
{
// Write time to Windows Title bar
	CString cstr;
	cstr.Format("Time = %.6f s", time);
	SetWindowText(cstr);
}

double CLandscapeView::interval_time( LARGE_INTEGER startCount, LARGE_INTEGER endCount)
{
// Calculate elapsed time 
	double time = ((double)(endCount.QuadPart - startCount.QuadPart))
	/((double)timerFrequency.QuadPart);

	return time;
}

void CLandscapeView::output_fps( double fps )
{
// Write time to Windows Title bar
	CString cstr;
	cstr.Format("fps = %.1f", fps);
	
	AfxGetApp()->GetMainWnd()->SetWindowText(cstr);
}
