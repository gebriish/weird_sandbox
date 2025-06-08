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

#define internal      static
#define global        static
#define local_persist static


//=====================================
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

#endif
