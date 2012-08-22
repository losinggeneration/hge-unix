/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** hge_tut07 - Thousand of Hares
*/


// Copy the files "font2.fnt", "font2.png", "bg2.png"
// and "zazaka.png" from the folder "precompiled" to
// the folder with executable file. Also copy hge.dll
// to the same folder.


#include "hge_c.h"
#include "hgefont_c.h"
#include "hgesprite_c.h"

#include <malloc.h>

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

#define MIN_OBJECTS	100
#define MAX_OBJECTS 2000

typedef struct sprObject
{
	float x,y;
	float dx,dy;
	float scale,rot;
	float dscale,drot;
	DWORD color;
} sprObject;

sprObject*	pObjects;
int			nObjects;
int			nBlend;

// Pointer to the HGE interface (helper classes require this to work)

HGE_t *hge=0;

// Resource handles

HTEXTURE			tex, bgtex;
HGE_Sprite_t		*spr, *bgspr;
HGE_Font_t			*fnt;

// Set up blending mode for the scene

void SetBlend(int blend)
{
	static int sprBlend[5]=
	{
		BLEND_COLORMUL | BLEND_ALPHABLEND | BLEND_NOZWRITE,
		BLEND_COLORADD | BLEND_ALPHABLEND | BLEND_NOZWRITE,
		BLEND_COLORMUL | BLEND_ALPHABLEND | BLEND_NOZWRITE,
		BLEND_COLORMUL | BLEND_ALPHAADD   | BLEND_NOZWRITE,
		BLEND_COLORMUL | BLEND_ALPHABLEND | BLEND_NOZWRITE
	};

	static DWORD fntColor[5]=
	{
		0xFFFFFFFF, 0xFF000000, 0xFFFFFFFF, 0xFF000000, 0xFFFFFFFF
	};

	static DWORD sprColors[5][5]=
	{
		{ 0xFFFFFFFF, 0xFFFFE080, 0xFF80A0FF, 0xFFA0FF80, 0xFFFF80A0 },
		{ 0xFF000000, 0xFF303000, 0xFF000060, 0xFF006000, 0xFF600000 },
		{ 0x80FFFFFF, 0x80FFE080, 0x8080A0FF, 0x80A0FF80, 0x80FF80A0 },
		{ 0x80FFFFFF, 0x80FFE080, 0x8080A0FF, 0x80A0FF80, 0x80FF80A0 },
		{ 0x40202020, 0x40302010, 0x40102030, 0x40203010, 0x40102030 }
	};

	if(blend>4) blend=0;
	nBlend=blend;

	HGE_Sprite_SetBlendMode(spr, sprBlend[blend]);
	HGE_Font_SetColor(fnt, fntColor[blend]);
	int i;
	for(i=0;i<MAX_OBJECTS;i++) pObjects[i].color=sprColors[blend][HGE_Random_Int(hge, 0,4)];
}

BOOL FrameFunc()
{
	float dt=HGE_Timer_GetDelta(hge);
	int i;

	// Process keys

	switch(HGE_Input_GetKey(hge))
	{
		case HGE_K_UP:		if(nObjects<MAX_OBJECTS) nObjects+=100; break;
		case HGE_K_DOWN:		if(nObjects>MIN_OBJECTS) nObjects-=100; break;
		case HGE_K_SPACE:	SetBlend(++nBlend); break;
		case HGE_K_ESCAPE:	return 1;
	}

	// Update the scene

	for(i=0;i<nObjects;i++)
	{
		pObjects[i].x+=pObjects[i].dx*dt;
		if(pObjects[i].x>SCREEN_WIDTH || pObjects[i].x<0) pObjects[i].dx=-pObjects[i].dx;
		pObjects[i].y+=pObjects[i].dy*dt;
		if(pObjects[i].y>SCREEN_HEIGHT || pObjects[i].y<0) pObjects[i].dy=-pObjects[i].dy;
		pObjects[i].scale+=pObjects[i].dscale*dt;
		if(pObjects[i].scale>2 || pObjects[i].scale<0.5) pObjects[i].dscale=-pObjects[i].dscale;
		pObjects[i].rot+=pObjects[i].drot*dt;
	}

	return 0;
}


