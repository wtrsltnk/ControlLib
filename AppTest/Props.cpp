// Props.cpp: implementation of the CProps class.
//
//////////////////////////////////////////////////////////////////////

#include "Props.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProps::CProps()
{
	this->m_hInstance = GetModuleHandle(NULL);
	this->m_dwResourceDlg = IDD_PROPS;
}

CProps::~CProps()
{
}

void CProps::DlgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			::BeginPaint(this->m_hDlg, &ps);

			SelectObject(ps.hdc, ::GetStockObject(DKGRAY_BRUSH));
			Rectangle(ps.hdc, 0, 0, 100, 100);

			::EndPaint(this->m_hDlg, &ps);
			break;
		}
	}
	CWPropertieDialog::DlgProc(uMsg, wParam, lParam);
}
