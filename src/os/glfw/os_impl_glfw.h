#pragma once
#include <GLFW/glfw3.h>

void os_glfw_window_close_callback(GLFWwindow *window);
void os_glfw_window_focus_callback(GLFWwindow *window, int focused);
void os_glfw_frambuffer_size_callback(GLFWwindow *window, int width, int height);
void os_glfw_keyboard_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void os_glfw_mouse_callback(GLFWwindow *window, int button, int action, int mods);
void os_glfw_char_callback(GLFWwindow *window, unsigned int codepoint);
void os_glfw_cursor_callback(GLFWwindow *window, double x, double y);
void os_glfw_scroll_callback(GLFWwindow *window, double x, double y);

