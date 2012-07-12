/*
 * * Haaf's Game Engine 1.7
 ** Copyright(C) 2003-2007, Relish Games
 ** hge.relishgames.com
 **
 ** HGE_Color_*** helper classes
 */


#ifndef HGECOLOR_H
#define HGECOLOR_H


#include "hge.h"


#define HGE_Color HGE_Color_RGB

void HGE_Color_Clamp(float *x);

typedef struct HGE_Color_RGB_s HGE_Color_RGB_t;
// float r,g,b,a;

HGE_Color_RGB_t *HGE_Color_RGB_New(float r, float g, float b, float a);
HGE_Color_RGB_t *HGE_Color_RGB_NewColor(DWORD col);
HGE_Color_RGB_t *HGE_Color_RGB_NewEmpty();
void HGE_Color_RGB_Free(HGE_Color_RGB_t *rgb);

// HGE_Color_RGB_t *operator-(const HGE_Color_RGB_t *c);
// HGE_Color_RGB_t *operator+(const HGE_Color_RGB_t *c);
// HGE_Color_RGB_t *operator*(const HGE_Color_RGB_t *c);
// HGE_Color_RGB_t *operator-=(const HGE_Color_RGB_t *c);
// HGE_Color_RGB_t *operator+=(const HGE_Color_RGB_t *c);
// BOOL operator==(const HGE_Color_RGB_t *c);
// BOOL operator!=(const HGE_Color_RGB_t *c);
//
// HGE_Color_RGB_t *operator/(const float scalar);
// HGE_Color_RGB_t *operator*(const float scalar);
// HGE_Color_RGB_t *operator*=(const float scalar);

void HGE_Color_RGB_Clamp(HGE_Color_RGB_t *rgb);
void HGE_Color_RGB_SetHWColor(HGE_Color_RGB_t *rgb, DWORD col);
DWORD HGE_Color_RGB_GetHWColor(HGE_Color_RGB_t *rgb);

// HGE_Color_RGB_t *operator*(const float sc, const HGE_Color_RGB &c);


typedef struct HGE_Color_HSV_s HGE_Color_HSV_t;
// float h,s,v,a;

HGE_Color_HSV_t *HGE_Color_HSV_New(float h, float s, float v, float a);
HGE_Color_HSV_t *HGE_Color_HSV_NewColor(DWORD col);
HGE_Color_HSV_t *HGE_Color_HSV_NewEmpty();
HGE_Color_HSV_t *HGE_Color_HSV_Free(HGE_Color_HSV_t *hsv);

// HGE_Color_HSV_t *operator-(const HGE_Color_HSV_t *c);
// HGE_Color_HSV_t *operator+(const HGE_Color_HSV_t *c);
// HGE_Color_HSV_t *operator*(const HGE_Color_HSV_t *c);
// HGE_Color_HSV_t *operator-=(const HGE_Color_HSV_t *c);
// HGE_Color_HSV_t *operator+=(const HGE_Color_HSV_t *c);
// BOOL operator==(const HGE_Color_HSV_t *c);
// BOOL operator!=(const HGE_Color_HSV_t *c);
//
// HGE_Color_HSV_t *operator/(const float scalar);
// HGE_Color_HSV_t *operator*(const float scalar);
// HGE_Color_HSV_t *operator*=(const float scalar);

void HGE_Color_HSV_Clamp(HGE_Color_HSV_t *hsv);
void HGE_Color_HSV_SetHWColor(HGE_Color_HSV_t *hsv, DWORD col);
DWORD HGE_Color_HSV_GetHWColor(HGE_Color_HSV_t *hsv);

// HGE_Color_HSV operator*(const float sc, const HGE_Color_HSV &c);

#endif
