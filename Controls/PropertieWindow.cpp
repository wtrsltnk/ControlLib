// PropertieWindow.cpp: implementation of the CWPropertieWindow class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWPropertieWindow::CWPropertieWindow()
{
	this->m_strClassName	 = "PropWindow";
	this->m_hbrBackground	 = (HBRUSH)COLOR_WINDOW;//COLOR_GRAYTEXT;
	this->m_dwExStyle		 = WS_EX_CLIENTEDGE;
	this->m_dwStyle			 = WS_CHILD;

	this->m_pDlgHead		 = new CWBasePropertieChild();
	this->m_nScrollAmount	 = 0;
	this->m_nTotalHeight	 = 0;
	this->m_bDrag			 = false;
    this->m_hHand			 = ::LoadCursor(GetModuleHandle("controls.dll"), MAKEINTRESOURCE(IDC_HANDICON));
}

CWPropertieWindow::~CWPropertieWindow()
{
	delete this->m_pDlgHead;
	this->m_pDlgHead = NULL;
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
LRESULT CWPropertieWindow::ScrollChilds(int scrollamount)
{
	int oldamount = this->m_nScrollAmount;
	if (this->m_ClRc.bottom - this->m_ClRc.top < this->m_pDlgHead->GetHeight())
	{
		int newAmount = this->m_nScrollAmount + scrollamount;
		int maxAmount = this->m_ClRc.bottom - this->m_ClRc.top - this->m_pDlgHead->GetHeight();

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
		this->m_pDlgHead->MoveDialog(this->m_ClRc.left, this->m_ClRc.top + this->m_nScrollAmount, this->m_ClRc.right - this->m_ClRc.left);
	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
LRESULT CWPropertieWindow::ViewProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static POINT pt = {0};
	switch (uMsg)
	{
	case 0x020A:
		{
			ScrollChilds((short) HIWORD(wParam) / 2);
			break;
		}

	case WM_LBUTTONDOWN:
		{
			::GetCursorPos(&pt);
			::SetCapture(this->m_hWnd);

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
					if (ScrollChilds(newpt.y - pt.y))
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
			this->m_pDlgHead->MoveDialog(this->m_ClRc.left, this->m_ClRc.top + this->m_nScrollAmount, this->m_ClRc.right - this->m_ClRc.left);
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
void CWPropertieWindow::Resize(int x, int y, int width, int height)
{
	CWCustomControl::Resize(x, y, width, height);

	GetClientRect(this->m_hWnd, &this->m_ClRc);

	this->m_ClRc.top += 2;
	this->m_ClRc.bottom -= 2;
	this->m_ClRc.left += 2;
	this->m_ClRc.right -= 2;

	this->m_pDlgHead->MoveDialog(this->m_ClRc.left, this->m_ClRc.top + this->m_nScrollAmount, this->m_ClRc.right - this->m_ClRc.left);
	Refresh();
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
LRESULT CWPropertieWindow::AddDialog(CWBasePropertieChild* dlg)
{
	if (dlg)
	{
		CWBasePropertieChild* tmp = this->m_pDlgHead;

		while (tmp->m_pNext)
			tmp = tmp->m_pNext;

		tmp->m_pNext = dlg;

		dlg->Show(this->m_hWnd);

		this->m_nTotalHeight += dlg->GetHeight();

		this->m_pDlgHead->MoveDialog(this->m_ClRc.left, this->m_ClRc.top + this->m_nScrollAmount, this->m_ClRc.right - this->m_ClRc.left);

		return TRUE;
	}

	return FALSE;
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
void CWPropertieWindow::ClearDialogs()
{
	this->m_pDlgHead->Close();
	
	this->m_nScrollAmount = 0;
	this->m_nTotalHeight = 0;
	
	ScrollChilds(0);
	Refresh();
}
