#define ENGINE_DEBUG_MODE 1

//[h]
#include "base/base_inc.h"
#include "engine/engine_core.h"

//[cpp]
#include "base/base_inc.cpp"

EXPORT_FN void game_init(GameMemory *mem)
{
}

EXPORT_FN void game_update(GameMemory *mem, f32 dt)
{
}

EXPORT_FN GameMemory* game_alloc_state(Arena *arena)
{
	return (GameMemory*) arena_alloc(arena, sizeof(GameMemory));
}

extern "C" EXPORT_FN GameProc get_game_proc()
{
	return (GameProc) {
		.init = game_init,
		.update = game_update,
		.alloc_state = game_alloc_state
	};
}
