#include "hgecolor.h"
#include "hgecolor_c.h"

#include <malloc.h>

extern "C" {

void HGE_Color_Clamp(float *x);

typedef struct HGE_Color_RGB_s {
	hgeColorRGB *rgb;
} HGE_Color_RGB_t;

typedef struct HGE_Color_HSV_s {
	hgeColorHSV *hsv;
} HGE_Color_HSV_t;

HGE_Color_RGB_t *HGE_Color_RGB_New(float r, float g, float b, float a) {
	HGE_Color_RGB_t *rgb = (HGE_Color_RGB_t *)malloc(sizeof(HGE_Color_RGB_t));

	rgb->rgb = new hgeColorRGB(r, g, b, a);

	return rgb;
}

HGE_Color_RGB_t *HGE_Color_RGB_NewColor(DWORD col) {
	HGE_Color_RGB_t *rgb = (HGE_Color_RGB_t *)malloc(sizeof(HGE_Color_RGB_t));

	rgb->rgb = new hgeColorRGB(col);

	return rgb;
}

HGE_Color_RGB_t *HGE_Color_RGB_NewEmpty() {
	HGE_Color_RGB_t *rgb = (HGE_Color_RGB_t *)malloc(sizeof(HGE_Color_RGB_t));

	rgb->rgb = new hgeColorRGB();

	return rgb;
}

void HGE_Color_RGB_Free(HGE_Color_RGB_t *rgb) {
	delete rgb->rgb;
	free(rgb);
}

void HGE_Color_RGB_SetR(HGE_Color_RGB_t *rgb, float r) {
	rgb->rgb->r = r;
}

float HGE_Color_RGB_GetR(HGE_Color_RGB_t *rgb) {
	return rgb->rgb->r;
}

void HGE_Color_RGB_SetG(HGE_Color_RGB_t *rgb, float g) {
	rgb->rgb->g = g;
}

float HGE_Color_RGB_GetG(HGE_Color_RGB_t *rgb) {
	return rgb->rgb->g;
}

void HGE_Color_RGB_SetB(HGE_Color_RGB_t *rgb, float b) {
	rgb->rgb->b = b;
}

float HGE_Color_RGB_GetB(HGE_Color_RGB_t *rgb) {
	return rgb->rgb->b;
}

void HGE_Color_RGB_SetA(HGE_Color_RGB_t *rgb, float a) {
	rgb->rgb->a = a;
}

float HGE_Color_RGB_GetA(HGE_Color_RGB_t *rgb) {
	return rgb->rgb->a;
}

void HGE_Color_RGB_Set(HGE_Color_RGB_t *rgb, const HGE_Color_RGB_t *rgb2) {
	*rgb->rgb = *rgb2->rgb;
}

void HGE_Color_RGB_Subtract(HGE_Color_RGB_t *rgb, const HGE_Color_RGB_t *rgb2) {
	*rgb->rgb -= *rgb2->rgb;
}

void HGE_Color_RGB_Add(HGE_Color_RGB_t *rgb, const HGE_Color_RGB_t *rgb2) {
	*rgb->rgb += *rgb2->rgb;
}

void HGE_Color_RGB_Multiply(HGE_Color_RGB_t *rgb, const HGE_Color_RGB_t *rgb2) {
	hgeColorRGB *r = new hgeColorRGB(*rgb->rgb * *rgb2->rgb);
	delete rgb->rgb;
	rgb->rgb = r;
}

void HGE_Color_RGB_Divide(HGE_Color_RGB_t *rgb, float scalar) {
	hgeColorRGB *r = new hgeColorRGB(*rgb->rgb / scalar);
	delete rgb->rgb;
	rgb->rgb = r;
}

void HGE_Color_RGB_MultiplyScalar(HGE_Color_RGB_t *rgb, float scalar) {
	*rgb->rgb *= scalar;
}

BOOL HGE_Color_RGB_Equal(const HGE_Color_RGB_t *rgb1, const HGE_Color_RGB_t *rgb2) {
	return rgb1 == rgb2;
}

BOOL HGE_Color_RGB_NotEqual(const HGE_Color_RGB_t *rgb1, const HGE_Color_RGB_t *rgb2) {
	return rgb1 != rgb2;
}

void HGE_Color_RGB_Clamp(HGE_Color_RGB_t *rgb) {
	rgb->rgb->Clamp();
}

void HGE_Color_RGB_SetHWColor(HGE_Color_RGB_t *rgb, DWORD col) {
	rgb->rgb->SetHWColor(col);
}

DWORD HGE_Color_RGB_GetHWColor(HGE_Color_RGB_t *rgb) {
	return rgb->rgb->GetHWColor();
}

HGE_Color_HSV_t *HGE_Color_HSV_New(float h, float s, float v, float a) {
	HGE_Color_HSV_t *hsv = (HGE_Color_HSV_t *)malloc(sizeof(HGE_Color_HSV_t));

	hsv->hsv = new hgeColorHSV(h, s, v, a);

	return hsv;
}

HGE_Color_HSV_t *HGE_Color_HSV_NewColor(DWORD col) {
	HGE_Color_HSV_t *hsv = (HGE_Color_HSV_t *)malloc(sizeof(HGE_Color_HSV_t));

	hsv->hsv = new hgeColorHSV(col);

	return hsv;
}

HGE_Color_HSV_t *HGE_Color_HSV_NewEmpty() {
	HGE_Color_HSV_t *hsv = (HGE_Color_HSV_t *)malloc(sizeof(HGE_Color_HSV_t));

	hsv->hsv = new hgeColorHSV();

	return hsv;
}

HGE_Color_HSV_t *HGE_Color_HSV_Free(HGE_Color_HSV_t *hsv) {
	delete hsv->hsv;
	free(hsv);
}

void HGE_Color_HSV_SetH(HGE_Color_HSV_t *hsv, float h) {
	hsv->hsv->h = h;
}

float HGE_Color_HSV_GetH(HGE_Color_HSV_t *hsv) {
	return hsv->hsv->h;
}

void HGE_Color_HSV_SetS(HGE_Color_HSV_t *hsv, float s) {
	hsv->hsv->s = s;
}

float HGE_Color_HSV_GetS(HGE_Color_HSV_t *hsv) {
	return hsv->hsv->s;
}

void HGE_Color_HSV_SetV(HGE_Color_HSV_t *hsv, float v) {
	hsv->hsv->v = v;
}

float HGE_Color_HSV_GetV(HGE_Color_HSV_t *hsv) {
	return hsv->hsv->v;
}

void HGE_Color_HSV_SetA(HGE_Color_HSV_t *hsv, float a) {
	hsv->hsv->a = a;
}

float HGE_Color_HSV_GetA(HGE_Color_HSV_t *hsv) {
	return hsv->hsv->a;
}

void HGE_Color_HSV_Subtract(HGE_Color_HSV_t *hsv, const HGE_Color_HSV_t *hsv2) {
	*hsv->hsv -= *hsv2->hsv;
}

void HGE_Color_HSV_Add(HGE_Color_HSV_t *hsv, const HGE_Color_HSV_t *hsv2) {
	*hsv->hsv += *hsv2->hsv;
}

void HGE_Color_HSV_Multiply(HGE_Color_HSV_t *hsv, const HGE_Color_HSV_t *hsv2) {
	hgeColorHSV *h = new hgeColorHSV(*hsv->hsv * *hsv2->hsv);
	delete hsv->hsv;
	hsv->hsv = h;
}

void HGE_Color_HSV_Divide(HGE_Color_HSV_t *hsv, float scalar) {
	hgeColorHSV *h = new hgeColorHSV(*hsv->hsv / scalar);
	delete hsv->hsv;
	hsv->hsv = h;
}

void HGE_Color_HSV_MultiplyScalar(HGE_Color_HSV_t *hsv, float scalar) {
	*hsv->hsv *= scalar;
}

BOOL HGE_Color_HSV_Equal(const HGE_Color_HSV_t *hsv1, const HGE_Color_HSV_t *hsv2) {
	return hsv1->hsv == hsv2->hsv;
}

BOOL HGE_Color_HSV_NotEqual(const HGE_Color_HSV_t *hsv1, const HGE_Color_HSV_t *hsv2) {
	return hsv1->hsv != hsv2->hsv;
}

void HGE_Color_HSV_Clamp(HGE_Color_HSV_t *hsv) {
	hsv->hsv->Clamp();
}

void HGE_Color_HSV_SetHWColor(HGE_Color_HSV_t *hsv, DWORD col) {
	hsv->hsv->SetHWColor(col);
}

DWORD HGE_Color_HSV_GetHWColor(HGE_Color_HSV_t *hsv) {
	return hsv->hsv->GetHWColor();
}

}
