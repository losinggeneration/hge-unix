/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** Core functions implementation: power status
*/


#include "hge_impl_unix.h"

#if !PLATFORM_UNIX
#error This source file is for Unix and Mac OS X. Use power.cpp for Windows.
#endif

#if PLATFORM_UNIX

void HGE_Impl::_InitPowerStatus()
{
	nPowerStatus = HGEPWR_UNSUPPORTED;
}

void HGE_Impl::_UpdatePowerStatus()
{
	nPowerStatus = HGEPWR_UNSUPPORTED;
}

void HGE_Impl::_DonePowerStatus()
{
	nPowerStatus = HGEPWR_UNSUPPORTED;
}

#endif

