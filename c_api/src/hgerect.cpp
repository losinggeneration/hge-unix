#include "hgerect_impl.h"
#include "hgerect_c.h"

#include <malloc.h>

extern "C" {

HGE_Rect_t *HGE_Rect_NewEmpty() {
	HGE_Rect_t *r = (HGE_Rect_t *)malloc(sizeof(HGE_Rect_t));

	r->r = new hgeRect();

	return r;
}

HGE_Rect_t *HGE_Rect_New(float x1, float y1, float x2, float y2) {
	HGE_Rect_t *r = (HGE_Rect_t *)malloc(sizeof(HGE_Rect_t));

	r->r = new hgeRect(x1,y1,x2,y2);

	return r;
}

void HGE_Rect_Free(HGE_Rect_t *rect) {
	delete rect->r;
	free(rect);
}

void HGE_Rect_SetX1(HGE_Rect_t *rect, float x1) {
	rect->r->x1 = x1;
}

float HGE_Rect_GetX1(HGE_Rect_t *rect) {
	return rect->r->x1;
}

void HGE_Rect_SetX2(HGE_Rect_t *rect, float x2) {
	rect->r->x2 = x2;
}

float HGE_Rect_GetX2(HGE_Rect_t *rect) {
	return rect->r->x2;
}

void HGE_Rect_SetY1(HGE_Rect_t *rect, float y1) {
	rect->r->y1 = y1;
}

float HGE_Rect_GetY1(HGE_Rect_t *rect) {
	return rect->r->y1;
}

void HGE_Rect_SetY2(HGE_Rect_t *rect, float y2) {
	rect->r->y2 = y2;
}

float HGE_Rect_GetY2(HGE_Rect_t *rect) {
	return rect->r->y2;
}

void HGE_Rect_Clear(HGE_Rect_t *rect) {
	rect->r->Clear();
}

BOOL HGE_Rect_IsClean(HGE_Rect_t *rect) {
	rect->r->IsClean();
}

void HGE_Rect_Set(HGE_Rect_t *rect, float x1, float y1, float x2, float y2) {
	rect->r->Set(x1, y1, x2, y2);
}

void HGE_Rect_SetRadius(HGE_Rect_t *rect, float x, float y, float r) {
	rect->r->SetRadius(x, y, r);
}

void HGE_Rect_Encapsulate(HGE_Rect_t *rect, float x, float y) {
	rect->r->Encapsulate(x, y);
}

BOOL HGE_Rect_TestPoint(HGE_Rect_t *rect, float x, float y) {
	rect->r->TestPoint(x, y);
}

BOOL HGE_Rect_Intersect(HGE_Rect_t *rect, const HGE_Rect_t *rect2) {
	rect->r->Intersect(rect2->r);
}

}
