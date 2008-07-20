/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** Core functions implementation: unix ini file
*/

#include "hge_impl_unix.h"

#if !PLATFORM_UNIX
#error This source file is for Unix and Mac OS X. Use ini.cpp for Windows.
#endif

#if PLATFORM_UNIX

#include <sys/stat.h>

const char *HGE_Impl::_BuildProfilePath(const char *section, const char *name, const char *szIniFile)
{
	// !!! FIXME: not efficient.
	static char path[_MAX_PATH];
	const char *home = getenv("HOME");
	strcpy(path, home);
	mkdir(path, S_IRWXU);

	#if PLATFORM_MACOSX
	strcat(path, "/Library");
	mkdir(path, S_IRWXU);
	strcat(path, "/Application Support");
	mkdir(path, S_IRWXU);
	strcat(path, "/Magic Match");
	mkdir(path, S_IRWXU);
	#else
	strcat(path, ".magicmatch");
	mkdir(path, S_IRWXU);
	#endif

	strcat(path, "/");
	strcat(path, szIniFile);
	mkdir(path, S_IRWXU);
	strcat(path, "/");
	strcat(path, section);
	mkdir(path, S_IRWXU);
	strcat(path, "/");
	strcat(path, name);

	return path;
}

bool HGE_Impl::_WritePrivateProfileString(const char *section, const char *name, const char *buf, const char *szIniFile)
{
	const char *path = _BuildProfilePath(section, name, szIniFile);
	FILE *io = fopen(path, "wb");
	if (io == NULL)
		return false;
	const size_t rc = fwrite(buf, strlen(buf), 1, io);
	if (fclose(io) == EOF)
		return false;
	return (rc == 1);
}

bool HGE_Impl::_GetPrivateProfileString(const char *section, const char *name, const char *deflt, char *buf, size_t bufsize, const char *szIniFile)
{
	bool retval = false;
	const char *path = _BuildProfilePath(section, name, szIniFile);
	FILE *io = fopen(path, "rb");
	if (io != NULL)
	{
		const size_t rc = fread(buf, bufsize, 1, io);
		fclose(io);
		retval = (rc == 1);
	}

	if (!retval)
		snprintf(buf, bufsize, "%s", deflt);

	return retval;
}

void CALL HGE_Impl::Ini_SetInt(const char *section, const char *name, int value)
{
	char buf[256];

	if(szIniFile[0]) {
		sprintf(buf,"%d",value);
		_WritePrivateProfileString(section, name, buf, szIniFile);
	}
}


int CALL HGE_Impl::Ini_GetInt(const char *section, const char *name, int def_val)
{
	char buf[256];

	if(szIniFile[0]) {
		if(_GetPrivateProfileString(section, name, "", buf, sizeof(buf), szIniFile))
		{ return atoi(buf); }
		else { return def_val; }
	}
	return def_val;
}


void CALL HGE_Impl::Ini_SetFloat(const char *section, const char *name, float value)
{
	char buf[256];

	if(szIniFile[0]) {
		sprintf(buf,"%f",value);
		_WritePrivateProfileString(section, name, buf, szIniFile);
	}
}


float CALL HGE_Impl::Ini_GetFloat(const char *section, const char *name, float def_val)
{
	char buf[256];

	if(szIniFile[0]) {
		if(_GetPrivateProfileString(section, name, "", buf, sizeof(buf), szIniFile))
		{ return (float)atof(buf); }
		else { return def_val; }
	}
	return def_val;
}


void CALL HGE_Impl::Ini_SetString(const char *section, const char *name, const char *value)
{
	if(szIniFile[0]) _WritePrivateProfileString(section, name, value, szIniFile);
}


char* CALL HGE_Impl::Ini_GetString(const char *section, const char *name, const char *def_val)
{
	if(szIniFile[0]) _GetPrivateProfileString(section, name, def_val, szIniString, sizeof(szIniString), szIniFile);
	else strcpy(szIniString, def_val);
	return szIniString;
}

#endif  // PLATFORM_UNIX


