#ifndef OS_CORE_H
#define OS_CORE_H

#include "base/base_core.h"

typedef void* OS_LibHandle;

struct OS_Handle {
	u64 v;
};

internal OS_LibHandle os_open_dl(const char* path);
internal void os_close_dl(OS_LibHandle handle);
internal void *os_dl_symbol(OS_LibHandle handle, const char *symbol);

internal u64 os_file_write_time(const char *path);

internal f64 os_get_seconds();
internal void os_sleep_ms(u64 milliseconds);

#endif
