#ifndef _INCL_UNIX_COMPAT_H_
#define _INCL_UNIX_COMPAT_H_

#if (defined(__APPLE__) && defined(__MACH__))
#define PLATFORM_MACOSX 1
#endif

#if ( defined(unix) || PLATFORM_MACOSX )
#define PLATFORM_UNIX 1
#endif

// Useful to sprinkle around the codebase without a bunch of #ifdefs...
#ifdef _WINDOWS
#define BYTESWAP(x)
#define STUBBED(x)
#endif

// don't want rest of this header on Windows, etc.
#if (PLATFORM_UNIX)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>

#include "SDL.h"

#define _MAX_PATH PATH_MAX
#define MAX_PATH PATH_MAX

typedef int64_t __int64;
typedef uint32_t DWORD;
typedef uint64_t UINT64;
typedef uint8_t BYTE;
typedef void *HANDLE;
typedef HANDLE HWND;
typedef int32_t BOOL;

static inline DWORD timeGetTime(void)
{
    return SDL_GetTicks();
} // timeGetTime


// macro so I know what is still on the TODO list...
#if 1
#define STUBBED(x)
#else
void CalledSTUBBED(void);  // you can set a breakpoint on this.
#define STUBBED(x) \
do { \
    static bool seen_this = false; \
    if (!seen_this) { \
        seen_this = true; \
        fprintf(stderr, "STUBBED: %s at %s (%s:%d)\n", x, __FUNCTION__, __FILE__, __LINE__); \
        fflush(stderr); \
        CalledSTUBBED(); \
    } \
} while (false)
#endif

static inline char *itoa(const int i, char *s, const int radix)
{
    assert(radix == 10);
    sprintf(s, "%d", i);
    return s;
}

static inline char *_i64toa(const __int64 i, char *s, const int radix)
{
    assert(radix == 10);
    assert(sizeof (long long) == sizeof (__int64));
    sprintf(s, "%lld", (long long) i);
    return s;
}

static inline __int64 _atoi64(const char *str)
{
    return (__int64) strtoll(str, NULL, 10);
}

static inline void Sleep(const int ms)
{
    usleep(ms * 1000);
}

static inline char *_gcvt(const double value, const int digits, char *buffer)
{
    char fmt[32];
    snprintf(fmt, sizeof (fmt), "%%.%dg", digits);
    sprintf(buffer, fmt, value);
    return buffer;
}

#define ZeroMemory(a,b) memset(a, '\0', b)

#ifdef __cplusplus
#ifdef max
#undef max
#endif
template <class T> inline const T &max(const T &a, const T &b) { return (a > b) ? a : b; }
#ifdef min
#undef min
#endif
template <class T> inline const T &min(const T &a, const T &b) { return (a < b) ? a : b; }
#endif

// Byteswap magic...

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
#define PLATFORM_BIGENDIAN 1
#define PLATFORM_LITTLEENDIAN 0
#else
#define PLATFORM_BIGENDIAN 0
#define PLATFORM_LITTLEENDIAN 1
#endif

#if PLATFORM_BIGENDIAN
    #define SWAPPER64(t) \
        inline void BYTESWAP(t &x) { \
            union { t orig; Uint64 ui; } swapper; \
            swapper.orig = x; \
            swapper.ui = SDL_SwapLE64(swapper.ui); \
            x = swapper.orig; \
        }
    #define SWAPPER32(t) \
        inline void BYTESWAP(t &x) { \
            union { t orig; Uint32 ui; } swapper; \
            swapper.orig = x; \
            swapper.ui = SDL_SwapLE32(swapper.ui); \
            x = swapper.orig; \
        }
    #define SWAPPER16(t) \
        inline void BYTESWAP(t &x) { \
            union { t orig; Uint16 ui; } swapper; \
            swapper.orig = x; \
            swapper.ui = SDL_SwapLE16(swapper.ui); \
            x = swapper.orig; \
        }
    #define SWAPPER8(t) inline void BYTESWAP(t &_x) {}
    SWAPPER64(double)
    SWAPPER32(size_t)   // !!! FIXME: this will fail on gnuc/amd64.
    SWAPPER32(int)
    SWAPPER32(float)
    SWAPPER32(DWORD)
    SWAPPER16(WORD)
    SWAPPER16(short)
    SWAPPER8(BYTE)
    #undef SWAPPER32
    #undef SWAPPER16
    #undef SWAPPER8
#else
    #define BYTESWAP(x)
#endif

#endif  // PLATFORM_UNIX

#endif  // include-once blocker.
