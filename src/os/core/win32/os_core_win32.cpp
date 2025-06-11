#include "os/core/win32/os_core_win32.h"
#include "base/base_core.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

internal void os_sleep(u64 milliseconds)
{
	Sleep((DWORD)milliseconds);
}
