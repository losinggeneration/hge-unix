
#ifndef TEXASM_H
#define TEXASM_H

#include "../../include/hge.h"

#include <stdio.h>
#ifndef PLATFORM_UNIX
#include <windows.h>
#endif

extern HGE *hge;

void SysLog(const char *format, ...);


#endif
