// Trackbar.cpp: implementation of the CWTrackbar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWTrackbar::CWTrackbar()
{
	this->m_dwStyle			 = WS_CHILD | WS_VISIBLE;
	this->m_strClassName	 = "TrackBarControl";
	this->m_hbrBackground	 = (HBRUSH)COLOR_WINDOW;

	InitWindowClass();

	this->m_bHasFocus = false;
	this->m_bDrag = false;

	this->m_nStart = 0;
	this->m_nEnd = 10;
	this->m_nStepCount = this->m_nEnd - this->m_nStart;
	this->m_nStep = 2;
}

CWTrackbar::~CWTrackbar()
{
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////	
void CWTrackbar::SetRange(int start, int end)
{
	if (end - start > 1)
	{
		this->m_nStart = start;
		this->m_nEnd = end;

		this->m_nStepCount = this->m_nEnd - this->m_nStart;
	}
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////	
void CWTrackbar::SetStep(int step)
{
	if (step >= 0 && step <= this->m_nStepCount)
	{
		this->m_nStep = step;
		::InvalidateRect(this->m_hWnd, NULL, FALSE);
	}
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////	
int CWTrackbar::GetStep()
{
	return this->m_nStep + this->m_nStart;
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////	
void CWTrackbar::Increase()
{
	if ((this->m_nStep + 1) < this->m_nStepCount)
	{
		this->m_nStep += 1;
		::InvalidateRect(this->m_hWnd, NULL, TRUE);
	}
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////	
void CWTrackbar::Decrease()
{
	if ((this->m_nStep - 1) >= 0)
	{
		this->m_nStep -= 1;
		::InvalidateRect(this->m_hWnd, NULL, TRUE);
	}
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////	
LRESULT CWTrackbar::ViewProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static int dragX = 0;
	static int dragY = 0;

	switch (uMsg)	
	{
	case WM_PAINT:
		{
			PAINTSTRUCT ps = {0};

			::BeginPaint(this->m_hWnd, &ps);

			DrawRange(ps.hdc, this->m_nStepCount);
			DrawStep(ps.hdc, this->m_nStepCount, this->m_nStep);

			::EndPaint(this->m_hWnd, &ps);

			break;
		}

	case WM_SETFOCUS:
		{
			this->m_bHasFocus = true;
			::InvalidateRect(this->m_hWnd, NULL, FALSE);
			break;
		}

	case WM_KILLFOCUS:
		{
			this->m_bHasFocus = false;
			::InvalidateRect(this->m_hWnd, NULL, FALSE);
			break;
		}

	case WM_LBUTTONDOWN:
		{
			::SetFocus(this->m_hWnd);

			dragX = LOWORD(lParam);
			dragY = HIWORD(lParam);
			this->m_bDrag = true;
			::SetCapture(this->m_hWnd);
			break;
		}

	case WM_LBUTTONUP:
		{
			this->m_bDrag = false;
			::ReleaseCapture();
			break;
		}

	case WM_MOUSEMOVE:
		{
			if (this->m_bDrag)
			{
				float space = GetStepSpace(this->m_nStepCount);

				if (LOWORD(lParam) < dragX)
				{
					if (-(LOWORD(lParam) - dragX) > space)
					{
						RECT rc = {0};
						GetStepArea(&rc, this->m_nStepCount, this->m_nStep);

						Decrease();
						dragX = LOWORD(lParam);
						dragY = HIWORD(lParam);

						::InvalidateRect(this->m_hWnd, &rc, TRUE);
					}
				}
				else
				{
					if ((LOWORD(lParam) - dragX) > space)
					{
						RECT rc = {0};
						GetStepArea(&rc, this->m_nStepCount, this->m_nStep);

						Increase();
						dragX = LOWORD(lParam);
						dragY = HIWORD(lParam);

						::InvalidateRect(this->m_hWnd, &rc, TRUE);
					}
				}
			}
			break;
		}

	case WM_RBUTTONDOWN:
		{
			::SetFocus(GetParent(this->m_hWnd));
			break;
		}

	case WM_KEYDOWN:
		{
			switch ((int) wParam)
			{
			case VK_SUBTRACT:
			case VK_NEXT:
			case VK_DOWN:
			case VK_LEFT:
				{
					Decrease();
					break;
				}

			case VK_ADD:
			case VK_PRIOR:
			case VK_UP:
			case VK_RIGHT:
				{
					Increase();
					break;
				}

			case VK_HOME:
				{
					this->m_nStep = this->m_nStart;
					break;
				}

			case VK_END:
				{
					this->m_nStep = this->m_nEnd;
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
void CWTrackbar::DrawRange(HDC hdc, int steps)
{
	RECT area = {0};
	float space = 0.0f;
	
	space =GetStepSpace(steps);
	GetDrawArea(&area);

	::Rectangle(hdc, area.left, area.top, area.right, area.bottom);

	for (int i = 1; i < steps - 1; i++)
	{
		::MoveToEx(hdc, area.left + (space * i), area.top, NULL);
		::LineTo(hdc, area.left + (space * i), area.bottom);
	}
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////	
void CWTrackbar::DrawStep(HDC hdc, int steps, int step)
{
	RECT area = {0};

	GetStepArea(&area, steps, step);

	HBRUSH tmpBrush = 0;

	if (this->m_bHasFocus)
		tmpBrush = (HBRUSH)::SelectObject(hdc, ::GetStockObject(GRAY_BRUSH));
	else
		tmpBrush = (HBRUSH)::SelectObject(hdc, ::GetStockObject(LTGRAY_BRUSH));

	HPEN tmpPen = (HPEN)::SelectObject(hdc, ::GetStockObject(BLACK_PEN));

	::Rectangle(hdc, area.left, area.top, area.right, area.bottom);

	::SelectObject(hdc, tmpBrush);
	::SelectObject(hdc, tmpPen);
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////	
void CWTrackbar::GetDrawArea(RECT* area)
{
	if (area)
	{
		::GetClientRect(this->m_hWnd, area);

		area->left += 10;
		area->right -= 10;
		area->top += 10;
		area->bottom -= 10;
	}
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////	
void CWTrackbar::GetStepArea(RECT* area, int steps, int step)
{
	if (area)
	{
		RECT draw = {0};
		float space = 0.0f;

		space = GetStepSpace(steps);
		GetDrawArea(&draw);

		area->left = draw.left + (space * step) - 3;
		area->top = draw.top - 2;
		area->right = draw.left + (space * step) + 3;
		area->bottom = draw.bottom + 2;
	}
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////	
float CWTrackbar::GetStepSpace(int steps)
{
	float result = 0.0f;

	if (steps > 1)
	{
		PAINTSTRUCT ps = {0};
		RECT client = {0};

		GetDrawArea(&client);

		int start = client.left;
		int end = client.right;
		int width = end - start;

		result = (float)width / (steps - 1);
	}

	return result;
}
