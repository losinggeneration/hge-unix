/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** Copyright (C) 2014 Harley Laue <losinggeneration@gmail.com>
** hge.relishgames.com
**
** Core functions implementation: power status
*/

#include "hge_impl.h"

void HGE_Impl::_InitPowerStatus()
{
	_UpdatePowerStatus();
}

void HGE_Impl::_UpdatePowerStatus()
{
	SDL_PowerState pwst;
	int pct;
	pwst = SDL_GetPowerInfo(NULL, &pct);
	switch(pwst) {
		case SDL_POWERSTATE_UNKNOWN:
			nPowerStatus = HGEPWR_UNSUPPORTED;
			break;
		case SDL_POWERSTATE_ON_BATTERY:
			/*
			 * If SDL couldn't get the value for pct it's going to be -1, which
			 * is HGEPWR_AC. That's not really correcrt, but it should be fine.
			 */
			nPowerStatus = pct;
			break;
		case SDL_POWERSTATE_CHARGED:
		case SDL_POWERSTATE_NO_BATTERY:
		case SDL_POWERSTATE_CHARGING:
			nPowerStatus = HGEPWR_AC;
			break;
		default:
			nPowerStatus = HGEPWR_UNSUPPORTED;
			break;
	}
}

void HGE_Impl::_DonePowerStatus()
{
	// Nothing to do
}
