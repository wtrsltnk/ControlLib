// Document.cpp: implementation of the CDocument class.
//
//////////////////////////////////////////////////////////////////////

#include "Document.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDocument::CDocument()
{
}

CDocument::~CDocument()
{
	this->engine->Kill();
	delete engine;
}

void CDocument::ViewProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		{
			this->engine = new CW3DEngine();
			this->engine->Init(this->m_hWnd);
			break;
		}

	case WM_SIZE:
		{
			this->engine->Resize(LOWORD(lParam), HIWORD(lParam));
			break;
		}

	case WM_PAINT:
		{
			float color[4] = {1.0f, 1.0f, 1.0f, 0.1f};
			RECT rc = {10, 10, 100, 100};

			this->engine->Use();
			this->engine->PreRender();
		
				this->engine->Goto2D();
				this->engine->Render2DFilledRect(&rc, color);
				rc.left += 20;
				rc.top += 20;
				rc.right += 20;
				rc.bottom += 20;
				this->engine->Render2DFilledRect(&rc, color);
				color[3] = 1.0f;
				this->engine->Render2DRect(&rc, color);
				this->engine->Leave2D();

				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				glTranslatef(0.0f, 0.0f, -10.0f);
				glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
				glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
				glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Right Of The Texture and Quad
				glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Top Left Of The Texture and Quad
				glEnd();
			this->engine->PostRender();
			ValidateRect(this->m_hWnd, NULL);
			break;
		}
	}
}