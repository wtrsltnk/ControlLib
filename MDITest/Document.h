// Document.h: interface for the CDocument class.
//
//////////////////////////////////////////////////////////////////////

#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "controls.h"

class CDocument : public CWMDIChild
{
private:
	CW3DEngine* engine;
public:
	CDocument();
	virtual ~CDocument();

	void ViewProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif
