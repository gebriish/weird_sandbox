#pragma once
#include <base/base_core.h>

#if OS_WINDOWS && !ENGINE_DEBUG_BUILD
#include <windows.h>
#define MAIN_FUNC() CALLBACK int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
#define MAIN_FUNC() int main(int argc, char **argv)
#endif

#if OS_MAC 
# error Mac os is not supported [OpenGL Version 4.3+]
#endif
