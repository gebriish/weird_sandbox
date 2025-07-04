#ifndef BASE_CORE_H
#define BASE_CORE_H

//=====================================
// Compiler and OS related Macros
#if defined(_MSC_VER)
# define COMPILER_CL 1
#	if defined(_WIN32)
#  define OS_WINDOWS 1
# else
#  error missing OS detection
# endif
#elif defined(__clang__)
# define COMPILER_CLANG 1
#	if defined(_WIN32)
#  define OS_WINDOWS 1
# elif defined(__linux__)
#  define OS_LINUX 1
# elif defined(__APPLE__) && defined(__MACH__)
#  define OS_MAC 1
# else 
#  error missing OS detection
# endif
#elif defined(__GNUC__)
# define COMPILER_GCC 1
#	if defined(_WIN32)
#  define OS_WINDOWS 1
# elif defined(__linux__)
#  define OS_LINUX 1
# elif defined(__APPLE__) && defined(__MACH__)
#  define OS_MAC 1
# else 
#  error missing OS detection
# endif
#endif

#if !defined(COMPILER_CL)
# define COMPILER_CL 0
#endif
#if !defined(COMPILER_CLANG)
# define COMPILER_CLANG 0
#endif
#if !defined(COMPILER_GCC)
# define COMPILER_GCC 0
#endif
#if !defined(OS_WINDOWS)
# define OS_WINDOWS 0
#endif
#if !defined(OS_LINUX)
# define OS_LINUX 0
#endif
#if !defined(OS_MAC)
# define OS_MAC 0
#endif

#if COMPILER_CL
# define force_inline __forceinline
#elif COMPILER_CLANG || COMPILER_GCC
# define force_inline __attribute__((always_inline)) inline
#else 
# define force_inline inline
#endif

#if defined(_MSC_VER)
 #include <intrin.h>
 #define DEBUG_BREAK() __debugbreak()
#elif defined(__GNUC__) || defined(__clang__)
 #if defined(__i386__) || defined(__x86_64__)
  #define DEBUG_BREAK() __asm__ volatile("int3")
 #else
  #include <signal.h>
  #define DEBUG_BREAK() raise(SIGTRAP)
 #endif
#else
 #define DEBUG_BREAK() ((void)0)
#endif

#define internal      static
#define global        static
#define local_persist static

#if OS_WINDOWS
# define EXPORT_FN __declspec(dllexport)
#elif OS_LINUX
# define EXPORT_FN 
#else
# error OS not supported
#endif

#define UNUSED_VAR(x) ((void)x)

//============================
// Architecture Detection
#if defined(_M_X64) || defined(__x86_64__)
# define ARC_X64 1
#else
# define ARC_X64 0
#endif

#if defined(_M_IX86) || defined(__i386__)
# define ARC_X86 1
#else
# define ARC_X86 0
#endif

#if defined(__aarch64__) || defined(_M_ARM64)
# define ARC_ARM64 1
#else
# define ARC_ARM64 0
#endif

#if defined(__arm__) || defined(_M_ARM)
# define ARC_ARM32 1
#else
# define ARC_ARM32 0
#endif

// Convenience macro
#if ARC_X64 || ARC_X86
# define ARC_X86_FAMILY 1
#else
# define ARC_X86_FAMILY 0
#endif

#if ARC_ARM64 || ARC_ARM32
# define ARC_ARM_FAMILY 1
#else
# define ARC_ARM_FAMILY 0
#endif

//=====================================
// SIMD Detection
#if ARC_X86_FAMILY
# if defined(__AVX2__) || (defined(_MSC_VER) && defined(__AVX2__))
#  define SIMD_AVX2 1
# else
#  define SIMD_AVX2 0
# endif

# if defined(__AVX__) || (defined(_MSC_VER) && defined(__AVX__))
#  define SIMD_AVX 1
# else
#  define SIMD_AVX 0
# endif

# if defined(__SSE4_1__) || (defined(_MSC_VER) && defined(__SSE4_1__))
#  define SIMD_SSE4_1 1
# else
#  define SIMD_SSE4_1 0
# endif

# if defined(__SSE2__) || (defined(_MSC_VER) && defined(_M_IX86_FP) && _M_IX86_FP >= 2)
#  define SIMD_SSE2 1
# else
#  define SIMD_SSE2 0
# endif

# if defined(__SSE__) || (defined(_MSC_VER) && defined(_M_IX86_FP) && _M_IX86_FP >= 1)
#  define SIMD_SSE 1
# else
#  define SIMD_SSE 0
# endif

#else
// For non-x86 architectures
# define SIMD_AVX2   0
# define SIMD_AVX    0
# define SIMD_SSE4_1 0
# define SIMD_SSE2   0
# define SIMD_SSE    0
#endif

#if ARC_ARM_FAMILY
# if defined(__ARM_NEON) || defined(__ARM_NEON__)
#  define SIMD_NEON 1
# else
#  define SIMD_NEON 0
# endif
#else
# define SIMD_NEON 0
#endif


//====================
// Scalar types

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

//====================
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

#endif
