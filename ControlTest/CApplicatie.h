#ifndef CAPPLICATIE_H
#define CAPPLICATIE_H

#include "CWin.h"
#include "controls.h"
#include "Test.h"

enum controls
{
	Edit = 1,
	Button,
	Combo,
	ComboList,
	ListView,
	TreeView,
	Splitter
};

class CApplicatie : public CWin
{
private:
	CWOpengl* m_pGl;
	CWSplitter* m_pSplitter;
	CWEdit* edit1;
	CWEdit* edit2;
	CWCustomButton* custButton;
public:
	CApplicatie();
	~CApplicatie();

	LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
};

#endif
