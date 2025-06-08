#ifndef BASE_MATH_H
#define BASE_MATH_H

#include "base_core.h"
#include <math.h>

//=====================================
// Vector functions

//=================
// vec2

force_inline vec2 operator+(const vec2& a, const vec2& b) {
  return vec2{a.x + b.x, a.y + b.y};
}

force_inline vec2 operator-(const vec2& a, const vec2& b) {
  return vec2{a.x - b.x, a.y - b.y};
}

force_inline vec2 operator*(const vec2& v, f32 s) {
  return vec2{v.x * s, v.y * s};
}

force_inline vec2 operator*(f32 s, const vec2& v) {
  return vec2{v.x * s, v.y * s};
}

force_inline vec2 operator/(const vec2& v, f32 s) {
  return vec2{v.x / s, v.y / s};
}

force_inline vec2& operator+=(vec2& a, const vec2& b) {
  a.x += b.x; a.y += b.y; return a;
}

force_inline vec2& operator-=(vec2& a, const vec2& b) {
  a.x -= b.x; a.y -= b.y; return a;
}

force_inline vec2& operator*=(vec2& a, f32 s) {
  a.x *= s; a.y *= s; return a;
}

force_inline vec2& operator/=(vec2& a, f32 s) {
  a.x /= s; a.y /= s; return a;
}

force_inline vec2 operator-(const vec2& v) {
  return vec2{-v.x, -v.y};
}

force_inline f32 dot(const vec2& a, const vec2& b) {
  return a.x * b.x + a.y * b.y;
}

force_inline f32 length_squared(const vec2& v) {
  return v.x * v.x + v.y * v.y;
}

force_inline f32 length(const vec2& v) {
  return sqrt(v.x * v.x + v.y * v.y);
}

//=================
// ivec2
force_inline ivec2 operator+(const ivec2& a, const ivec2& b) {
  return ivec2{a.x + b.x, a.y + b.y};
}

force_inline ivec2 operator-(const ivec2& a, const ivec2& b) {
  return ivec2{a.x - b.x, a.y - b.y};
}

force_inline ivec2& operator+=(ivec2& a, const ivec2& b) {
  a.x += b.x; a.y += b.y; return a;
}

force_inline ivec2& operator-=(ivec2& a, const ivec2& b) {
  a.x -= b.x; a.y -= b.y; return a;
}

force_inline ivec2 operator-(const ivec2& v) {
  return ivec2{-v.x, -v.y};
}

force_inline bool operator==(const ivec2& a, const ivec2& b) {
  return a.x == b.x && a.y == b.y;
}

//=================
// vec3
force_inline vec3 operator+(const vec3& a, const vec3& b) {
  return vec3{a.x + b.x, a.y + b.y, a.z + b.z};
}

force_inline vec3 operator-(const vec3& a, const vec3& b) {
  return vec3{a.x - b.x, a.y - b.y, a.z - b.z};
}

force_inline vec3 operator*(const vec3& v, f32 s) {
  return vec3{v.x * s, v.y * s, v.z * s};
}

force_inline vec3 operator*(f32 s, const vec3& v) {
  return vec3{v.x * s, v.y * s, v.z * s};
}

force_inline vec3 operator/(const vec3& v, f32 s) {
  return vec3{v.x / s, v.y / s, v.z / s};
}

force_inline vec3& operator+=(vec3& a, const vec3& b) {
  a.x += b.x; a.y += b.y; a.z += b.z; return a;
}

force_inline vec3& operator-=(vec3& a, const vec3& b) {
  a.x -= b.x; a.y -= b.y; a.z -= b.z; return a;
}

force_inline vec3& operator*=(vec3& a, f32 s) {
  a.x *= s; a.y *= s; a.z *= s; return a;
}

force_inline vec3& operator/=(vec3& a, f32 s) {
  a.x /= s; a.y /= s; a.z /= s; return a;
}

force_inline vec3 operator-(const vec3& v) {
  return vec3{-v.x, -v.y, -v.z};
}

force_inline f32 dot(const vec3& a, const vec3& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

force_inline f32 length_squared(const vec3& v) {
  return v.x * v.x + v.y * v.y + v.z * v.z;
}

force_inline f32 length(const vec3& v) {
  return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

//=================
// ivec3
force_inline ivec3 operator+(const ivec3& a, const ivec3& b) {
  return ivec3{a.x + b.x, a.y + b.y, a.z + b.z};
}

force_inline ivec3 operator-(const ivec3& a, const ivec3& b) {
  return ivec3{a.x - b.x, a.y - b.y, a.z - b.z};
}

force_inline ivec3& operator+=(ivec3& a, const ivec3& b) {
  a.x += b.x; a.y += b.y; a.z += b.z; return a;
}

force_inline ivec3& operator-=(ivec3& a, const ivec3& b) {
  a.x -= b.x; a.y -= b.y; a.z -= b.z; return a;
}

force_inline ivec3 operator-(const ivec3& v) {
  return ivec3{-v.x, -v.y, -v.z};
}

force_inline bool operator==(const ivec3& a, const ivec3& b) {
  return a.x == b.x && a.y == b.y && a.z == b.z;
}

//=====================================A

#endif
