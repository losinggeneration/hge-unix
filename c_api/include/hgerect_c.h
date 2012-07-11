#ifndef HGE_RECT_C_H
#define HGE_RECT_C_H

#include "unix_compat.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct HGE_Rect_s HGE_Rect_t;

HGE_Rect_t *HGE_Rect_NewEmpty();
HGE_Rect_t *HGE_Rect_New(float x1, float y1, float x2, float y2);
void HGE_Rect_Free(HGE_Rect_t *rect);

void HGE_Rect_SetX1(HGE_Rect_t *rect, float x1);
float HGE_Rect_GetX1(HGE_Rect_t *rect);
void HGE_Rect_SetX2(HGE_Rect_t *rect, float x2);
float HGE_Rect_GetX2(HGE_Rect_t *rect);
void HGE_Rect_SetY1(HGE_Rect_t *rect, float y1);
float HGE_Rect_GetY1(HGE_Rect_t *rect);
void HGE_Rect_SetY2(HGE_Rect_t *rect, float y2);
float HGE_Rect_GetY2(HGE_Rect_t *rect);

void HGE_Rect_Clear(HGE_Rect_t *rect);
BOOL HGE_Rect_IsClean(HGE_Rect_t *rect);
void HGE_Rect_Set(HGE_Rect_t *rect, float x1, float y1, float x2, float y2);
void HGE_Rect_SetRadius(HGE_Rect_t *rect, float x, float y, float r);
void HGE_Rect_Encapsulate(HGE_Rect_t *rect, float x, float y);
BOOL HGE_Rect_TestPoint(HGE_Rect_t *rect, float x, float y);
BOOL HGE_Rect_Intersect(HGE_Rect_t *rect, const HGE_Rect_t *rect2);

#ifdef __cplusplus
}
#endif

#endif
