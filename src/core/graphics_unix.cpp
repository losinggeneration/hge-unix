/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** Core functions implementation: graphics
*/


#include "hge_impl_unix.h"

#if !PLATFORM_UNIX
#error This source file is for Unix and Mac OS X. Use graphics.cpp for Windows.
#endif

#if PLATFORM_UNIX

#define SUPPORT_CXIMAGE 1
#if SUPPORT_CXIMAGE
#include "CxImage/CxImage/ximage.h"
#endif

#ifndef GL_TEXTURE_RECTANGLE_ARB
#define GL_TEXTURE_RECTANGLE_ARB 0x84F5
#endif

struct gltexture
{
	GLuint name;
	GLuint width;
	GLuint height;
	DWORD *pixels;  // copy in main memory
	DWORD *lock_pixels;  // for locked texture
	bool lock_readonly;
	GLint lock_x;
	GLint lock_y;
	GLint lock_width;
	GLint lock_height;
};

void CALL HGE_Impl::Gfx_Clear(DWORD color)
{
	GLbitfield flags = GL_COLOR_BUFFER_BIT;
	if ( ((pCurTarget) && (pCurTarget->pDepth)) || bZBuffer )
		flags |= GL_DEPTH_BUFFER_BIT;

	const GLfloat a = ((GLfloat) ((color >> 24) & 0xFF)) / 255.0f;
	const GLfloat r = ((GLfloat) ((color >> 16) & 0xFF)) / 255.0f;
	const GLfloat g = ((GLfloat) ((color >>  8) & 0xFF)) / 255.0f;
	const GLfloat b = ((GLfloat) ((color >>  0) & 0xFF)) / 255.0f;
	pOpenGLDevice->glClearColor(r, g, b, a);
	pOpenGLDevice->glClear(flags);

	// !!! FIXME: clear FBOs/pBuffers, etc.
	STUBBED("FBOs");
}

void CALL HGE_Impl::Gfx_SetClipping(int x, int y, int w, int h)
{
	int scr_width, scr_height;
	struct { int X; int Y; int Width; int Height; float MinZ; float MaxZ; } vp;

	if(!pCurTarget) {
		scr_width=pHGE->System_GetStateInt(HGE_SCREENWIDTH);
		scr_height=pHGE->System_GetStateInt(HGE_SCREENHEIGHT);
	}
	else {
		scr_width=Texture_GetWidth((HTEXTURE)pCurTarget->pTex);
		scr_height=Texture_GetHeight((HTEXTURE)pCurTarget->pTex);
	}

	if(!w) {
		vp.X=0;
		vp.Y=0;
		vp.Width=scr_width;
		vp.Height=scr_height;
	}
	else
	{
		if(x<0) { w+=x; x=0; }
		if(y<0) { h+=y; y=0; }

		if(x+w > scr_width) w=scr_width-x;
		if(y+h > scr_height) h=scr_height-y;

		vp.X=x;
		vp.Y=y;
		vp.Width=w;
		vp.Height=h;
	}

	vp.MinZ=0.0f;
	vp.MaxZ=1.0f;

	_render_batch();

	pOpenGLDevice->glViewport(vp.X, vp.Y, vp.Width, vp.Height);
	pOpenGLDevice->glDepthRange(vp.MinZ, vp.MaxZ);
	pOpenGLDevice->glMatrixMode(GL_PROJECTION);
	pOpenGLDevice->glLoadIdentity();
	pOpenGLDevice->glOrtho((float)vp.X, (float)(vp.X+vp.Width), -((float)(vp.Y+vp.Height)), -((float)vp.Y), vp.MinZ, vp.MaxZ);
	pOpenGLDevice->glRotatef(0.0f, 0.0f, 0.0f, 1.0f);
}

void CALL HGE_Impl::Gfx_SetTransform(float x, float y, float dx, float dy, float rot, float hscale, float vscale)
{
	_render_batch();

	pOpenGLDevice->glMatrixMode(GL_MODELVIEW);
	if(vscale==0.0f) pOpenGLDevice->glLoadIdentity();
	else
	{
		pOpenGLDevice->glTranslatef(-x, -y, 0.0f);
		//pOpenGLDevice->glScalef(1.0f, -1.0f, 1.0f);
		pOpenGLDevice->glRotatef(-rot, 0.0f, 0.0f, -1.0f);
		pOpenGLDevice->glTranslatef(x+dx, y+dy, 0.0f);
	}
}

