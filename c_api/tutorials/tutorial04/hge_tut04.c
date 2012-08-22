/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** hge_tut04 - Using render targets
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


HGE_t *hge=0;


HGE_Sprite_t*			spr;
HGE_Sprite_t*			spt;
HGE_Sprite_t*			tar;
HGE_Font_t*			fnt;
HGE_Particle_System_t*	par;

HTEXTURE			tex;
HEFFECT				snd;

// HGE render target handle
HTARGET				target;

float x=100.0f, y=100.0f;
float dx=0.0f, dy=0.0f;

const float speed=90;
const float friction=0.98f;

void boom() {
	int pan=((x-256)/2.56f);
	float pitch=(dx*dx+dy*dy)*0.0005f+0.2f;
	HGE_Effect_PlayEx(hge, snd,100,pan,pitch,0);
}

// This function will be called by HGE when
// render targets were lost and have been just created
// again. We use it here to update the render
// target's texture handle that changes during recreation.
BOOL GfxRestoreFunc()
{
	if(tar && target) HGE_Sprite_SetTexture(tar, HGE_Target_GetTexture(hge, target));
	return 0;
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
	if(x>496) {x=496-(x-496);dx=-dx;boom();}
	if(x<16) {x=16+16-x;dx=-dx;boom();}
	if(y>496) {y=496-(y-496);dy=-dy;boom();}
	if(y<16) {y=16+16-y;dy=-dy;boom();}

	// Update particle system
	HGE_Particle_System_GetInfo(par)->nEmission = (dx*dx+dy*dy);
	HGE_Particle_System_MoveTo(par, x, y, 0);
	HGE_Particle_System_Update(par, dt);

	return 0;
}


BOOL RenderFunc()
{
	int i;

	// Render graphics to the texture
	HGE_Gfx_BeginScene(hge, target);
	HGE_Gfx_Clear(hge, 0);
	HGE_Particle_System_Render(par);
	HGE_Sprite_Render(spr, x, y);
	HGE_Gfx_EndScene(hge);

	// Now put several instances of the rendered texture to the screen
	HGE_Gfx_BeginScene(hge, 0);
	HGE_Gfx_Clear(hge, 0);
	for(i=0;i<6;i++)
	{
		HGE_Sprite_RenderEx(tar, i*100.0f, i*50.0f, i*M_PI/8, 1.0f-i*0.1f, 0.0f);
		HGE_Sprite_SetColor(tar, 0xFFFFFF | (((5-i)*40+55)<<24), -1);
	}
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

	HGE_System_SetStateString(hge, HGE_C_LOGFILE, "hge_tut04.log");
	HGE_System_SetStateFunc(hge, HGE_C_FRAMEFUNC, FrameFunc);
	HGE_System_SetStateFunc(hge, HGE_C_RENDERFUNC, RenderFunc);
	HGE_System_SetStateFunc(hge, HGE_C_GFXRESTOREFUNC, GfxRestoreFunc);
	HGE_System_SetStateString(hge, HGE_C_TITLE, "HGE Tutorial 04 - Using render targets");
	HGE_System_SetStateInt(hge, HGE_C_FPS, 100);
	HGE_System_SetStateBool(hge, HGE_C_WINDOWED, 1);
	HGE_System_SetStateInt(hge, HGE_C_SCREENWIDTH, 800);
	HGE_System_SetStateInt(hge, HGE_C_SCREENHEIGHT, 600);
	HGE_System_SetStateInt(hge, HGE_C_SCREENBPP, 32);

	tar=0;
	target=0;

	if(HGE_System_Initiate(hge)) {
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

		spr = HGE_Sprite_New(tex, 96, 64, 32, 32);
		HGE_Sprite_SetColor(spr, 0xFFFFA000, -1);
		HGE_Sprite_SetHotSpot(spr, 16, 16);

		fnt = HGE_Font_New("font1.fnt", 0);

		spt = HGE_Sprite_New(tex, 32, 32, 32, 32);
		HGE_Sprite_SetBlendMode(spt, BLEND_COLORMUL | BLEND_ALPHAADD | BLEND_NOZWRITE);
		HGE_Sprite_SetHotSpot(spt, 16, 16);
		par = HGE_Particle_System_New("trail.psi", spt, 0.0);
		HGE_Particle_System_Fire(par);

		// Create a render target and a sprite for it
		target=HGE_Target_Create(hge, 512,512,0);
		tar = HGE_Sprite_New(HGE_Target_GetTexture(hge, target),0,0,512,512);
		HGE_Sprite_SetBlendMode(tar, BLEND_COLORMUL | BLEND_ALPHAADD | BLEND_NOZWRITE);

		// Let's rock now!
		HGE_System_Start(hge);

		// Delete created objects and free loaded resources
		HGE_Particle_System_Fire(par);
		HGE_Font_Free(fnt);
		HGE_Sprite_Free(spt);
		HGE_Sprite_Free(spr);
		HGE_Sprite_Free(tar);
		HGE_Target_Free(hge, target);
		HGE_Texture_Free(hge, tex);
		HGE_Effect_Free(hge, snd);
	}

	// Clean up and shutdown
	HGE_System_Shutdown(hge);
	HGE_Release(hge);
	return 0;
}
