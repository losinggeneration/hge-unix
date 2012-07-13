#include "hgedistort.h"
#include "hgedistort_c.h"
#include "hgedistort_impl.h"

#include <malloc.h>

extern "C" {

HGE_DistortionMesh_t *HGE_DistortionMesh_New(int cols, int rows) {
	HGE_DistortionMesh_t *dm = (HGE_DistortionMesh_t *)malloc(sizeof(HGE_DistortionMesh_t));

	dm->dm = new hgeDistortionMesh(cols, rows);

	return dm;
}

HGE_DistortionMesh_t *HGE_DistortionMesh_Copy(const HGE_DistortionMesh_t *dm) {
	HGE_DistortionMesh_t *d = (HGE_DistortionMesh_t *)malloc(sizeof(HGE_DistortionMesh_t));

	d->dm = new hgeDistortionMesh(*dm->dm);

	return d;
}

void HGE_DistortionMesh_Free(HGE_DistortionMesh_t *dm) {
	delete dm->dm;
	free(dm);
}

HGE_DistortionMesh_t *HGE_DistortionMesh_Set(HGE_DistortionMesh_t *dm, const HGE_DistortionMesh_t *cp) {
	dm->dm = cp->dm;
	return dm;
}

void HGE_DistortionMesh_Render(HGE_DistortionMesh_t *dm, float x, float y) {
	dm->dm->Render(x, y);
}

void HGE_DistortionMesh_Clear(HGE_DistortionMesh_t *dm, DWORD col, float z) {
	dm->dm->Clear(col, z);
}

void HGE_DistortionMesh_SetTexture(HGE_DistortionMesh_t *dm, HTEXTURE tex) {
	dm->dm->SetTexture(tex);
}

void HGE_DistortionMesh_SetTextureRect(HGE_DistortionMesh_t *dm, float x, float y, float w, float h) {
	dm->dm->SetTextureRect(x, y, w, h);
}

void HGE_DistortionMesh_SetBlendMode(HGE_DistortionMesh_t *dm, int blend) {
	dm->dm->SetBlendMode(blend);
}

void HGE_DistortionMesh_SetZ(HGE_DistortionMesh_t *dm, int col, int row, float z) {
	dm->dm->SetZ(col, row, z);
}

void HGE_DistortionMesh_SetColor(HGE_DistortionMesh_t *dm, int col, int row, DWORD color) {
	dm->dm->SetColor(col, row, color);
}

void HGE_DistortionMesh_SetDisplacement(HGE_DistortionMesh_t *dm, int col, int row, float dx, float dy, int ref) {
	dm->dm->SetDisplacement(col, row, dx, dy, ref);
}

HTEXTURE HGE_DistortionMesh_GetTexture(HGE_DistortionMesh_t *dm) {
	return dm->dm->GetTexture();
}

void HGE_DistortionMesh_GetTextureRect(HGE_DistortionMesh_t *dm, float *x, float *y, float *w, float *h) {
	dm->dm->GetTextureRect(x, y, w, h);
}

int HGE_DistortionMesh_GetBlendMode(HGE_DistortionMesh_t *dm) {
	return dm->dm->GetBlendMode();
}

float HGE_DistortionMesh_GetZ(HGE_DistortionMesh_t *dm, int col, int row) {
	return dm->dm->GetZ(col, row);
}

DWORD HGE_DistortionMesh_GetColor(HGE_DistortionMesh_t *dm, int col, int row) {
	return dm->dm->GetColor(col, row);
}

void HGE_DistortionMesh_GetDisplacement(HGE_DistortionMesh_t *dm, int col, int row, float *dx, float *dy, int ref) {
	dm->dm->GetDisplacement(col, row, dx, dy, ref);
}

int HGE_DistortionMesh_GetRows(HGE_DistortionMesh_t *dm) {
	return dm->dm->GetRows();
}

int HGE_DistortionMesh_GetCols(HGE_DistortionMesh_t *dm) {
	return dm->dm->GetCols();
}

}