bool CALL HGE_Impl::Gfx_BeginScene(HTARGET targ)
{
//	LPDIRECT3DSURFACE8 pSurf=0, pDepth=0;
//	D3DDISPLAYMODE Mode;
	CRenderTargetList *target=(CRenderTargetList *)targ;

	if(VertArray)
	{
		_PostError("Gfx_BeginScene: Scene is already being rendered");
		return false;
	}

	if(target != pCurTarget)
	{
        STUBBED("render target");
#if 0
		if(target)
		{
			target->pTex->GetSurfaceLevel(0, &pSurf);
			pDepth=target->pDepth;
		}
		else
		{
			pSurf=pScreenSurf;
			pDepth=pScreenDepth;
		}
		if(FAILED(pD3DDevice->SetRenderTarget(pSurf, pDepth)))
		{
			if(target) pSurf->Release();
			_PostError("Gfx_BeginScene: Can't set render target");
			return false;
		}
		if(target)
		{
			pSurf->Release();
			if(target->pDepth) pD3DDevice->SetRenderState( D3DRS_ZENABLE, D3DZB_TRUE ); 
			else pD3DDevice->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE ); 
			_SetProjectionMatrix(target->width, target->height);
		}
		else
		{
			if(bZBuffer) pD3DDevice->SetRenderState( D3DRS_ZENABLE, D3DZB_TRUE );
			else pD3DDevice->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE );
			_SetProjectionMatrix(nScreenWidth, nScreenHeight);
		}

		pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
		D3DXMatrixIdentity(&matView);
		pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

		pCurTarget=target;
#endif
	}

	VertArray = pVB;
	return true;
}

void CALL HGE_Impl::Gfx_EndScene()
{
	_render_batch(true);
	if(!pCurTarget) SDL_GL_SwapBuffers();
	const GLenum err = pOpenGLDevice->glGetError();
	if (err != GL_NO_ERROR) printf("GL error! 0x%X\n", (int) err);
	//Gfx_Clear(0xFF | (0xFF<<24) | (random() & 0xFF << 16) | (random() & 0xFF << 8));
	//Gfx_Clear(0xFF000000);
}

void HGE_Impl::_SetTextureFilter()
{
	const GLenum filter = (bTextureFilter) ? GL_LINEAR : GL_NEAREST;
	pOpenGLDevice->glTexParameteri(pOpenGLDevice->TextureTarget, GL_TEXTURE_MIN_FILTER, filter);
	pOpenGLDevice->glTexParameteri(pOpenGLDevice->TextureTarget, GL_TEXTURE_MAG_FILTER, filter);

	// !!! FIXME: this isn't what HGE's Direct3D code does, but the game I'm working with
	// !!! FIXME:  forces clamping outside of HGE, so I just wedged it in here.
	pOpenGLDevice->glTexParameteri(pOpenGLDevice->TextureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP);
	pOpenGLDevice->glTexParameteri(pOpenGLDevice->TextureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP);
	pOpenGLDevice->glTexParameteri(pOpenGLDevice->TextureTarget, GL_TEXTURE_WRAP_R, GL_CLAMP);
}

void CALL HGE_Impl::Gfx_RenderLine(float x1, float y1, float x2, float y2, DWORD color, float z)
{
	if(VertArray)
	{
		if(CurPrimType!=HGEPRIM_LINES || nPrim>=VERTEX_BUFFER_SIZE/HGEPRIM_LINES || CurTexture || CurBlendMode!=BLEND_DEFAULT)
		{
			_render_batch();

			CurPrimType=HGEPRIM_LINES;
			if(CurBlendMode != BLEND_DEFAULT) _SetBlendMode(BLEND_DEFAULT);
			if(CurTexture) { pOpenGLDevice->glBindTexture(pOpenGLDevice->TextureTarget, 0); CurTexture=0; }
		}

		int i=nPrim*HGEPRIM_LINES;
		VertArray[i].x = x1; VertArray[i+1].x = x2;
		VertArray[i].y = y1; VertArray[i+1].y = y2;
		VertArray[i].z     = VertArray[i+1].z = z;
		VertArray[i].col   = VertArray[i+1].col = color;
		VertArray[i].tx    = VertArray[i+1].tx =
		VertArray[i].ty    = VertArray[i+1].ty = 0.0f;

		nPrim++;
	}
}
    
