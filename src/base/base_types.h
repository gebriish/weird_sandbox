#pragma once

//=====================================
// Base types
//=====================================
#include <stdint.h>
#include <stddef.h>

typedef uint8_t  u8;
typedef int8_t   i8;
typedef uint16_t u16;
typedef int16_t  i16;
typedef uint32_t u32;
typedef int32_t  i32;
typedef uint64_t u64;
typedef int64_t  i64;
typedef float    f32;
typedef double   f64;

//=====================================
// Vector types

union vec2 {
  struct {
    f32 x, y;
  };
  f32 v[2];
};

union ivec2 {
  struct {
    i32 x, y;
  };
  i32 v[2];
};

union vec3 {
  struct {
    f32 x, y, z;
  };
  f32 v[3];
};

union ivec3 {
  struct {
    i32 x, y, z;
  };
  i32 v[3];
};

union vec4 {
  struct {
    f32 x, y, z, w;
  };
  f32 v[4];
};

union ivec4 {
  struct {
    i32 x, y, z, w;
  };
  i32 v[4];
};
