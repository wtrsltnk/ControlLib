// ToolBoxContainer.cpp: implementation of the CWToolBoxContainer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWToolBoxContainer::CWToolBoxContainer()
{
	this->m_strClassName		 = "ToolBoxContainer";
	this->m_dwStyle				 = WS_CHILD;
	this->m_hbrBackground		 = (HBRUSH)COLOR_WINDOW;
	this->m_hHand				 = ::LoadCursor(GetModuleHandle("controls.dll"), MAKEINTRESOURCE(IDC_HAND));
	this->m_bDrag				 = false;
	this->m_nScrollAmount		 = 0;
	this->m_nTotalHeight		 = 0;
}

CWToolBoxContainer::~CWToolBoxContainer()
{
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
LRESULT CWToolBoxContainer::Scroll(int amount)
{
	int oldamount = this->m_nScrollAmount;
	if (this->m_ClRc.bottom - this->m_ClRc.top < this->m_Layer.Height())
	{
		int newAmount = this->m_nScrollAmount + amount;
		int maxAmount = this->m_ClRc.bottom - this->m_ClRc.top - this->m_Layer.Height();

		if (newAmount <= 0)
		{
			if (newAmount <= maxAmount)
				this->m_nScrollAmount = maxAmount;
			else
				this->m_nScrollAmount = newAmount;
		}
		else
		{
			if (this->m_nScrollAmount != 0)
				this->m_nScrollAmount = 0;
		}
	}
	else
	{
		if (this->m_nScrollAmount != 0)
			this->m_nScrollAmount = 0;
	}

	if (oldamount != this->m_nScrollAmount)
	{
		this->m_Layer.Y(this->m_ClRc.top + this->m_nScrollAmount);
	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
void CWToolBoxContainer::UpdateBoxes()
{
	if (this->m_Head.m_pNext)
	this->m_Layer.Height(this->m_Head.m_pNext->Move(2, 4, this->m_Layer.Width()-4) + 2);
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
LRESULT CWToolBoxContainer::ViewProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static POINT pt = {0};
	switch (uMsg)
	{
	case WM_CREATE:
		{
			m_Layer.Create(this, 5);
			break;
		}

	case WM_SIZE:
		{
			::GetClientRect(this->m_hWnd, &this->m_ClRc);
			this->m_Layer.Width(LOWORD(lParam) - 4);
			this->m_Layer.X(2);
			this->m_Layer.Y(this->m_nScrollAmount);
			UpdateBoxes();
			Scroll(0);
			break;
		}

	case 0x020A:
		{
			Scroll((short) HIWORD(wParam) / 4);
			break;
		}

	case WM_LBUTTONDOWN:
		{
			::GetCursorPos(&pt);
			::SetCapture(this->m_hWnd);
			::SetFocus(this->m_hWnd);

			::SetCursor(this->m_hHand);

			this->m_bDrag = true;
			break;
		}

	case WM_MOUSEMOVE:
		{
			if (this->m_bDrag)
			{
				POINT newpt;

				::GetCursorPos(&newpt);

				if (newpt.y - pt.y != 0)
				{
					if (Scroll(newpt.y - pt.y))
					{
						::GetCursorPos(&pt);
					}
				}
			}
			break;
		}

	case WM_LBUTTONUP:
		{
			::ReleaseCapture();

			this->m_bDrag = false;
			break;
		}

	case WM_SCROLLDLGS:
		{
			UpdateBoxes();
			Scroll(0);
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
LRESULT CWToolBoxContainer::AddToolBox(CWToolBox* toolBox)
{
	CWToolBox* tmp = &this->m_Head;

	while (tmp->m_pNext)
	{
		tmp = tmp->m_pNext;
	}
	tmp->m_pNext = toolBox;

	toolBox->m_pNext = NULL;
	toolBox->Show(this->m_Layer.GetHandle());

	RECT rc;
	this->m_Layer.GetRect(&rc);
	
	UpdateBoxes();

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
LRESULT CWToolBoxContainer::RemoveToolBox(int id)
{
	CWToolBox* tmp = &this->m_Head;
	CWToolBox* tl = 0;

	while (tmp->m_pNext)
	{
		if (tmp->m_pNext->GetID() == id)
		{
			tl = tmp->m_pNext;
			if (tl)
			{
				tl->Close();
			}
			tmp->m_pNext = tmp->m_pNext->m_pNext;
		}
		else
			tmp = tmp->m_pNext;
	}

	UpdateBoxes();

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
void CWToolBoxContainer::ClearToolBoxes()
{
}


















////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
CWToolBoxContainer::Layer::Layer()
{
	this->m_strClassName		 = "Layer";
	this->m_dwStyle				 = WS_CHILD;
	this->m_hbrBackground		 = (HBRUSH)COLOR_WINDOW;
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
CWToolBoxContainer::Layer::~Layer()
{
}
////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
int CWToolBoxContainer::Layer::X()
{
	return this->m_nX;
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
int CWToolBoxContainer::Layer::Y()
{
	return this->m_nY;
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
int CWToolBoxContainer::Layer::Width()
{
	return this->m_nWidth;
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
int CWToolBoxContainer::Layer::Height()
{
	return this->m_nHeight;
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
void CWToolBoxContainer::Layer::X(int x)
{
	Resize(x, this->m_nY, this->m_nWidth, this->m_nHeight);
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
void CWToolBoxContainer::Layer::Y(int y)
{
	Resize(this->m_nX, y, this->m_nWidth, this->m_nHeight);
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
void CWToolBoxContainer::Layer::Height(int h)
{
	Resize(this->m_nX, this->m_nY, this->m_nWidth, h);
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
void CWToolBoxContainer::Layer::Width(int w)
{
	Resize(this->m_nX, this->m_nY, w, this->m_nHeight);
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
LRESULT CWToolBoxContainer::Layer::ViewProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
	case WM_MOUSEMOVE:
	case WM_LBUTTONUP:
	case WM_SCROLLDLGS:
	case 0x020A:
		{
			::SendMessage(this->m_hParent, uMsg, wParam, lParam);
			break;
		}

	}
	return CWCustomControl::ViewProc(uMsg, wParam, lParam);
}