void CALL HGE_Impl::Gfx_RenderTriple(const hgeTriple *triple)
{
	if(VertArray)
	{
		if(CurPrimType!=HGEPRIM_TRIPLES || nPrim>=VERTEX_BUFFER_SIZE/HGEPRIM_TRIPLES || CurTexture!=triple->tex || CurBlendMode!=triple->blend)
		{
			_render_batch();

			CurPrimType=HGEPRIM_TRIPLES;
			if(CurBlendMode != triple->blend) _SetBlendMode(triple->blend);
			if(triple->tex != CurTexture) {
				pOpenGLDevice->glBindTexture(pOpenGLDevice->TextureTarget, triple->tex ? ((gltexture*)triple->tex)->name : 0);
				CurTexture = triple->tex;
				_SetTextureFilter();
			}
		}

		memcpy(&VertArray[nPrim*HGEPRIM_TRIPLES], triple->v, sizeof(hgeVertex)*HGEPRIM_TRIPLES);
		nPrim++;
	}
}

void CALL HGE_Impl::Gfx_RenderQuad(const hgeQuad *quad)
{
	if(VertArray)
	{
		if(CurPrimType!=HGEPRIM_QUADS || nPrim>=VERTEX_BUFFER_SIZE/HGEPRIM_QUADS || CurTexture!=quad->tex || CurBlendMode!=quad->blend)
		{
			_render_batch();

			CurPrimType=HGEPRIM_QUADS;
			if(CurBlendMode != quad->blend) _SetBlendMode(quad->blend);
			if(quad->tex != CurTexture)
			{
				pOpenGLDevice->glBindTexture(pOpenGLDevice->TextureTarget, quad->tex ? ((gltexture*)quad->tex)->name : 0);
				CurTexture = quad->tex;
				_SetTextureFilter();
			}
		}

		memcpy(&VertArray[nPrim*HGEPRIM_QUADS], quad->v, sizeof(hgeVertex)*HGEPRIM_QUADS);
		nPrim++;
	}
}

hgeVertex* CALL HGE_Impl::Gfx_StartBatch(int prim_type, HTEXTURE tex, int blend, int *max_prim)
{
	if(VertArray)
	{
		_render_batch();

		CurPrimType=prim_type;
		if(CurBlendMode != blend) _SetBlendMode(blend);
		if(tex != CurTexture)
		{
			pOpenGLDevice->glBindTexture(pOpenGLDevice->TextureTarget, tex ? ((gltexture*)tex)->name : 0);
			CurTexture = tex;
			_SetTextureFilter();
		}

		*max_prim=VERTEX_BUFFER_SIZE / prim_type;
		return VertArray;
	}
	else return 0;
}

void CALL HGE_Impl::Gfx_FinishBatch(int nprim)
{
	nPrim=nprim;
}

HTARGET CALL HGE_Impl::Target_Create(int width, int height, bool zbuffer)
{
STUBBED("render target");
return 0;
#if 0
	CRenderTargetList *pTarget;
	D3DSURFACE_DESC TDesc;

	pTarget = new CRenderTargetList;
	pTarget->pTex=0;
	pTarget->pDepth=0;

	if(FAILED(D3DXCreateTexture(pD3DDevice, width, height, 1, D3DUSAGE_RENDERTARGET,
						d3dpp->BackBufferFormat, D3DPOOL_DEFAULT, &pTarget->pTex)))
	{
		_PostError("Can't create render target texture");
		delete pTarget;
		return 0;
	}

	pTarget->pTex->GetLevelDesc(0, &TDesc);
	pTarget->width=TDesc.Width;
	pTarget->height=TDesc.Height;

	if(zbuffer)
	{
		if(FAILED(pD3DDevice->CreateDepthStencilSurface(pTarget->width, pTarget->height,
						D3DFMT_D16, D3DMULTISAMPLE_NONE, &pTarget->pDepth)))
		{   
			pTarget->pTex->Release();
			_PostError("Can't create render target depth buffer");
			delete pTarget;
			return 0;
		}
	}

	pTarget->next=pTargets;
	pTargets=pTarget;

	return (HTARGET)pTarget;
#endif
}

void CALL HGE_Impl::Target_Free(HTARGET target)
{
STUBBED("render target");
return;
#if 0
	CRenderTargetList *pTarget=pTargets, *pPrevTarget=NULL;

	while(pTarget)
	{
		if((CRenderTargetList *)target == pTarget)
		{
			if(pPrevTarget)
				pPrevTarget->next = pTarget->next;
			else
				pTargets = pTarget->next;

			if(pTarget->pTex) pTarget->pTex->Release();
			if(pTarget->pDepth) pTarget->pDepth->Release();

			delete pTarget;
			return;
		}

		pPrevTarget = pTarget;
		pTarget = pTarget->next;
	}
#endif
}

