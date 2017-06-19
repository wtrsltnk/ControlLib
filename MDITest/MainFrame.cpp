// MainFrame.cpp: implementation of the CMainFrame class.
//
//////////////////////////////////////////////////////////////////////

#include "MainFrame.h"

//////////////////////////////////////////////////////////////////////
// WinMain
//////////////////////////////////////////////////////////////////////

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	CMainFrame app;

	if (!app.Init(hInstance))
	{
		::MessageBox(NULL, "Unable to create Form", "ERROR :", MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}
	
	return app.Run();
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMainFrame::CMainFrame()
{
	this->m_dwClientExWindowStyle = WS_EX_CLIENTEDGE;
	this->m_pMenu->InsertItem("Nieuw", 5, 0);
	this->m_hbrChildWindowColor = (HBRUSH)CreateSolidBrush(RGB(175, 235, 255));

	this->m_pSystrayIcon = new CTrayIcon();
}

CMainFrame::~CMainFrame()
{

}

LRESULT CMainFrame::ViewProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		{
			this->m_pSysMenu->InsertItem("Hahah", 534, 0);
			this->m_pSysMenu->InsertSeperator(1);
			break;
		}

	case WM_SYSCOMMAND:
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case 5:
				{
					CDocument* doc = new CDocument();
					doc->Create(this->m_hClient, this->m_strChildWindowClass);
					break;
				}
			}
			break;
		}
	}
	return CWBaseMDIApp::ViewProc(uMsg, wParam, lParam);
}