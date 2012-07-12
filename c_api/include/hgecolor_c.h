#ifndef HGE_COLOR_C_H
#define HGE_COLOR_C_H

#include "unix_compat.h"

#ifdef __cplusplus
extern "C" {
	#endif

#define HGE_Color HGE_Color_RGB

void HGE_Color_Clamp(float *x);

typedef struct HGE_Color_RGB_s HGE_Color_RGB_t;
// float r,g,b,a;
void HGE_Color_RGB_SetH(HGE_Color_RGB_t *rgb, float h);
float HGE_Color_RGB_GetH(HGE_Color_RGB_t *rgb);
void HGE_Color_RGB_SetS(HGE_Color_RGB_t *rgb, float s);
float HGE_Color_RGB_GetS(HGE_Color_RGB_t *rgb);
void HGE_Color_RGB_SetV(HGE_Color_RGB_t *rgb, float v);
float HGE_Color_RGB_GetV(HGE_Color_RGB_t *rgb);
void HGE_Color_RGB_SetA(HGE_Color_RGB_t *rgb, float a);
float HGE_Color_RGB_GetA(HGE_Color_RGB_t *rgb);

HGE_Color_RGB_t *HGE_Color_RGB_New(float r, float g, float b, float a);
HGE_Color_RGB_t *HGE_Color_RGB_NewColor(DWORD col);
HGE_Color_RGB_t *HGE_Color_RGB_NewEmpty();
void HGE_Color_RGB_Free(HGE_Color_RGB_t *rgb);

HGE_Color_RGB_t *HGE_Color_RGB_Subtract(const HGE_Color_RGB_t *rgb1, const HGE_Color_RGB_t *rgb2);
HGE_Color_RGB_t *HGE_Color_RGB_Add(const HGE_Color_RGB_t *rgb1, const HGE_Color_RGB_t *rgb2);
HGE_Color_RGB_t *HGE_Color_RGB_Multiply(const HGE_Color_RGB_t *rgb1, const HGE_Color_RGB_t *rgb2);
HGE_Color_RGB_t *HGE_Color_RGB_SubtractEqual(HGE_Color_RGB_t *v1, const HGE_Color_RGB_t *rgb2);
HGE_Color_RGB_t *HGE_Color_RGB_AddEqual(HGE_Color_RGB_t *v1, const HGE_Color_RGB_t *rgb2);
BOOL HGE_Color_RGB_Equal(const HGE_Color_RGB_t *rgb1, const HGE_Color_RGB_t *rgb2);
BOOL HGE_Color_RGB_NotEqual(const HGE_Color_RGB_t *rgb1, const HGE_Color_RGB_t *rgb2);

HGE_Color_RGB_t *HGE_Color_RGB_Divide(const HGE_Color_RGB_t rgb1, float scalar);
HGE_Color_RGB_t *HGE_Color_RGB_MultiplyScalar(const HGE_Color_RGB_t rgb1, float scalar);
HGE_Color_RGB_t *HGE_Color_RGB_MultiplyEqual(HGE_Color_RGB_t *v1, float scalar);

void HGE_Color_RGB_Clamp(HGE_Color_RGB_t *rgb);
void HGE_Color_RGB_SetHWColor(HGE_Color_RGB_t *rgb, DWORD col);
DWORD HGE_Color_RGB_GetHWColor(HGE_Color_RGB_t *rgb);

typedef struct HGE_Color_HSV_s HGE_Color_HSV_t;
void HGE_Color_HSV_SetH(HGE_Color_HSV_t *hsv, float h);
float HGE_Color_HSV_GetH(HGE_Color_HSV_t *hsv);
void HGE_Color_HSV_SetS(HGE_Color_HSV_t *hsv, float s);
float HGE_Color_HSV_GetS(HGE_Color_HSV_t *hsv);
void HGE_Color_HSV_SetV(HGE_Color_HSV_t *hsv, float v);
float HGE_Color_HSV_GetV(HGE_Color_HSV_t *hsv);
void HGE_Color_HSV_SetA(HGE_Color_HSV_t *hsv, float a);
float HGE_Color_HSV_GetA(HGE_Color_HSV_t *hsv);

HGE_Color_HSV_t *HGE_Color_HSV_New(float h, float s, float v, float a);
HGE_Color_HSV_t *HGE_Color_HSV_NewColor(DWORD col);
HGE_Color_HSV_t *HGE_Color_HSV_NewEmpty();
HGE_Color_HSV_t *HGE_Color_HSV_Free(HGE_Color_HSV_t *hsv);

HGE_Color_HSV_t *HGE_Color_HSV_Subtract(const HGE_Color_HSV_t *hsv1, const HGE_Color_HSV_t *hsv2);
HGE_Color_HSV_t *HGE_Color_HSV_Add(const HGE_Color_HSV_t *hsv1, const HGE_Color_HSV_t *hsv2);
HGE_Color_HSV_t *HGE_Color_HSV_Multiply(const HGE_Color_HSV_t *hsv1, const HGE_Color_HSV_t *hsv2);
HGE_Color_HSV_t *HGE_Color_HSV_SubtractEqual(HGE_Color_HSV_t *v1, const HGE_Color_HSV_t *hsv2);
HGE_Color_HSV_t *HGE_Color_HSV_AddEqual(HGE_Color_HSV_t *v1, const HGE_Color_HSV_t *hsv2);
BOOL HGE_Color_HSV_Equal(const HGE_Color_HSV_t *hsv1, const HGE_Color_HSV_t *hsv2);
BOOL HGE_Color_HSV_NotEqual(const HGE_Color_HSV_t *hsv1, const HGE_Color_HSV_t *hsv2);

HGE_Color_HSV_t *HGE_Color_HSV_Divide(const HGE_Color_HSV_t hsv1, float scalar);
HGE_Color_HSV_t *HGE_Color_HSV_MultiplyScalar(const HGE_Color_HSV_t hsv1, float scalar);
HGE_Color_HSV_t *HGE_Color_HSV_MultiplyEqual(HGE_Color_HSV_t *v1, float scalar);

void HGE_Color_HSV_Clamp(HGE_Color_HSV_t *hsv);
void HGE_Color_HSV_SetHWColor(HGE_Color_HSV_t *hsv, DWORD col);
DWORD HGE_Color_HSV_GetHWColor(HGE_Color_HSV_t *hsv);

#ifdef __cplusplus
}
#endif

#endif
