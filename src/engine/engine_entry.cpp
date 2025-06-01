#include "engine_entry.h"
#include "engine_core.h"

#include <base/base_core.h>
#include <base/base_log.h>
#include <render/render_core.h>
#include <glad/glad.h>

#if ENGINE_DEBUG_BUILD
internal bool g_editor_active = false;

internal void _toggle_editor() {
  ENGINE_LOG_WARN("Editor toggled : %s", g_editor_active ? "ON"  : "OFF");
  g_editor_active = !g_editor_active;
}

#endif

MAIN_FUNC()
{
  StartupConfig config {
    .width = 640,
    .height = 480,
    .window_flags = OS_WindowFlags_Decorated | OS_WindowFlags_Resizable
  };

  engine_create_context(config);
  OS_Handle window_handle = engine_get_window();

  r_init();

  while(os_window_is_open(window_handle))
  {
    OS_Event event;
    while(os_next_event(&event))
    {
      os_event_reset(&event);
    }


#if ENGINE_DEBUG_BUILD
#endif

    engine_update_state();
  }
}