HTEXTURE CALL HGE_Impl::Target_GetTexture(HTARGET target)
{
	CRenderTargetList *targ=(CRenderTargetList *)target;
	if(target) return (HTEXTURE)targ->pTex;
	else return 0;
}

HTEXTURE HGE_Impl::_BuildTexture(int width, int height, DWORD *pixels)
{
	gltexture *retval = new gltexture;
	memset(retval, '\0', sizeof (gltexture));

	GLuint tex = 0;
	pOpenGLDevice->glGenTextures(1, &tex);

	retval->name = tex;
	retval->width = width;
	retval->height = height;
	retval->pixels = pixels;

	pOpenGLDevice->glBindTexture(pOpenGLDevice->TextureTarget, tex);
	if (pOpenGLDevice->TextureTarget != GL_TEXTURE_RECTANGLE_ARB)
	{
		pOpenGLDevice->glTexParameteri(pOpenGLDevice->TextureTarget, GL_TEXTURE_BASE_LEVEL, 0);
		pOpenGLDevice->glTexParameteri(pOpenGLDevice->TextureTarget, GL_TEXTURE_MAX_LEVEL, 0);
	}
	_SetTextureFilter();
	pOpenGLDevice->glTexImage2D(pOpenGLDevice->TextureTarget, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	pOpenGLDevice->glBindTexture(pOpenGLDevice->TextureTarget, CurTexture ? (((gltexture *) CurTexture)->name) : 0);

	return (HTEXTURE)retval;
}

HTEXTURE CALL HGE_Impl::Texture_Create(int width, int height)
{
	DWORD *pixels = new DWORD[width * height];
	memset(pixels, '\0', sizeof (DWORD) * width * height);
	return _BuildTexture(width, height, pixels);
}

HTEXTURE CALL HGE_Impl::Texture_Load(const char *filename, DWORD size, bool bMipmap)
{
	HTEXTURE retval = 0;
	int width = 0;
	int height = 0;

#if SUPPORT_CXIMAGE
	void *data;
	DWORD _size;
	CTextureList *texItem;

	if(size) { data=(void *)filename; _size=size; }
	else
	{
		data=pHGE->Resource_Load(filename, &_size);
		if(!data) return NULL;
	}

	CxImage img;
	img.Decode((BYTE*)data, _size, CXIMAGE_FORMAT_UNKNOWN);
	if (img.IsValid())
	{
		width = img.GetWidth();
		height = img.GetHeight();
		DWORD *pixels = new DWORD[width * height];
		BYTE *wptr = (BYTE *) pixels;
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				const RGBQUAD rgb = img.GetPixelColor(x, y, true);
				*(wptr++) = rgb.rgbRed;
				*(wptr++) = rgb.rgbGreen;
				*(wptr++) = rgb.rgbBlue;
				*(wptr++) = rgb.rgbReserved;  // alpha.
			}
		}
		retval = _BuildTexture(width, height, pixels);
	}
#endif

	if(!size) Resource_Free(data);

	if (retval == 0)
	{
		STUBBED("texture load fail!");
		_PostError("Can't create texture");
	}
	else
	{
		texItem=new CTextureList;
		texItem->tex=retval;
		texItem->width=width;
		texItem->height=height;
		texItem->next=textures;
		textures=texItem;
	}

	return retval;
}

void CALL HGE_Impl::Texture_Free(HTEXTURE tex)
{
	CTextureList *texItem=textures, *texPrev=0;

	while(texItem)
	{
		if(texItem->tex==tex)
		{
			if(texPrev) texPrev->next=texItem->next;
			else textures=texItem->next;
			delete texItem;
			break;
		}
		texPrev=texItem;
		texItem=texItem->next;
	}
	if(tex)
	{
		gltexture *pTex = (gltexture *) tex;
		delete[] pTex->pixels;
		delete[] pTex->lock_pixels;
		pOpenGLDevice->glDeleteTextures(1, &pTex->name);
		delete pTex;
	}
}

int CALL HGE_Impl::Texture_GetWidth(HTEXTURE tex, bool bOriginal)
{
	CTextureList *texItem=textures;

	if(bOriginal)
	{
		while(texItem)
		{
			if(texItem->tex==tex) return texItem->width;
			texItem=texItem->next;
		}
	}
	else
	{
		return ((gltexture*)tex)->width;
	}
	return 0;
}


