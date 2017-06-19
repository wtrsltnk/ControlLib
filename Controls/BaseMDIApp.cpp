// BaseApp.cpp: implementation of the CWBaseApp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////
// Statics
//////////////////////////////////////////////////////////////////////

CWBaseMDIApp* CWBaseMDIApp::m_pInstance = NULL;

LRESULT CWBaseMDIApp::StaticProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (CWBaseMDIApp::m_pInstance)
	{
		CWBaseMDIApp::m_pInstance->m_hWnd = hWnd;

		switch (uMsg)
		{
		case WM_CREATE:
			{
				if (!CWBaseMDIApp::m_pInstance->InitClientArea())
					return FALSE;

				if (CWBaseMDIApp::m_pInstance->m_pSystrayIcon)
					CWBaseMDIApp::m_pInstance->m_pSystrayIcon->Init(hWnd, ID_SYSTRAY);

				CWBaseMDIApp::m_pInstance->m_pSysMenu = CWMenu::FromSystemMenu(hWnd);
				break;
			}
		case WM_SHELLNOTIFY:
			{
				switch (lParam)
				{
				case WM_LBUTTONDOWN:
					{
						CWBaseMDIApp::m_pInstance->m_pSystrayIcon->OnClick(wParam, lParam);
						break;
					}

				case WM_RBUTTONDOWN:
					{
						CWBaseMDIApp::m_pInstance->m_pSystrayIcon->OnRClick(wParam, lParam);
						break;
					}

				case WM_LBUTTONDBLCLK:
					{
						CWBaseMDIApp::m_pInstance->m_pSystrayIcon->OnDblClick(wParam, lParam);
						break;
					}
				}
				break;
			}
		case WM_DESTROY:
			{
				if (CWBaseMDIApp::m_pInstance->m_pSystrayIcon)
					CWBaseMDIApp::m_pInstance->m_pSystrayIcon->Kill();
				break;
			}
		case WM_MDICHILDACTIVATE:
			{
				CWBaseMDIApp::m_pInstance->OnChildActivate(wParam, lParam);
				break;
			}
		case WM_MDICHILDCLOSE:
			{
				CWBaseMDIApp::m_pInstance->OnChildClose(wParam, lParam);
				break;
			}
		}
		return CWBaseMDIApp::m_pInstance->ViewProc(uMsg, wParam, lParam);
	}

	return FALSE;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWBaseMDIApp::CWBaseMDIApp()
{
	this->m_pPrevInstance			 = CWBaseMDIApp::m_pInstance;
	CWBaseMDIApp::m_pInstance		 = this;

	this->m_hWnd					 = NULL;
	this->m_hClient					 = NULL;
	this->m_hInstance				 = GetModuleHandle(NULL);
	this->m_hIcon					 = LoadIcon(m_hInstance, (LPCTSTR)IDI_APPLICATION);
	this->m_hSmallIcon				 = this->m_hIcon;
	this->m_hCursor					 = LoadCursor(NULL, IDC_ARROW);
	this->m_hbrWindowColor			 = (HBRUSH)COLOR_WINDOW;
	this->m_strWindowClass			 = "MDIApp";

	this->m_strWindowTitle			 = "BaseMDIApplication";

	this->m_dwWindowStyle			 = WS_OVERLAPPEDWINDOW;
	this->m_dwExWindowStyle			 = WS_EX_WINDOWEDGE;

	this->m_PosX					 = CW_USEDEFAULT;	
	this->m_PosY					 = CW_USEDEFAULT;	
	this->m_dwCreationWidth			 = CW_USEDEFAULT;
	this->m_dwCreationHeight		 = CW_USEDEFAULT;
	this->m_dwCreationFlags			 = SW_SHOW;

//	Client props
	this->m_dwClientExWindowStyle	 = WS_EX_CLIENTEDGE;
	this->m_dwClientWindowStyle		 = WS_CHILD | WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL | WS_VISIBLE;

	this->m_ClientPosX				 = 0;	
	this->m_ClientPosY				 = 0;	
	this->m_dwClientCreationWidth	 = 100;
	this->m_dwClientCreationHeight	 = 100;

//	Child props
	this->m_hChildIcon				 = LoadIcon(m_hInstance, (LPCTSTR)IDI_APPLICATION);
	this->m_hChildSmallIcon			 = this->m_hChildIcon;
	this->m_hChildCursor			 = LoadCursor(NULL, IDC_ARROW);
	this->m_hbrChildWindowColor		 = (HBRUSH)(COLOR_WINDOW+1);
	this->m_strChildWindowClass		 = "MDIChild";

	this->m_pSystrayIcon			 = NULL;
	this->m_pSysMenu				 = NULL;

//	Menu
	this->m_pWindowMenu = new CWMenu("Window");
	this->m_pWindowMenu->AddItem("Ne&xt", IDM_WINDOW_NEXT);
	this->m_pWindowMenu->AddItem("Pre&vious", IDM_WINDOW_PREVIOUS);
	this->m_pWindowMenu->AddSeperator();
	this->m_pWindowMenu->AddItem("Tile &Horizontaal", IDM_WINDOW_TILEHORIZONTAAL);
	this->m_pWindowMenu->AddItem("Tile &Verticaal", IDM_WINDOW_TILEVERTICAAL);
	this->m_pWindowMenu->AddItem("&Cascade", IDM_WINDOW_CASCADE);
	this->m_pWindowMenu->AddSeperator();
	this->m_pWindowMenu->AddItem("Cl&ose", IDM_WINDOW_CLOSE);
	this->m_pWindowMenu->AddItem("Close Al&l", IDM_WINDOW_CLOSEALL);

	this->m_pMenu = new CWMenu();
	this->m_pMenu->AddSubMenu(this->m_pWindowMenu);
}

