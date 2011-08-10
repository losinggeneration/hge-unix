// PLEASE NOTE that this is not the 1.81 version of hgeparticle.cpp ...
//  the game I'm working on used an older HGE that breaks with the 1.81
//  particle system. If you want 1.81, add the "byteswap" stuff to it.  --ryan.

/*
** Haaf's Game Engine 1.61
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** hgeParticleSystem helper class implementation
*/


#include "../../include/hgeparticle.h"

HGE	*hgeParticleSystem::hge=0;

hgeParticleSystem::hgeParticleSystem(const char *filename, hgeSprite *sprite, float fps)
{
	void *psi;

	hge=hgeCreate(HGE_VERSION);

	psi=hge->Resource_Load(filename);
	if(!psi) return;

	char *ptr = (char *) psi;
	memset(&info, '\0', sizeof (info));
	info.sprite = sprite;
	ptr += 4;  // skip these bytes.

	#define SETMEMBER(typ, x) \
		{ info.x = *((const typ *) ptr); ptr += sizeof (typ); BYTESWAP(info.x); }
	SETMEMBER(int, nEmission);
	SETMEMBER(float, fLifetime);
	SETMEMBER(float, fParticleLifeMin);
	SETMEMBER(float, fParticleLifeMax);
	SETMEMBER(float, fDirection);
	SETMEMBER(float, fSpread);
	SETMEMBER(BYTE, bRelative);
	ptr += 3;  // padding.
	SETMEMBER(float, fSpeedMin);
	SETMEMBER(float, fSpeedMax);
	SETMEMBER(float, fGravityMin);
	SETMEMBER(float, fGravityMax);
	SETMEMBER(float, fRadialAccelMin);
	SETMEMBER(float, fRadialAccelMax);
	SETMEMBER(float, fTangentialAccelMin);
	SETMEMBER(float, fTangentialAccelMax);
	SETMEMBER(float, fSizeStart);
	SETMEMBER(float, fSizeEnd);
	SETMEMBER(float, fSizeVar);
	SETMEMBER(float, fSpinStart);
	SETMEMBER(float, fSpinEnd);
	SETMEMBER(float, fSpinVar);
	SETMEMBER(float, colColorStart.r);
	SETMEMBER(float, colColorStart.g);
	SETMEMBER(float, colColorStart.b);
	SETMEMBER(float, colColorStart.a);
	SETMEMBER(float, colColorEnd.r);
	SETMEMBER(float, colColorEnd.g);
	SETMEMBER(float, colColorEnd.b);
	SETMEMBER(float, colColorEnd.a);
	SETMEMBER(float, fColorVar);
	SETMEMBER(float, fAlphaVar);
	#undef SETMEMBER

	hge->Resource_Free(psi);

	vecLocation.x=vecPrevLocation.x=0.0f;
	vecLocation.y=vecPrevLocation.y=0.0f;
	fTx=fTy=0;

	fEmissionResidue=0.0f;
	nParticlesAlive=0;
	fAge=-2.0;
	if(fps!=0.0f) fUpdSpeed=1.0f/fps;
	else fUpdSpeed=0.0f;
	fResidue=0.0f;

	rectBoundingBox.Clear();
	bUpdateBoundingBox=false;
}

hgeParticleSystem::hgeParticleSystem(hgeParticleSystemInfo *psi, float fps)
{
	hge=hgeCreate(HGE_VERSION);

	memcpy(&info, psi, sizeof(hgeParticleSystemInfo));

	vecLocation.x=vecPrevLocation.x=0.0f;
	vecLocation.y=vecPrevLocation.y=0.0f;
	fTx=fTy=0;

	fEmissionResidue=0.0f;
	nParticlesAlive=0;
	fAge=-2.0;
	if(fps!=0.0f) fUpdSpeed=1.0f/fps;
	else fUpdSpeed=0.0f;
	fResidue=0.0f;

	rectBoundingBox.Clear();
	bUpdateBoundingBox=false;
}