int CALL HGE_Impl::Texture_GetHeight(HTEXTURE tex, bool bOriginal)
{
	CTextureList *texItem=textures;

	if(bOriginal)
	{
		while(texItem)
		{
			if(texItem->tex==tex) return texItem->height;
			texItem=texItem->next;
		}
	}
	else
	{
		return ((gltexture*)tex)->height;
	}
	return 0;
}


DWORD * CALL HGE_Impl::Texture_Lock(HTEXTURE tex, bool bReadOnly, int left, int top, int width, int height)
{
	gltexture *pTex=(gltexture*)tex;

	if (pTex->lock_pixels)
	{
		assert(false && "multiple lock of texture...");
		return 0;
	}

	// !!! FIXME: is this right?
	if((width == 0) && (height == 0))
	{
		width = pTex->width;
		height = pTex->height;
	}

	// !!! FIXME: do something with this?
	assert(width > 0);
	assert(width <= pTex->width);
	assert(height > 0);
	assert(height <= pTex->height);
	assert(left >= 0);
	assert(left <= width);
	assert(top >= 0);
	assert(top <= height);

	pTex->lock_readonly = bReadOnly;
	pTex->lock_x = left;
	pTex->lock_y = top;
	pTex->lock_width = width;
	pTex->lock_height = height;

	pTex->lock_pixels = new DWORD[width * height];
	DWORD *src = pTex->pixels + left;
	DWORD *dst = pTex->lock_pixels;
	for (int i = 0; i < height; i++)
	{
		memcpy(dst, src, width * sizeof (DWORD));
		dst += width;
		src += pTex->width;
	}

	return pTex->lock_pixels;
}


void CALL HGE_Impl::Texture_Unlock(HTEXTURE tex)
{
	gltexture *pTex=(gltexture*)tex;

	if (pTex->lock_pixels == NULL) return;  // not locked.

	if (!pTex->lock_readonly)  // have to reupload to the hardware.
	{
		pOpenGLDevice->glBindTexture(pOpenGLDevice->TextureTarget, pTex->name);
		pOpenGLDevice->glTexSubImage2D(pOpenGLDevice->TextureTarget, 0, pTex->lock_x, pTex->lock_y,
		                               pTex->lock_width, pTex->lock_height, GL_RGBA,
		                               GL_UNSIGNED_BYTE, pTex->lock_pixels);
		pOpenGLDevice->glBindTexture(pOpenGLDevice->TextureTarget, CurTexture ? (((gltexture *) CurTexture)->name) : 0);
	}

	delete[] pTex->lock_pixels;
	pTex->lock_pixels = NULL;
	pTex->lock_readonly = false;
	pTex->lock_x = -1;
	pTex->lock_y = -1;
	pTex->lock_width = -1;
	pTex->lock_height = -1;
}

//////// Implementation ////////

#define DEBUG_VERTICES 0
#if DEBUG_VERTICES
static inline void print_vertex(const hgeVertex *v)
{
    printf("  (%f, %f, %f), 0x%X, (%f, %f)\n", v->x, v->y, v->z, v->col, v->tx, v->ty);
}
#endif

void HGE_Impl::_render_batch(bool bEndScene)
{
	if(VertArray)
	{
		if(nPrim)
		{
			// !!! FIXME: just correct the transformation matrix instead (except the texture rectangle stuff?)
			const float h = (float) (((SDL_Surface *) this->hwnd)->h);

			// texture rectangles range from 0 to size, not 0 to 1.  :/
			float texwmult = 1.0f;
			float texhmult = 1.0f;
			if ((CurTexture) && (pOpenGLDevice->TextureTarget == GL_TEXTURE_RECTANGLE_ARB))
			{
				texwmult = ((gltexture *)CurTexture)->width;
				texhmult = ((gltexture *)CurTexture)->height;
			}

			for (int i = 0; i < nPrim*CurPrimType; i++)
			{
				VertArray[i].y = h - VertArray[i].y;
				VertArray[i].z *= -1.0f;
				VertArray[i].tx = VertArray[i].tx * texwmult;
				VertArray[i].ty = (1.0f - VertArray[i].ty) * texhmult;
			}

			switch(CurPrimType)
			{
				case HGEPRIM_QUADS:
					pOpenGLDevice->glDrawElements(GL_TRIANGLES, nPrim * 6, GL_UNSIGNED_SHORT, pIB);
					#if DEBUG_VERTICES
					for (int i = 0; i < nPrim*6; i+=3)
					{
						printf("QUAD'S TRIANGLE:\n");
						print_vertex(&pVB[pIB[i+0]]);
						print_vertex(&pVB[pIB[i+1]]);
						print_vertex(&pVB[pIB[i+2]]);
					}
					printf("DONE.\n");
					#endif
					break;

				case HGEPRIM_TRIPLES:
					pOpenGLDevice->glDrawArrays(GL_TRIANGLES, 0, nPrim * 3);
					break;

				case HGEPRIM_LINES:
					pOpenGLDevice->glDrawArrays(GL_LINES, 0, nPrim * 2);
					break;
			}

			nPrim=0;
		}
		if(bEndScene) VertArray = 0;
		else VertArray = pVB;
	}
}

