#include "os/core/os_core.h"
#include "os/core/linux/os_core_linux.h"
#include "base/base_core.h"

#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dlfcn.h>

internal OS_LibHandle os_open_dl(const char* path)
{
	return dlopen(path, RTLD_NOW);
}

internal void os_close_dl(OS_LibHandle handle)
{
	if (handle) {
		dlclose(handle);
	}
}

internal void *os_dl_symbol(OS_LibHandle handle, const char *symbol)
{
	return dlsym(handle, symbol);
}

internal u64 os_file_write_time(const char *path)
{
	struct stat attr;
	if (stat(path, &attr) == 0) {
		return (u64) attr.st_mtime;
	}
	return 0;
}

internal void os_sleep_ms(u64 milliseconds)
{
	struct timespec ts;
  ts.tv_sec = milliseconds / 1000;
  ts.tv_nsec = (milliseconds % 1000) * 1000000;
  nanosleep(&ts, NULL);
}
