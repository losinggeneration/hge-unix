--
-- Haaf's Game Engine 1.7
-- Copyright (C) 2003-2007, Relish Games
-- hge.relishgames.com
--
-- hgeSprite helper class header
--

bindhgeSprite = {
	classes = {
		{
		name = 'hge.Sprite',
		className = 'hgeSprite',
		ctors = {
			'(HTEXTURE tex, float x, float y, float w, float h)',
			'(const hgeSprite &spr)',
		},
		memberFunctions = {
			{ 'void Render(float x, float y);' },
			{ 'void RenderEx(float x, float y, float rot, float hscale, float vscale);' },
			{ 'void RenderStretch(float x1, float y1, float x2, float y2);' },
			{ 'void Render4V(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3);' },

			{ 'void SetTexture(HTEXTURE tex);' },
			{ 'void SetTextureRect(float x, float y, float w, float h, bool adjSize);' },
			{ 'void SetColor(DWORD col, int i);' },
			{ 'void SetZ(float z, int i);' },
			{ 'void SetBlendMode(int blend);' },
			{ 'void SetHotSpot(float x, float y);' },
			{ 'void SetFlip(bool bX, bool bY, bool bHotSpot);' },

			{ 'HTEXTURE GetTexture() const;' },
			{ 'DWORD GetColor(int i) const;' },
			{ 'float GetZ(int i) const;' },
			{ 'int GetBlendMode() const;' },
-- 			{ 'void GetTextureRect(float *x, float *y, float *w, float *h) const;' },
-- 			{ 'void GetHotSpot(float *x, float *y) const;' },
-- 			{ 'void GetFlip(bool *bX, bool *bY) const;' },

			{ 'float GetWidth() const;' },
			{ 'float GetHeight() const;' },
			{ 'hgeRect* GetBoundingBox(float x, float y, hgeRect *rect) const;' },
			{ 'hgeRect* GetBoundingBoxEx(float x, float y, float rot, float hscale, float vscale, hgeRect *rect) const;' },
		},
		},
	},
	modules = {
	},
}

--[[

#include "hgerect.h"

/*
** HGE Sprite class
*/
class hgeSprite
;
public:
 hgeSprite(HTEXTURE tex, float x, float y, float w, float h);
 hgeSprite(const hgeSprite &spr);

 void Render(float x, float y);
 void RenderEx(float x, float y, float rot, float hscale=1.0f, float vscale);
 void RenderStretch(float x1, float y1, float x2, float y2);
 void Render4V(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3);

 void SetTexture(HTEXTURE tex);
 void SetTextureRect(float x, float y, float w, float h, bool adjSize);
 void SetColor(DWORD col, int i);
 void SetZ(float z, int i);
 void SetBlendMode(int blend);
 void SetHotSpot(float x, float y);
 void SetFlip(bool bX, bool bY, bool bHotSpot = false);

 HTEXTURE GetTexture() const;
 void GetTextureRect(float *x, float *y, float *w, float *h) const;
 DWORD GetColor(int i) const;
 float GetZ(int i) const;
 int GetBlendMode() const;
 void GetHotSpot(float *x, float *y) const;
 void GetFlip(bool *bX, bool *bY) const;

 float GetWidth() const;
 float GetHeight() const;
 hgeRect* GetBoundingBox(float x, float y, hgeRect *rect) const;
 hgeRect* GetBoundingBoxEx(float x, float y, float rot, float hscale, float vscale, hgeRect *rect) const;

protected:
 hgeSprite();
 static HGE *hge;

 hgeQuad quad;
 float tx, ty, width, height;
 float tex_width, tex_height;
 float hotX, hotY;
 bool bXFlip, bYFlip, bHSFlip;
};

--]]