CWBaseMDIApp::~CWBaseMDIApp()
{
	CWBaseMDIApp::m_pInstance = this->m_pPrevInstance;

	if (this->m_pMenu)
	{
		delete this->m_pMenu;
		this->m_pMenu = NULL;
	}

	if (this->m_pWindowMenu)
	{
		delete this->m_pWindowMenu;
		this->m_pWindowMenu = NULL;
	}

	if (this->m_pSysMenu)
	{
		delete this->m_pSysMenu;
		this->m_pSysMenu = NULL;
	}

	if (this->m_pSystrayIcon)
	{
		delete this->m_pSystrayIcon;
		this->m_pSystrayIcon = NULL;
	}
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
LRESULT CWBaseMDIApp::Init(HINSTANCE hInstance)
{
	this->m_hInstance = hInstance;

	if (!InitWindowClasses())
		return FALSE;

	this->m_hWnd = ::CreateWindowEx(	this->m_dwExWindowStyle,
										this->m_strWindowClass,
										this->m_strWindowTitle, 
										this->m_dwWindowStyle,
										this->m_PosX,
										this->m_PosY,
										this->m_dwCreationWidth,
										this->m_dwCreationHeight, 
										NULL,
										this->m_pMenu->Handle(),
										this->m_hInstance,
										NULL);


	if (!this->m_hWnd)
		return FALSE;

	this->m_pSysMenu = CWMenu::FromSystemMenu(this->m_hWnd);
	::ShowWindow(this->m_hWnd, this->m_dwCreationFlags);

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
LRESULT CWBaseMDIApp::Run()
{
	MSG	msg;

	while (GetMessage(&msg, (HWND) NULL, 0, 0))
	{
		if (!TranslateMDISysAccel(this->m_hClient, &msg))
		{
			TranslateMessage(&msg); 
			DispatchMessage(&msg); 
		} 
	}
	return msg.wParam;
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
LRESULT CWBaseMDIApp::InitWindowClasses()
{
	WNDCLASSEX winclass;

	winclass.cbSize         = sizeof(WNDCLASSEX);
	winclass.style		   	= CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc   	= (WNDPROC) CWBaseMDIApp::StaticProc;
	winclass.cbClsExtra		= 0;
	winclass.cbWndExtra		= 0;
	winclass.hInstance		= this->m_hInstance;
	winclass.hIcon		   	= this->m_hIcon;
	winclass.hCursor		= this->m_hCursor;
	winclass.hbrBackground	= this->m_hbrWindowColor;
	winclass.lpszMenuName	= NULL;
	winclass.lpszClassName	= this->m_strWindowClass;
	winclass.hIconSm        = this->m_hChildSmallIcon;

	// Register the Frame window class
	if (!RegisterClassEx(&winclass))
		return FALSE;

	winclass.cbSize         = sizeof(WNDCLASSEX);
	winclass.style		   	= CS_DBLCLKS;
	winclass.lpfnWndProc	= (WNDPROC) CWMDIChild::StaticProc;
	winclass.cbClsExtra		= 0;
	winclass.cbWndExtra		= 0;
	winclass.hInstance		= this->m_hInstance;
	winclass.hIcon		   	= this->m_hChildIcon;
	winclass.hCursor		= this->m_hChildCursor;
	winclass.hbrBackground	= this->m_hbrChildWindowColor;
	winclass.lpszMenuName	= NULL;
	winclass.lpszClassName	= this->m_strChildWindowClass;
	winclass.hIconSm        = this->m_hChildSmallIcon;

	// Register the MDI Child window class
	if (!RegisterClassEx(&winclass))
		return FALSE;

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
LRESULT CWBaseMDIApp::InitClientArea()
{
	CLIENTCREATESTRUCT ccs;

	ccs.hWindowMenu = this->m_pWindowMenu->Handle();
	ccs.idFirstChild = 2303;

	this->m_hClient = ::CreateWindowEx(	this->m_dwClientExWindowStyle,
										"MDICLIENT",
										(LPCTSTR) NULL,
										this->m_dwClientWindowStyle,
										this->m_ClientPosX,
										this->m_ClientPosY,
										this->m_dwClientCreationWidth,
										this->m_dwClientCreationHeight,
										this->m_hWnd,
										(HMENU)10,
										this->m_hInstance,
										(LPSTR)&ccs);

	if (!this->m_hClient)
		return FALSE;

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
LRESULT CWBaseMDIApp::ViewProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDM_WINDOW_NEXT:
				{
					PostMessage(this->m_hClient, WM_MDINEXT, (WPARAM)CWMDIChild::m_hActiveWnd, (LPARAM)TRUE);
					break;
				}

			case IDM_WINDOW_PREVIOUS:
				{
					PostMessage(this->m_hClient, WM_MDINEXT, (WPARAM)CWMDIChild::m_hActiveWnd, (LPARAM)FALSE);
					break;
				}

			case IDM_WINDOW_TILEHORIZONTAAL:
				{
					PostMessage(this->m_hClient, WM_MDITILE, MDITILE_HORIZONTAL, 0);
					break;
				}

			case IDM_WINDOW_TILEVERTICAAL:
				{
					PostMessage(this->m_hClient, WM_MDITILE, MDITILE_VERTICAL, 0);
					break;
				}

			case IDM_WINDOW_CASCADE:
				{
					PostMessage(this->m_hClient, WM_MDICASCADE, 0, 0);
					break;
				}

			case IDM_WINDOW_CLOSE:
				{
					PostMessage(this->m_hClient, WM_MDIDESTROY, (WPARAM)CWMDIChild::m_hActiveWnd, 0);
					break;
				}

			case IDM_WINDOW_CLOSEALL:
				{
					break;
				}
			}
			break;
		}

	case WM_SIZE:
		{
			::MoveWindow(this->m_hClient, 10, 10, LOWORD(lParam) - 20, HIWORD(lParam) - 20, TRUE);
			return 0;
		}

	case WM_DESTROY:
		{
			::PostQuitMessage(0);
			break;
		}
	}
	return DefFrameProc(this->m_hWnd, this->m_hClient, uMsg, wParam, lParam);
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
LRESULT CWBaseMDIApp::OnChildActivate(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
LRESULT CWBaseMDIApp::OnChildClose(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}