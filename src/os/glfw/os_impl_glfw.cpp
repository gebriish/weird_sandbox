#include "os_impl_glfw.h"

#include "../os_core.h"
#include <base/base_core.h>
#include <base/base_log.h>

constexpr size_t WINDOW_LIST_SIZE = 1;
internal OS_Handle g_window_list[WINDOW_LIST_SIZE];
internal GLFWwindow *g_glfwwindow_table[WINDOW_LIST_SIZE] = {0};
internal OS_HandleArray g_window_table {
  .handles = g_window_list,
  .len = 0
};

internal GLFWwindow* _get_glfw_window(OS_Handle& handle) {
  return g_glfwwindow_table[handle.id];
}

void os_glfw_window_close_callback(GLFWwindow *window)
{
	OS_Event* event = _os_new_event();
  event->type = OS_Event_WindowClose;
}

void os_glfw_window_focus_callback(GLFWwindow *window, int focused)
{
	OS_Event* event = _os_new_event();
  event->type = focused ? OS_Event_Focused : OS_Event_Defocused;
}

void os_glfw_frambuffer_size_callback(GLFWwindow *window, int width, int height)
{
  OS_Event *event = _os_new_event();
  event->type = OS_Event_FramebufferResize;
  event->size = { width, height };
}

void os_glfw_keyboard_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	OS_Event* event = _os_new_event();
  event->type = OS_Event_Keyboard;
  event->keyboard.key = key;
  event->keyboard.scancode = scancode;
  event->keyboard.mods = mods;
  event->keyboard.action = action;
}

void os_glfw_mouse_callback(GLFWwindow *window, int button, int action, int mods)
{
	OS_Event* event = _os_new_event();
  event->type = OS_Event_Mouse;
  event->mouse.button = button;
  event->mouse.action = action;
  event->mouse.mods = mods;
}

void os_glfw_char_callback(GLFWwindow* window, unsigned int codepoint)
{
	OS_Event* event = _os_new_event();
	event->type = OS_Event_Codepoint;
	event->codepoint = codepoint;
}

void os_glfw_cursor_callback(GLFWwindow *window, double x, double y)
{
	OS_Event *event = _os_new_event();
  event->type = OS_Event_Cursor;
  event->pos = {(i32) x, (i32) y};
}

void os_glfw_scroll_callback(GLFWwindow *window, double x, double y)
{
	OS_Event *event = _os_new_event();
	event->type = OS_Event_Scroll;
	event->scroll = { x, y };
}

void os_layer_init()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

OS_Handle os_window_open(const ivec2& rect, OS_WindowFlags flags, const std::string& title)
{
  ENGINE_ASSERT(g_window_table.len < WINDOW_LIST_SIZE, "Maximum number of window %zu passed", WINDOW_LIST_SIZE);

  glfwWindowHint(GLFW_RESIZABLE, (flags & OS_WindowFlags_Resizable) ? GLFW_TRUE : GLFW_FALSE);
  glfwWindowHint(GLFW_DECORATED, (flags & OS_WindowFlags_Decorated) ? GLFW_TRUE : GLFW_FALSE);

  GLFWmonitor* monitor = nullptr;
  if (flags & OS_WindowFlags_Fullscreen) {
    monitor = glfwGetPrimaryMonitor();
  }

  GLFWwindow* window = glfwCreateWindow(rect.x, rect.y, title.c_str(), monitor, nullptr);
  ENGINE_ASSERT(window != nullptr, "Failed to create GLFW window '%s'", title.c_str());

  size_t index = g_window_table.len;

  OS_Handle handle = {
    .id = index,
    .flags = flags,
  };

  g_glfwwindow_table[index] = window;
  g_window_table.handles[index] = handle;
  g_window_table.len++;

  glfwMakeContextCurrent(window);
  return handle;
}


void os_window_close(OS_Handle& window)
{
  GLFWwindow* glfw_window = _get_glfw_window(window);
  if (glfw_window) {
    glfwDestroyWindow(glfw_window);
    g_glfwwindow_table[window.id] = nullptr;
  }
}

void os_window_set_title(OS_Handle& window, const std::string& new_title)
{
  GLFWwindow* glfw_window = _get_glfw_window(window);
  if (glfw_window) {
    glfwSetWindowTitle(glfw_window, new_title.c_str());
  }
}

void os_window_focus(OS_Handle& window)
{
  GLFWwindow* glfw_window = _get_glfw_window(window);
  if (glfw_window) {
    glfwFocusWindow(glfw_window);
  }
}

bool os_window_is_focused(OS_Handle& window)
{
  GLFWwindow* glfw_window = _get_glfw_window(window);
  return glfw_window && glfwGetWindowAttrib(glfw_window, GLFW_FOCUSED) == GLFW_TRUE;
}

bool os_window_is_fullscreen(OS_Handle& window)
{
  GLFWwindow* glfw_window = _get_glfw_window(window);
  return glfw_window && glfwGetWindowMonitor(glfw_window) != nullptr;
}

