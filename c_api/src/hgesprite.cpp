#include "hgesprite.h"
#include "hgesprite_c.h"
#include "hgesprite_impl.h"
#include "hgerect_c.h"
#include "hgerect_impl.h"

#include <malloc.h>

extern "C" {

HGE_Sprite_t *HGE_Sprite_Empty() {
	return (HGE_Sprite_t *)malloc(sizeof(HGE_Sprite_t));
}

HGE_Sprite_t *HGE_Sprite_New(HTEXTURE tex, float x, float y, float w, float h) {
	HGE_Sprite_t *s = HGE_Sprite_Empty();

	s->s = new hgeSprite(tex, x, y, w, h);

	return s;
}

HGE_Sprite_t *HGE_Sprite_Copy(const HGE_Sprite_t *spr) {
	HGE_Sprite_t *s = HGE_Sprite_Empty();

	s->s = new hgeSprite(*spr->s);

	return s;
}

void HGE_Sprite_Free(HGE_Sprite_t *sprite) {
	delete sprite->s;
	free(sprite);
}

void HGE_Sprite_Render(HGE_Sprite_t *sprite, float x, float y) {
	sprite->s->Render(x, y);
}

void HGE_Sprite_RenderEx(HGE_Sprite_t *sprite, float x, float y, float rot, float hscale, float vscale) {
	sprite->s->RenderEx(x, y, rot, hscale, vscale);
}

void HGE_Sprite_RenderStretch(HGE_Sprite_t *sprite, float x1, float y1, float x2, float y2) {
	sprite->s->RenderStretch(x1, y1, x2, y2);
}

void HGE_Sprite_Render4V(HGE_Sprite_t *sprite, float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3) {
	sprite->s->Render4V(x0, y0, x1, y1, x2, y2, x3, y3);
}

void HGE_Sprite_SetTexture(HGE_Sprite_t *sprite, HTEXTURE tex) {
	sprite->s->SetTexture(tex);
}

void HGE_Sprite_SetTextureRect(HGE_Sprite_t *sprite, float x, float y, float w, float h, BOOL adjSize) {
	sprite->s->SetTextureRect(x, y, w, h, adjSize);
}

void HGE_Sprite_SetColor(HGE_Sprite_t *sprite, DWORD col, int i) {
	sprite->s->SetColor(col, i);
}

void HGE_Sprite_SetZ(HGE_Sprite_t *sprite, float z, int i) {
	sprite->s->SetZ(z, i);
}

void HGE_Sprite_SetBlendMode(HGE_Sprite_t *sprite, int blend) {
	sprite->s->SetBlendMode(blend);
}

void HGE_Sprite_SetHotSpot(HGE_Sprite_t *sprite, float x, float y) {
	sprite->s->SetHotSpot(x, y);
}

void HGE_Sprite_SetFlip(HGE_Sprite_t *sprite, BOOL bX, BOOL bY, BOOL bHotSpot) {
	sprite->s->SetFlip(bX, bY, bHotSpot);
}

HTEXTURE HGE_Sprite_GetTexture(HGE_Sprite_t *sprite) {
	return sprite->s->GetTexture();
}

void HGE_Sprite_GetTextureRect(HGE_Sprite_t *sprite, float *x, float *y, float *w, float *h) {
	sprite->s->GetTextureRect(x, y, w, h);
}

DWORD HGE_Sprite_GetColor(HGE_Sprite_t *sprite, int i) {
	return sprite->s->GetColor(i);
}

float HGE_Sprite_GetZ(HGE_Sprite_t *sprite, int i) {
	return sprite->s->GetZ(i);
}

int HGE_Sprite_GetBlendMode(HGE_Sprite_t *sprite) {
	return sprite->s->GetBlendMode();
}

void HGE_Sprite_GetHotSpot(HGE_Sprite_t *sprite, float *x, float *y) {
	sprite->s->GetHotSpot(x, y);
}

void HGE_Sprite_GetFlip(HGE_Sprite_t *sprite, BOOL *bX, BOOL *bY) {
	sprite->s->GetFlip(((bool *)bX), ((bool *)bY));
}

float HGE_Sprite_GetWidth(HGE_Sprite_t *sprite) {
	return sprite->s->GetWidth();
}

float HGE_Sprite_GetHeight(HGE_Sprite_t *sprite) {
	return sprite->s->GetHeight();
}

HGE_Rect_t* HGE_Sprite_GetBoundingBox(HGE_Sprite_t *sprite, float x, float y, HGE_Rect_t *rect) {
	HGE_Rect_t *r = HGE_Rect_NewEmpty();

	r->r = sprite->s->GetBoundingBox(x, y, rect->r);

	return r;
}
HGE_Rect_t* HGE_Sprite_GetBoundingBoxEx(HGE_Sprite_t *sprite, float x, float y, float rot, float hscale, float vscale, HGE_Rect_t *rect) {
	HGE_Rect_t *r = HGE_Rect_NewEmpty();

	r->r = sprite->s->GetBoundingBoxEx(x, y, rot, hscale, vscale, rect->r);

	return r;
}

}
