// CustomButton.cpp: implementation of the CCustomButton class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWCustomButton::CWCustomButton()
{
	this->m_dwStyle			 = WS_CHILD | WS_VISIBLE;
	this->m_strClassName	 = "CustomButton";

	InitWindowClass();

	this->m_bPressed		= false;
	
	SetBGColor(RGB(240, 230, 200));
	SetFGColor(RGB(50, 45, 35));
	SetBorderColor(RGB(150, 145, 135));
}

CWCustomButton::~CWCustomButton()
{
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
LRESULT CWCustomButton::ViewProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		{
			break;
		}

	case WM_LBUTTONDOWN:
		{			
			this->m_bPressed = true;

			SetCapture(this->m_hWnd);
			Refresh();
			break;
		}

	case WM_LBUTTONUP:
		{
			POINT pt;
			GetCursorPos(&pt);

			if (WindowFromPoint(pt) == this->m_hWnd)
			{
				WPARAM wP = MAKEWPARAM(this->m_nID, BN_CLICKED);
				LPARAM lP = (LPARAM)this->m_hWnd; 
				::SendMessage(this->m_hParent, WM_COMMAND, wP, lP);
			}
			this->m_bPressed = false;

			ReleaseCapture();
			Refresh();
			break;
		}

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			RECT rc;

			GetClientRect(this->m_hWnd, &rc);

			::BeginPaint(this->m_hWnd, &ps);
			::SetBkMode(ps.hdc, TRANSPARENT);

			if (IsEnabled())
			{
				::SetTextColor(ps.hdc, this->m_cFGColor);
			}
			else
			{
				::SetTextColor(ps.hdc, RGB(150, 150, 150));
			}

			COLORREF bgColor = this->m_cBGColor;
			COLORREF brColor = this->m_cBorderColor;
			RECT txtRect = rc;
			if (this->m_bPressed)
			{
				bgColor = RGB(GetRValue(bgColor)+15, GetGValue(bgColor)+15, GetBValue(bgColor)+15);
				brColor = RGB(GetRValue(brColor)-15, GetGValue(brColor)-15, GetBValue(brColor)-15);
				txtRect.top+=2;
				txtRect.left+=2;
			}

			HBRUSH oldBr = (HBRUSH)::SelectObject(ps.hdc, CreateSolidBrush(bgColor));
			HPEN oldPen = (HPEN)::SelectObject(ps.hdc, CreatePen(PS_SOLID, 1, brColor));
			HFONT oldFont = (HFONT)::SelectObject(ps.hdc, m_hFont);

			Rectangle(ps.hdc, rc.left, rc.top, rc.right, rc.bottom);
			DrawTextEx(ps.hdc, (LPTSTR)this->m_strTitle, strlen(this->m_strTitle), &txtRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE, NULL);

			::DeleteObject(::SelectObject(ps.hdc, oldBr));
			::DeleteObject(::SelectObject(ps.hdc, oldPen));

			::EndPaint(this->m_hWnd, &ps);
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
void CWCustomButton::SetBGColor(COLORREF rgb)
{
	this->m_cBGColor = rgb;

	Refresh();
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
void CWCustomButton::SetFGColor(COLORREF rgb)
{
	this->m_cFGColor = rgb;

	Refresh();
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
void CWCustomButton::SetBorderColor(COLORREF rgb)
{
	this->m_cBorderColor = rgb;

	Refresh();
}
