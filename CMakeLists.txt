cmake_minimum_required(VERSION 3.10)
project(weird_sandbox)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(OpenGL_GL_PREFERENCE "GLVND")

add_subdirectory(lib/glfw)
add_subdirectory(lib/glad)

file(GLOB_RECURSE SOURCE_FILES
  # BASE FILES
	${CMAKE_SOURCE_DIR}/src/base/base_arena.cpp
  
  # ENGINE FILES
	${CMAKE_SOURCE_DIR}/src/engine/engine_core.cpp
	${CMAKE_SOURCE_DIR}/src/engine/engine_entry.cpp

  # OS FILES
	${CMAKE_SOURCE_DIR}/src/os/os_core.cpp

  # RENDER FILES
	${CMAKE_SOURCE_DIR}/src/render/render_core.cpp

)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME}
	PRIVATE ${CMAKE_SOURCE_DIR}/lib/glfw/include
	PRIVATE ${CMAKE_SOURCE_DIR}/lib/glad/include
	PRIVATE ${CMAKE_SOURCE_DIR}/src
)

find_package(OpenGL REQUIRED)

if (WIN32)
	target_link_libraries(${PROJECT_NAME} PRIVATE glfw opengl32 glad)
else()
	target_link_libraries(${PROJECT_NAME} PRIVATE glfw GL glad)
endif ()
