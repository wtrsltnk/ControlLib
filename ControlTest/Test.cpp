// Test.cpp: implementation of the CTest class.
//
//////////////////////////////////////////////////////////////////////

#include "Test.h"
#include <stdio.h>

int CTest::m_nNextID = 0;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTest::CTest()
{
	this->m_nID = m_nNextID++;
}

CTest::~CTest()
{

}

char* CTest::Identify()
{
	char* text = new char[255];

	sprintf(text, "Test object %d", this->m_nID);
	return text;
}
