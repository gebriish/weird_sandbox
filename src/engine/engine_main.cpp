#define ENGINE_DEBUG_MODE 1

//[h]
#include <stdio.h>
#include "base/base_inc.h"
#include "os/os_inc.h"
#include "engine/engine_core.h"

//[cpp]
#include "base/base_inc.cpp"
#include "os/os_inc.cpp"

typedef GameProc (*GetGameAPIFunc)();

internal void engine_unload_game(GameLib *lib)
{
	if (lib->handle) {
		os_close_dl(lib->handle);
		lib->handle = nullptr;
	}
	memset(&lib->api, 0, sizeof(GameProc));
}

internal bool engine_load_game(GameLib *lib, const char* path)
{
	lib->last_write_time = os_file_write_time(path);
	lib->handle = os_open_dl(path);
	if (!lib->handle) {
		log_erro("Failed to load game library '%s'", path);
		return false;
	}

	const char *GAME_API_FN_SYM = "get_game_proc";
	GetGameAPIFunc get_game_proc = (GetGameAPIFunc)os_dl_symbol(lib->handle, GAME_API_FN_SYM);
	if (!get_game_proc) {
		log_erro("'%s' symbol not found in game dl", GAME_API_FN_SYM);
		os_close_dl(lib->handle);
		lib->handle = nullptr;
		return false;
	}

	lib->api = get_game_proc();
	return true;
}


constexpr const char *LIB_PATH =
#if OS_WINDOWS
	"./Sandbox.dll";
#elif OS_LINUX 
	"./libSandbox.so";
#else
# error OS not supported
#endif

//========================
// game entry point

internal i32 engine_main(i32 argc, char **argv)
{
	GameLib game_lib = {};
	if (!engine_load_game(&game_lib, LIB_PATH)) return 1;

	//==== init engine state ====
	EngineState engine_state = {};
	engine_state.time_scale = 1.0f;
	//===========================

	Arena persist_mem = arena_begin(MB(50));
	Arena transient_mem = arena_begin(MB(50));

	GameMemory *mem = game_lib.api.alloc_state(&persist_mem);
	game_lib.api.init(mem);

	OS_WindowConfig config = {
		.width = 1280,
		.height = 800,
		.title = "Sandbox",
		.widow_flags = OS_WindowFlag_Decorated | OS_WindowFlag_Resizable
	};

	if(!os_window_open(config)) return 1;

	f64 last_frame_time = os_get_seconds();
	while(os_is_window_open())
	{
		f64 current_time = os_get_seconds();
		f64 delta_time = current_time - last_frame_time;
		last_frame_time = current_time;

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

		game_lib.api.update(mem, (f32) delta_time);

		os_window_update();
		arena_reset(&transient_mem);
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
