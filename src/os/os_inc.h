#ifndef OS_INC_H
#define OS_INC_H

#include "base/base_core.h"
#include "os/core/os_core.h"

#if OS_WINDOWS
# include "os/core/win32/os_core_win32.h"
#elif OS_LINUX
# include "os/core/linux/os_core_linux.h"
#else
# error OS not supported
#endif

#include "os/gfx/os_gfx.h"

#endif
