// Test.h: interface for the CTest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEST_H__CA5653CE_88B2_47C4_99FE_33CBCD90ACC4__INCLUDED_)
#define AFX_TEST_H__CA5653CE_88B2_47C4_99FE_33CBCD90ACC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTest  
{
private:
	static int m_nNextID;
	int m_nID;
public:
	CTest();
	virtual ~CTest();

	char* Identify();
};

#endif // !defined(AFX_TEST_H__CA5653CE_88B2_47C4_99FE_33CBCD90ACC4__INCLUDED_)
