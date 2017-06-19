// Props.h: interface for the CProps class.
//
//////////////////////////////////////////////////////////////////////

#ifndef PROPS_H
#define PROPS_H

#include "controls.h"
#include "resource.h"

class CProps : public CWPropertieDialog
{
public:
	CProps();
	virtual ~CProps();

	void DlgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

};

#endif
