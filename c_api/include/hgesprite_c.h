#ifndef HGE_SPRITE_C_H
#define HGE_SPRITE_C_H

#include "unix_compat.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct HGE_Rect_s HGE_Rect_t;
typedef struct HGE_Sprite_s HGE_Sprite_t;

HGE_Sprite_t *HGE_Sprite_New(HTEXTURE tex, float x, float y, float w, float h);
HGE_Sprite_t *HGE_Sprite_Copy(const HGE_Sprite_t *spr);
void HGE_Sprite_Free(HGE_Sprite_t *sprite);

void HGE_Sprite_Render(HGE_Sprite_t *sprite, float x, float y);
/// float hscale=1.0f, float vscale=0.0f
void HGE_Sprite_RenderEx(HGE_Sprite_t *sprite, float x, float y, float rot, float hscale, float vscale);
void HGE_Sprite_RenderStretch(HGE_Sprite_t *sprite, float x1, float y1, float x2, float y2);
void HGE_Sprite_Render4V(HGE_Sprite_t *sprite, float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3);

void HGE_Sprite_SetTexture(HGE_Sprite_t *sprite, HTEXTURE tex);
void HGE_Sprite_SetTextureRect(HGE_Sprite_t *sprite, float x, float y, float w, float h, BOOL adjSize);
/// int i=-1
void HGE_Sprite_SetColor(HGE_Sprite_t *sprite, DWORD col, int i);
void HGE_Sprite_SetZ(HGE_Sprite_t *sprite, float z, int i);
void HGE_Sprite_SetBlendMode(HGE_Sprite_t *sprite, int blend);
void HGE_Sprite_SetHotSpot(HGE_Sprite_t *sprite, float x, float y);
void HGE_Sprite_SetFlip(HGE_Sprite_t *sprite, BOOL bX, BOOL bY, BOOL bHotSpot);

HTEXTURE HGE_Sprite_GetTexture(HGE_Sprite_t *sprite);
void HGE_Sprite_GetTextureRect(HGE_Sprite_t *sprite, float *x, float *y, float *w, float *h);
DWORD HGE_Sprite_GetColor(HGE_Sprite_t *sprite, int i);
float HGE_Sprite_GetZ(HGE_Sprite_t *sprite, int i);
int HGE_Sprite_GetBlendMode(HGE_Sprite_t *sprite);
void HGE_Sprite_GetHotSpot(HGE_Sprite_t *sprite, float *x, float *y);
void HGE_Sprite_GetFlip(HGE_Sprite_t *sprite, BOOL *bX, BOOL *bY);

float HGE_Sprite_GetWidth(HGE_Sprite_t *sprite);
float HGE_Sprite_GetHeight(HGE_Sprite_t *sprite);
HGE_Rect_t* HGE_Sprite_GetBoundingBox(HGE_Sprite_t *sprite, float x, float y, HGE_Rect_t *rect);
HGE_Rect_t* HGE_Sprite_GetBoundingBoxEx(HGE_Sprite_t *sprite, float x, float y, float rot, float hscale, float vscale, HGE_Rect_t *rect);

#ifdef __cplusplus
}
#endif

#endif
