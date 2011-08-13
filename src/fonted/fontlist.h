/*
** Haaf's Game Engine 1.1
** Copyright (C) 2003, Relish Games
** hge.relishgames.com
**
** Bitmap Font Builder
*/


#ifndef FONTLIST_H
#define FONTLIST_H

#include "unix_compat.h"

#ifndef PLATFORM_UNIX
#include <windows.h>
#endif


struct CFontListItem
{
#ifdef PLATFORM_UNIX
	/// FIXME This is 100% wrong
	char family[256];
#else
	char		  family[LF_FACESIZE];
#endif
	CFontListItem *next;
};

class CFontList
{
#ifdef PLATFORM_UNIX
	friend int EnumFontFamiliesEx(int *lpelfe, int *lpntme, DWORD FontType, void *lParam);
#else
	friend int CALLBACK EnumFontFamExProc(ENUMLOGFONTEX *lpelfe, NEWTEXTMETRICEX *lpntme, DWORD FontType, LPARAM lParam);
#endif

public:
	CFontList();
	~CFontList();

	void	BuildList();
	int		GetNumFonts() { return nFonts; }
	char	*GetFontByIdx(int n);

private:
	void			ClearList();
	void			FindSortAdd(char *family);

	int				nFonts;
	CFontListItem	*pFonts;
};

extern CFontList	*FontList;


#endif // FONTLIST_H
