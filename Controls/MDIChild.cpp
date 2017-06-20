// MDIChild.cpp: implementation of the CWMDIChild class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////
// Statics
//////////////////////////////////////////////////////////////////////

HWND CWMDIChild::m_hActiveWnd = NULL;

LRESULT CWMDIChild::StaticProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	CWMDIChild *pChild = 0;
	MDICREATESTRUCT* cr;

	if(uMsg == WM_NCCREATE)
	{
		cr = reinterpret_cast <MDICREATESTRUCT*> (((LPCREATESTRUCT)lParam)->lpCreateParams);
		pChild = reinterpret_cast <CWMDIChild*> (cr->lParam);
		
		if (pChild)
		{
			pChild->SetHandle(hWnd);
			::SetWindowLong(hWnd, GWL_USERDATA, reinterpret_cast<long>(pChild));
		}
	}
	else if (uMsg == WM_DESTROY)
	{
		delete pChild;
		::SetWindowLong(hWnd, GWL_USERDATA, 0);
	}
	else
	{
		pChild = reinterpret_cast <CWMDIChild *> (::GetWindowLong(hWnd, GWL_USERDATA));
			
		if (pChild)
		{
			switch (uMsg)
			{
			case WM_CLOSE:
				{
					pChild->OnClose(wParam, lParam);
					::SendMessage(::GetParent(pChild->m_hClient), WM_MDICHILDCLOSE, 0, (LPARAM)pChild);
				}
			case WM_SIZE:
				{
					pChild->OnSize(wParam, lParam);
				}
			case WM_MDIACTIVATE:
				{
					pChild->OnActivate(wParam, lParam);
					pChild->Activate();
					::SetFocus(hWnd);
					::SendMessage(::GetParent(pChild->m_hClient), WM_MDICHILDACTIVATE, 0, (LPARAM)pChild);
				}
			}

			if (uMsg != WM_NCDESTROY)
			{
				pChild->ViewProc(uMsg, wParam, lParam);
			}
		}
	}

	return DefMDIChildProc(hWnd, uMsg, wParam, lParam);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWMDIChild::CWMDIChild()
{
	this->m_hInstance			 = GetModuleHandle(NULL);
	this->m_hWnd				 = NULL;
	this->m_hClient				 = NULL;
	this->m_strTitle			 = "MDI Child";
	this->m_dwStyle				 = MDIS_ALLCHILDSTYLES;
	this->m_PosX				 = CW_USEDEFAULT;
	this->m_PosY				 = CW_USEDEFAULT;
	this->m_dwCreationHeight	 = CW_USEDEFAULT;
	this->m_dwCreationWidth		 = CW_USEDEFAULT;
	this->m_dwCreationFlags		 = SW_SHOW;
}

CWMDIChild::~CWMDIChild()
{
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// OUtput  : 
//////////////////////////////////////////////////////////////////////
LRESULT CWMDIChild::Create(HWND hClient, LPCTSTR strWindowClass)
{
	this->m_hClient = hClient;

	MDICREATESTRUCT mcs;

	mcs.szTitle			 = this->m_strTitle;
	mcs.szClass			 = strWindowClass;
	mcs.hOwner			 = this->m_hInstance;
	mcs.x				 = this->m_PosX;
	mcs.y				 = this->m_PosY;
	mcs.cx				 = this->m_dwCreationWidth;
	mcs.cy				 = this->m_dwCreationHeight;
	mcs.style			 = this->m_dwStyle;
	mcs.lParam			 = (LPARAM)this;

	this->m_hWnd = (HWND)SendMessage(this->m_hClient, WM_MDICREATE, 0, (LPARAM)&mcs);

	if (!this->m_hWnd)
		return FALSE;

	::ShowWindow(this->m_hWnd, this->m_dwCreationFlags);
	return TRUE;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// OUtput  : 
//////////////////////////////////////////////////////////////////////
void CWMDIChild::ViewProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// OUtput  : 
//////////////////////////////////////////////////////////////////////
void CWMDIChild::SetHandle(HWND hWnd)
{
	this->m_hWnd = hWnd;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// OUtput  : 
//////////////////////////////////////////////////////////////////////
void CWMDIChild::Activate()
{
	CWMDIChild::m_hActiveWnd = this->m_hWnd;
}
