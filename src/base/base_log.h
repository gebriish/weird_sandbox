#pragma once

#include "./base_core.h"
#include "./base_types.h"
#include <stdio.h>

enum TextColor /* for ascii logging */
{
	TEXT_COLOR_RED = 0,
	TEXT_COLOR_WHITE,
	TEXT_COLOR_YELLOW,
	TEXT_COLOR_GREEN,
	TEXT_COLOR_COUNT
};
 
template <typename ...Args>
force_inline void _log(const char *prefix, const char *msg, TextColor color, Args... args)
{
	local_persist const char* textColorTable[TEXT_COLOR_COUNT] {
		"\x1b[31m", // Red
    "\x1b[37m", // White
    "\x1b[33m", // Yellow
    "\x1b[32m"  // Green	
	};

	char formatBuffer[8192] = {0};
	sprintf(formatBuffer, "%s %s %s\033[0m", textColorTable[color], prefix, msg);

	char textBuffer[8192] = {0};
	sprintf(textBuffer, formatBuffer, args...);
	puts(textBuffer);
}

#define ENGINE_LOG_INFO(msg, ...)  _log("TRACE : ", msg, TEXT_COLOR_GREEN, ##__VA_ARGS__)
#define ENGINE_LOG_WARN(msg, ...)  _log("WARN  : ", msg, TEXT_COLOR_YELLOW, ##__VA_ARGS__)
#define ENGINE_LOG_ERROR(msg, ...) _log("ERROR : ", msg, TEXT_COLOR_RED, ##__VA_ARGS__)

#if OS_WINDOWS 
# define ENGINE_DEBUG_BREAK() __debugbreak()
#elif OS_LINUX
# define ENGINE_DEBUG_BREAK() __builtin_debugtrap()
#elif OS_MAC
# define ENGINE_DEBUG_BREAK() __builtin_trap[]
#endif

#define ENGINE_ASSERT(x, msg, ...)                     \
{                                                      \
	if (!(x)) {																					 \
		ENGINE_LOG_ERROR(msg, ##__VA_ARGS__);              \
		ENGINE_DEBUG_BREAK();                              \
	}                                                    \
}                                                      \