void HGE_Impl::_SetBlendMode(int blend)
{
	if((blend & BLEND_ALPHABLEND) != (CurBlendMode & BLEND_ALPHABLEND))
	{
		if(blend & BLEND_ALPHABLEND) pOpenGLDevice->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		else pOpenGLDevice->glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	}

	if((blend & BLEND_ZWRITE) != (CurBlendMode & BLEND_ZWRITE))
	{
		if(blend & BLEND_ZWRITE) pOpenGLDevice->glDepthMask(GL_TRUE);
		else pOpenGLDevice->glDepthMask(GL_FALSE);
	}
	
	if((blend & BLEND_COLORADD) != (CurBlendMode & BLEND_COLORADD))
	{
		if(blend & BLEND_COLORADD) pOpenGLDevice->glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
		else pOpenGLDevice->glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}

	CurBlendMode = blend;
}

void HGE_Impl::_SetProjectionMatrix(int width, int height)
{
	pOpenGLDevice->glMatrixMode(GL_PROJECTION);
	pOpenGLDevice->glLoadIdentity();
	pOpenGLDevice->glOrtho(0, (float)width, 0, (float)height, 0.0f, 1.0f);
}

void HGE_Impl::_UnloadOpenGLEntryPoints()
{
    #define GL_PROC(fn,call,ret,params) pOpenGLDevice->fn = NULL;
	#include "hge_glfuncs.h"
	#undef GL_PROC
}

