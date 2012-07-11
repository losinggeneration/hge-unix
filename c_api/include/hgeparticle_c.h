#ifndef HGE_PARTICLE_C_H
#define HGE_PARTICLE_C_H

#include "unix_compat.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct HGE_Color_s HGE_Color_t;
typedef struct HGE_Sprite_s HGE_Sprite_t;
typedef struct HGE_Rect_s HGE_Rect_t;

struct HGE_Particle_SystemInfo_t
{
	HGE_Sprite_t* sprite; // texture + blend mode
	int nEmission; // particles per sec
	float fLifetime;

	float fParticleLifeMin;
	float fParticleLifeMax;

	float fDirection;
	float fSpread;
	BYTE bRelative; // was "bool", but that's 4 bytes on PowerPC instead of 1, and it broke loading from disk...

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
};

/// hgeParticleSystem
typedef struct HGE_Particle_System_s HGE_Particle_System_t;
// HGE_Particle_SystemInfo_t info;
//
// HGE_Particle_System(const char *filename, HGE_Sprite_t *sprite, float fps);
// HGE_Particle_System(HGE_Particle_SystemInfo_t *psi, float fps);
// HGE_Particle_System(const HGE_Particle_System_t *ps);
// ~HGE_Particle_System();
//
// HGE_Particle_System& operator= (const HGE_Particle_System *ps);
//
// void Render();
// void FireAt(float x, float y);
// void Fire();
// void Stop(bool bKillParticles);
// void Update(float fDeltaTime);
// void MoveTo(float x, float y, bool bMoveParticles);
// void Transpose(float x, float y);
// void TrackBoundingBox(bool bTrack);
//
// int GetParticlesAlive();
// float GetAge();
// void GetPosition(float *x, float *y);
// void GetTransposition(float *x, float *y);
// HGE_Rect_t* GetBoundingBox(HGE_Rect_t *rect);

/// hgeParticleManager
typedef struct HGE_Particle_Manager_s HGE_Particle_Manager_t;
// HGE_Particle_Manager(float fps);
// ~HGE_Particle_Manager();
//
// void Update(float dt);
// void Render();
//
// HGE_Particle_System_t* SpawnPS(HGE_Particle_SystemInfo_t *psi, float x, float y);
// bool IsPSAlive(HGE_Particle_System_t *ps);
// void Transpose(float x, float y);
// void GetTransposition(float *dx, float *dy);
// void KillPS(HGE_Particle_System_t *ps);
// void KillAll();

#ifdef __cplusplus
}
#endif

#endif
