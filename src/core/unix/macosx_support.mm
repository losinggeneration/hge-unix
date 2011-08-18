// BOOL is defined in Cocoa headers, too.
#define BOOL ___HGE__BOOL___
#include "hge_impl_unix.h"
#undef BOOL

#if !PLATFORM_MACOSX
#error This source file is for Mac OS X only.
#endif

#import <Cocoa/Cocoa.h>

void HGE_Impl::_MacMinimizeWindow()
{
    if ((NSApp == NULL) || (!bWindowed))
        return;

    NSWindow *window = [NSApp mainWindow];
    if (window != NULL)
        [window performMiniaturize:NSApp];
}

void HGE_Impl::_MacHideOtherWindows()
{
    if ((NSApp == NULL) || (!bWindowed))
        return;
    [NSApp hideOtherApplications:NSApp];
}

void HGE_Impl::_MacHideWindow()
{
    if ((NSApp == NULL) || (!bWindowed))
        return;
    [NSApp hide:NSApp];
}

// end of macosx_support.mm ...

