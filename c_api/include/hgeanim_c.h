#ifndef HGE_ANIM_C_H
#define HGE_ANIM_C_H

#ifdef __cplusplus
extern "C" {
#endif

#define HGE_ANIM_FWD 0
#define HGE_ANIM_REV 1
#define HGE_ANIM_PINGPONG 2
#define HGE_ANIM_NOPINGPONG 0
#define HGE_ANIM_LOOP 4
#define HGE_ANIM_NOLOOP 0

typedef struct HGE_Animation_s HGE_Animation_t;

HGE_Animation_t *HGE_Animation_New(HTEXTURE tex, int nframes, float FPS, float x, float y, float w, float h);
HGE_Animation_t *HGE_Animation_Copy(const HGE_Animation_t *anim);
void HGE_Animation_Free(HGE_Animation_t *a);

void HGE_Animation_Play(HGE_Animation_t *a);
void HGE_Animation_Stop(HGE_Animation_t *a);
void HGE_Animation_Resume(HGE_Animation_t *a);
void HGE_Animation_Update(HGE_Animation_t *a, float fDeltaTime);
BOOL HGE_Animation_IsPlaying(HGE_Animation_t *a);

void HGE_Animation_SetTexture(HGE_Animation_t *a, HTEXTURE tex);
void HGE_Animation_SetTextureRect(HGE_Animation_t *a, float x1, float y1, float x2, float y2);
void HGE_Animation_SetMode(HGE_Animation_t *a, int mode);
void HGE_Animation_SetSpeed(HGE_Animation_t *a, float FPS);
void HGE_Animation_SetFrame(HGE_Animation_t *a, int n);
void HGE_Animation_SetFrames(HGE_Animation_t *a, int n);

int HGE_Animation_GetMode(HGE_Animation_t *a);
float HGE_Animation_GetSpeed(HGE_Animation_t *a);
int HGE_Animation_GetFrame(HGE_Animation_t *a);
int HGE_Animation_GetFrames(HGE_Animation_t *a);

#ifdef __cplusplus
}
#endif

#endif
