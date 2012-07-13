#include "hgeresource.h"
#include "hgeresource_c.h"

#include "hgeanim_impl.h"
#include "hgedistort_impl.h"
#include "hgefont_impl.h"
#include "hgeparticle_impl.h"
#include "hgesprite_impl.h"
#include "hgestrings_impl.h"

#include <malloc.h>
#include <string.h>

extern "C" {

typedef struct HGE_Resource_Manager_s {
	hgeResourceManager *rm;
} HGE_Resource_Manager_t;

typedef struct HGE_Resource_Desc_s {
	ResDesc *rd;
} HGE_Resource_Desc_t;

// external structures
// typedef struct HGE_Animation_s HGE_Animation_t;
// typedef struct HGE_DistortionMesh_s HGE_DistortionMesh_t;
// typedef struct HGE_Font_s HGE_Font_t;
// typedef struct HGE_ParticleSystem_s HGE_ParticleSystem_t;
// typedef struct HGE_Sprite_s HGE_Sprite_t;
// typedef struct HGE_StringTable_s HGE_StringTable_t;

static HGE_Resource_Desc_t *HGE_Resource_Desc_New() {
	return (HGE_Resource_Desc_t *)malloc(sizeof(HGE_Resource_Desc_t));
}

// HGE_Resource_Desc_t
void HGE_Resource_Desc_Free(HGE_Resource_Desc_t *desc) {
	free(desc);
}

void HGE_Resource_Desc_Release(HGE_Resource_Desc_t *desc) {
	desc->rd->Free();
}

DWORD HGE_Resource_Desc_Get(HGE_Resource_Desc_t *desc, HGE_Resource_Manager_t *rm) {
	return desc->rd->Get(rm->rm);
}

// properties
void HGE_Resource_Desc_SetName(HGE_Resource_Desc_t *desc, const char *name) {
	strncpy(desc->rd->name, name, MAXRESCHARS);
}

const char *HGE_Resource_Desc_GetName(HGE_Resource_Desc_t *desc) {
	return desc->rd->name;
}

void HGE_Resource_Desc_SetResourceGroup(HGE_Resource_Desc_t *desc, int resgroup) {
	desc->rd->resgroup = resgroup;
}

int HGE_Resource_Desc_GetResourceGroup(HGE_Resource_Desc_t *desc) {
	return desc->rd->resgroup;
}

void HGE_Resource_Desc_SetHandle(HGE_Resource_Desc_t *desc, size_t handle) {
	desc->rd->handle = handle;
}

size_t HGE_Resource_Desc_GetHandle(HGE_Resource_Desc_t *desc) {
	return desc->rd->handle;
}

void HGE_Resource_Desc_SetNext(HGE_Resource_Desc_t *desc, HGE_Resource_Desc_t *next) {
	desc->rd->next = next->rd;
}

HGE_Resource_Desc_t *HGE_Resource_Desc_GetNext(HGE_Resource_Desc_t *desc) {
	HGE_Resource_Desc_t *r = HGE_Resource_Desc_New();

	r->rd = desc->rd->next;

	return r;
}

// HGE_Resource_Manager_t
HGE_Resource_Manager_t *HGE_Resource_Manager_New(const char *scriptname) {
	HGE_Resource_Manager_t *rm = (HGE_Resource_Manager_t *)malloc(sizeof(HGE_Resource_Manager_t));

	rm->rm = new hgeResourceManager(scriptname);

	return rm;
}

void HGE_Resource_Manager_Free(HGE_Resource_Manager_t *manager) {
	delete manager->rm;
	free(manager);
}

void HGE_Resource_Manager_ChangeScript(HGE_Resource_Manager_t *manager, const char *scriptname) {
	manager->rm->ChangeScript(scriptname);
}

bool HGE_Resource_Manager_Precache(HGE_Resource_Manager_t *manager, int groupid) {
	return manager->rm->Precache(groupid);
}

void HGE_Resource_Manager_Purge(HGE_Resource_Manager_t *manager, int groupid) {
	manager->rm->Purge(groupid);
}

void* HGE_Resource_Manager_GetResource(HGE_Resource_Manager_t *manager, const char *name, int resgroup) {
	return manager->rm->GetResource(name, resgroup);
}

HTEXTURE HGE_Resource_Manager_GetTexture(HGE_Resource_Manager_t *manager, const char *name, int resgroup) {
	return manager->rm->GetTexture(name, resgroup);
}

HEFFECT HGE_Resource_Manager_GetEffect(HGE_Resource_Manager_t *manager, const char *name, int resgroup) {
	return manager->rm->GetEffect(name, resgroup);
}

HMUSIC HGE_Resource_Manager_GetMusic(HGE_Resource_Manager_t *manager, const char *name, int resgroup) {
	return manager->rm->GetMusic(name, resgroup);
}

HSTREAM HGE_Resource_Manager_GetStream(HGE_Resource_Manager_t *manager, const char *name, int resgroup) {
	return manager->rm->GetStream(name, resgroup);
}

HTARGET HGE_Resource_Manager_GetTarget(HGE_Resource_Manager_t *manager, const char *name) {
	return manager->rm->GetTarget(name);
}

HGE_Sprite_t *HGE_Resource_Manager_GetSprite(HGE_Resource_Manager_t *manager, const char *name) {
	HGE_Sprite_t *s = (HGE_Sprite_t *)malloc(sizeof(HGE_Sprite_t));

	s->s = manager->rm->GetSprite(name);

	return s;
}

HGE_Animation_t *HGE_Resource_Manager_GetAnimation(HGE_Resource_Manager_t *manager, const char *name) {
	HGE_Animation_t *a = (HGE_Animation_t *)malloc(sizeof(HGE_Animation_t));

	a->a = manager->rm->GetAnimation(name);

	return a;
}

HGE_Font_t *HGE_Resource_Manager_GetFont(HGE_Resource_Manager_t *manager, const char *name) {
	HGE_Font_t *f = (HGE_Font_t *)malloc(sizeof(HGE_Font_t));

	f->f = manager->rm->GetFont(name);

	return f;
}

HGE_ParticleSystem_t *HGE_Resource_Manager_GetParticleSystem(HGE_Resource_Manager_t *manager, const char *name) {
	HGE_ParticleSystem_t *ps = (HGE_ParticleSystem_t *)malloc(sizeof(HGE_ParticleSystem_t));

	ps->ps = manager->rm->GetParticleSystem(name);

	return ps;
}

HGE_DistortionMesh_t *HGE_Resource_Manager_GetDistortionMesh(HGE_Resource_Manager_t *manager, const char *name) {
	HGE_DistortionMesh_t *dm = (HGE_DistortionMesh_t *)malloc(sizeof(HGE_DistortionMesh_t));

	dm->dm = manager->rm->GetDistortionMesh(name);

	return dm;
}

HGE_StringTable_t *HGE_Resource_Manager_GetStringTable(HGE_Resource_Manager_t *manager, const char *name, int resgroup) {
	HGE_StringTable_t *st = (HGE_StringTable_t *)malloc(sizeof(HGE_StringTable_t));

	st->st = manager->rm->GetStringTable(name, resgroup);

	return st;
}

}
