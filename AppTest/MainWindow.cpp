// MainWindow.cpp: implementation of the CMainWindow class.
//
//////////////////////////////////////////////////////////////////////

#include "MainWindow.h"

//////////////////////////////////////////////////////////////////////
// WinMain
//////////////////////////////////////////////////////////////////////

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	CMainWindow app;

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

CMainWindow::CMainWindow()
{
	this->m_strWindowClass = "MainWindow";
	this->m_pMenu = new CWMenu();
	this->m_dwExWindowStyle = WS_EX_WINDOWEDGE;
	this->m_hbrWindowColor = (HBRUSH)COLOR_WINDOW;
	this->m_pMenu->AddItem("Bestand", 98798);
	
	this->m_pSystrayIcon = new CTrayIcon();

	this->m_pPropDialog = new CWBasePropertieChild();
	this->m_pPropDialog->Init(200, 400, IDD_PROPS, 36);
	this->m_pPropDialog->SetTitle("Props");
	this->m_pPropDialog2 = new CWBasePropertieChild();
	this->m_pPropDialog2->Init(200, 400, IDD_PROPS, 66);
	this->m_pPropDialog2->SetTitle("Props2");
	this->m_pPropDialog3 = new CWBasePropertieChild();
	this->m_pPropDialog3->Init(200, 400, IDD_PROPS, 64);
	this->m_pPropDialog3->SetTitle("Props3");
}

CMainWindow::~CMainWindow()
{

}


LRESULT CMainWindow::ViewProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		{
			this->m_pSysMenu->InsertItem("Hahah", 534, 0);
			this->m_pSysMenu->InsertSeperator(1);

			this->m_pPropWindow = new CWPropertieWindow();
			this->m_pPropWindow->Create(this->m_hWnd, 64);
			this->m_pPropWindow->AddDialog(this->m_pPropDialog);
			this->m_pPropWindow->AddDialog(this->m_pPropDialog2);
			this->m_pPropWindow->AddDialog(this->m_pPropDialog3);
			break;
		}

	case WM_LBUTTONDOWN:
		{
			this->m_pPropWindow->ClearDialogs();
			break;
		}

	case WM_RBUTTONDOWN:
		{
			this->m_pPropWindow->ClearDialogs();
			this->m_pPropWindow->AddDialog(this->m_pPropDialog);
			this->m_pPropWindow->AddDialog(this->m_pPropDialog2);
			this->m_pPropWindow->AddDialog(this->m_pPropDialog3);
			break;
		}

	case WM_SIZE:
		{
			m_pPropWindow->Resize(0, 0, 200, HIWORD(lParam));
			break;
		}
	}
	return CWBaseApp::ViewProc(uMsg, wParam, lParam);
}
