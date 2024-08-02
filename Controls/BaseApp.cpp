// BaseApp.cpp: implementation of the CWBaseApp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////
// Statics
//////////////////////////////////////////////////////////////////////

CWBaseApp* CWBaseApp::m_pInstance = NULL;

LRESULT CALLBACK CWBaseApp::StaticProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (CWBaseApp::m_pInstance)
	{
		CWBaseApp::m_pInstance->m_hWnd = hWnd;

		switch (uMsg)
		{
		case WM_CREATE:
			{
				if (CWBaseApp::m_pInstance->m_pSystrayIcon)
					CWBaseApp::m_pInstance->m_pSystrayIcon->Init(hWnd, ID_SYSTRAY);

				CWBaseApp::m_pInstance->m_pSysMenu = CWMenu::FromSystemMenu(hWnd);
				break;
			}
		case WM_SHELLNOTIFY:
			{
				switch (lParam)
				{
				case WM_LBUTTONDOWN:
					{
						CWBaseApp::m_pInstance->m_pSystrayIcon->OnClick(wParam, lParam);
						break;
					}

				case WM_RBUTTONDOWN:
					{
						CWBaseApp::m_pInstance->m_pSystrayIcon->OnRClick(wParam, lParam);
						break;
					}

				case WM_LBUTTONDBLCLK:
					{
						CWBaseApp::m_pInstance->m_pSystrayIcon->OnDblClick(wParam, lParam);
						break;
					}
				break;
				}
			}
		case WM_DESTROY:
			{
				if (CWBaseApp::m_pInstance->m_pSystrayIcon)
					CWBaseApp::m_pInstance->m_pSystrayIcon->Kill();
				break;
			}
		}
		return CWBaseApp::m_pInstance->ViewProc(uMsg, wParam, lParam);
	}

	return FALSE;
}

char* CWBaseApp::AppPath()
{
	if (CWBaseApp::m_pInstance)
	{
		return CWBaseApp::m_pInstance->m_strAppPath;
	}

	return 0;
}

char* CWBaseApp::ExeName()
{
	if (CWBaseApp::m_pInstance)
	{
		return CWBaseApp::m_pInstance->m_strExeName;
	}

	return 0;
}

int CWBaseApp::Args(char* argv[])
{
	return 0;
}

void CWBaseApp::GoFullscreen(int width, int height, int bits)
{
	DEVMODE dm;

	dm.dmSize = sizeof(DEVMODE);
	dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
	dm.dmBitsPerPel = bits;
	dm.dmPelsWidth = width;
	dm.dmPelsHeight = height;

	if (width != 0 && height != 0 && bits != 0)
	{
		ChangeDisplaySettings(&dm, CDS_FULLSCREEN);
	}
}

void CWBaseApp::LeavFullscreen()
{
	ChangeDisplaySettings(0, 0);
}

SIZE* CWBaseApp::GetScreensize()
{
	static SIZE size;

	size.cx = GetSystemMetrics (SM_CXSCREEN);
	size.cy = GetSystemMetrics (SM_CYSCREEN);

	return &size;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWBaseApp::CWBaseApp(
    HINSTANCE hInstance)
{
    this->m_hInstance = hInstance;

	this->m_pPrevInstance	 = CWBaseApp::m_pInstance;
    CWBaseApp::m_pInstance	 = this;

	char path[MAX_PATH];
	GetModuleFileName (0, path, 256);
	char *ptr = strrchr (path, '\\');
	
	if (ptr)
	{
		strcpy(this->m_strExeName, ++ptr);
		*ptr = '\0';
	}
	strcpy(this->m_strAppPath, path);

	this->m_hWnd			 = NULL;
	this->m_dwWindowStyle	 = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
	this->m_dwExWindowStyle	 = WS_EX_OVERLAPPEDWINDOW;
	this->m_PosX			 = CW_USEDEFAULT;	
	this->m_PosY			 = CW_USEDEFAULT;	
	this->m_dwCreationWidth  = CW_USEDEFAULT;
	this->m_dwCreationHeight = CW_USEDEFAULT;
	this->m_dwCreationFlags	 = SW_SHOW;
	this->m_hbrWindowColor	 = (HBRUSH)(COLOR_WINDOW+1);
    this->m_hIcon			 = LoadIcon(m_hInstance, (LPCTSTR)IDI_APPLICATION);
	this->m_hCursor			 = LoadCursor(NULL, IDC_ARROW);
	this->m_strWindowTitle	 = "BaseApplication";
	this->m_strWindowClass	 = 0;
	this->m_pMenu			 = NULL;
	this->m_pSysMenu		 = NULL;
	this->m_pSystrayIcon	 = NULL;
}

CWBaseApp::~CWBaseApp()
{
	CWBaseApp::m_pInstance = this->m_pPrevInstance;

	if (this->m_pMenu)
	{
		delete this->m_pMenu;
		this->m_pMenu = NULL;
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
LRESULT CWBaseApp::Init()
{
	HMENU hMenu = NULL;

	if (!InitWindowClass())
		return FALSE;

	if (this->m_pMenu)
		hMenu = this->m_pMenu->Handle();

	this->m_hWnd = ::CreateWindowEx(		this->m_dwExWindowStyle,
											this->m_strWindowClass,
											this->m_strWindowTitle, 
											this->m_dwWindowStyle,
											this->m_PosX,
											this->m_PosY,
											this->m_dwCreationWidth,
											this->m_dwCreationHeight, 
											NULL,
											hMenu,
											this->m_hInstance,
											NULL);

	if (!m_hWnd)
		return FALSE;

	::ShowWindow(this->m_hWnd, this->m_dwCreationFlags);

	this->m_pSysMenu = CWMenu::FromSystemMenu(this->m_hWnd);

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
LRESULT CWBaseApp::Run()
{
	MSG msg;
	
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, this->m_hAccelTable, &msg)) 
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
LRESULT CWBaseApp::InitWindowClass()
{
	WNDCLASSEX wcex;

	wcex.cbSize			= sizeof(WNDCLASSEX); 
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC) CWBaseApp::StaticProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.lpszMenuName	= NULL;
	wcex.hIconSm		= NULL;

	wcex.hInstance		= this->m_hInstance;
	wcex.hIcon			= this->m_hIcon;
	wcex.hbrBackground	= this->m_hbrWindowColor;
	wcex.lpszClassName	= this->m_strWindowClass;
	wcex.hCursor		= this->m_hCursor;

	if (!::RegisterClassEx(&wcex))
		return FALSE;

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
LRESULT CWBaseApp::ViewProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
	}
	return DefWindowProc(this->m_hWnd, uMsg, wParam, lParam);
}