bool os_window_is_maximized(OS_Handle& window)
{
  GLFWwindow* glfw_window = _get_glfw_window(window);
  return glfw_window && glfwGetWindowAttrib(glfw_window, GLFW_MAXIMIZED) == GLFW_TRUE;
}

void os_window_set_fullscreen(OS_Handle& window, bool state)
{
  GLFWwindow* glfw_window = _get_glfw_window(window);
  if (!glfw_window) return;

  GLFWmonitor* monitor = glfwGetPrimaryMonitor();
  const GLFWvidmode* mode = glfwGetVideoMode(monitor);

  if (state) {
    glfwSetWindowMonitor(glfw_window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
  } else {
    glfwSetWindowMonitor(glfw_window, nullptr, 100, 100, 800, 600, GLFW_DONT_CARE);
  }
}

void os_window_set_maximized(OS_Handle& window, bool state)
{
  GLFWwindow* glfw_window = _get_glfw_window(window);
  if (!glfw_window) return;

  if (state) {
    glfwMaximizeWindow(glfw_window);
  } else {
    glfwRestoreWindow(glfw_window);
  }
}

void os_window_set_monitor(OS_Handle& window, OS_Handle& monitor)
{
  GLFWwindow* glfw_window = _get_glfw_window(window);
  GLFWmonitor* glfw_monitor = reinterpret_cast<GLFWmonitor*>(monitor.id);
  const GLFWvidmode* mode = glfwGetVideoMode(glfw_monitor);

  glfwSetWindowMonitor(glfw_window, glfw_monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
}

ivec2 os_window_get_rect(OS_Handle& window)
{
  GLFWwindow* glfw_window = _get_glfw_window(window);
  if (!glfw_window) return {0, 0};

  int width = 0, height = 0;
  glfwGetWindowSize(glfw_window, &width, &height);
  return { width, height };
}

void os_poll_events()
{
  glfwPollEvents();
}

void os_window_swapbuffers(OS_Handle& window)
{
  GLFWwindow* glfw_window = _get_glfw_window(window);
  if (glfw_window) {
    glfwSwapBuffers(glfw_window);
  }
}

OS_Handle os_primary_monitor()
{
  GLFWmonitor* monitor = glfwGetPrimaryMonitor();
  ENGINE_ASSERT(monitor, "No primary monitor found");

  return OS_Handle{
    .id = reinterpret_cast<u64>(monitor),
    .flags = 0
  };
}

ivec2 os_monitor_rect(OS_Handle& monitor)
{
  GLFWmonitor* glfw_monitor = reinterpret_cast<GLFWmonitor*>(monitor.id);
  ENGINE_ASSERT(glfw_monitor, "Invalid monitor handle");

  int xpos, ypos, width, height;
  glfwGetMonitorWorkarea(glfw_monitor, &xpos, &ypos, &width, &height);
  return (ivec2) { width, height };
}

OS_HandleArray os_get_monitors(Arena* arena)
{
  int count;
  GLFWmonitor** monitors = glfwGetMonitors(&count);
  ENGINE_ASSERT(count > 0, "No monitors found");

  OS_Handle* handles = (OS_Handle*) arena_alloc(arena, sizeof(OS_Handle) * count);

  for (int i = 0; i < count; ++i) {
    handles[i].id = reinterpret_cast<u64>(monitors[i]);
    handles[i].flags = 0;
  }

  return OS_HandleArray {
    .handles = handles,
    .len = size_t(count)
  };
}

bool os_window_is_open(OS_Handle& window)
{
  GLFWwindow *glfw_window = g_glfwwindow_table[window.id];
  if (glfw_window)
  {
    return !glfwWindowShouldClose(glfw_window);
  }
  return false;
}

void* os_window_ogl_procaddress()
{
  return (void*) glfwGetProcAddress;
}

f64 os_get_seconds()
{
  return glfwGetTime();
}


void os_window_ogl_hintversion()
{
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void os_event_hook(OS_Handle& window)
{
	GLFWwindow* glfw_window = _get_glfw_window(window);
  if(!glfw_window) return;

  glfwSetWindowCloseCallback(glfw_window, os_glfw_window_close_callback);
  glfwSetWindowFocusCallback(glfw_window, os_glfw_window_focus_callback);
  glfwSetFramebufferSizeCallback(glfw_window, os_glfw_frambuffer_size_callback);
  glfwSetKeyCallback(glfw_window, os_glfw_keyboard_callback);
  glfwSetMouseButtonCallback(glfw_window, os_glfw_mouse_callback);
  glfwSetCharCallback(glfw_window, os_glfw_char_callback);
  glfwSetCursorPosCallback(glfw_window, os_glfw_cursor_callback);
  glfwSetScrollCallback(glfw_window, os_glfw_scroll_callback);
}


