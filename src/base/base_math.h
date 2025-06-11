#ifndef BASE_MATH_H
#define BASE_MATH_H

#include "base_core.h"
#include <math.h>

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

//======================================
// matricies

#if SIMD_AVX || SIMD_AVX2
  #include <immintrin.h>
#elif SIMD_SSE2 || SIMD_SSE || SIMD_SSE4_1
  #include <xmmintrin.h>
#endif

union mat4 {
	struct {
		f32 e00, e10, e20, e30;
		f32 e01, e11, e21, e31;
		f32 e02, e12, e22, e32;
		f32 e03, e13, e23, e33;
	};
	struct {
		vec4 c0, c1, c2, c3;
	};
	f32 v[16];
};


force_inline mat4 mat4_add(mat4 a, mat4 b)
{
	mat4 result;

#if SIMD_SSE
	_mm_storeu_ps(&result.c0.x, _mm_add_ps(_mm_loadu_ps(&a.c0.x), _mm_loadu_ps(&b.c0.x)));
	_mm_storeu_ps(&result.c1.x, _mm_add_ps(_mm_loadu_ps(&a.c1.x), _mm_loadu_ps(&b.c1.x)));
	_mm_storeu_ps(&result.c2.x, _mm_add_ps(_mm_loadu_ps(&a.c2.x), _mm_loadu_ps(&b.c2.x)));
	_mm_storeu_ps(&result.c3.x, _mm_add_ps(_mm_loadu_ps(&a.c3.x), _mm_loadu_ps(&b.c3.x)));
#else
	for (int i = 0; i < 16; ++i)
		result.v[i] = a.v[i] + b.v[i];
#endif

	return result;
}

static inline mat4 mat4_mul(mat4 a, mat4 b)
{
	mat4 result;

#if SIMD_SSE
	__m128 a0 = _mm_loadu_ps(&a.c0.x);
	__m128 a1 = _mm_loadu_ps(&a.c1.x);
	__m128 a2 = _mm_loadu_ps(&a.c2.x);
	__m128 a3 = _mm_loadu_ps(&a.c3.x);

	for (int i = 0; i < 4; ++i) {
		f32* bc = &b.c0.x + i * 4;

		__m128 b0 = _mm_set1_ps(bc[0]);
		__m128 b1 = _mm_set1_ps(bc[1]);
		__m128 b2 = _mm_set1_ps(bc[2]);
		__m128 b3 = _mm_set1_ps(bc[3]);

		__m128 r = _mm_add_ps(
			_mm_add_ps(_mm_mul_ps(a0, b0), _mm_mul_ps(a1, b1)),
			_mm_add_ps(_mm_mul_ps(a2, b2), _mm_mul_ps(a3, b3))
		);

		_mm_storeu_ps(&((&result.c0)[i].x), r);
	}
#else
	for (int col = 0; col < 4; ++col) {
		for (int row = 0; row < 4; ++row) {
			result.v[col * 4 + row] =
				a.v[0 * 4 + row] * b.v[col * 4 + 0] +
				a.v[1 * 4 + row] * b.v[col * 4 + 1] +
				a.v[2 * 4 + row] * b.v[col * 4 + 2] +
				a.v[3 * 4 + row] * b.v[col * 4 + 3];
		}
	}
#endif

	return result;
}


#endif
