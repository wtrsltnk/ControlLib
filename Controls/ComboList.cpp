// ComboList.cpp: implementation of the CComboList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWComboList::CWComboList()
{
	this->m_dwStyle			= WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST;
	this->m_strClassName	= "COMBOBOX";
    strcpy(this->m_strTitle, "Combolistbox");
}

CWComboList::~CWComboList()
{
}
