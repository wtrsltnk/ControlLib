// TrayIcon.h: interface for the CTrayIcon class.
//
//////////////////////////////////////////////////////////////////////

#ifndef TRAYICON_H
#define TRAYICON_H

#include "controls.h"
#include "resource.h"

class CTrayIcon : public CWSystrayIcon  
{
public:
	CTrayIcon();
	virtual ~CTrayIcon();

	LRESULT OnClick(WPARAM wParam, LPARAM lParam);
	LRESULT OnDblClick(WPARAM wParam, LPARAM lParam);
	LRESULT OnRClick(WPARAM wParam, LPARAM lParam);
};

#endif
