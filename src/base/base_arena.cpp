#include "base_arena.h"
#include "base_log.h"

#include <stdlib.h>
#include <string.h>

TempAllocScope::TempAllocScope(Arena *arena)
{
  this->arena = arena;
  this->mark = arena->used;
}

TempAllocScope::~TempAllocScope()
{
  arena->used = mark;
}

Arena arena_begin(size_t capacity)
{
  ENGINE_ASSERT(capacity >= ARENA_MIN_CAPACITY, "Arena should be atleast %ld bytes", ARENA_MIN_CAPACITY);
  Arena arena;
  arena.base = (u8 *) malloc(capacity);

#if ENGINE_ZERO_INITIALIZE
  memset(arena.base, 0, capacity);
#endif

  arena.freelist = nullptr;
  arena.capacity = capacity;
  arena.used = 0;
  return arena;
}

void arena_reset(Arena *arena)
{
  arena->used = 0;
  arena->freelist = nullptr;
}

void arena_end(Arena *arena)
{
  if(!arena || !arena->base) return;
  free(arena->base);
  arena->base = nullptr;
  arena->freelist = nullptr;
  arena->used = arena->capacity = 0;
}

void *arena_alloc(Arena *arena, size_t size)
{
  void *result = nullptr;
  const size_t aligned_size = (size + 7) & ~7;

  MemHeader **prev = &arena->freelist;
  for (MemHeader *it = arena->freelist; it; it = it->next) { // is this even safe ? idk
    if (it->alloc_size >= aligned_size) {
      *prev = it->next;
      result = (u8*) it + ARENA_HEADER_SIZE;
#if ENGINE_ZERO_INITIALIZE
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
#if ENGINE_ZERO_INITIALIZE
    memset(result, 0, aligned_size);
#endif 

    arena->used += size_required;
  } else {
    ENGINE_ASSERT(false, "Arena ran out of space");
  }

  return result;
}


void arena_free(Arena *arena, void *memory)
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

void arena_visualize(Arena *arena)
{
#if ENGINE_DEBUG_BUILD 
  ENGINE_LOG_INFO("%s", "=== Arena Visualization ===");
  ENGINE_LOG_INFO("Capacity: %zu bytes", arena->capacity);
  ENGINE_LOG_INFO("Used:     %zu bytes (%.2f%%)", 
                  arena->used, 
                  (arena->used / (double)arena->capacity) * 100.0);

  // ASCII usage bar
  const int bar_width = 50;
  int used_chars = (int)((arena->used / (double)arena->capacity) * bar_width);
  char usage_bar[bar_width + 1];
  for (int i = 0; i < bar_width; ++i)
    usage_bar[i] = i < used_chars ? '#' : '-';
  usage_bar[bar_width] = '\0';
  ENGINE_LOG_INFO("Usage:    [%s]", usage_bar);

  // Free list visualization
  int freelist_count = 0;
  size_t freelist_total = 0;
  for (MemHeader *it = arena->freelist; it; it = it->next) {
    freelist_total += it->alloc_size;
    freelist_count++;
  }

  ENGINE_LOG_INFO("Freelist Blocks: %d", freelist_count);
  ENGINE_LOG_INFO("Freelist Bytes:  %zu", freelist_total);

#if 1
  if (freelist_count > 0) {
    ENGINE_LOG_INFO("%s", "Freelist Block Sizes:");
    int idx = 0;
    for (MemHeader *it = arena->freelist; it; it = it->next) {
      ENGINE_LOG_INFO("  [%02d] %zu bytes", idx++, it->alloc_size);
    }
  }
#endif

  ENGINE_LOG_INFO("%s", "============================");
#endif
}
