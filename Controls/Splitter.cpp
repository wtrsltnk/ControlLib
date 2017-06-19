// Edit.cpp: implementation of the CEdit class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWSplitter::CWSplitter()
{
	this->m_dwStyle			= WS_CHILD | WS_VISIBLE;
	this->m_hbrBackground	= (HBRUSH)(COLOR_WINDOW);

	this->m_pControlA		= NULL;
	this->m_pControlB		= NULL;
	this->m_nSplitPosition	= 100;
	this->m_nMinPosition	= 100;
	this->m_nMaxPosition	= 100;

	this->m_nWidth = 300;
	this->m_nHeight = 300;

}

CWSplitter::~CWSplitter()
{
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
void CWSplitter::DrawHorzXorBar(HDC hdc)
{
  static WORD _dotPatternBmp[8] = { 0x00aa, 0x0055, 0x00aa, 0x0055, 
                                    0x00aa, 0x0055, 0x00aa, 0x0055};

  HBITMAP hbm;
  HBRUSH  hbr, hbrushOld;

  /* create a monochrome checkered pattern */
  hbm = CreateBitmap(8, 8, 1, 1, _dotPatternBmp);

  hbr = CreatePatternBrush(hbm);
    
  SetBrushOrgEx(hdc, 0, this->m_nSplitPosition-2, 0);
  hbrushOld = (HBRUSH)SelectObject(hdc, hbr);
    
  /* draw the checkered rectangle to the screen */
  PatBlt(hdc, 0, this->m_nSplitPosition-2, this->m_nWidth, 4, PATINVERT);
    
  SelectObject(hdc, hbrushOld);
    
  DeleteObject(hbr);
  DeleteObject(hbm);
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
void CWSplitter::DrawVertXorBar(HDC hdc)
{
  static WORD _dotPatternBmp[8] = { 0x00aa, 0x0055, 0x00aa, 0x0055, 
                                    0x00aa, 0x0055, 0x00aa, 0x0055};

  HBITMAP hbm;
  HBRUSH  hbr, hbrushOld;

  /* create a monochrome checkered pattern */
  hbm = CreateBitmap(8, 8, 1, 1, _dotPatternBmp);

  hbr = CreatePatternBrush(hbm);
    
  SetBrushOrgEx(hdc, this->m_nSplitPosition-2, 0, 0);
  hbrushOld = (HBRUSH)SelectObject(hdc, hbr);
    
  /* draw the checkered rectangle to the screen */
  PatBlt(hdc, this->m_nSplitPosition-2, 0, 4, this->m_nHeight, PATINVERT);
    
  SelectObject(hdc, hbrushOld);
    
  DeleteObject(hbr);
  DeleteObject(hbm);
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
LRESULT CWSplitter::ViewProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	static int currentX = 0;
	static int currentY = 0;

	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
		{
			currentX = LOWORD(lParam);
			currentY = HIWORD(lParam);
			SetCapture(this->m_hWnd);
			
			HDC hDC = GetDC(this->m_hWnd);
			if (!this->m_bHorzSplit)
			{
				DrawVertXorBar(hDC);
			}
			else
			{
				DrawHorzXorBar(hDC);
			}
			ReleaseDC(this->m_hWnd, hDC);
			break;
		}

	case WM_LBUTTONUP:
		{
			ReleaseCapture();
			ResizeControls();
			break;
		}

	case WM_MOUSEMOVE:
		{
			if (wParam == MK_LBUTTON)
			{
				HDC hDC = GetDC(this->m_hWnd);
				if (!this->m_bHorzSplit)
				{
					int newpos = this->m_nSplitPosition + (LOWORD(lParam) - currentX);
					DrawVertXorBar(hDC);
					
					if (newpos < this->m_nMinPosition)
						newpos = this->m_nMinPosition;

					if (newpos > (this->m_nWidth - this->m_nMaxPosition))
						newpos = (this->m_nWidth - this->m_nMaxPosition);

					this->m_nSplitPosition = newpos;
					currentX = LOWORD(lParam);

					DrawVertXorBar(hDC);
				}
				else
				{
					int newpos = this->m_nSplitPosition + (HIWORD(lParam) - currentY);
					DrawHorzXorBar(hDC);
					
					if (newpos < this->m_nMinPosition)
						newpos = this->m_nMinPosition;

					if (newpos > (this->m_nHeight - this->m_nMaxPosition))
						newpos = (this->m_nHeight - this->m_nMaxPosition);

					this->m_nSplitPosition = newpos;
					currentY = HIWORD(lParam);

					DrawHorzXorBar(hDC);
				}
				ReleaseDC(this->m_hWnd, hDC);
			}
			break;
		}

	case WM_NOTIFY:
	case WM_COMMAND:
		{
			int id = LOWORD(wParam);

			if (this->m_pControlA && this->m_pControlB)
			{
				if (id == this->m_pControlA->GetID() || id == this->m_pControlB->GetID())
				{
					return SendMessage(this->m_hParent, uMsg, wParam, lParam);
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
void CWSplitter::Create(HWND parent, int id, bool horz)
{
	this->m_bHorzSplit = horz;
	if (horz)
	{
		this->m_strClassName	= "WSPLITTER_HORZ";
		this->m_hCursor			= LoadCursor(NULL, IDC_SIZENS);
		InitWindowClass();
	}
	else
	{
		this->m_strClassName	= "WSPLITTER_VERT";
		this->m_hCursor			= LoadCursor(NULL, IDC_SIZEWE);
		InitWindowClass();
	}

	CWCustomControl::Create(parent, id);
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
void CWSplitter::Resize(int x, int y, int width, int height)
{
	CWCustomControl::Resize(x, y, width, height);

	ResizeControls();
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
void CWSplitter::ResizeControls()
{
	if (this->m_pControlA && this->m_pControlB)
	{
		if (!this->m_bHorzSplit)
		{
			this->m_pControlA->Resize(0, 0, this->m_nSplitPosition-2, this->m_nHeight);
			this->m_pControlB->Resize(this->m_nSplitPosition+2, 0, this->m_nWidth-this->m_nSplitPosition-2, this->m_nHeight);
		}
		else
		{
			this->m_pControlA->Resize(0, 0, this->m_nWidth, this->m_nSplitPosition-2);
			this->m_pControlB->Resize(0, this->m_nSplitPosition+2, this->m_nWidth, this->m_nHeight-this->m_nSplitPosition-2);
		}
	}
	else if (this->m_pControlA && (this->m_pControlB == NULL))
	{
		this->m_pControlA->Resize(this->m_nX, this->m_nY, this->m_nWidth, this->m_nHeight);
	}
	else if (this->m_pControlB && (this->m_pControlA == NULL))
	{
		this->m_pControlB->Resize(this->m_nX, this->m_nY, this->m_nWidth, this->m_nHeight);
	}
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
void CWSplitter::SetControlA(CWControl* controlA, int minSize)
{
	this->m_pControlA = controlA;
	this->m_pControlA->ReCreate(this->m_hWnd);
	this->m_nMinPosition = minSize;
	if (minSize > this->m_nSplitPosition)
		this->m_nSplitPosition = minSize;
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
void CWSplitter::SetControlB(CWControl* controlB, int minSize)
{
	this->m_pControlB = controlB;
	this->m_pControlB->ReCreate(this->m_hWnd);
	this->m_nMaxPosition = minSize;
}