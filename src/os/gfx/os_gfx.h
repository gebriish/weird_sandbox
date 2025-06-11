#ifndef OS_GFX_H
#define OS_GFX_H

#include "base/base_core.h"

constexpr u64 OS_EVENT_QUEUE_CAPACITY = 1024;

enum OS_EventType
{
	OS_EventType_None = 0,
};

struct OS_Event
{
	union {
		struct { i32 x; i32 y; }										pos;
		struct { i32 width; i32 height; }						size;
		struct { double x; double y; }							scroll;
		struct { i32 key; i32 scancode; i32 mods; } keyboard;
		struct { i32 button; i32 mods; }						mouse;
		struct { char **paths; u32  count; }				file;
		struct { float x; float y; }								scale;
		u32																					codepoint;
	};
	OS_EventType type;
};

typedef u64 OS_WindowFlags;
enum 
{
	OS_WindowFlag_None 			= 0,
	OS_WindowFlag_Resizable = (1 << 0),
	OS_WindowFlag_Maximized = (1 << 1),
	OS_WindowFlag_Decorated = (1 << 2),
};

struct OS_WindowConfig
{
	i32 width, height;
	const char *title;
	OS_WindowFlags widow_flags;
};

internal bool os_window_open(const OS_WindowConfig &config);
internal void os_window_close();

internal void os_window_update();
internal bool os_is_window_open();

#endif
