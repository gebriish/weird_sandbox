#define ENGINE_DEBUG_MODE 1

//[h]
#include "base/base_inc.h"
#include "engine/engine_core.h"

//[cpp]
#include "base/base_inc.cpp"

struct GameMemory
{
	i32 counter;
};

EXPORT_FN void game_init(GameMemory *mem)
{
	mem->counter = 0;
}

EXPORT_FN void game_update(GameMemory *mem, f32 dt)
{
	mem->counter += 1;
	log_info("different message %d", mem->counter);
}

EXPORT_FN GameMemory *game_alloc(Arena *arena)
{
	return (GameMemory*) arena_alloc(arena, sizeof(GameMemory));
}

extern "C" EXPORT_FN GameAPI get_game_api()
{
	const GameAPI api = {
		.init = game_init,
		.update = game_update,
		.alloc_mem = game_alloc,
	};
	return api;
}
