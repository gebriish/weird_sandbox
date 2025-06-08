cmake_minimum_required(VERSION 3.10)
project(WeirdSandbox)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(OpenGL_GL_PREFERENCE "GLVND")

set(ENGINE_NAME "engine")
set(GAME_NAME "sandbox")

add_executable(${ENGINE_NAME} src/engine/engine_main.cpp)

target_include_directories(${ENGINE_NAME} 
	PRIVATE lib/glad
	PRIVATE src
)

#if(WIN32)
#	target_link_libraries(${ENGINE_NAME} PRIVATE opengl32)
#elseif(APPLE)
#	target_link_libraries(${ENGINE_NAME} PRIVATE OpenGL)
#else() # Linux and other UNIX
#	target_link_libraries(${ENGINE_NAME} PRIVATE GL)
#endif()

set_target_properties(${ENGINE_NAME} PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
	OUTPUT_NAME ${GAME_NAME}_app
)
