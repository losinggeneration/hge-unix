/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** Core functions implementation: resources management
*/

#include "hge_impl.h"

#ifndef strupr
void strupr(char *s) {
	while(*s) {
		*s = toupper(*s);
		s++;
	}
}
#endif

#include <zlib.h>  // the system version is better here. HGE's is out of date.

#define NOCRYPT
//#define NOUNCRYPT
#include "ZLIB/unzip.h"


bool CALL HGE_Impl::Resource_AttachPack(const char *filename, const char *password)
{
	char *szName;
	CResourceList *resItem=res;
	unzFile zip;

	szName=Resource_MakePath(filename);
	strupr(szName);

	while(resItem)
	{
		if(!strcmp(szName,resItem->filename)) return false;
		resItem=resItem->next;
	}

	zip=unzOpen(szName);
	if(!zip) return false;
	unzClose(zip);

	resItem=new CResourceList;
	strcpy(resItem->filename, szName);
	if(password) strcpy(resItem->password, password);
	else resItem->password[0]=0;
	resItem->next=res;
	res=resItem;

	return true;
}

void CALL HGE_Impl::Resource_RemovePack(const char *filename)
{
	char *szName;
	CResourceList *resItem=res, *resPrev=0;

	szName=Resource_MakePath(filename);
	strupr(szName);

	while(resItem)
	{
		if(!strcmp(szName,resItem->filename))
		{
			if(resPrev) resPrev->next=resItem->next;
			else res=resItem->next;
			delete resItem;
			break;
		}

		resPrev=resItem;
		resItem=resItem->next;
	}
}

void CALL HGE_Impl::Resource_RemoveAllPacks()
{
	CResourceList *resItem=res, *resNextItem;

	while(resItem)
	{
		resNextItem=resItem->next;
		delete resItem;
		resItem=resNextItem;
	}

	res=0;
}

void* CALL HGE_Impl::Resource_Load(const char *filename, DWORD *size)
{
	const char *res_err="Can't load resource: %s";

	CResourceList *resItem=res;
	char szName[_MAX_PATH];
	char szZipName[_MAX_PATH];
	unzFile zip;
	unz_file_info file_info;
	int done, i;
	void *ptr;
	FILE *hF;

	if(filename[0]=='\\' || filename[0]=='/' || filename[1]==':') goto _fromfile; // skip absolute paths

	// Load from pack

	strcpy(szName,filename);
	strupr(szName);
	for(i=0; szName[i]; i++) { if(szName[i]=='/') szName[i]='\\'; }

	while(resItem)
	{
		zip=unzOpen(resItem->filename);
		done=unzGoToFirstFile(zip);
		while(done==UNZ_OK)
		{
			unzGetCurrentFileInfo(zip, &file_info, szZipName, sizeof(szZipName), NULL, 0, NULL, 0);
			strupr(szZipName);
			for(i=0; szZipName[i]; i++)	{ if(szZipName[i]=='/') szZipName[i]='\\'; }
			if(!strcmp(szName,szZipName))
			{
				if(unzOpenCurrentFilePassword(zip, resItem->password[0] ? resItem->password : 0) != UNZ_OK)
				{
					unzClose(zip);
					sprintf(szName, res_err, filename);
					_PostError(szName);
					return 0;
				}

				ptr = malloc(file_info.uncompressed_size);
				if(!ptr)
				{
					unzCloseCurrentFile(zip);
					unzClose(zip);
					sprintf(szName, res_err, filename);
					_PostError(szName);
					return 0;
				}

				if(unzReadCurrentFile(zip, ptr, file_info.uncompressed_size) < 0)
				{
					unzCloseCurrentFile(zip);
					unzClose(zip);
					free(ptr);
					sprintf(szName, res_err, filename);
					_PostError(szName);
					return 0;
				}
				unzCloseCurrentFile(zip);
				unzClose(zip);
				if(size) *size=file_info.uncompressed_size;
				return ptr;
			}

			done=unzGoToNextFile(zip);
		}

		unzClose(zip);
		resItem=resItem->next;
	}

	// Load from file
_fromfile:

	hF = fopen(Resource_MakePath(filename), "rb");
	if(hF == NULL)
	{
		sprintf(szName, res_err, filename);
		_PostError(szName);
		return 0;
	}

	struct stat statbuf;
	if (fstat(fileno(hF), &statbuf) == -1)
	{
		fclose(hF);
		sprintf(szName, res_err, filename);
		_PostError(szName);
		return 0;
	}

	file_info.uncompressed_size = statbuf.st_size;
	ptr = malloc(file_info.uncompressed_size);
	if(!ptr)
	{
		fclose(hF);
		sprintf(szName, res_err, filename);
		_PostError(szName);
		return 0;
	}
	if(fread(ptr, file_info.uncompressed_size, 1, hF) != 1)
	{
		fclose(hF);
		free(ptr);
		sprintf(szName, res_err, filename);
		_PostError(szName);
		return 0;
	}

	fclose(hF);

	if(size) *size=file_info.uncompressed_size;
	return ptr;
}


void CALL HGE_Impl::Resource_Free(void *res)
{
	if(res) free(res);
}

