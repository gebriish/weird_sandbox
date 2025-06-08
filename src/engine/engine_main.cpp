#define ENGINE_DEBUG_MODE 1

//[h]
#include <stdio.h>
#include "base/base_inc.h"
#include "os/os_inc.h"

//[cpp]
#include "base/base_inc.cpp"
#include "os/os_inc.cpp"

internal i32 engine_main(i32 argc, char **argv)
{
	return 0;
}

//========================
// os specific entry point

#if OS_WINDOWS && !ENGINE_DEBUG_MODE
#include <Windows.h>
#include <stdlib.h> // for __argc & __argv
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	(void)hInstance;
	(void)hPrevInstance;
	(void)lpCmdLine;
	(void)nCmdShow;
	return engine_main((i32)__argc, __argv);
}
#else
int main(int argc, char** argv) {
	return engine_main((i32)argc, argv);
}
#endif

//========================
