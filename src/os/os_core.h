#pragma once
#include <base/base_types.h>
#include <base/base_arena.h>

#include <string>

typedef void* (*GLProcAddressFunc)(const char* name);

struct OS_Handle 
{
  u64 id;
  u64 flags;
};

struct OS_HandleArray
{
  OS_Handle *handles;
  size_t len;
};

typedef u64 OS_WindowFlags;
enum : u64 
{
  OS_WindowFlags_None       = 0,
  OS_WindowFlags_Fullscreen = 1 << 0,
  OS_WindowFlags_Resizable  = 1 << 1,
  OS_WindowFlags_Decorated  = 1 << 2,
};

constexpr size_t OS_EVENT_QUEUE_CAPACITY = 1024;

enum OS_EventType
{
  OS_Event_None = 0,
  OS_Event_WindowClose,
  OS_Event_WindowFocus,
  OS_Event_FramebufferResize,
  OS_Event_Keyboard,
  OS_Event_Mouse,
  OS_Event_Cursor,
  OS_Event_Codepoint,
  OS_Event_Scroll,
  OS_Event_Focused,
  OS_Event_Defocused
};

struct OS_Event
{
  OS_EventType type;

  union {
    struct { i32 x, y; }                        pos;
    struct { i32 width, height; }               size;
    struct { f64 x; f64 y; }                    scroll;
    struct { i32 key, scancode, action, mods; } keyboard;
    struct { i32 button, action, mods; }        mouse;
    u32                                         codepoint;
  };
};

void      os_layer_init();

//=====================================
// Window handling
//=====================================

OS_Handle os_window_open(const ivec2& rect, OS_WindowFlags flags, const std::string& title);
void      os_window_close(OS_Handle& window);
void      os_window_set_title(OS_Handle& window, const std::string& new_title);
void      os_window_focus(OS_Handle& window);
bool      os_window_is_focused(OS_Handle& window);
bool      os_window_is_fullscreen(OS_Handle& window);
bool      os_window_is_maximized(OS_Handle& window);
void      os_window_set_fullscreen(OS_Handle& window, bool state);
void      os_window_set_maximized(OS_Handle& window, bool state);
void      os_window_set_monitor(OS_Handle& window, OS_Handle& monitor);
ivec2     os_window_get_rect(OS_Handle& window);
void      os_window_swapbuffers(OS_Handle& window);
bool      os_window_is_open(OS_Handle& window);
void      os_poll_events();
f64       os_get_seconds(); // seconds since startup

// OpenGL specifics
void*     os_window_ogl_procaddress();
void      os_window_ogl_hintversion();

//=====================================
// Monitor handling
//=====================================
OS_Handle      os_primary_monitor();
ivec2          os_monitor_rect(OS_Handle& monitor);
OS_HandleArray os_get_monitors(Arena *arena);


//=====================================
// Event handling
//=====================================

void os_event_hook(OS_Handle& window);
bool os_next_event(OS_Event *event);
void os_event_reset(OS_Event *event);
OS_Event *_os_new_event(); /* for internal use ONLY */
