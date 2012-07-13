#ifndef HGE_PARTICLE_C_H
#define HGE_PARTICLE_C_H

#include "unix_compat.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct HGE_Color_s HGE_Color_t;
typedef struct HGE_Sprite_s HGE_Sprite_t;
typedef struct HGE_Rect_s HGE_Rect_t;

typedef struct HGE_Particle_SystemInfo_s
{
	HGE_Sprite_t* sprite; // texture + blend mode
	int nEmission; // particles per sec
	float fLifetime;

	float fParticleLifeMin;
	float fParticleLifeMax;

	float fDirection;
	float fSpread;
	BYTE bRelative; // was "BOOL", but that's 4 bytes on PowerPC instead of 1, and it broke loading from disk...

	float fSpeedMin;
	float fSpeedMax;

	float fGravityMin;
	float fGravityMax;

	float fRadialAccelMin;
	float fRadialAccelMax;

	float fTangentialAccelMin;
	float fTangentialAccelMax;

	float fSizeStart;
	float fSizeEnd;
	float fSizeVar;

	float fSpinStart;
	float fSpinEnd;
	float fSpinVar;

	HGE_Color_t *colColorStart; // + alpha
	HGE_Color_t *colColorEnd;
	float fColorVar;
	float fAlphaVar;
} HGE_Particle_SystemInfo_t;

/// hgeParticleSystem
typedef struct HGE_Particle_System_s HGE_Particle_System_t;
/// float fps=0.0
HGE_Particle_System_t *HGE_Particle_System_New(const char *filename, HGE_Sprite_t *sprite, float fps);
HGE_Particle_System_t *HGE_Particle_System_NewInfo(HGE_Particle_SystemInfo_t *psi, float fps);
HGE_Particle_System_t *HGE_Particle_System_Copy(const HGE_Particle_System_t *ps);
void HGE_Particle_System_Free(HGE_Particle_System_t *ps);

HGE_Particle_SystemInfo_t *HGE_Particle_System_GetInfo(HGE_Particle_System_t *ps);

void HGE_Particle_System_Set(HGE_Particle_System_t *ps, const HGE_Particle_System_t *ps2);

void HGE_Particle_System_Render(HGE_Particle_System_t *ps);
void HGE_Particle_System_FireAt(HGE_Particle_System_t *ps, float x, float y);
void HGE_Particle_System_Fire(HGE_Particle_System_t *ps);
void HGE_Particle_System_Stop(HGE_Particle_System_t *ps, BOOL bKillParticles);
void HGE_Particle_System_Update(HGE_Particle_System_t *ps, float fDeltaTime);
/// bool bMoveParticles=false
void HGE_Particle_System_MoveTo(HGE_Particle_System_t *ps, float x, float y, BOOL bMoveParticles);
void HGE_Particle_System_Transpose(HGE_Particle_System_t *ps, float x, float y);
void HGE_Particle_System_TrackBoundingBox(HGE_Particle_System_t *ps, BOOL bTrack);

int HGE_Particle_System_GetParticlesAlive(HGE_Particle_System_t *ps);
float HGE_Particle_System_GetAge(HGE_Particle_System_t *ps);
void HGE_Particle_System_GetPosition(HGE_Particle_System_t *ps, float *x, float *y);
void HGE_Particle_System_GetTransposition(HGE_Particle_System_t *ps, float *x, float *y);
HGE_Rect_t* HGE_Particle_System_GetBoundingBox(HGE_Particle_System_t *ps, HGE_Rect_t *rect);

/// hgeParticleManager
typedef struct HGE_Particle_Manager_s HGE_Particle_Manager_t;
HGE_Particle_Manager_t *HGE_Particle_Manager_New(float fps);
void HGE_Particle_Manager_Free(HGE_Particle_Manager_t *pm);

void HGE_Particle_Manager_Update(HGE_Particle_Manager_t *pm, float dt);
void HGE_Particle_Manager_Render(HGE_Particle_Manager_t *pm);

HGE_Particle_System_t* HGE_Particle_Manager_SpawnPS(HGE_Particle_Manager_t *pm, HGE_Particle_SystemInfo_t *psi, float x, float y);
BOOL HGE_Particle_Manager_IsPSAlive(HGE_Particle_Manager_t* pm, HGE_Particle_System_t* ps);
void HGE_Particle_Manager_Transpose(HGE_Particle_Manager_t *pm, float x, float y);
void HGE_Particle_Manager_GetTransposition(HGE_Particle_Manager_t *pm, float *dx, float *dy);
void HGE_Particle_Manager_KillPS(HGE_Particle_Manager_t *pm, HGE_Particle_System_t *ps);
void HGE_Particle_Manager_KillAll(HGE_Particle_Manager_t *pm);

#ifdef __cplusplus
}
#endif

#endif
