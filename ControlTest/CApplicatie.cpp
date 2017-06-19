#include "CApplicatie.h"
#include <tchar.h>
#include <gl/glaux.h>

/////////////////////////////////////
// Constructors / Destructors      //
/////////////////////////////////////
CApplicatie::CApplicatie()
{
	this->m_dwWindowStyle	 = WS_OVERLAPPEDWINDOW;
	this->m_dwExWindowStyle	 = WS_EX_WINDOWEDGE;
	this->m_hbrWindowColor	 = (HBRUSH)(COLOR_WINDOW);
	this->m_hIcon			 = LoadIcon(m_hInstance, (LPCTSTR)IDI_APPLICATION);
	this->m_strWindowTitle	 = _T("Control library Test application");
	this->m_hMenu			 = NULL;
}


CApplicatie::~CApplicatie()
{
}

/////////////////////////////////////
// Memberfuncties                  //
/////////////////////////////////////

LRESULT CApplicatie::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		{
			m_pGl = new CWOpengl();
			m_pGl->Create(hWnd, 200);
			m_pGl->Resize(0, 0, 10, 10);
			m_pGl->Use();
/*/
			m_pSplitter = new CWSplitter();
			m_pSplitter->Create(hWnd, Splitter, true);

			edit1 = new CWEdit();
			edit2 = new CWEdit();

			edit1->Create(this->m_hWnd, 487);
			edit2->Create(this->m_hWnd, 488);

			m_pSplitter->SetControlA(edit1, 50);
			m_pSplitter->SetControlB(edit2, 200);
//*/

			custButton = new CWCustomButton();
			custButton->SetVisible(true);
			custButton->Create(this->m_hWnd, 4563);
			custButton->SetTitle("Ok");
			break;
		}

	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case 4563:
				{
					switch (HIWORD(wParam))
					{
					case BN_CLICKED:
						{
							this->custButton->SetVisible(true);
							break;
						}
					}
					break;
				}
			}
			break;
		}

	case WM_SIZE:
		{
//*
			m_pGl->Resize(10, 40, LOWORD(lParam)-20, HIWORD(lParam)-50);
			custButton->Resize(10, 10, 120, 24);
/*/

			this->m_pSplitter->Resize(10, 110, LOWORD(lParam)-20, HIWORD(lParam)-120);
//*/
			break;
		}

	case WM_PAINT:
		{
//*
			if (m_pGl)
			{
				float color[4] = {1.0f, 1.0f, 1.0f, 0.1f};
				RECT rc = {10, 10, 100, 100};
				m_pGl->Use();
				m_pGl->PreRender();

					m_pGl->Goto2D();
					m_pGl->Render2DFilledRect(&rc, color);
					rc.left += 20;
					rc.top += 20;
					rc.right += 20;
					rc.bottom += 20;
					m_pGl->Render2DFilledRect(&rc, color);
					color[3] = 1.0f;
					m_pGl->Render2DRect(&rc, color);
					m_pGl->Render2DText(10, 10, color, "Hallo");
					m_pGl->Leave2D();

				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				glTranslatef(0.0f, 0.0f, -10.0f);
				glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
				glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
				glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Right Of The Texture and Quad
				glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Top Left Of The Texture and Quad
				glEnd();
					
				m_pGl->PostRender();
			}
			ValidateRect(hWnd, NULL);
//*/
			break;
		}
	}
	return CWin::MsgProc(hWnd, uMsg, wParam, lParam);
}

