#include "os/gfx/os_gfx.h"
#include "base/base_core.h"
#include "base/base_log.h"

#include <GLFW/glfw3.h>

global struct 
{
	GLFWwindow *window;
} g_glfw_window = {0};

internal bool os_window_open(const OS_WindowConfig &config)
{
	if (g_glfw_window.window) {
		os_window_close();
	}

	if(!glfwInit())
	{
		log_erro("Failed to create window [ glfwInit Failed ]");
		return false;
	}

	i32 width = config.width > 0 ? config.width : 640;
	i32 height = config.height > 0 ? config.height : 480;
	const char *title = config.title ? config.title : "Untitled";
	
	glfwWindowHint(GLFW_RESIZABLE, config.widow_flags & OS_WindowFlag_Resizable ? GLFW_TRUE : GLFW_FALSE);
	glfwWindowHint(GLFW_DECORATED, config.widow_flags & OS_WindowFlag_Decorated ? GLFW_TRUE : GLFW_FALSE);
	glfwWindowHint(GLFW_MAXIMIZED, config.widow_flags & OS_WindowFlag_Maximized ? GLFW_TRUE : GLFW_FALSE);

	GLFWwindow *window = glfwCreateWindow(width, height, title, 0, 0);

	if(!window) {
		log_erro("Failed to create window [ glfwCreateWindow Failed ]");
		return false;
	}

	glfwMakeContextCurrent(window);
	g_glfw_window.window = window;

	return true;
}

internal void os_window_close()
{
	if (!g_glfw_window.window) return;

	glfwDestroyWindow(g_glfw_window.window);
	glfwTerminate();

	g_glfw_window = {0};
}

internal void os_window_update()
{
	if (!g_glfw_window.window) return;

	glfwSwapBuffers(g_glfw_window.window);
	glfwPollEvents();
}

internal bool os_is_window_open()
{
	return (g_glfw_window.window) && !glfwWindowShouldClose(g_glfw_window.window);
}

internal f64 os_get_seconds()
{
	return (f64) glfwGetTime();
}