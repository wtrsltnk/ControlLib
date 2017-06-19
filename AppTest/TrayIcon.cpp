// TrayIcon.cpp: implementation of the CTrayIcon class.
//
//////////////////////////////////////////////////////////////////////

#include "TrayIcon.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTrayIcon::CTrayIcon()
{
	this->m_strTitle = "Systray icoontje";
	this->m_hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON));
}

CTrayIcon::~CTrayIcon()
{

}

LRESULT CTrayIcon::OnClick(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

LRESULT CTrayIcon::OnDblClick(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

LRESULT CTrayIcon::OnRClick(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}
