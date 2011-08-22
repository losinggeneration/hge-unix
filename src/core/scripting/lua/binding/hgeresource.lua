--
-- Haaf's Game Engine 1.7
-- Copyright (C) 2003-2007, Relish Games
-- hge.relishgames.com
--
-- hgeResourceManager helper class header
--

array.pushBack(gen_lua.number_types, 'size_t')

bindhgeResource = {
	classes = {
-- Not needed?
-- 		{
-- 			name = 'hge.ResDesc',
-- 			className = 'ResDesc',
-- 			ctors = {
-- 				'()',
-- 			},
-- 			properties = {
-- -- 				'char * name',
-- 				'int resgroup',
-- 				'size_t handle',
-- 				'ResDesc * next',
-- 			},
-- 			memberFunctions = {
-- 				{rename = 'get', 'DWORD Get(hgeResourceManager *rm);'},
-- 				{rename = 'free', 'void  Free();'},
-- 			},
-- 		},
		{
			name = 'hge.ResourceManager',
			className = 'hgeResourceManager',
			ctors = {
				'(const char *scriptname)',
			},
-- 			properties = {
-- 				'ResDesc* res[RESTYPES]',
-- 			},
			memberFunctions = {
				{ rename = 'changescript', 'void ChangeScript(const char *scriptname);'},
				{ rename = 'precache', 'bool Precache(int groupid)' },
				{ rename = 'purge', 'void Purge(int groupid)' },

-- 				{ rename = 'getresource', 'void* GetResource(const char *name, int resgroup)' },
-- 				{ rename = 'gettexture', 'HTEXTURE GetTexture(const char *name, int resgroup)' },
-- 				{ rename = 'geteffect', 'HEFFECT GetEffect(const char *name, int resgroup)' },
-- 				{ rename = 'getmusic', 'HMUSIC GetMusic(const char *name, int resgroup)' },
-- 				{ rename = 'getstream', 'HSTREAM GetStream(const char *name, int resgroup)' },
-- 				{ rename = 'gettarget', 'HTARGET GetTarget(const char *name)' },

-- 				{ rename = 'getsprite', 'hgeSprite* GetSprite(const char *name)' },
-- 				{ rename = 'getanimation', 'hgeAnimation* GetAnimation(const char *name)' },
-- 				{ rename = 'getfont', 'hgeFont* GetFont(const char *name)' },
-- 				{ rename = 'getparticlesystem', 'hgeParticleSystem* GetParticleSystem(const char *name)' },
-- 				{ rename = 'getdistortionmesh', 'hgeDistortionMesh* GetDistortionMesh(const char *name)' },
				{ rename = 'getstringtable', 'hgeStringTable* GetStringTable(const char *name, int resgroup)' },
			},
		},
	},
	modules = {
	},
}

--[[

#include "hge.h"
#include "hgesprite.h"
#include "hgeanim.h"
#include "hgefont.h"
#include "hgeparticle.h"
#include "hgedistort.h"
#include "hgestrings.h"


#define RESTYPES 13
#define MAXRESCHARS 128

class hgeResourceManager;

struct ResDesc
{
	char		name[MAXRESCHARS];
	int			resgroup;
	size_t		handle;
	ResDesc*	next;

	ResDesc()	{ hge=hgeCreate(HGE_VERSION); }
	~ResDesc()	{ hge->Release(); }

	virtual DWORD Get(hgeResourceManager *rm) = 0;
	virtual void  Free() = 0;

protected:
	static HGE	*hge;
};

/*
** HGE Resource manager class
*/
class hgeResourceManager
{
public:
	hgeResourceManager(const char *scriptname=0);
	~hgeResourceManager();

	void				ChangeScript(const char *scriptname=0);
	bool				Precache(int groupid=0);
	void				Purge(int groupid=0);

	void*				GetResource(const char *name, int resgroup=0);
	HTEXTURE			GetTexture(const char *name, int resgroup=0);
	HEFFECT				GetEffect(const char *name, int resgroup=0);
	HMUSIC				GetMusic(const char *name, int resgroup=0);
	HSTREAM				GetStream(const char *name, int resgroup=0);
	HTARGET				GetTarget(const char *name);

	hgeSprite*			GetSprite(const char *name);
	hgeAnimation*		GetAnimation(const char *name);
	hgeFont*			GetFont(const char *name);
	hgeParticleSystem*	GetParticleSystem(const char *name);
	hgeDistortionMesh*	GetDistortionMesh(const char *name);
	hgeStringTable*		GetStringTable(const char *name, int resgroup=0);

	ResDesc*			res[RESTYPES];
};

--]]
