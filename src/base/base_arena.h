#pragma once
#include "base_core.h"
#include "base_types.h"

#define KB(SIZE) SIZE * 1024
#define MB(SIZE) SIZE * KB(1024)
#define GB(SIZE) SIZE * MB(1024)

#define ARENA_HEADER_SIZE 128

enum ArenaFlags
{
  ArenaFlag_NoChain =  (1 << 0),
  ArenaFlag_LargePage = (1 << 1)
};

struct Arena
{
};
