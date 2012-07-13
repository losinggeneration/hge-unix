#include "hgeanim.h"
#include "hgeanim_c.h"
#include "hgeanim_impl.h"

#include <malloc.h>

extern "C" {

HGE_Animation_t *HGE_Animation_New(HTEXTURE tex, int nframes, float FPS, float x, float y, float w, float h) {
	HGE_Animation_t *a = (HGE_Animation_t *)malloc(sizeof(HGE_Animation_t));

	a->a = new hgeAnimation(tex, nframes, FPS, x, y, w, h);

	return a;
}

HGE_Animation_t *HGE_Animation_Copy(const HGE_Animation_t *anim) {
	HGE_Animation_t *a = (HGE_Animation_t *)malloc(sizeof(HGE_Animation_t));

	a->a = new hgeAnimation(*anim->a);

	return a;
}

void HGE_Animation_Free(HGE_Animation_t *a) {
	delete a->a;
	free(a);
}

void HGE_Animation_Play(HGE_Animation_t *a) {
	a->a->Play();
}

void HGE_Animation_Stop(HGE_Animation_t *a) {
	a->a->Stop();
}

void HGE_Animation_Resume(HGE_Animation_t *a) {
	a->a->Resume();
}

void HGE_Animation_Update(HGE_Animation_t *a, float fDeltaTime) {
	a->a->Update(fDeltaTime);
}

BOOL HGE_Animation_IsPlaying(HGE_Animation_t *a) {
	a->a->IsPlaying();
}

void HGE_Animation_SetTexture(HGE_Animation_t *a, HTEXTURE tex) {
	a->a->SetTexture(tex);
}

void HGE_Animation_SetTextureRect(HGE_Animation_t *a, float x1, float y1, float x2, float y2) {
	a->a->SetTextureRect(x1, y1, x2, y2);
}

void HGE_Animation_SetMode(HGE_Animation_t *a, int mode) {
	a->a->SetMode(mode);
}

void HGE_Animation_SetSpeed(HGE_Animation_t *a, float FPS) {
	a->a->SetSpeed(FPS);
}

void HGE_Animation_SetFrame(HGE_Animation_t *a, int n) {
	a->a->SetFrame(n);
}

void HGE_Animation_SetFrames(HGE_Animation_t *a, int n) {
	a->a->SetFrames(n);
}

int HGE_Animation_GetMode(HGE_Animation_t *a) {
	a->a->GetMode();
}

float HGE_Animation_GetSpeed(HGE_Animation_t *a) {
	a->a->GetSpeed();
}

int HGE_Animation_GetFrame(HGE_Animation_t *a) {
	a->a->GetFrame();
}

int HGE_Animation_GetFrames(HGE_Animation_t *a) {
	a->a->GetFrames();
}

}
