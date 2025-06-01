#pragma once
#include <os/os_core.h>

struct StartupConfig
{
  i32 width, height;
  OS_WindowFlags window_flags;
};

void engine_create_context(StartupConfig config);
void engine_cleanup();
void engine_update_state();
OS_Handle engine_get_window();
