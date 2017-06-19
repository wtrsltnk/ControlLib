// ToolWindow.cpp: implementation of the CWToolWindow class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWToolWindow::CWToolWindow()
{
	this->m_strClassName		 = "TlWindow";
	this->m_hbrBackground		 = (HBRUSH)COLOR_WINDOW;

	InitWindowClass();

	this->m_dwExStyle			 = WS_EX_TOOLWINDOW;
	this->m_dwStyle				 = WS_POPUP | WS_SYSMENU | WS_THICKFRAME | WS_CAPTION;
}

CWToolWindow::~CWToolWindow()
{
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
void CWToolWindow::Create(HWND parent)
{
	CWControl::Create(parent, 0);
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
LRESULT CWToolWindow::ViewProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_NCACTIVATE:
		{
			DefWindowProc(this->m_hParent, uMsg, TRUE, lParam);
			return CWCustomControl::ViewProc(uMsg, TRUE, lParam);
		}
	}
	return CWCustomControl::ViewProc(uMsg, wParam, lParam);
}