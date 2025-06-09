#ifndef ENGINE_CORE_H
#define ENGINE_CORE_H

#include "base/base_core.h"
#include "base/base_arena.h"
#include "os/core/os_core.h"
#include <time.h>

struct GameMemory;

struct GameAPI
{
	void (*init)(GameMemory *mem);
	void (*update)(GameMemory *mem, f32 dt);
	GameMemory* (*alloc_mem)(Arena *arena);
};

struct GameLib
{
	OS_LibHandle handle;
	time_t last_write_time;
	GameAPI api;
};

#endif

