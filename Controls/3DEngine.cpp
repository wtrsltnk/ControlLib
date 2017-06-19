// 3DEngine.cpp: implementation of the C3DEngine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <stdio.h>
#include <stdarg.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CW3DEngine::CW3DEngine()
{
	this->m_hDC					 = NULL;
	this->m_hRC					 = NULL;
	this->m_uFont				 = 0;

	this->m_nWidth				 = 100;
	this->m_nHeight				 = 100;
	this->m_fAspect				 = 0.0f;

	this->m_fFieldOfView		 = 45.0f;
	this->m_fNearClipping		 = 0.1f;
	this->m_fFarClipping		 = 300.0f;
}

CW3DEngine::~CW3DEngine()
{
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
LRESULT CW3DEngine::InitPixelFormat()
{
	PIXELFORMATDESCRIPTOR pfd;
	int format;
	
	::ZeroMemory(&pfd, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;
	
	if ((format = ::ChoosePixelFormat(this->m_hDC, &pfd)) == 0)
		return FALSE;

	if (::SetPixelFormat(this->m_hDC, format, &pfd) == 0)
		return FALSE;

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
void CW3DEngine::Goto3D()
{
	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();
	::glPushMatrix();

	::gluPerspective(this->m_fFieldOfView, this->m_fAspect, this->m_fNearClipping, this->m_fFarClipping);

	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
void CW3DEngine::Leave3D()
{
	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();
	::glPopMatrix();
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
LRESULT CW3DEngine::Init(HWND hWnd)
{
	this->m_hWnd = hWnd;

	if (!this->m_hWnd)
	{
		Kill();
		return FALSE;
	}

	this->m_hDC = ::GetDC(this->m_hWnd);
	if (!m_hDC)
	{
		Kill();
		return FALSE;
	}

	if (!InitPixelFormat())
	{
		Kill();
		return FALSE;
	}

	this->m_hRC = ::wglCreateContext(this->m_hDC);
	if (!this->m_hRC)
	{
		Kill();
		return FALSE;
	}
	
	if (!::wglMakeCurrent(this->m_hDC, this->m_hRC))
	{
		Kill();
		return FALSE;
	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
LRESULT CW3DEngine::Kill()
{
	::wglMakeCurrent(NULL, NULL);

	if (this->m_hRC)
		::wglDeleteContext(this->m_hRC);
	
	if (this->m_hWnd && this->m_hDC)
		::ReleaseDC(this->m_hWnd, this->m_hDC);

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
void CW3DEngine::Resize(int width, int height)
{
	this->m_nWidth = width;
	this->m_nHeight = height;
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
void CW3DEngine::Use()
{
	::wglMakeCurrent(this->m_hDC, this->m_hRC);
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
void CW3DEngine::PreRender()
{
	::glViewport(0, 0, this->m_nWidth, this->m_nHeight);

	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();

	::glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Goto3D();
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
void CW3DEngine::PostRender()
{
	Leave3D();
	::SwapBuffers(this->m_hDC);
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
void CW3DEngine::Goto2D()
{
	Leave3D();
	
	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();
	::glPushMatrix();

	::gluOrtho2D(0.0, this->m_nWidth, 0.0, this->m_nHeight);

	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
void CW3DEngine::Leave2D()
{
	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();
	::glPopMatrix();

	Goto3D();
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
void CW3DEngine::Render2DFilledRect(RECT* rc, float color[4])
{
	::glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	::glEnable(GL_BLEND);
	::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	::glColor4f(color[0], color[1], color[2], color[3]);
	::glRecti(rc->left, this->m_nHeight - rc->top, rc->right, this->m_nHeight - rc->bottom);
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
void CW3DEngine::Render2DRect(RECT* rc, float color[4])
{
	::glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	::glEnable(GL_BLEND);
	::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	::glColor4f(color[0], color[1], color[2], color[3]);
	::glRecti(rc->left, this->m_nHeight - rc->top, rc->right, this->m_nHeight - rc->bottom);
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
void CW3DEngine::Render2DText(int x, int y, float color[4], UINT font, const char *format, ...)
{
    va_list argp;
    char text[256];

    va_start(argp, format);
    vsprintf(text, format, argp);
    va_end(argp );

	for ( int i = 0; i < strlen(text); i++ )
		text[i] -= 1;

    glColor3f(color[0], color[1], color[2]);
    glRasterPos2i(x, this->m_nHeight - y - 10);
    glListBase(font);
    glCallLists(strlen(text), GL_BYTE, text);
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
void CW3DEngine::AddFont(char* face, int height, int width, UINT* fontid)
{
	*fontid = ::glGenLists(255);

    HFONT verdana = ::CreateFont(height, width, 0, 0, FW_MEDIUM, FALSE,
						FALSE, FALSE, DEFAULT_CHARSET, OUT_TT_PRECIS,
						CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
						FF_DONTCARE | DEFAULT_PITCH, face);

    ::SelectObject(this->m_hDC, verdana);

    ::wglUseFontBitmaps(this->m_hDC, 1, 255, *fontid);
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
void CW3DEngine::AddFont(HFONT hFont, UINT* fontid)
{
	*fontid = ::glGenLists(255);

    ::SelectObject(this->m_hDC, hFont);

    ::wglUseFontBitmaps(this->m_hDC, 1, 255, *fontid);
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
void CW3DEngine::AddTexture(BITMAP bmp, unsigned int* texid)
{
	::glGenTextures(1, texid);
	
	// Typical Texture Generation Using Data From The Bitmap
	::glBindTexture(GL_TEXTURE_2D, *texid);								// Bind To The Texture ID
	::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Min Filter
	::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// Linear Mag Filter
	::glTexImage2D(GL_TEXTURE_2D, 0, 3, bmp.bmWidth, bmp.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, bmp.bmBits);
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
void CW3DEngine::UseTexture(int i)
{
	::glBindTexture(GL_TEXTURE_2D, i);
}
