#include "base_core.h"
#include "base_types.h"
#include "base_log.h"

int main(i32 argc, char **argv)
{
  const char *os_string;
  const char *compiler_string;

#if OS_WINDOWS 
  os_string = "Windows";
#elif OS_LINUX 
  os_string = "Linux";
#elif OS_MAC
  os_String = "Mac";
#endif

#if COMPILER_CL 
  compiler_string = "MSVC";
#elif COMPILER_GCC 
  compiler_string = "GCC";
#elif COMPILER_CLANG 
  compiler_string = "Clang";
#endif

  ENGINE_LOG_INFO("Runtime OS : %s", os_string);
  ENGINE_LOG_WARN("Compiler   : %s", compiler_string);
}