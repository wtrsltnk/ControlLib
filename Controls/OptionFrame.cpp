// OptionFrame.cpp: implementation of the CWOptionFrame class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWOptionFrame::CWOptionFrame()
{
	this->m_dwStyle			= WS_CHILD | WS_VISIBLE | BS_NOTIFY | BS_GROUPBOX;
	this->m_strClassName	= "BUTTON";
    strcpy(this->m_strTitle, "Titel");
	this->m_nNumOptions		= 0;
}

CWOptionFrame::~CWOptionFrame()
{
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
bool CWOptionFrame::AddOption(CWOption* option, int id)
{
	if (m_hWnd == NULL)
		return false;

	m_nNumOptions++;
	m_aOptions.push_back(option);
	option->Create(m_hWnd, id);
	option->Resize(10, (m_nNumOptions*20), this->m_nWidth-20, 20);
	return false;
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
int CWOptionFrame::GetSelectedOption()
{
	for (int i = 0; i < m_aOptions.size(); i++)
	{
		if (m_aOptions[i]->GetState() == BST_CHECKED)
			return m_aOptions[i]->GetID();
	}
	return -1;
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
void CWOptionFrame::SetSelectedOption(int id)
{
	for (int i = 0; i < m_aOptions.size(); i++)
	{
		if (m_aOptions[i]->GetID() == id)
			m_aOptions[i]->SetState(BST_CHECKED);
		else
			m_aOptions[i]->SetState(BST_UNCHECKED);
	}
}
