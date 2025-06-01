#pragma once
#include <base/base_core.h>

#if OS_WINDOWS || OS_LINUX
 #include "./opengl/render_impl_gl_core.cpp"
#endif

