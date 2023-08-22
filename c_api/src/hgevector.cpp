#include "hgevector.h"
#include "hgevector_c.h"

extern "C" {

typedef struct HGE_Vector_s {
	hgeVector v;
} HGE_Vector_t;

float HGE_InvSqrt(float x) {
	return InvSqrt(x);
}

float HGE_Vector_GetX(HGE_Vector_t *v) {
	return v->v.x;
}

float HGE_Vector_GetY(HGE_Vector_t *v) {
	return v->v.y;
}

void HGE_Vector_SetX(HGE_Vector_t *v, float x) {
	v->v.x = x;
}

void HGE_Vector_SetY(HGE_Vector_t *v, float y) {
	v->v.y = y;
}

HGE_Vector_t *HGE_Vector_New(float x, float y) {
	HGE_Vector_t *v = (HGE_Vector_t *)malloc(sizeof(HGE_Vector_t));
	v->v.x = x;
	v->v.y = y;
	return v;
}

HGE_Vector_t *HGE_Vector_NewEmpty() {
	HGE_Vector_t *v = (HGE_Vector_t *)malloc(sizeof(HGE_Vector_t));
	return v;
}

void HGE_Vector_Free(HGE_Vector_t *v) {
	free(v);
}

HGE_Vector_t *HGE_Vector_Negate(const HGE_Vector_t v) {
	-v.v;
	return HGE_Vector_New(v.v.x, v.v.y);
}

HGE_Vector_t *HGE_Vector_Subtract(const HGE_Vector_t v1, const HGE_Vector_t v2) {
	auto v = v1.v-v2.v;
	return HGE_Vector_New(v.x, v.y);
}

HGE_Vector_t *HGE_Vector_Add(const HGE_Vector_t v1, const HGE_Vector_t v2) {
	auto v = v1.v + v2.v;
	return HGE_Vector_New(v.x, v.y);
}

HGE_Vector_t *HGE_Vector_Multiply(const HGE_Vector_t v1, float scalar) {
	auto v = v1.v * scalar;
	return HGE_Vector_New(v.x, v.y);
}

HGE_Vector_t *HGE_Vector_Divide(const HGE_Vector_t v1, float scalar) {
	auto v = v1.v / scalar;
	return HGE_Vector_New(v.x, v.y);
}

HGE_Vector_t *HGE_Vector_SubtractEqual(HGE_Vector_t *v1, const HGE_Vector_t v2) {
	v1->v -= v2.v;
	return v1;
}

HGE_Vector_t *HGE_Vector_AddEqual(HGE_Vector_t *v1, const HGE_Vector_t v2) {
	v1->v += v2.v;
	return v1;
}

HGE_Vector_t *HGE_Vector_MultiplyEqual(HGE_Vector_t *v1, float scalar) {
	v1->v *= scalar;
	return v1;
}

BOOL HGE_Vector_Equal(const HGE_Vector_t v1, const HGE_Vector_t v2) {
	return v1.v == v2.v;
}

BOOL HGE_Vector_NotEqual(const HGE_Vector_t v1, const HGE_Vector_t v2) {
	return v1.v != v2.v;
}

float HGE_Vector_Dot(const HGE_Vector_t *v1, const HGE_Vector_t *v2) {
	return v1->v.Dot(&v2->v);
}

float HGE_Vector_Length(const HGE_Vector_t *v1) {
	return v1->v.Length();
}

float HGE_Vector_Angle(const HGE_Vector_t *v1, const HGE_Vector_t *v2) {
	return v1->v.Angle(&v2->v);
}

void HGE_Vector_Clamp(HGE_Vector_t *v, const float max) {
	v->v.Clamp(max);
}

HGE_Vector_t *Normalize(HGE_Vector_t *v) {
	v->v.Normalize();
	return v;
}

HGE_Vector_t *Rotate(HGE_Vector_t *v, float a) {
	v->v.Rotate(a);
	return v;
}

}
