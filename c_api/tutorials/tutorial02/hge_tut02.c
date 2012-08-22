/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** hge_tut02 - Using input, sound and rendering
*/


// Copy the files "particles.png" and "menu.wav"
// from the folder "precompiled" to the folder with
// executable file. Also copy hge.dll and bass.dll
// to the same folder.


#include "hge_c.h"

HGE_t *hge=0;

// Quad is the basic primitive in HGE
// used for rendering graphics.
// Quad contains 4 vertices, numbered
// 0 to 3 clockwise.
HGE_Quad_t quad;

// Handle for a sound effect
HEFFECT snd;

// Some "gameplay" variables and constants
float x=100.0f, y=100.0f;
float dx=0.0f, dy=0.0f;

const float speed=90;
const float friction=0.98f;

// This function plays collision sound with
// parameters based on sprite position and speed
void boom() {
	int pan=((x-400)/4);
	float pitch=(dx*dx+dy*dy)*0.0005f+0.2f;
	HGE_Effect_PlayEx(hge, snd, 100, pan, pitch, 0);
}

BOOL FrameFunc()
{
	// Get the time elapsed since last call of FrameFunc().
	// This will help us to synchronize on different
	// machines and video modes.
	float dt=HGE_Timer_GetDelta(hge);

	// Process keys
	if (HGE_Input_GetKeyState(hge, HGE_K_ESCAPE)) return 1;
	if (HGE_Input_GetKeyState(hge, HGE_K_LEFT)) dx-=speed*dt;
	if (HGE_Input_GetKeyState(hge, HGE_K_RIGHT)) dx+=speed*dt;
	if (HGE_Input_GetKeyState(hge, HGE_K_UP)) dy-=speed*dt;
	if (HGE_Input_GetKeyState(hge, HGE_K_DOWN)) dy+=speed*dt;

	// Do some movement calculations and collision detection
	dx*=friction; dy*=friction; x+=dx; y+=dy;
	if(x>784) {x=784-(x-784);dx=-dx;boom();}
	if(x<16) {x=16+16-x;dx=-dx;boom();}
	if(y>584) {y=584-(y-584);dy=-dy;boom();}
	if(y<16) {y=16+16-y;dy=-dy;boom();}

	// Set up quad's screen coordinates
	quad.v[0].x=x-16; quad.v[0].y=y-16;
	quad.v[1].x=x+16; quad.v[1].y=y-16;
	quad.v[2].x=x+16; quad.v[2].y=y+16;
	quad.v[3].x=x-16; quad.v[3].y=y+16;

	// Continue execution
	return 0;
}

// This function will be called by HGE when
// the application window should be redrawn.
// Put your rendering code here.
BOOL RenderFunc()
{
	// Begin rendering quads.
	// This function must be called
	// before any actual rendering.
	HGE_Gfx_BeginScene(hge, 0);

	// Clear screen with black color
	HGE_Gfx_Clear(hge, 0);

	// Render quads here. This time just
	// one of them will serve our needs.
	HGE_Gfx_RenderQuad(hge, &quad);

	// End rendering and update the screen
	HGE_Gfx_EndScene(hge);

	// RenderFunc should always return 0
	return 0;
}

#ifdef PLATFORM_UNIX
int main(int argc, char *argv[])
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#endif
{
	// Get HGE interface
	hge = HGE_Create(HGE_VERSION);

	// Set up log file, frame function, render function and window title
	HGE_System_SetStateString(hge, HGE_C_LOGFILE, "hge_tut02.log");
	HGE_System_SetStateFunc(hge, HGE_C_FRAMEFUNC, FrameFunc);
	HGE_System_SetStateFunc(hge, HGE_C_RENDERFUNC, RenderFunc);
	HGE_System_SetStateString(hge, HGE_C_TITLE, "HGE Tutorial 02 - Using input, sound and rendering");

	// Set up video mode
	HGE_System_SetStateBool(hge, HGE_C_WINDOWED, 1);
	HGE_System_SetStateInt(hge, HGE_C_SCREENWIDTH, 800);
	HGE_System_SetStateInt(hge, HGE_C_SCREENHEIGHT, 600);
	HGE_System_SetStateInt(hge, HGE_C_SCREENBPP, 32);

	if(HGE_System_Initiate(hge))
	{
		// Load sound and texture
#ifdef PLATFORM_UNIX
		snd=HGE_Effect_Load(hge, "menu.ogg", 0);
#else
		snd=HGE_Effect_Load(hge, "menu.wav", 0);
#endif
		quad.tex=HGE_Texture_Load(hge, "particles.png", 0, 0);
		if(!snd || !quad.tex)
		{
			// If one of the data files is not found, display
			// an error message and shutdown.
#ifdef PLATFORM_UNIX
			fprintf(stderr, "Error: Can't load menu.wav or particles.png\n");
#else
			MessageBox(NULL, "Can't load menu.wav or particles.png", "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
#endif
			HGE_System_Shutdown(hge);
			HGE_Release(hge);
			return 0;
		}

		// Set up quad which we will use for rendering sprite
		quad.blend=BLEND_ALPHAADD | BLEND_COLORMUL | BLEND_ZWRITE;

		int i;
		for(i=0;i<4;i++)
		{
			// Set up z-coordinate of vertices
			quad.v[i].z=0.5f;
			// Set up color. The format of DWORD col is 0xAARRGGBB
			quad.v[i].col=0xFFFFA000;
		}

		// Set up quad's texture coordinates.
		// 0,0 means top left corner and 1,1 -
		// bottom right corner of the texture.
		quad.v[0].tx=96.0/128.0; quad.v[0].ty=64.0/128.0;
		quad.v[1].tx=128.0/128.0; quad.v[1].ty=64.0/128.0;
		quad.v[2].tx=128.0/128.0; quad.v[2].ty=96.0/128.0;
		quad.v[3].tx=96.0/128.0; quad.v[3].ty=96.0/128.0;

		// Let's rock now!
		HGE_System_Start(hge);

		// Free loaded texture and sound
		HGE_Texture_Free(hge, quad.tex);
		HGE_Effect_Free(hge, snd);
	}
	else {
#ifdef PLATFORM_UNIX
		fprintf(stderr, "Error: %s\n", HGE_System_GetErrorMessage(hge));
#else
		MessageBox(NULL, HGE_System_GetErrorMessage(hge), "Error", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
#endif
	}

	// Clean up and shutdown
	HGE_System_Shutdown(hge);
	HGE_Release(hge);
	return 0;
}
