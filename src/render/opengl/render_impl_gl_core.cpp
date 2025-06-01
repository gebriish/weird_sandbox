#include <render/render_core.h>
#include <os/os_core.h>
#include <base/base_log.h>

#include <glad/glad.h>

void r_init()
{
  os_window_ogl_hintversion();

  if (!gladLoadGLLoader((GLADloadproc)os_window_ogl_procaddress()))
  {
    ENGINE_LOG_ERROR("%s", "Failed to Initialize Opengl Function loader");
  }
}
