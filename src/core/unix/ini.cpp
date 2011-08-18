/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** Core functions implementation: unix ini file
*/

#include "hge_impl.h"

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
	strcat(path, "/");
	strcat(path, szWinTitle);
	mkdir(path, S_IRWXU);
	#else
	strcat(path, "/.");
	strcat(path, szWinTitle);
	mkdir(path, S_IRWXU);
	#endif

	strcat(path, "/inis");
	mkdir(path, S_IRWXU);

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
		const size_t rc = fread(buf, 1, bufsize-1, io);
		retval = (ferror(io) == 0);
		fclose(io);
		if (retval)
			buf[rc] = '\0';
	}

	if (!retval)
		snprintf(buf, bufsize, "%s", deflt);

	return retval;
}

// We parse the usual .ini files, and build them into our directory tree when items don't exist.
// !!! FIXME: this code sort of stinks. In fact, the whole directory tree thing could be a mistake...
void HGE_Impl::_LoadIniFile(const char *fname)
{
	char section[128] = { 0 };
	struct stat statbuf;
	if (stat(fname, &statbuf) == -1)
		return;
	FILE *io = fopen(fname, "rb");
	char *buf = new char[statbuf.st_size + 1];
	size_t rc = fread(buf, statbuf.st_size, 1, io);
	buf[statbuf.st_size] = '\0';
	fclose(io);
	if (rc == 1)
	{
		char *start = buf;
		char *ptr = start;
		while (start <= (buf + statbuf.st_size))
		{
			while ((*ptr != '\r') && (*ptr != '\n') && (*ptr != '\0'))
				ptr++;
			*ptr = '\0';

			while ((*start == ' ') || (*start == '\t') || (*start == '\r') || (*start == '\n'))
				start++;

			if ((*start == ';') || (*start == '\0'))  // comment or empty line.
				;
			else if (*start == '[')  // section
			{
				start++;
				char *end = strchr(start, ']');
				if (end != NULL)
				{
					*end = '\0';
					snprintf(section, sizeof (section), "%s", start);
				}
			}
			else if (section[0] != '\0')
			{
				char *eq = strchr(start, '=');
				if (eq != NULL)
				{
					*eq = '\0';
					eq++;
					char tmpbuf[128];
					if (!_GetPrivateProfileString(section, start, "", tmpbuf, sizeof (tmpbuf), fname))
						_WritePrivateProfileString(section, start, eq, fname);
				}
			}
			ptr++;
			start = ptr;
		}
	}
	delete[] buf;
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
