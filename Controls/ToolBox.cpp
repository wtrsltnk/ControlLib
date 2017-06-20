// ToolBox.cpp: implementation of the CWToolBox class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWToolBox::CWToolBox()
{
	this->m_strClassName		 = "ToolBox";
	this->m_dwStyle				 = WS_CHILD;
	this->m_pNext				 = NULL;
	this->m_hbrBackground		 = (HBRUSH)COLOR_WINDOW;
}

CWToolBox::~CWToolBox()
{
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
LRESULT CWToolBox::Show(HWND hParent)
{
	this->m_hParent = hParent;

	CWCustomControl::Create(this->m_hParent, this->m_nID);

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
LRESULT CWToolBox::Close()
{
	if (this->m_hWnd)
	{
		::DestroyWindow(this->m_hWnd);
		this->m_hWnd = NULL;
		this->m_hParent = NULL;
		this->m_Dialog.Close();
		this->m_Button.Kill();
	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
int CWToolBox::Move(int x, int y, int width)
{
	this->m_nX = x;
	this->m_nY = y;
	this->m_nWidth = width;

	::MoveWindow(this->m_hWnd, x, y, this->m_nWidth, this->m_nHeight, true);

	if (this->m_pNext)
		return this->m_pNext->Move(x, y + this->m_nHeight + 2, width);

	return y + this->m_nHeight;
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
LRESULT CWToolBox::ViewProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{

	case WM_CREATE:
		{
			this->m_Dialog.Show(this->m_hWnd);

			this->m_Button.Create(this->m_hWnd, IDM_TITLEBUTTON);
			this->m_Button.SetTitle((LPTSTR)this->m_strTitle);
			break;
		}

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
			tmpPen = (HPEN)::SelectObject(ps.hdc, hWhite);

			::Rectangle(ps.hdc, 1, 10, this->m_nWidth, this->m_nHeight);

			::SelectObject(ps.hdc, hGray);
			::Rectangle(ps.hdc, 0, 9, this->m_nWidth-1, this->m_nHeight-1);

			::SelectObject(ps.hdc, tmpBrush);
			::SelectObject(ps.hdc, tmpPen);

			::EndPaint(this->m_hWnd, &ps);

			::DeleteObject(hGray);
			::DeleteObject(hWhite);
			break;
		}

	case WM_SIZE:
		{
			this->m_Dialog.Resize(4, 20, this->m_nWidth - 8, this->m_nHeight - 24);
			this->m_Button.Resize(4, 1, this->m_nWidth - 8, 17);
			break;
		}

	case WM_LBUTTONDOWN:
	case WM_MOUSEMOVE:
	case WM_LBUTTONUP:
	case WM_SCROLLDLGS:
	case 0x020A:
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
							Move(this->m_nX, this->m_nY, this->m_nWidth);
							::SendMessage(this->m_hParent, WM_SCROLLDLGS, 0, 0);
							::SetFocus(this->m_hParent);
							break;
						}
					}
					break;
				}
			}
			break;
		}
	}
	return CWCustomControl::ViewProc(uMsg, wParam, lParam);	
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
void CWToolBox::Initialize(int height, int id, DWORD resource)
{
	this->m_nHeight = height;
	this->m_nID = id;

	if (resource != 0)
		this->m_dwResource = resource;

	this->m_Dialog.Init(this->m_dwResource);
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
void CWToolBox::SetTitle(const char* title)
{
	CWControl::SetTitle(title);
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
void CWToolBox::SetButtonStyle(DWORD style)
{
	this->m_Button.SetStyle(style);
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
int CWToolBox::GetID()
{
	return CWControl::GetID();
}
