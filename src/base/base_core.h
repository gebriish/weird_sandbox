#pragma once

//=====================================
// Compiler and OS related Macros
//=====================================

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
# elif defined(__gnu_linux__)
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
# elif defined(__gnu_linux__)
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
# define force_inline __forceinline inline
#elif COMPILER_CLANG || COMPILER_GCC
# define force_inline __attribute__((always_inline)) inline
#else 
# define force_inline inline
#endif

#define internal      static
#define global        static
#define local_persist static

/* set this to 0 in release build */
#define ENGINE_DEBUG_MODE 1
