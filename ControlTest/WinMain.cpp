// WinClass.cpp : Defines the entry point for the application.
//
#include "CApplicatie.h"

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	CApplicatie app;

	if (!app.Create())
		return 0;
	
	return app.Run();
}
