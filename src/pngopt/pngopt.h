#include "../../include/hge.h"
#include "unix_compat.h"

#include <stdio.h>
#include <stdlib.h>
#ifndef PLATFORM_UNIX
#include <windows.h>
#endif


extern HGE *hge;

bool Write32BitPNGWithPitch(FILE* fp, void* pBits, bool bNeedAlpha, int nWidth, int nHeight, int nPitch);
