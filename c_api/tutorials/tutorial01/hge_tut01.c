/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** hge_tut01 - Minimal HGE application
*/

#include "hge_c.h"

HGE_t *hge = 0;

// This function will be called by HGE once per frame.
// Put your game loop code here. In this example we
// just check whether ESC key has been pressed.
BOOL FrameFunc()
{
	// By returning "true" we tell HGE
	// to stop running the application.
	if (HGE_Input_GetKeyState(hge, HGE_K_ESCAPE)) return 1;

	// Continue execution
	return 0;
}

#ifdef PLATFORM_UNIX
int main(int argc, char *argv[])
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#endif
{
	// Here we use global pointer to HGE interface.
	// Instead you may use hgeCreate() every
	// time you need access to HGE. Just be sure to
	// have a corresponding hge->Release()
	// for each call to hgeCreate()
	hge = HGE_Create(HGE_VERSION);

	// Set our frame function
	HGE_System_SetStateFunc(hge, HGE_C_FRAMEFUNC, FrameFunc);

	// Set the window title
	HGE_System_SetStateString(hge, HGE_C_TITLE, "HGE Tutorial 01 - Minimal HGE application");

	// Run in windowed mode
	// Default window size is 800x600
	HGE_System_SetStateBool(hge, HGE_C_WINDOWED, 1);

	// Don't use BASS for sound
	HGE_System_SetStateBool(hge, HGE_C_USESOUND, 0);

	// Tries to initiate HGE with the states set.
	// If something goes wrong, "false" is returned
	// and more specific description of what have
	// happened can be read with System_GetErrorMessage().
	if(HGE_System_Initiate(hge))
	{
		// Starts running FrameFunc().
		// Note that the execution "stops" here
		// until "true" is returned from FrameFunc().
		HGE_System_Start(hge);
	}
	else
	{
		// If HGE initialization failed show error message
#ifdef PLATFORM_UNIX
		fprintf(stderr, "Error: %s\n", HGE_System_GetErrorMessage(hge));
#else
		MessageBox(NULL, HGE_System_GetErrorMessage(hge), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
#endif
	}

	// Now ESC has been pressed or the user
	// has closed the window by other means.

	// Restore video mode and free
	// all allocated resources
	HGE_System_Shutdown(hge);

	// Release the HGE interface.
	// If there are no more references,
	// the HGE object will be deleted.
	HGE_Release(hge);

	return 0;
}
