// Label.cpp: implementation of the CLabel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWLabel::CWLabel()
{
	this->m_strClassName	= "STATIC";
    strcpy(this->m_strTitle, "Label");
}

CWLabel::~CWLabel()
{
}
