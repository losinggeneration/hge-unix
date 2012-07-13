#ifndef HGE_DISTORT_C_H
#define HGE_DISTORT_C_H

#include "unix_compat.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HGE_DISP_NODE 0
#define HGE_DISP_TOPLEFT 1
#define HGE_DISP_CENTER 2

typedef struct HGE_DistortionMesh_s HGE_DistortionMesh_t;

HGE_DistortionMesh_t *HGE_DistortionMesh_New(int cols, int rows);
HGE_DistortionMesh_t *HGE_DistortionMesh_Copy(const HGE_DistortionMesh_t *dm);
void HGE_DistortionMesh_Free(HGE_DistortionMesh_t *dm);
HGE_DistortionMesh_t *HGE_DistortionMesh_Set(HGE_DistortionMesh_t *dm, const HGE_DistortionMesh_t *cp);

void HGE_DistortionMesh_Render(HGE_DistortionMesh_t *dm, float x, float y);
/// DWORD col=0xFFFFFFFF, float z=0.5f
void HGE_DistortionMesh_Clear(HGE_DistortionMesh_t *dm, DWORD col, float z);

void HGE_DistortionMesh_SetTexture(HGE_DistortionMesh_t *dm, HTEXTURE tex);
void HGE_DistortionMesh_SetTextureRect(HGE_DistortionMesh_t *dm, float x, float y, float w, float h);
void HGE_DistortionMesh_SetBlendMode(HGE_DistortionMesh_t *dm, int blend);
void HGE_DistortionMesh_SetZ(HGE_DistortionMesh_t *dm, int col, int row, float z);
void HGE_DistortionMesh_SetColor(HGE_DistortionMesh_t *dm, int col, int row, DWORD color);
void HGE_DistortionMesh_SetDisplacement(HGE_DistortionMesh_t *dm, int col, int row, float dx, float dy, int ref);

HTEXTURE HGE_DistortionMesh_GetTexture(HGE_DistortionMesh_t *dm);
void HGE_DistortionMesh_GetTextureRect(HGE_DistortionMesh_t *dm, float *x, float *y, float *w, float *h);
int HGE_DistortionMesh_GetBlendMode(HGE_DistortionMesh_t *dm);
float HGE_DistortionMesh_GetZ(HGE_DistortionMesh_t *dm, int col, int row);
DWORD HGE_DistortionMesh_GetColor(HGE_DistortionMesh_t *dm, int col, int row);
void HGE_DistortionMesh_GetDisplacement(HGE_DistortionMesh_t *dm, int col, int row, float *dx, float *dy, int ref);

int HGE_DistortionMesh_GetRows(HGE_DistortionMesh_t *dm);
int HGE_DistortionMesh_GetCols(HGE_DistortionMesh_t *dm);

#ifdef __cplusplus
}
#endif

#endif