// this is from PhysicsFS originally ( http://icculus.org/physfs/ )
//  (also zlib-licensed.)
static int locateOneElement(char *buf)
{
	char *ptr = NULL;
	DIR *dirp = NULL;
	struct dirent *dent = NULL;

	if (access(buf, F_OK) == 0)
		return 1;  /* quick rejection: exists in current case. */

	ptr = strrchr(buf, '/');  /* find entry at end of path. */
	if (ptr == NULL)
	{
		dirp = opendir(".");
		ptr = buf;
	}
	else
	{
		*ptr = '\0';
		dirp = opendir(buf);
		*ptr = '/';
		ptr++;  /* point past dirsep to entry itself. */
	}

	while ((dent = readdir(dirp)) != NULL)
	{
		if (strcasecmp(dent->d_name, ptr) == 0)
		{
			strcpy(ptr, dent->d_name); /* found a match. Overwrite with this case. */
			closedir(dirp);
			return 1;
		}
	}

	/* no match at all... */
	closedir(dirp);
	return 0;
}

static int locateCorrectCase(char *buf)
{
	char *ptr = buf;
	char *prevptr = buf;

	while (ptr = strchr(ptr + 1, '/'))
	{
		*ptr = '\0';  /* block this path section off */
		if (!locateOneElement(buf))
		{
			*ptr = '/'; /* restore path separator */
			return -2;  /* missing element in path. */
		}
		*ptr = '/'; /* restore path separator */
	}

	/* check final element... */
	return locateOneElement(buf) ? 0 : -1;
}

char* CALL HGE_Impl::Resource_MakePath(const char *filename)
{
	int i;

	if(!filename)
		strcpy(szTmpFilename, szAppPath);
	else if(filename[0]=='\\' || filename[0]=='/' || filename[1]==':')
		strcpy(szTmpFilename, filename);
	else
	{
		strcpy(szTmpFilename, szAppPath);
		if(filename) strcat(szTmpFilename, filename);
	}

	for(i=0; szTmpFilename[i]; i++) { if(szTmpFilename[i]=='\\') szTmpFilename[i]='/'; }

	locateCorrectCase(szTmpFilename);

	return szTmpFilename;
}

// !!! FIXME: kinda messy, and probably doesn't get all the corner cases right.
bool HGE_Impl::_WildcardMatch(const char *str, const char *wildcard)
{
	if ((str == NULL) || (wildcard == NULL))
		return false;

	while ((*str) && (*wildcard))
	{
		const char wildch = *wildcard;
		const char strch = *str;
		if (wildch == '?')
			; // okay.
		else if (wildch == '*')
		{
			do {
				wildcard++;
			} while (((*wildcard == '*') || (*wildcard == '?')) && (*wildcard != '\0'));
			const char newwild = *wildcard;
			if (newwild == '\0') return true;
			const char *ptr = str;
			while (*ptr)  // find the greediest match possible...
			{
				if (*ptr == newwild)
					str = ptr;
				ptr++;
			}
		}
		else if ( (toupper(strch)) != (toupper(wildch)) )
		{
			return false;
		}

		str++;
		wildcard++;
	}

	while (*wildcard == '*')
		wildcard++;

	return ((*str == '\0') && (*wildcard == '\0'));
}

bool HGE_Impl::_PrepareFileEnum(const char *wildcard)
{
	if(hSearch) { closedir(hSearch); hSearch=0; }
	char *madepath = Resource_MakePath(wildcard);
	const char *fname = strrchr(madepath, '/');
	const char *dir = NULL;
	if (fname == NULL) {
		dir = ".";
		fname = madepath;
	} else {
		dir = madepath;
		char *ptr = (char *) fname;
		*ptr = '\0';  // split dir and filename.
		fname++;
	}

	strcpy(szSearchDir, dir);
	strcpy(szSearchWildcard, fname);

	hSearch=opendir(dir);
	return (hSearch!=0);
}

char *HGE_Impl::_DoEnumIteration(const bool wantdir)
{
	if(!hSearch) return 0;
	while (true)
	{
		struct dirent *dent = readdir(hSearch);
		if(dent == NULL) { closedir(hSearch); hSearch=0; return 0; }
		if ((strcmp(dent->d_name, ".") == 0) || (strcmp(dent->d_name, "..") == 0))
			continue;
		if (!_WildcardMatch(dent->d_name, szSearchWildcard))
			continue;
		char fullpath[_MAX_PATH];
		snprintf(fullpath, sizeof (fullpath), "%s/%s", szSearchDir, dent->d_name);
		struct stat statbuf;
		if (stat(fullpath, &statbuf) == -1)  // this follows symlinks.
			continue;
		const bool isdir = ((S_ISDIR(statbuf.st_mode)) != 0);
		if (isdir == wantdir)  // this treats pipes, devs, etc, as "files" ...
		{
			strcpy(szSearchResult, dent->d_name);
			return szSearchResult;
		}
	}
	return 0;
}

char* CALL HGE_Impl::Resource_EnumFiles(const char *wildcard)
{
	if(wildcard)
	{
		if (!_PrepareFileEnum(wildcard))
			return 0;
	}
	return _DoEnumIteration(false);
}

char* CALL HGE_Impl::Resource_EnumFolders(const char *wildcard)
{
	if(wildcard)
	{
		if (!_PrepareFileEnum(wildcard))
			return 0;
	}
	return _DoEnumIteration(true);
}
