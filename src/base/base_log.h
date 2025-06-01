#pragma once

#include "./base_core.h"

enum TextColor /* for ascii logging */
{
  TEXT_COLOR_RED = 0,
  TEXT_COLOR_WHITE,
  TEXT_COLOR_YELLOW,
  TEXT_COLOR_GREEN,
  TEXT_COLOR_COUNT
};

#if ENGINE_DEBUG_BUILD
#include <stdio.h>

template <typename ...Args>
force_inline void _log(const char *prefix, const char *msg, TextColor color, Args... args)
{
  local_persist const char* color_table[TEXT_COLOR_COUNT] {
    "\x1b[31m", // Red
    "\x1b[37m", // White
    "\x1b[33m", // Yellow
    "\x1b[32m"  // Green  
  };

  char format_buffer[8192] = {0};
  sprintf(format_buffer, "%s %s %s\033[0m", color_table[color], prefix, msg);

  char text_buffer[8192] = {0};
  sprintf(text_buffer, format_buffer, args...);
  puts(text_buffer);
}

#define ENGINE_LOG_INFO(msg, ...)  _log("TRACE : ", msg, TEXT_COLOR_GREEN, ##__VA_ARGS__)
#define ENGINE_LOG_WARN(msg, ...)  _log("WARN  : ", msg, TEXT_COLOR_YELLOW, ##__VA_ARGS__)
#define ENGINE_LOG_ERROR(msg, ...) _log("ERROR : ", msg, TEXT_COLOR_RED, ##__VA_ARGS__)

#define ENGINE_INTERNAL_ASSERT_FMT_(fmt, ...) \
  do { \
    fprintf(stderr, fmt "\n", ##__VA_ARGS__); \
  } while (0)

#define ENGINE_ASSERT(cond, ...) \
  do { \
    if (!(cond)) { \
      fprintf(stderr, "[ASSERT FAILED] %s:%d: ", __FILE__, __LINE__); \
      if (sizeof(#__VA_ARGS__) > 1) { \
        ENGINE_INTERNAL_ASSERT_FMT_(__VA_ARGS__); \
      } else { \
        fprintf(stderr, "Assertion failed: %s\n", #cond); \
      } \
      abort(); \
    } \
  } while (0)

#else

#define ENGINE_LOG_INFO(msg, ...) ((void)0)
#define ENGINE_LOG_WARN(msg, ...) ((void)0)
#define ENGINE_LOG_ERROR(msg, ...) ((void)0)
#define ENGINE_ASSERT(cond, ...) ((void)0)

#endif // ENGINE_DEBUG_BUILD
