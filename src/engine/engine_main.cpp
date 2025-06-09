#define ENGINE_DEBUG_MODE 1

//[h]
#include <stdio.h>
#include "base/base_inc.h"
#include "os/os_inc.h"
#include "engine/engine_core.h"

//[cpp]
#include "base/base_inc.cpp"
#include "os/os_inc.cpp"

typedef GameAPI (*GetGameAPIFunc)();

internal void engine_unload_game(GameLib *lib)
{
	if (lib->handle) {
		os_close_dl(lib->handle);
		lib->handle = nullptr;
	}
	memset(&lib->api, 0, sizeof(GameAPI));
}

internal bool engine_load_game(GameLib *lib, const char* path)
{
	lib->last_write_time = os_file_write_time(path);
	lib->handle = os_open_dl(path);
	if (!lib->handle) {
		log_erro("Failed to load game library '%s'", path);
		return false;
	}

	const char *GAME_API_FN_SYM = "get_game_api";
	GetGameAPIFunc get_game_api = (GetGameAPIFunc)os_dl_symbol(lib->handle, GAME_API_FN_SYM);
	if (!get_game_api) {
		log_erro("'%s' symbol not found in game dl", GAME_API_FN_SYM);
		os_close_dl(lib->handle);
		lib->handle = nullptr;
		return false;
	}

	lib->api = get_game_api();
	return true;
}


constexpr const char *LIB_PATH =
#if OS_WINDOWS
	"./sandbox.dll";
#elif OS_LINUX 
	"./libsandbox.so";
#else
# error OS not supported
#endif

internal i32 engine_main(i32 argc, char **argv)
{
	GameLib game_lib = {};
	if (!engine_load_game(&game_lib, LIB_PATH)) return 1;

	Arena persist_mem = arena_begin(MB(50));
	Arena transient_mem = arena_begin(MB(50));

	GameMemory *mem = game_lib.api.alloc_mem(&persist_mem);
	game_lib.api.init(mem);

	while(true)
	{
#if ENGINE_DEBUG_MODE
		u64 new_time = os_file_write_time(LIB_PATH);
		if (new_time != game_lib.last_write_time) {
			log_warn("hot reloading game library");
			engine_unload_game(&game_lib);
			os_sleep_ms(100);

			if(!engine_load_game(&game_lib, LIB_PATH)) {
				log_erro("Hot reload failed, keeping previous version");
				continue;
			}
		}
#endif

		game_lib.api.update(mem, 0.0f);
		os_sleep_ms(1000);
	}

	engine_unload_game(&game_lib);
	return 0;
}

//========================
// os specific entry point

#if OS_WINDOWS && !ENGINE_DEBUG_MODE
#include <Windows.h>
#include <stdlib.h> // for __argc & __argv
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	UNUSED_VAR(hInstance);
	UNUSED_VAR(hPrevInstance);
	UNUSED_VAR(lpCmdLine);
	UNUSED_VAR(nCmdShow);
	return engine_main((i32)__argc, __argv);
}
#else

int main(int argc, char** argv) {
	return engine_main((i32)argc, argv);
}
#endif

//========================