bool HGE_Impl::_LoadOpenGLEntryPoints()
{
	bool ok = true;

    #define GL_PROC(fn,call,ret,params) \
        if (ok) { \
            if ((pOpenGLDevice->fn = (_HGE_PFN_##fn) SDL_GL_GetProcAddress(#fn)) == NULL) { \
                 _PostError("Failed to load OpenGL entry point '" #fn "'"); \
                 ok = false; \
            } \
        } else {}
	#include "hge_glfuncs.h"
	#undef GL_PROC

	if (!ok)
		_UnloadOpenGLEntryPoints();
	return ok;
}

static bool _HaveOpenGLExtension(const char *extlist, const char *ext)
{
    const char *ptr = strstr(extlist, ext);
    if (ptr == NULL)
        return false;

    const char endchar = ptr[strlen(ext)];
    if ((endchar == '\0') || (endchar == ' '))
        return true;  // extension is in the list.

    return false;  // just not supported, fail.
}

bool HGE_Impl::_GfxInit()
{
// Init OpenGL ... SDL should have created a context at this point.
	assert(pOpenGLDevice == NULL);
	pOpenGLDevice = new COpenGLDevice;
	if (!_LoadOpenGLEntryPoints())
		return false;   // already called _PostError().

	System_Log("GL_RENDERER: %s", (const char *) pOpenGLDevice->glGetString(GL_RENDERER));
	System_Log("GL_VENDOR: %s", (const char *) pOpenGLDevice->glGetString(GL_VENDOR));
	System_Log("GL_VERSION: %s", (const char *) pOpenGLDevice->glGetString(GL_VERSION));

	const char *verstr = (const char *) pOpenGLDevice->glGetString(GL_VERSION);
	System_Log("GL_VERSION: %s", verstr);
	int maj = 0;
	int min = 0;
	sscanf(verstr, "%d.%d", &maj, &min);

	if ( (maj < 1) || ((maj == 1) && (min < 1)) )
	{
		_PostError("OpenGL implementation must be at least version 1.1");
		return false;
	}

	pOpenGLDevice->have_GL_ARB_texture_rectangle = false;
	pOpenGLDevice->have_GL_ARB_texture_non_power_of_two = false;

	const char *exts = (const char *) pOpenGLDevice->glGetString(GL_EXTENSIONS);
	if (_HaveOpenGLExtension(exts, "GL_ARB_texture_rectangle"))
		pOpenGLDevice->have_GL_ARB_texture_rectangle = true;
	else if (_HaveOpenGLExtension(exts, "GL_EXT_texture_rectangle"))
		pOpenGLDevice->have_GL_ARB_texture_rectangle = true;
	else if (_HaveOpenGLExtension(exts, "GL_NV_texture_rectangle"))
		pOpenGLDevice->have_GL_ARB_texture_rectangle = true;
	else if (_HaveOpenGLExtension(exts, "GL_NV_texture_rectangle"))
		pOpenGLDevice->have_GL_ARB_texture_rectangle = true;

	if (maj >= 2)
		pOpenGLDevice->have_GL_ARB_texture_non_power_of_two = true;
	else if (_HaveOpenGLExtension(exts, "GL_ARB_texture_non_power_of_two"))
		pOpenGLDevice->have_GL_ARB_texture_non_power_of_two = true;

	if (pOpenGLDevice->have_GL_ARB_texture_rectangle)
	{
		System_Log("OpenGL: Using GL_ARB_texture_rectangle");
		pOpenGLDevice->TextureTarget = GL_TEXTURE_RECTANGLE_ARB;
	}
	else if (pOpenGLDevice->have_GL_ARB_texture_non_power_of_two)
	{
		System_Log("OpenGL: Using GL_ARB_texture_non_power_of_two");
		pOpenGLDevice->TextureTarget = GL_TEXTURE_2D;
	}
	else
	{
		_PostError("No non-power-of-two texture support in this OpenGL.");
		pOpenGLDevice->TextureTarget = GL_NONE;
		return false;
	}

	nScreenBPP=SDL_GetVideoSurface()->format->BitsPerPixel;

	_AdjustWindow();

	System_Log("Mode: %d x %d\n",nScreenWidth,nScreenHeight);

// Create vertex batch buffer

	VertArray=0;
	textures=0;

// Init all stuff that can be lost

	_SetProjectionMatrix(nScreenWidth, nScreenHeight);
	pOpenGLDevice->glMatrixMode(GL_MODELVIEW);
	pOpenGLDevice->glLoadIdentity();

	if(!_init_lost()) return false;

	// make sure the framebuffers are cleared and force to screen
	Gfx_Clear(0);
	SDL_GL_SwapBuffers();
	Gfx_Clear(0);
	SDL_GL_SwapBuffers();

	return true;
}

void HGE_Impl::_AdjustWindow()
{
	// no-op.
}

void HGE_Impl::_Resize(int width, int height)
{
	if(hwndParent)
	{
		//if(procFocusLostFunc) procFocusLostFunc();
		STUBBED("resize");
		#if 0
		d3dppW.BackBufferWidth=width;
		d3dppW.BackBufferHeight=height;
		nScreenWidth=width;
		nScreenHeight=height;

		_SetProjectionMatrix(nScreenWidth, nScreenHeight);
		_GfxRestore();
		#endif

		//if(procFocusGainFunc) procFocusGainFunc();
	}
}

void HGE_Impl::_GfxDone()
{
	CRenderTargetList *target=pTargets, *next_target;
	
	while(textures)	Texture_Free(textures->tex);

	STUBBED("cleanup stuff");
	#if 0
	if(pScreenSurf) { pScreenSurf->Release(); pScreenSurf=0; }
	if(pScreenDepth) { pScreenDepth->Release(); pScreenDepth=0; }

	while(target)
	{
		if(target->pTex) target->pTex->Release();
		if(target->pDepth) target->pDepth->Release();
		next_target=target->next;
		delete target;
		target=next_target;
	}
	pTargets=0;
#endif

	VertArray = 0;
	delete[] pVB;
	pVB=0;
	delete[] pIB;
	pIB=0;

	if(pOpenGLDevice)
	{
		delete pOpenGLDevice;
		pOpenGLDevice=0;
	}
}


bool HGE_Impl::_GfxRestore()
{
	CRenderTargetList *target=pTargets;

	//if(!pD3DDevice) return false;
	//if(pD3DDevice->TestCooperativeLevel() == D3DERR_DEVICELOST) return;

STUBBED("render target stuff");
#if 0
	if(pScreenSurf) pScreenSurf->Release();
	if(pScreenDepth) pScreenDepth->Release();

	while(target)
	{
		if(target->pTex) target->pTex->Release();
		if(target->pDepth) target->pDepth->Release();
		target=target->next;
	}
#endif

    delete[] pVB;
	pVB=0;

	delete[] pIB;
	pIB=0;

	_UnloadOpenGLEntryPoints();
	if (!_LoadOpenGLEntryPoints())
		return false;

	if(!_init_lost()) return false;

	if(procGfxRestoreFunc) return procGfxRestoreFunc();

	return true;
}


bool HGE_Impl::_init_lost()
{
STUBBED("(re)create render targets");
#if 0
	CRenderTargetList *target=pTargets;

// Store render target

	pScreenSurf=0;
	pScreenDepth=0;

	pD3DDevice->GetRenderTarget(&pScreenSurf);
	pD3DDevice->GetDepthStencilSurface(&pScreenDepth);
	
	while(target)
	{
		if(target->pTex)
			D3DXCreateTexture(pD3DDevice, target->width, target->height, 1, D3DUSAGE_RENDERTARGET,
							  d3dpp->BackBufferFormat, D3DPOOL_DEFAULT, &target->pTex);
		if(target->pDepth)
			pD3DDevice->CreateDepthStencilSurface(target->width, target->height,
												  D3DFMT_D16, D3DMULTISAMPLE_NONE, &target->pDepth);
		target=target->next;
	}
#endif

// Create Vertex buffer
	// We just use a client-side array, since you can reasonably count on support
	//  existing in any GL, and it basically offers the same functionality that
	//  HGE uses in Direct3D: it locks the vertex buffer, unlocks in time to
	//  draw something, then relocks again immediately...more or less, that method
	//  offers the same performance metrics as a client-side array.
	pVB = new hgeVertex[VERTEX_BUFFER_SIZE];

	pOpenGLDevice->glVertexPointer(3, GL_FLOAT, sizeof (hgeVertex), &pVB[0].x);
	pOpenGLDevice->glColorPointer(4, GL_UNSIGNED_BYTE, sizeof (hgeVertex), &pVB[0].col);
	pOpenGLDevice->glTexCoordPointer(2, GL_FLOAT, sizeof (hgeVertex), &pVB[0].tx);
	pOpenGLDevice->glEnableClientState(GL_VERTEX_ARRAY);
	pOpenGLDevice->glEnableClientState(GL_COLOR_ARRAY);
	pOpenGLDevice->glEnableClientState(GL_TEXTURE_COORD_ARRAY);

// Create and setup Index buffer
	pIB = new GLushort[VERTEX_BUFFER_SIZE*6/4];
	GLushort *pIndices = pIB;
	int n = 0;
	for(int i=0; i<VERTEX_BUFFER_SIZE/4; i++) {
		*pIndices++=n;
		*pIndices++=n+1;
		*pIndices++=n+2;
		*pIndices++=n+2;
		*pIndices++=n+3;
		*pIndices++=n;
		n+=4;
	}

// Set common render states

	pOpenGLDevice->glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	pOpenGLDevice->glPixelStorei(GL_PACK_ALIGNMENT, 1);

	//pD3DDevice->SetRenderState( D3DRS_LASTPIXEL, FALSE );
	pOpenGLDevice->glDisable(GL_TEXTURE_2D);
	if (pOpenGLDevice->have_GL_ARB_texture_rectangle)
		pOpenGLDevice->glDisable(GL_TEXTURE_RECTANGLE_ARB);
	pOpenGLDevice->glEnable(pOpenGLDevice->TextureTarget);
	pOpenGLDevice->glDisable(GL_CULL_FACE);
	pOpenGLDevice->glDisable(GL_LIGHTING);
	pOpenGLDevice->glDisable(GL_DEPTH_TEST);

	pOpenGLDevice->glEnable(GL_BLEND);
	pOpenGLDevice->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	pOpenGLDevice->glEnable(GL_ALPHA_TEST);
	pOpenGLDevice->glAlphaFunc(GL_GEQUAL, 1.0f / 255.0f);

	pOpenGLDevice->glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	nPrim=0;
	CurPrimType=HGEPRIM_QUADS;
	CurBlendMode = BLEND_DEFAULT;
	CurTexture = NULL;

	// currently done elsewhere.
	//pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
	//pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);

	return true;
}

#endif  // PLATFORM_UNIX

