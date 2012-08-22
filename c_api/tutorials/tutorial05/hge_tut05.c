/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** hge_tut05 - Using distortion mesh
*/


// Copy the files "particles.png", "menu.wav",
// "font1.fnt", "font1.png" and "trail.psi" from
// the folder "precompiled" to the folder with
// executable file. Also copy hge.dll and bass.dll
// to the same folder.


#include "hge_c.h"
#include "hgefont_c.h"
#include "hgedistort_c.h"

#include <math.h>


// Pointer to the HGE interface.
// Helper classes require this to work.
HGE_t *hge=0;

HTEXTURE			tex;

// Pointers to the HGE objects we will use
HGE_DistortionMesh_t*	dis;
HGE_Font_t*			fnt;

// Some "gameplay" variables
#define nRows 16
#define nCols 16
const float cellw=512.0f/(nCols-1);
const float cellh=512.0f/(nRows-1);

const float meshx=144;
const float meshy=44;


BOOL FrameFunc()
{
	float dt=HGE_Timer_GetDelta(hge);
	static float t=0.0f;
	static int trans=0;

	int i, j, col;
	float r, a, dx, dy;

	t+=dt;

	// Process keys
	switch(HGE_Input_GetKey(hge))
	{
		case HGE_K_ESCAPE:
			return 1;

		case HGE_K_SPACE:
			if(++trans > 2) trans=0;
			HGE_DistortionMesh_Clear(dis, 0xFF000000, 0.5f);
			break;
	}

	// Calculate new displacements and coloring for one of the three effects
	switch(trans)
	{
		case 0:	for(i=1;i<nRows-1;i++)
					for(j=1;j<nCols-1;j++)
					{
						HGE_DistortionMesh_SetDisplacement(dis, j,i,cosf(t*10+(i+j)/2)*5,sinf(t*10+(i+j)/2)*5,HGE_DISP_NODE);
					}
				break;

		case 1:	for(i=0;i<nRows;i++)
					for(j=1;j<nCols-1;j++)
					{
						HGE_DistortionMesh_SetDisplacement(dis, j,i,cosf(t*5+j/2)*15,0,HGE_DISP_NODE);
						col=((cosf(t*5+(i+j)/2)+1)*35);
						HGE_DistortionMesh_SetColor(dis, j,i,0xFF<<24 | col<<16 | col<<8 | col);
					}
				break;

		case 2:	for(i=0;i<nRows;i++)
					for(j=0;j<nCols;j++)
					{
						r=sqrtf(powf(j-(float)nCols/2,2)+powf(i-(float)nRows/2,2));
						a=r*cosf(t*2)*0.1f;
						dx=sinf(a)*(i*cellh-256)+cosf(a)*(j*cellw-256);
						dy=cosf(a)*(i*cellh-256)-sinf(a)*(j*cellw-256);
						HGE_DistortionMesh_SetDisplacement(dis, j,i,dx,dy,HGE_DISP_CENTER);
						col=((cos(r+t*4)+1)*40);
						HGE_DistortionMesh_SetColor(dis, j,i,0xFF<<24 | col<<16 | (col/2)<<8);
					}
					break;
	}

	return 0;
}


BOOL RenderFunc()
{
	// Render graphics
	HGE_Gfx_BeginScene(hge, 0);
	HGE_Gfx_Clear(hge, 0);
	HGE_DistortionMesh_Render(dis, meshx, meshy);
	HGE_Font_printf(fnt, 5, 5, HGE_TEXT_LEFT, "dt:%.3f\nFPS:%d\n\nUse your\nSPACE!", HGE_Timer_GetDelta(hge), HGE_Timer_GetFPS(hge));
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

	HGE_System_SetStateString(hge, HGE_C_LOGFILE, "hge_tut05.log");
	HGE_System_SetStateFunc(hge, HGE_C_FRAMEFUNC, FrameFunc);
	HGE_System_SetStateFunc(hge, HGE_C_RENDERFUNC, RenderFunc);
	HGE_System_SetStateString(hge, HGE_C_TITLE, "HGE Tutorial 05 - Using distortion mesh");
	HGE_System_SetStateBool(hge, HGE_C_WINDOWED, 1);
	HGE_System_SetStateInt(hge, HGE_C_SCREENWIDTH, 800);
	HGE_System_SetStateInt(hge, HGE_C_SCREENHEIGHT, 600);
	HGE_System_SetStateInt(hge, HGE_C_SCREENBPP, 32);
	HGE_System_SetStateBool(hge, HGE_C_USESOUND, 0);

	if(HGE_System_Initiate(hge)) {

		// Load sound and texture
		tex=HGE_Texture_Load(hge, "texture.jpg", 0, 0);
		if(!tex)
		{
			// If one of the data files is not found, display
			// an error message and shutdown.
#ifdef PLATFORM_UNIX
			fprintf(stderr, "Error: Can't load texture.jpg\n");
#else
			MessageBox(NULL, "Can't load texture.jpg", "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
#endif
			HGE_System_Shutdown(hge);
			HGE_Release(hge);
			return 0;
		}

		// Create a distortion mesh
		dis = HGE_DistortionMesh_New(nCols, nRows);
		HGE_DistortionMesh_SetTexture(dis, tex);
		HGE_DistortionMesh_SetTextureRect(dis, 0,0,512,512);
		HGE_DistortionMesh_SetBlendMode(dis, BLEND_COLORADD | BLEND_ALPHABLEND | BLEND_ZWRITE);
		HGE_DistortionMesh_Clear(dis, 0xFF000000, 0.5f);

		// Load a font
		fnt = HGE_Font_New("font1.fnt", 0);

		// Let's rock now!
		HGE_System_Start(hge);

		// Delete created objects and free loaded resources
		HGE_Font_Free(fnt);
		HGE_DistortionMesh_Free(dis);
		HGE_Texture_Free(hge, tex);
	}

	// Clean up and shutdown
	HGE_System_Shutdown(hge);
	HGE_Release(hge);
	return 0;
}
