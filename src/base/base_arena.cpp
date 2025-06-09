#include "base_arena.h"
#include "base_log.h"

#include <stdlib.h>
#include <string.h>

internal ArenaScope arena_scope_begin(Arena *arena)
{
	if (!arena || !arena->base) return ArenaScope {0};
	ArenaScope scope = {
		.arena = arena,
		.mark = arena->used
	};
	return scope;
}

internal void arena_scope_end(ArenaScope *scope)
{
	if (!scope || !scope->arena) return;
	scope->arena->used = scope->mark;
}

internal Arena arena_begin(size_t capacity)
{
	ASSERT(capacity >= ARENA_MIN_CAPACITY);

	Arena arena;
	arena.base = (u8 *) malloc(capacity);

#if ARENA_ZERO_INITIALIZE
	memset(arena.base, 0, capacity);
#endif

	arena.freelist = nullptr;
	arena.capacity = capacity;
	arena.used = 0;
	return arena;
}

internal void arena_reset(Arena *arena)
{
	arena->used = 0;
	arena->freelist = nullptr;
}

internal void arena_end(Arena *arena)
{
	if(!arena || !arena->base) return;
	free(arena->base);
	arena->base = nullptr;
	arena->freelist = nullptr;
	arena->used = arena->capacity = 0;
}

internal void *arena_alloc(Arena *arena, size_t size)
{
	void *result = nullptr;
	const size_t aligned_size = (size + 7) & ~7;

	MemHeader **prev = &arena->freelist;
	for (MemHeader *it = arena->freelist; it; it = it->next) { // is this even safe ? idk
		if (it->alloc_size >= aligned_size) {
			*prev = it->next;
			result = (u8*) it + ARENA_HEADER_SIZE;
#if ARENA_ZERO_INITIALIZE
			memset(result, 0, it->alloc_size);
#endif 
			return result;
		}
		prev = &it->next;
	}

	const size_t size_required = aligned_size + ARENA_HEADER_SIZE;  // header size is aligned
	if (arena->used + size_required <= arena->capacity) {
		MemHeader *header_address = (MemHeader*) (arena->base + arena->used);
		header_address->next = nullptr;
		header_address->alloc_size = aligned_size;

		result = (u8*) header_address + ARENA_HEADER_SIZE;
#if ARENA_ZERO_INITIALIZE
		memset(result, 0, aligned_size);
#endif 

		arena->used += size_required;
	} else {
		ASSERT_MSG(false, "Arena ran out of memory");
	}

	return result;
}


internal void arena_free(Arena *arena, void *memory)
{
	if (!memory) return;

	u8 *mem_ptr = (u8 *)memory;
	u8 *arena_start = arena->base + ARENA_HEADER_SIZE;
	u8 *arena_end = arena->base + arena->used;

	// Adjusted check: memory must be within the user data range
	if (mem_ptr < arena_start || mem_ptr > arena_end) return;

	MemHeader *header = (MemHeader *)(mem_ptr - ARENA_HEADER_SIZE);

	header->next = arena->freelist;
	arena->freelist = header;
}

