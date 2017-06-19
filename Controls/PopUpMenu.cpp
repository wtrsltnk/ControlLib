// PopUpMenu.cpp: implementation of the CWPopUpMenu class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWPopUpMenu::CWPopUpMenu()
{
	this->m_hMenu = CreatePopupMenu();

	strcpy(this->m_strName, "PopUpMenu");
}

CWPopUpMenu::CWPopUpMenu(char* name)
{
	this->m_hMenu = CreatePopupMenu();

	strcpy(this->m_strName, name);
}

CWPopUpMenu::~CWPopUpMenu()
{
	if (this->m_hMenu)
	{
		DestroyMenu(this->m_hMenu);
		this->m_hMenu = NULL;
	}
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
void CWPopUpMenu::ShowMenu(HWND hOwner, int x, int y)
{
	TrackPopupMenuEx(this->m_hMenu, TPM_VERTICAL | TPM_LEFTALIGN | TPM_TOPALIGN, x, y, hOwner, NULL);
}