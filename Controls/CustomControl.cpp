// CustomControl.cpp: implementation of the CWCustomControl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////
// Statics
//////////////////////////////////////////////////////////////////////

LRESULT CWCustomControl::StaticProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CWCustomControl *pView = 0; 

	if( uMsg == WM_NCCREATE ) 
	{
		pView = reinterpret_cast<CWCustomControl *>( ((LPCREATESTRUCT)lParam)->lpCreateParams );
		if (pView)
			pView->SetHWND(hWnd);
		
        ::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<long long>( pView ));
	} 
	else
	{
        pView = reinterpret_cast<CWCustomControl *>( ::GetWindowLongPtr(hWnd, GWLP_USERDATA) );
		
		if (pView)
		{
			switch (uMsg)
			{
			case WM_NCDESTROY:
				{
					return FALSE;
				}
			}
		}
	}

	if (pView)
		return pView->ViewProc(uMsg, wParam, lParam); 

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWCustomControl::CWCustomControl()
{
	this->m_hInstance			 = GetModuleHandle(NULL);
	this->m_hbrBackground		 = (HBRUSH)(COLOR_WINDOW+1);
    this->m_hIcon				 = LoadIcon(this->m_hInstance, (LPCTSTR)IDI_APPLICATION);
    this->m_hCursor				 = LoadCursor(NULL, IDC_ARROW);
    this->m_hIconSm				 = this->m_hIcon;

	this->m_dwStyle				 = WS_VISIBLE;
	this->m_dwExStyle			 = WS_EX_WINDOWEDGE;
}

CWCustomControl::~CWCustomControl()
{
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
LRESULT CWCustomControl::ViewProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(this->m_hWnd, uMsg, wParam, lParam);
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
LRESULT CWCustomControl::InitWindowClass()
{
	WNDCLASSEX wsex;

	wsex.hbrBackground = this->m_hbrBackground;
	wsex.hCursor = this->m_hCursor;
	wsex.hIcon = this->m_hIcon;
	wsex.hIconSm = this->m_hIconSm;
	wsex.lpszClassName = this->m_strClassName;

	wsex.cbClsExtra = 0;
	wsex.cbSize = sizeof(wsex);
	wsex.cbWndExtra = 0;
	wsex.hInstance = GetModuleHandle(NULL);
	wsex.lpfnWndProc = (WNDPROC)StaticProc;
	wsex.lpszMenuName = NULL;
	wsex.style = CS_HREDRAW | CS_VREDRAW;

	return RegisterClassEx(&wsex);
}
