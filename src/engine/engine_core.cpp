#include "engine_core.h"

#include "../base/base_core.h"
#include "../base/base_log.h"
#include "../os/os_core.h"

struct EngineContext
{
  OS_Handle window;
  bool initialized;
};

internal EngineContext g_engine_ctx = {0};

void engine_create_context(StartupConfig config)
{
  if(g_engine_ctx.initialized) return;

  os_layer_init();
  g_engine_ctx.window = os_window_open({config.width, config.height}, config.window_flags, "Weird Sandbox");
  
  os_event_hook(g_engine_ctx.window);
  g_engine_ctx.initialized = true;
}

void engine_cleanup()
{
  if (!g_engine_ctx.initialized) return;
  os_window_close(g_engine_ctx.window);
  g_engine_ctx.initialized = false;
}

void engine_update_state()
{
  ENGINE_ASSERT(g_engine_ctx.initialized);
  os_window_swapbuffers(g_engine_ctx.window);
  os_poll_events();
}


OS_Handle engine_get_window()
{
  ENGINE_ASSERT(g_engine_ctx.initialized);
  return g_engine_ctx.window;
}