BOOL RenderFunc()
{
	int i;

	// Render the scene
	HGE_Gfx_BeginScene(hge, 0);
	HGE_Sprite_Render(bgspr, 0, 0);

	for(i=0;i<nObjects;i++)
	{
		HGE_Sprite_SetColor(spr, pObjects[i].color, -1);
		HGE_Sprite_RenderEx(spr, pObjects[i].x, pObjects[i].y, pObjects[i].rot, pObjects[i].scale, 0.0f);
	}

	HGE_Font_printf(fnt, 7, 7, HGE_TEXT_LEFT, "UP and DOWN to adjust number of hares: %d\nSPACE to change blending mode: %d\nFPS: %d", nObjects, nBlend, HGE_Timer_GetFPS(hge));
	HGE_Gfx_EndScene(hge);

	return 0;
}

#ifdef PLATFORM_UNIX
int main(int argc, char *argv[])
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#endif
{
	int i;

	hge = HGE_Create(HGE_VERSION);

	// Set desired system states and initialize HGE
	HGE_System_SetStateString(hge, HGE_C_LOGFILE, "hge_tut07.log");
	HGE_System_SetStateFunc(hge, HGE_C_FRAMEFUNC, FrameFunc);
	HGE_System_SetStateFunc(hge, HGE_C_RENDERFUNC, RenderFunc);
	HGE_System_SetStateString(hge, HGE_C_TITLE, "HGE Tutorial 07 - Thousand of Hares");
	HGE_System_SetStateBool(hge, HGE_C_USESOUND, 0);
	HGE_System_SetStateBool(hge, HGE_C_WINDOWED, 1);
	HGE_System_SetStateInt(hge, HGE_C_SCREENWIDTH, SCREEN_WIDTH);
	HGE_System_SetStateInt(hge, HGE_C_SCREENHEIGHT, SCREEN_HEIGHT);
	HGE_System_SetStateInt(hge, HGE_C_SCREENBPP, 32);

	if(HGE_System_Initiate(hge))
	{

		// Load textures

		bgtex=HGE_Texture_Load(hge, "bg2.png", 0, 0);
		tex=HGE_Texture_Load(hge, "zazaka.png", 0, 0);
		if(!bgtex || !tex)
		{
			// If one of the data files is not found,
			// display an error message and shutdown
#ifdef PLATFORM_UNIX
			fprintf(stderr, "Error: Can't load bg2.png or zazaka.png\n");
#else
			MessageBox(NULL, "Can't load bg2.png or zazaka.png", "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
#endif
			HGE_System_Shutdown(hge);
			HGE_Release(hge);
			return 0;
		}

		// Load font, create sprites

		fnt = HGE_Font_New("font2.fnt", 0);
		spr = HGE_Sprite_New(tex, 0, 0, 64, 64);
		HGE_Sprite_SetHotSpot(spr, 32, 32);

		bgspr = HGE_Sprite_New(bgtex,0,0,800,600);
		HGE_Sprite_SetBlendMode(bgspr, BLEND_COLORADD | BLEND_ALPHABLEND | BLEND_NOZWRITE);
		HGE_Sprite_SetColor(bgspr, 0xFF000000,0);
		HGE_Sprite_SetColor(bgspr, 0xFF000000,1);
		HGE_Sprite_SetColor(bgspr, 0xFF000040,2);
		HGE_Sprite_SetColor(bgspr, 0xFF000040,3);

		// Initialize objects list

		pObjects=(sprObject*)malloc(sizeof(sprObject[MAX_OBJECTS]));
		nObjects=1000;

		for(i=0;i<MAX_OBJECTS;i++)
		{
			pObjects[i].x=HGE_Random_Float(hge, 0,SCREEN_WIDTH);
			pObjects[i].y=HGE_Random_Float(hge, 0,SCREEN_HEIGHT);
			pObjects[i].dx=HGE_Random_Float(hge, -200,200);
			pObjects[i].dy=HGE_Random_Float(hge, -200,200);
			pObjects[i].scale=HGE_Random_Float(hge, 0.5f,2.0f);
			pObjects[i].dscale=HGE_Random_Float(hge, -1.0f,1.0f);
			pObjects[i].rot=HGE_Random_Float(hge, 0,M_PI*2);
			pObjects[i].drot=HGE_Random_Float(hge, -1.0f,1.0f);
		}

		SetBlend(0);

		// Let's rock now!
		HGE_System_Start(hge);

		// Delete created objects and free loaded resources
		free(pObjects);
		HGE_Font_Free(fnt);
		HGE_Sprite_Free(spr);
		HGE_Sprite_Free(bgspr);
		HGE_Texture_Free(hge, tex);
		HGE_Texture_Free(hge, bgtex);
	}

	// Clean up and shutdown
	HGE_System_Shutdown(hge);
	HGE_Release(hge);

	return 0;
}