hgeParticleSystem::hgeParticleSystem(const hgeParticleSystem &ps)
{
	memcpy(this, &ps, sizeof(hgeParticleSystem));
	hge=hgeCreate(HGE_VERSION);
}

void hgeParticleSystem::Update(float fDeltaTime)
{
   if(fUpdSpeed==0.0f) _update(fDeltaTime);
   else
   {
      fResidue+=fDeltaTime;
      if(fResidue>=fUpdSpeed)
	  {
			_update(fUpdSpeed);
			while(fResidue>=fUpdSpeed) fResidue-=fUpdSpeed;
	  }
   }
}

void hgeParticleSystem::_update(float fDeltaTime)
{
	int i;
	float ang;
	hgeParticle *par;
	hgeVector vecAccel, vecAccel2;

	if(fAge >= 0)
	{
		fAge += fDeltaTime;
		if(fAge >= info.fLifetime) fAge = -2.0f;
	}

	// update all alive particles

	if(bUpdateBoundingBox) rectBoundingBox.Clear();
	par=particles;

	for(i=0; i<nParticlesAlive; i++)
	{
		par->fAge += fDeltaTime;
		if(par->fAge >= par->fTerminalAge)
		{
			nParticlesAlive--;
			memcpy(par, &particles[nParticlesAlive], sizeof(hgeParticle));
			i--;
			continue;
		}

		vecAccel = par->vecLocation-vecLocation;
		vecAccel.Normalize();
		vecAccel2 = vecAccel;
		vecAccel *= par->fRadialAccel;

		// vecAccel2.Rotate(M_PI_2);
		// the following is faster
		ang = vecAccel2.x;
		vecAccel2.x = -vecAccel2.y;
		vecAccel2.y = ang;

		vecAccel2 *= par->fTangentialAccel;
		par->vecVelocity += (vecAccel+vecAccel2)*fDeltaTime;
		par->vecVelocity.y += par->fGravity*fDeltaTime;

		par->vecLocation += par->vecVelocity;

		par->fSpin += par->fSpinDelta*fDeltaTime;
		par->fSize += par->fSizeDelta*fDeltaTime;
		par->colColor += par->colColorDelta*fDeltaTime;

		if(bUpdateBoundingBox) rectBoundingBox.Encapsulate(par->vecLocation.x, par->vecLocation.y);

		par++;
	}

	// generate new particles

	if(fAge != -2.0f)
	{
		float fParticlesNeeded = info.nEmission*fDeltaTime + fEmissionResidue;
		int nParticlesCreated = (unsigned int)fParticlesNeeded;
		fEmissionResidue=fParticlesNeeded-nParticlesCreated;

		par=&particles[nParticlesAlive];

		for(i=0; i<nParticlesCreated; i++)
		{
			if(nParticlesAlive>=MAX_PARTICLES) break;

			par->fAge = 0.0f;
			par->fTerminalAge = hge->Random_Float(info.fParticleLifeMin, info.fParticleLifeMax);

			par->vecLocation = vecPrevLocation+(vecLocation-vecPrevLocation)*hge->Random_Float(0.0f, 1.0f);
			par->vecLocation.x += hge->Random_Float(-2.0f, 2.0f);
			par->vecLocation.y += hge->Random_Float(-2.0f, 2.0f);

			ang=info.fDirection-M_PI_2+hge->Random_Float(0,info.fSpread)-info.fSpread/2.0f;
			if(info.bRelative) ang += (vecPrevLocation-vecLocation).Angle()+M_PI_2;
			par->vecVelocity.x = cosf(ang);
			par->vecVelocity.y = sinf(ang);
			par->vecVelocity *= hge->Random_Float(info.fSpeedMin, info.fSpeedMax);

			par->fGravity = hge->Random_Float(info.fGravityMin, info.fGravityMax);
			par->fRadialAccel = hge->Random_Float(info.fRadialAccelMin, info.fRadialAccelMax);
			par->fTangentialAccel = hge->Random_Float(info.fTangentialAccelMin, info.fTangentialAccelMax);

			par->fSize = hge->Random_Float(info.fSizeStart, info.fSizeStart+(info.fSizeEnd-info.fSizeStart)*info.fSizeVar);
			par->fSizeDelta = (info.fSizeEnd-par->fSize) / par->fTerminalAge;

			par->fSpin = hge->Random_Float(info.fSpinStart, info.fSpinStart+(info.fSpinEnd-info.fSpinStart)*info.fSpinVar);
			par->fSpinDelta = (info.fSpinEnd-par->fSpin) / par->fTerminalAge;

			par->colColor.r = hge->Random_Float(info.colColorStart.r, info.colColorStart.r+(info.colColorEnd.r-info.colColorStart.r)*info.fColorVar);
			par->colColor.g = hge->Random_Float(info.colColorStart.g, info.colColorStart.g+(info.colColorEnd.g-info.colColorStart.g)*info.fColorVar);
			par->colColor.b = hge->Random_Float(info.colColorStart.b, info.colColorStart.b+(info.colColorEnd.b-info.colColorStart.b)*info.fColorVar);
			par->colColor.a = hge->Random_Float(info.colColorStart.a, info.colColorStart.a+(info.colColorEnd.a-info.colColorStart.a)*info.fAlphaVar);

			par->colColorDelta.r = (info.colColorEnd.r-par->colColor.r) / par->fTerminalAge;
			par->colColorDelta.g = (info.colColorEnd.g-par->colColor.g) / par->fTerminalAge;
			par->colColorDelta.b = (info.colColorEnd.b-par->colColor.b) / par->fTerminalAge;
			par->colColorDelta.a = (info.colColorEnd.a-par->colColor.a) / par->fTerminalAge;

			if(bUpdateBoundingBox) rectBoundingBox.Encapsulate(par->vecLocation.x, par->vecLocation.y);

			nParticlesAlive++;
			par++;
		}
	}

	vecPrevLocation=vecLocation;
}

