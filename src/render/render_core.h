#pragma once
#include <base/base_types.h>

enum R_PassKind
{
  R_PassKind_Depth,
  R_PassKind_Forward,
};

struct R_Handle
{
  u64 id;
};

struct R_Pass
{
  R_PassKind kind;
};

struct R_PassNode
{
  R_PassNode *next;
  R_Pass v;
};

struct R_PassList
{
  R_PassNode *first;
  R_PassNode *last;
  u64 count;
};

void r_init();

