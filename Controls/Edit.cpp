// Edit.cpp: implementation of the CWEdit class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWEdit::CWEdit()
{
	this->m_strClassName	= "EDIT";
}

CWEdit::~CWEdit()
{
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// OUtput  : 
//////////////////////////////////////////////////////////////////////
void CWEdit::Append(char* text)
{
	int lenght = SendMessage(m_hWnd, WM_GETTEXTLENGTH, 0, 0);

	if (lenght <= 0)
	{
		SendMessage(m_hWnd, WM_SETTEXT, 0, (LPARAM)(LPTSTR)text);
		return;
	}

	char* cur = new char[lenght];
	SendMessage(m_hWnd, WM_GETTEXT, lenght+1, (LPARAM)(LPTSTR)cur);

	int newlenght = lenght + strlen(text);

	char* newtext = new char[newlenght];
	strcpy(newtext, cur);
	strcat(newtext, text);

	SendMessage(m_hWnd, WM_SETTEXT, 0, (LPARAM)(LPTSTR)newtext);

	delete [] newtext;
	delete [] cur;
}
