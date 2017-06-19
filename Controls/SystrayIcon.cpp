// SystrayIcon.cpp: implementation of the CWSystrayIcon class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWSystrayIcon::CWSystrayIcon()
{
	this->m_hWnd			 = NULL;
	this->m_hIcon			 = NULL;
	this->m_strTitle		 = "";
}

CWSystrayIcon::~CWSystrayIcon()
{
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
LRESULT CWSystrayIcon::Init(HWND hWnd, int id)
{
	this->m_hWnd							 = hWnd;
	this->m_iID								 = id;

	this->m_NotifyData.cbSize				 = sizeof(NOTIFYICONDATA);
	this->m_NotifyData.hIcon				 = this->m_hIcon;
	this->m_NotifyData.hWnd					 = this->m_hWnd;
	this->m_NotifyData.uID					 = this->m_iID;
	this->m_NotifyData.uCallbackMessage		 = WM_SHELLNOTIFY;
	this->m_NotifyData.uFlags				 = NIF_ICON | NIF_MESSAGE | NIF_TIP;

	strcpy(this->m_NotifyData.szTip, this->m_strTitle);

	Shell_NotifyIcon(NIM_ADD, &m_NotifyData);

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
LRESULT CWSystrayIcon::Kill()
{
	Shell_NotifyIcon(NIM_DELETE, &m_NotifyData);
	return TRUE;
}

