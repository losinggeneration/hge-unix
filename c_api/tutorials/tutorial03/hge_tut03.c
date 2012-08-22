/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** hge_tut03 - Using helper classes
*/


// Copy the files "particles.png", "menu.wav",
// "font1.fnt", "font1.png" and "trail.psi" from
// the folder "precompiled" to the folder with
// executable file. Also copy hge.dll and bass.dll
// to the same folder.


#include "hge_c.h"
#include "hgesprite_c.h"
#include "hgefont_c.h"
#include "hgeparticle_c.h"


// Pointer to the HGE interface.
// Helper classes require this to work.
HGE_t *hge=0;


// Pointers to the HGE objects we will use
HGE_Sprite_t*			spr;
HGE_Sprite_t*			spt;
HGE_Font_t*				fnt;
HGE_Particle_System_t*	par;

// Handles for HGE resourcces
HTEXTURE			tex;
HEFFECT				snd;

// Some "gameplay" variables
float x=100.0f, y=100.0f;
float dx=0.0f, dy=0.0f;

const float speed=90;
const float friction=0.98f;

// Play sound effect
void boom() {
	int pan=((x-400)/4);
	float pitch=(dx*dx+dy*dy)*0.0005f+0.2f;
	HGE_Effect_PlayEx(hge, snd,100,pan,pitch,0);
}

BOOL FrameFunc()
{
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

	// Update particle system
	HGE_Particle_SystemInfo_t *info = HGE_Particle_System_GetInfo(par);
	info->nEmission = ((int)(dx*dx+dy*dy)*2);
	HGE_Particle_System_MoveTo(par, x, y, 0);
	HGE_Particle_System_Update(par, dt);

	return 0;
}


BOOL RenderFunc()
{
	// Render graphics
	HGE_Gfx_BeginScene(hge, 0);
	HGE_Gfx_Clear(hge, 0);
	HGE_Particle_System_Render(par);
	HGE_Sprite_Render(spr, x, y);
	HGE_Font_printf(fnt, 5, 5, HGE_TEXT_LEFT, "dt:%.3f\nFPS:%d (constant)", HGE_Timer_GetDelta(hge), HGE_Timer_GetFPS(hge));

	HGE_Gfx_EndScene(hge);

	return 0;
}


#ifdef PLATFORM_UNIX
int main(int argc, char *argv[])
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#endif
{
	hge = HGE_Create(HGE_VERSION);

	HGE_System_SetStateString(hge, HGE_C_LOGFILE, "hge_tut03.log");
	HGE_System_SetStateFunc(hge, HGE_C_FRAMEFUNC, FrameFunc);
	HGE_System_SetStateFunc(hge, HGE_C_RENDERFUNC, RenderFunc);
	HGE_System_SetStateString(hge, HGE_C_TITLE, "HGE Tutorial 03 - Using helper classes");
	HGE_System_SetStateInt(hge, HGE_C_FPS, 100);
	HGE_System_SetStateBool(hge, HGE_C_WINDOWED, 1);
	HGE_System_SetStateInt(hge, HGE_C_SCREENWIDTH, 800);
	HGE_System_SetStateInt(hge, HGE_C_SCREENHEIGHT, 600);
	HGE_System_SetStateInt(hge, HGE_C_SCREENBPP, 32);

	if(HGE_System_Initiate(hge)) {

		// Load sound and texture
#ifdef PLATFORM_UNIX
		snd=HGE_Effect_Load(hge, "menu.ogg", 0);
#else
		snd=HGE_Effect_Load(hge, "menu.wav", 0);
#endif
		tex=HGE_Texture_Load(hge, "particles.png", 0, 0);
		if(!snd || !tex)
		{
			// If one of the data files is not found, display
			// an error message and shutdown.
#ifdef PLATFORM_UNIX
			fprintf(stderr, "Error: Can't load one of the following files:\nmenu.wav, particles.png, font1.fnt, font1.png, trail.psi\n");
#else
			MessageBox(NULL, "Can't load one of the following files:\nmenu.wav, particles.png, font1.fnt, font1.png, trail.psi", "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
#endif
			HGE_System_Shutdown(hge);
			HGE_Release(hge);
			return 0;
		}

		// Create and set up a sprite
		spr = HGE_Sprite_New(tex, 96, 64, 32, 32);
		HGE_Sprite_SetColor(spr, 0xFFFFA000, -1);
		HGE_Sprite_SetHotSpot(spr, 16,16);

		// Load a font
		fnt=HGE_Font_New("font1.fnt", 0);

		// Create and set up a particle system
		spt = HGE_Sprite_New(tex, 32, 32, 32, 32);
		HGE_Sprite_SetBlendMode(spt, BLEND_COLORMUL | BLEND_ALPHAADD | BLEND_NOZWRITE);
		HGE_Sprite_SetHotSpot(spt, 16,16);
		par = HGE_Particle_System_New("trail.psi", spt, 0.0);
		HGE_Particle_System_Fire(par);

		// Let's rock now!
		HGE_System_Start(hge);

		// Delete created objects and free loaded resources
		HGE_Particle_System_Free(par);
		HGE_Font_Free(fnt);
		HGE_Sprite_Free(spt);
		HGE_Sprite_Free(spr);
		HGE_Texture_Free(hge, tex);
		HGE_Effect_Free(hge, snd);
	}

	// Clean up and shutdown
	HGE_System_Shutdown(hge);
	HGE_Release(hge);
	return 0;
}
