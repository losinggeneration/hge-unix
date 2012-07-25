#include "hgeparticle.h"
#include "hgeparticle_c.h"
#include "hgeparticle_impl.h"

#include "hgerect_impl.h"
#include "hgesprite_impl.h"

#include <malloc.h>

extern "C" {

typedef struct HGE_Particle_System_s {
	hgeParticleSystem *ps;
} HGE_Particle_System_t;

typedef struct HGE_Particle_Manager_s {
	hgeParticleManager *pm;
} HGE_Particle_Manager_t;

static HGE_Particle_System_t *HGE_Particle_System_NewEmpty() {
	return (HGE_Particle_System_t *)malloc(sizeof(HGE_Particle_System_t));
}

HGE_Particle_System_t *HGE_Particle_System_New(const char *filename, HGE_Sprite_t *sprite, float fps) {
	HGE_Particle_System_t *ps = HGE_Particle_System_NewEmpty();

	ps->ps = new hgeParticleSystem(filename, sprite->s, fps);

	return ps;
}

HGE_Particle_System_t *HGE_Particle_System_NewInfo(HGE_Particle_SystemInfo_t *psi, float fps) {
	HGE_Particle_System_t *ps = HGE_Particle_System_NewEmpty();

	ps->ps = new hgeParticleSystem((hgeParticleSystemInfo *)psi, fps);

	return ps;
}

HGE_Particle_System_t *HGE_Particle_System_Copy(const HGE_Particle_System_t *ps) {
	HGE_Particle_System_t *p = HGE_Particle_System_NewEmpty();

	p->ps = new hgeParticleSystem(*ps->ps);

	return p;
}

void HGE_Particle_System_Free(HGE_Particle_System_t *ps) {
	delete ps->ps;
	free(ps);
}

HGE_Particle_SystemInfo_t *HGE_Particle_System_GetInfo(HGE_Particle_System_t *ps) {
	return (HGE_Particle_SystemInfo_t *)(&ps->ps->info);
}

void HGE_Particle_System_Set(HGE_Particle_System_t *ps, const HGE_Particle_System_t *ps2) {
	ps->ps = ps2->ps;
}

void HGE_Particle_System_Render(HGE_Particle_System_t *ps) {
	ps->ps->Render();
}

void HGE_Particle_System_FireAt(HGE_Particle_System_t *ps, float x, float y) {
	ps->ps->FireAt(x, y);
}

void HGE_Particle_System_Fire(HGE_Particle_System_t *ps) {
	ps->ps->Fire();
}

void HGE_Particle_System_Stop(HGE_Particle_System_t *ps, BOOL killParticles) {
	ps->ps->Stop(killParticles);
}

void HGE_Particle_System_Update(HGE_Particle_System_t *ps, float deltaTime) {
	ps->ps->Update(deltaTime);
}

void HGE_Particle_System_MoveTo(HGE_Particle_System_t *ps, float x, float y, BOOL moveParticles) {
	ps->ps->MoveTo(x, y, moveParticles);
}

void HGE_Particle_System_Transpose(HGE_Particle_System_t *ps, float x, float y) {
	ps->ps->Transpose(x, y);
}

void HGE_Particle_System_TrackBoundingBox(HGE_Particle_System_t *ps, BOOL track) {
	ps->ps->TrackBoundingBox(track);
}

int HGE_Particle_System_GetParticlesAlive(HGE_Particle_System_t *ps) {
	return ps->ps->GetParticlesAlive();
}

float HGE_Particle_System_GetAge(HGE_Particle_System_t *ps) {
	return ps->ps->GetAge();
}

void HGE_Particle_System_GetPosition(HGE_Particle_System_t *ps, float *x, float *y) {
	ps->ps->GetPosition(x, y);
}

void HGE_Particle_System_GetTransposition(HGE_Particle_System_t *ps, float *x, float *y) {
	ps->ps->GetTransposition(x, y);
}

HGE_Rect_t* HGE_Particle_System_GetBoundingBox(HGE_Particle_System_t *ps, HGE_Rect_t *rect) {
	ps->ps->GetBoundingBox(rect->r);
	return rect;
}

HGE_Particle_Manager_t *HGE_Particle_Manager_New(float fps) {
	HGE_Particle_Manager_t *pm = (HGE_Particle_Manager_t *)malloc(sizeof(HGE_Particle_Manager_t));

	pm->pm = new hgeParticleManager(fps);

	return pm;
}

void HGE_Particle_Manager_Free(HGE_Particle_Manager_t *pm) {
	delete pm->pm;
	free(pm);
}

void HGE_Particle_Manager_Update(HGE_Particle_Manager_t *pm, float dt) {
	pm->pm->Update(dt);
}

void HGE_Particle_Manager_Render(HGE_Particle_Manager_t *pm) {
	pm->pm->Render();
}

HGE_Particle_System_t* HGE_Particle_Manager_SpawnPS(HGE_Particle_Manager_t *pm, HGE_Particle_SystemInfo_t *psi, float x, float y) {
	HGE_Particle_System_t *ps = HGE_Particle_System_NewEmpty();
	ps->ps = pm->pm->SpawnPS((hgeParticleSystemInfo *)psi, x, y);
	return ps;
}

BOOL HGE_Particle_Manager_IsPSAlive(HGE_Particle_Manager_t *pm, HGE_Particle_System_t *ps) {
	return pm->pm->IsPSAlive(ps->ps);
}

void HGE_Particle_Manager_Transpose(HGE_Particle_Manager_t *pm, float x, float y) {
	pm->pm->Transpose(x, y);
}

void HGE_Particle_Manager_GetTransposition(HGE_Particle_Manager_t *pm, float *dx, float *dy) {
	pm->pm->GetTransposition(dx, dy);
}

void HGE_Particle_Manager_KillPS(HGE_Particle_Manager_t *pm, HGE_Particle_System_t *ps) {
	pm->pm->KillPS(ps->ps);
}

void HGE_Particle_Manager_KillAll(HGE_Particle_Manager_t *pm) {
	pm->pm->KillAll();
}

}
