cmake_minimum_required(VERSION 3.10)
project(WeirdSandbox)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(OpenGL_GL_PREFERENCE "GLVND")

set(ENGINE_NAME "Engine")
set(GAME_NAME "Sandbox")

# === build game as an so ===
add_library(${GAME_NAME} SHARED src/game/game_main.cpp)
set_target_properties(${GAME_NAME} PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
	OUTPUT_NAME ${GAME_NAME}
)

target_include_directories(${GAME_NAME} 
	PRIVATE lib/glad/include
	PRIVATE lib/glfw/include
	PRIVATE src
)

# === dependencies ===
add_subdirectory(lib/glfw)
add_subdirectory(lib/glad)

# === build engine as an executable ===
add_executable(${ENGINE_NAME} src/engine/engine_main.cpp)

target_include_directories(${ENGINE_NAME} 
	PRIVATE lib/glad/include
	PRIVATE lib/glfw/include
	PRIVATE src
)

find_package(OpenGL REQUIRED)

if(WIN32)
	target_link_libraries(${ENGINE_NAME} PRIVATE opengl32 glfw glad)
elseif(APPLE)
	target_link_libraries(${ENGINE_NAME} PRIVATE OpenGL glfw glad) # Not really sure about mac support
else()
	target_link_libraries(${ENGINE_NAME} PRIVATE GL dl glfw glad)  # Link dl for Linux hot-reload
endif()

set_target_properties(${ENGINE_NAME} PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
	OUTPUT_NAME ${GAME_NAME}_app
)

