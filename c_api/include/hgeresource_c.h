#ifndef HGE_RESOURCE_C_H
#define HGE_RESOURCE_C_H

#include "unix_compat.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HGE_RESTYPES 13
#define HGE_MAXRESCHARS 128

typedef struct HGE_Resource_Manager_s HGE_Resource_Manager_t;
typedef struct HGE_Resource_Desc_s HGE_Resource_Desc_t;

// external structures
typedef struct HGE_Animation_s HGE_Animation_t;
typedef struct HGE_DistortionMesh_s HGE_DistortionMesh_t;
typedef struct HGE_Font_s HGE_Font_t;
typedef struct HGE_ParticleSystem_s HGE_ParticleSystem_t;
typedef struct HGE_Sprite_s HGE_Sprite_t;
typedef struct HGE_StringTable_s HGE_StringTable_t;

// HGE_Resource_Desc_t
HGE_Resource_Desc_t *HGE_Resource_Desc_New();
void HGE_Resource_Desc_Free(HGE_Resource_Desc_t *desc);
DWORD HGE_Resource_Desc_Get(HGE_Resource_Manager_t *rm);

// properties
void HGE_Resource_Desc_SetName(HGE_Resource_Manager_t *rm, const char *name);
const char *HGE_Resource_Desc_GetName(HGE_Resource_Manager_t *rm);
void HGE_Resource_Desc_SetResourceGroup(HGE_Resource_Manager_t *rm, int resgroup);
int HGE_Resource_Desc_GetResourceGroup(HGE_Resource_Manager_t *rm);
void HGE_Resource_Desc_SetHandle(HGE_Resource_Manager_t *rm, size_t handle);
size_t HGE_Resource_Desc_GetHandle(HGE_Resource_Manager_t *rm);
void HGE_Resource_Desc_SetNext(HGE_Resource_Manager_t *rm, HGE_Resource_Desc_t *next);
HGE_Resource_Desc_t *HGE_Resource_Desc_GetNext(HGE_Resource_Manager_t *rm);

// HGE_Resource_Manager_t
HGE_Resource_Manager_t *HGE_Resource_Manager_New(const char *scriptname);
void HGE_Resource_Manager_Free(HGE_Resource_Manager_t *manager);

HGE_Resource_Desc_t *HGE_Resource_Manager_GetResources(HGE_Resource_Manager_t *manager);
void HGE_Resource_Manager_SetResources(HGE_Resource_Manager_t *manager, HGE_Resource_Desc_t *resources);

void HGE_Resource_Manager_ChangeScript(HGE_Resource_Manager_t *manager, const char *scriptname);
bool HGE_Resource_Manager_Precache(HGE_Resource_Manager_t *manager, int groupid);
void HGE_Resource_Manager_Purge(HGE_Resource_Manager_t *manager, int groupid);

void* HGE_Resource_Manager_GetResource(HGE_Resource_Manager_t *manager, const char *name, int resgroup);
HTEXTURE HGE_Resource_Manager_GetTexture(HGE_Resource_Manager_t *manager, const char *name, int resgroup);
HEFFECT HGE_Resource_Manager_GetEffect(HGE_Resource_Manager_t *manager, const char *name, int resgroup);
HMUSIC HGE_Resource_Manager_GetMusic(HGE_Resource_Manager_t *manager, const char *name, int resgroup);
HSTREAM HGE_Resource_Manager_GetStream(HGE_Resource_Manager_t *manager, const char *name, int resgroup);
HTARGET HGE_Resource_Manager_GetTarget(HGE_Resource_Manager_t *manager, const char *name);

HGE_Sprite_t *HGE_Resource_Manager_GetSprite(HGE_Resource_Manager_t *manager, const char *name);
HGE_Animation_t *HGE_Resource_Manager_GetAnimation(HGE_Resource_Manager_t *manager, const char *name);
HGE_Font_t *HGE_Resource_Manager_GetFont(HGE_Resource_Manager_t *manager, const char *name);
HGE_ParticleSystem_t *HGE_Resource_Manager_GetParticleSystem(HGE_Resource_Manager_t *manager, const char *name);
HGE_DistortionMesh_t *HGE_Resource_Manager_GetDistortionMesh(HGE_Resource_Manager_t *manager, const char *name);
HGE_StringTable_t *HGE_Resource_Manager_GetStringTable(HGE_Resource_Manager_t *manager, const char *name, int resgroup);

#ifdef __cplusplus
}
#endif

#endif
