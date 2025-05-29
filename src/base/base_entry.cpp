#include "base_core.h"
#include "base_types.h"
#include "base_log.h"

#if OS_WINDOWS && !ENGINE_DEBUG_MODE
#include <windows.h> // Required for HINSTANCE etc.
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int main(int argc, char **argv)
#endif
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
