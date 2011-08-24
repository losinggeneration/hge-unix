-- PLEASE NOTE that this is not the 1.81 version of hgeparticle.h ...
--  the game I'm working on used an older HGE that breaks with the 1.81
--  particle system. If you want 1.81, add the "bRelative" stuff to it.  --ryan.

--
-- Haaf's Game Engine 1.61
-- Copyright (C) 2003-2007, Relish Games
-- hge.relishgames.com
--
-- hgeParticleSystem helper class header
--

array.pushBack(gen_lua.number_types,  'BYTE')

bindhgeParticle = {
	classes = {
		{
			name = 'hge.Particle',
			className = 'hgeParticle',
			ctors = {
				'()'
			},
			properties = {
				'hgeVector vecLocation;',
				'hgeVector vecVelocity;',

				'float fGravity;',
				'float fRadialAccel;',
				'float fTangentialAccel;',

				'float fSpin;',
				'float fSpinDelta;',

				'float fSize;',
				'float fSizeDelta;',

-- 				'hgeColor colColor;',
-- 				'hgeColor colColorDelta;',
				'',
				'float fAge;',
				'float fTerminalAge;',
			},
		},
		{
			name = 'hge.Particle.SystemInfo',
			className = 'hgeParticleSystemInfo',
			ctors = {
				'()',
			},
			properties = {
				'hgeSprite* sprite;',
				'int nEmission;',
				'float fLifetime;',

				'float fParticleLifeMin;',
				'float fParticleLifeMax;',

				'float fDirection;',
				'float fSpread;',
				'BYTE bRelative;',

				'float fSpeedMin;',
				'float fSpeedMax;',

				'float fGravityMin;',
				'float fGravityMax;',

				'float fRadialAccelMin;',
				'float fRadialAccelMax;',

				'float fTangentialAccelMin;',
				'float fTangentialAccelMax;',

				'float fSizeStart;',
				'float fSizeEnd;',
				'float fSizeVar;',

				'float fSpinStart;',
				'float fSpinEnd;',
				'float fSpinVar;',

-- 				'hgeColor colColorStart;',
-- 				'hgeColor colColorEnd;',
				'float fColorVar;',
				'float fAlphaVar;',
			},
		},
		{
			name = 'hge.Partile.System',
			className =  'hgeParticleSystem',
			properties = {
				'hgeParticleSystemInfo info;',
			},
			ctors = {
				'(const char *filename, hgeSprite *sprite, float fps);',
				'(hgeParticleSystemInfo *psi, float fps);',
				'(const hgeParticleSystem &ps);',
			},
			memberFunctions =  {
				-- in header, but wasn't implemented
-- 				{ 'hgeParticleSystem& operator= (const hgeParticleSystem &ps);' },

				{ 'void Render();' },
				{ 'void FireAt(float x, float y);' },
				{ 'void Fire();' },
				{ 'void Stop(bool bKillParticles);' },
				{ 'void Update(float fDeltaTime);' },
				{ 'void MoveTo(float x, float y, bool bMoveParticles);' },
				{ 'void Transpose(float x, float y);' },
				{ 'void TrackBoundingBox(bool bTrack);' },

				{ 'int GetParticlesAlive() const;' },
				{ 'float GetAge() const;' },
-- 				{ 'void GetPosition(float *x, float *y) const;' },
-- 				{ 'void GetTransposition(float *x, float *y) const;' },
				{ 'hgeRect* GetBoundingBox(hgeRect *rect) const;' },
			},
		},
		{
			name = 'hge.Partile.Manager',
			className = 'hgeParticleManager',
			ctors = {
				'(float fps);',
			},
			memberFunctions = {
				{ 'void Update(float dt);' },
				{ 'void Render();' },

				{ 'hgeParticleSystem* SpawnPS(hgeParticleSystemInfo *psi, float x, float y);' },
				{ 'bool IsPSAlive(hgeParticleSystem *ps) const;' },
				{ 'void Transpose(float x, float y);' },
-- 				{ 'void GetTransposition(float *dx, float *dy) const;' },
				{ 'void KillPS(hgeParticleSystem *ps);' },
				{ 'void KillAll();' },
			},
		},
	},
	modules = {
	},
}

--[[

#define MAX_PARTICLES	500
#define MAX_PSYSTEMS	100

--]]
