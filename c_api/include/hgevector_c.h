#ifndef HGE_VECTOR_C_H
#define HGE_VECTOR_C_H

#include "unix_compat.h"

#ifdef __cplusplus
extern "C" {
#endif

float HGE_InvSqrt(float x);

typedef struct HGE_Vector_s HGE_Vector_t;

float HGE_Vector_GetX(HGE_Vector_t *v);
float HGE_Vector_GetY(HGE_Vector_t *v);
void HGE_Vector_SetX(HGE_Vector_t *v, float x);
void HGE_Vector_SetY(HGE_Vector_t *v, float y);

HGE_Vector_t HGE_Vector_New(float x, float y);
HGE_Vector_t HGE_Vector_NewEmpty();

HGE_Vector_t HGE_Vector_Negate(const HGE_Vector_t v);
HGE_Vector_t HGE_Vector_Subtract(const HGE_Vector_t v1, const HGE_Vector_t v2);
HGE_Vector_t HGE_Vector_Add(const HGE_Vector_t v1, const HGE_Vector_t v2);
HGE_Vector_t HGE_Vector_Multiply(const HGE_Vector_t v1, float scalar);
HGE_Vector_t HGE_Vector_Divide(const HGE_Vector_t v1, float scalar);

HGE_Vector_t *HGE_Vector_SubtractEqual(HGE_Vector_t *v1, const HGE_Vector_t v2);
HGE_Vector_t *HGE_Vector_AddEqual(HGE_Vector_t *v1, const HGE_Vector_t v2);
HGE_Vector_t *HGE_Vector_MultiplyEqual(HGE_Vector_t *v1, float scalar);
HGE_Vector_t *HGE_Vector_DivideEqual(HGE_Vector_t *v1, float scalar);
BOOL HGE_Vector_Equal(const HGE_Vector_t v1, const HGE_Vector_t v2);
BOOL HGE_Vector_NotEqual(const HGE_Vector_t v1, const HGE_Vector_t v2);

float HGE_Vector_Dot(const HGE_Vector_t *v1, const HGE_Vector_t *v2);
float HGE_Vector_Length(const HGE_Vector_t *v1);
float HGE_Vector_Angle(const HGE_Vector_t *v1, const HGE_Vector_t *v2);

void HGE_Vector_Clamp(HGE_Vector_t *v, const float max);
HGE_Vector_t *Normalize(HGE_Vector_t *v);
HGE_Vector_t *Rotate(HGE_Vector_t *v, float a);

#ifdef __cplusplus
}
#endif

#endif
