// MainWindow.h: interface for the CMainWindow class.
//
//////////////////////////////////////////////////////////////////////

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "controls.h"
#include "TrayIcon.h"

class CMainWindow : public CWBaseApp
{
private:
	CWPropertieWindow* m_pPropWindow;
	CWBasePropertieChild* m_pPropDialog;
	CWBasePropertieChild* m_pPropDialog2;
	CWBasePropertieChild* m_pPropDialog3;
public:
    CMainWindow(HINSTANCE hInstance);
	virtual ~CMainWindow();

	LRESULT ViewProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

};

#endif
