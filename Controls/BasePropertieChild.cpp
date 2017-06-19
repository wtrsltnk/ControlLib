// BasePropertieChild.cpp: implementation of the CWBasePropertieChild class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWBasePropertieChild::CWBasePropertieChild()
{
	this->m_dwStyle			 = WS_CHILD;
	this->m_strClassName	 = "PropertieChild";
	this->m_hbrBackground	 = (HBRUSH)COLOR_WINDOW;
	this->m_pNext			 = NULL;
	this->m_nX				 = 0;
	this->m_nY				 = 0;
	this->m_nWidth			 = 0;
	this->m_nHeight			 = 0;
}

CWBasePropertieChild::~CWBasePropertieChild()
{
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
void CWBasePropertieChild::Init(int width, int height, DWORD resource, int id)
{
	this->m_nWidth = width;
	this->m_nHeight = height;
	this->m_dwResource = resource;
	this->m_nID = id;

	this->m_Dialog.Init(this->m_dwResource);
	this->m_Button.SetStyle(BS_FLAT);
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
LRESULT CWBasePropertieChild::Show(HWND hParent)
{
	this->m_hParent = hParent;

	CWCustomControl::Create(this->m_hParent, this->m_nID);

	this->m_Dialog.Show(this->m_hWnd);
	this->m_Button.Create(this->m_hWnd, IDM_TITLEBUTTON);

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
LRESULT CWBasePropertieChild::Close()
{
	if (this->m_hWnd)
	{
		::DestroyWindow(this->m_hWnd);
		this->m_hWnd = NULL;
		this->m_hParent = NULL;
		this->m_Dialog.Close();
		this->m_Button.Kill();
	}

	if (this->m_pNext)
	{
		this->m_pNext->Close();
		this->m_pNext = NULL;
	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
int CWBasePropertieChild::MoveDialog(int x, int y, int width)
{
	this->m_nX = x;
	this->m_nY = y;
	this->m_nWidth = width;
	int res = 0;

	if (this->m_hWnd)
	{
		::SetWindowPos(this->m_hWnd, HWND_TOP, this->m_nX, this->m_nY, width, this->m_nHeight, SWP_NOCOPYBITS);
		Focus();
	}

	if (this->m_pNext)
	{
		res = this->m_pNext->MoveDialog(this->m_nX, this->m_nY + this->m_nHeight + 2, width);
	}
	return this->m_nHeight + res;
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
int CWBasePropertieChild::GetHeight()
{
	if (this->m_pNext)
		return this->m_pNext->GetHeight() + this->m_nHeight + 2;

	return this->m_nHeight;
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
HWND CWBasePropertieChild::GetItem(int id)
{
	return this->m_Dialog.GetItem(id);
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
void CWBasePropertieChild::SetTitle(LPTSTR strTitle)
{
	this->m_strTitle = strTitle;
	this->m_Button.SetTitle(strTitle);
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
LRESULT CWBasePropertieChild::ViewProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_PAINT:
		{
			HPEN hGray, hWhite;
			HPEN tmpPen;
			HBRUSH tmpBrush;
			PAINTSTRUCT ps;

			hGray = ::CreatePen(PS_SOLID, 1, RGB(128,128,128));
			hWhite = ::CreatePen(PS_SOLID, 1, RGB(255,255,255));
			::BeginPaint(this->m_hWnd, &ps);

			tmpBrush = (HBRUSH)::SelectObject(ps.hdc, ::GetStockObject(HOLLOW_BRUSH));
			tmpPen = (HPEN)::SelectObject(ps.hdc, hGray);

			::Rectangle(ps.hdc, 0, 9, this->m_nWidth-1, this->m_nHeight-1);

			::SelectObject(ps.hdc, hWhite);
			::Rectangle(ps.hdc, 1, 10, this->m_nWidth, this->m_nHeight);

			::SelectObject(ps.hdc, tmpBrush);
			::SelectObject(ps.hdc, tmpPen);

			::EndPaint(this->m_hWnd, &ps);

			::DeleteObject(hGray);
			::DeleteObject(hWhite);
			break;
		}

	case WM_LBUTTONDOWN:
	case WM_MOUSEMOVE:
	case WM_LBUTTONUP:
		{
			::SendMessage(this->m_hParent, uMsg, wParam, lParam);
			break;
		}

	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDM_TITLEBUTTON:
				{
					switch (HIWORD(wParam))
					{
					case BN_CLICKED:
						{
							if (this->m_nHeight == 22)
							{
								this->m_nHeight = this->m_nOriginalHeight;
							}
							else
							{
								this->m_nOriginalHeight = this->m_nHeight;
								this->m_nHeight = 22;
							}
							MoveDialog(this->m_nX, this->m_nY, this->m_nWidth);
							::SendMessage(this->m_hParent, WM_SCROLLDLGS, 0, 0);
							break;
						}
					}
					break;
				}
			}
			break;
		}

	case WM_INITDIALOG:
		{
			this->OnInitDialog(wParam, lParam);
			break;
		}

	case WM_SIZE:
		{
			this->m_Dialog.Resize(4, 20, this->m_nWidth - 8, this->m_nHeight - 24);
			this->m_Button.Resize(4, 1, this->m_nWidth - 8, 17);
			break;
		}
	}
	return CWCustomControl::ViewProc(uMsg, wParam, lParam);
}