#include "base/base_core.h"
#include "os/core/os_core.cpp"

#if OS_WINDOWS
# include "os/core/win32/os_core_win32.cpp"
#elif OS_LINUX
# include "os/core/linux/os_core_linux.cpp"
#else
# error OS not supported
#endif