void hgeParticleSystem::MoveTo(float x, float y, bool bMoveParticles)
{
	int i;
	float dx,dy;
	
	if(bMoveParticles)
	{
		dx=x-vecLocation.x;
		dy=y-vecLocation.y;

		for(i=0;i<nParticlesAlive;i++)
		{
			particles[i].vecLocation.x += dx;
			particles[i].vecLocation.y += dy;
		}

		vecPrevLocation.x=vecPrevLocation.x + dx;
		vecPrevLocation.y=vecPrevLocation.y + dy;
	}
	else
	{
		if(fAge==-2.0) { vecPrevLocation.x=x; vecPrevLocation.y=y; }
		else { vecPrevLocation.x=vecLocation.x;	vecPrevLocation.y=vecLocation.y; }
	}

	vecLocation.x=x;
	vecLocation.y=y;
}

void hgeParticleSystem::FireAt(float x, float y)
{
	Stop();
	MoveTo(x,y);
	Fire();
}

void hgeParticleSystem::Fire()
{
	if(info.fLifetime==-1.0f) fAge=-1.0f;
	else fAge=0.0f;
	fResidue=0.0;
}

void hgeParticleSystem::Stop(bool bKillParticles)
{
	fAge=-2.0f;
	if(bKillParticles) 
	{
		nParticlesAlive=0;
		rectBoundingBox.Clear();
	}
}

void hgeParticleSystem::Render()
{
	int i;
	DWORD col;
	hgeParticle *par=particles;

	col=info.sprite->GetColor();

	for(i=0; i<nParticlesAlive; i++)
	{
		info.sprite->SetColor(par->colColor.GetHWColor());
		info.sprite->RenderEx(par->vecLocation.x+fTx, par->vecLocation.y+fTy, par->fSpin*par->fAge, par->fSize);
		par++;
	}

	info.sprite->SetColor(col);
}

