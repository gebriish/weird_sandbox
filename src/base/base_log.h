#ifndef BASE_LOG_H
#define BASE_LOG_H

#if ENGINE_DEBUG_MODE
#include <stdio.h>
#include "base_core.h"

#define COLOR_RESET   "\x1b[0m"
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_WHITE   "\x1b[37m"

#define LOG_INFO(fmt, ...)   fprintf(stderr, COLOR_CYAN    "[INFO]  : " fmt COLOR_RESET "\n", ##__VA_ARGS__)
#define LOG_WARN(fmt, ...)   fprintf(stderr, COLOR_YELLOW  "[WARN]  : " fmt COLOR_RESET "\n", ##__VA_ARGS__)
#define LOG_ERRO(fmt, ...)   fprintf(stderr, COLOR_RED     "[ERROR] : " fmt COLOR_RESET "\n", ##__VA_ARGS__)
#define LOG_DEBG(fmt, ...)   fprintf(stderr, COLOR_MAGENTA "[DEBUG] : " fmt COLOR_RESET "\n", ##__VA_ARGS__)
#define LOG_SUCC(fmt, ...)   fprintf(stderr, COLOR_GREEN   "[OK]    : " fmt COLOR_RESET "\n", ##__VA_ARGS__)

#define ASSERT_MSG(expr, msg, ...) do {                                                                    \
	if (!(expr)) {                                                                                           \
		fprintf(stderr, COLOR_RED "[ASSERT] %s:%d: " msg COLOR_RESET "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
		DEBUG_BREAK();                                                                                         \
		abort();                                                                                               \
	}                                                                                                        \
} while (0)
#define ASSERT(expr) ASSERT_MSG((expr), "Assertion failed: %s", #expr)

#else

#define LOG_INFO(fmt, ...) ((void)0)
#define LOG_WARN(fmt, ...) ((void)0)
#define LOG_ERRO(fmt, ...) ((void)0)
#define LOG_DEBG(fmt, ...) ((void)0)
#define LOG_SUCC(fmt, ...) ((void)0)
#define ASSERT_MSG(expr, msg, ...) ((void)0)
#define ASSERT(expr) ((void)0)

#endif

#endif
