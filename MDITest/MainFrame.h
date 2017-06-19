// MainFrame.h: interface for the CMainFrame class.
//
//////////////////////////////////////////////////////////////////////

#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "controls.h"
#include "Document.h"
#include "TrayIcon.h"

class CMainFrame : public CWBaseMDIApp
{
public:
	CMainFrame();
	virtual ~CMainFrame();

	LRESULT ViewProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif
