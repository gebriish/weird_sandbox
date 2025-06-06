#pragma once
#include "base_types.h"

#define KB(SIZE) SIZE * 1024
#define MB(SIZE) SIZE * KB(1024)
#define GB(SIZE) SIZE * MB(1024)

constexpr size_t ARENA_MIN_CAPACITY = KB(1);

struct MemHeader 
{
  MemHeader *next; // pointer to free list node ( if itself is one )
  size_t     alloc_size; // the size of block in front of this
};

constexpr size_t ARENA_HEADER_SIZE = sizeof(MemHeader);

struct Arena
{
  u8 *base;
  MemHeader *freelist;
  size_t capacity;
  size_t used;
};

struct TempAllocScope // scope controlled arena block
{
  Arena *arena;
  size_t mark;

  TempAllocScope(Arena *arena);
  ~TempAllocScope();
};

Arena arena_begin(size_t capacity);
void arena_reset(Arena *arena);
void arena_end(Arena *arena);

void *arena_alloc(Arena *arena, size_t size);
void arena_free(Arena *arena, void *memory); // not recommended but sometimes useful

void arena_visualize(Arena *arena);
