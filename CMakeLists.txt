cmake_minimum_required(VERSION 2.8)

PROJECT(nes)

# Define the operating system types.
set(WINDOWS_ENUM 0)
set(UNIX_ENUM 1)

# Define the compiler types.
set(GCC_ENUM 2)
set(MINGW_ENUM 3)
set(VISUAL_STUDIO_ENUM 4)

# Define the render systems.
set(SDL_ENUM 5)
set(GLX_ENUM 6)

# Define the architecture.
set(X86_ENUM 7)
set(X64_ENUM 8)

# Detect the operating system.
if (WIN32)
  set(OPERATING_SYSTEM ${WINDOWS_ENUM})
elseif (UNIX)
  set(OPERATING_SYSTEM ${UNIX_ENUM})
else (WIN32)
  message(FATAL_ERROR "An unknown operating system is being used." )
endif (WIN32)

# Detect the compiler.
if (MSVC)
  set(COMPILER ${VISUAL_STUDIO_ENUM})
elseif (MINGW)
  set(COMPILER ${MINGW_ENUM})
elseif (CMAKE_COMPILER_IS_GNUCC)
  set(COMPILER ${GCC_ENUM})
else (MSVC)
  message(FATAL_ERROR "An unknown compiler is being used." )
endif (MSVC)

SET(DARKENTITY_PATH ${CMAKE_CURRENT_SOURCE_DIR}/darkentity)
SET(DARKENTITY_PROJECT nes)

set(CMAKE_BUILD_TYPE Debug)

# Set user specified flags.
if (MSVC)
set(CMAKE_CXX_FLAGS "-DGLEW_STATIC -D_USE_MATH_DEFINES")
else ()
set(CMAKE_CXX_FLAGS "-DGLEW_STATIC -D_USE_MATH_DEFINES -DDEBUG -g -Wall -O0 -std=c++0x")
endif()

set(SRC_DARKENTITY_GAME
  ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/display.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/renderer.cpp
  
  ${CMAKE_CURRENT_SOURCE_DIR}/src/librocket/gui_renderer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/librocket/nes_element.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/librocket/system_interface.cpp
  
  ${CMAKE_CURRENT_SOURCE_DIR}/src/ui/window.cpp
  
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/nes_emulator.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/system.cpp
)

set(SRC_GLEW
  ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glew-1.10.0/glew.cpp
)

find_package(OpenGL)
if (OPENGL_FOUND)
  MESSAGE("OpenGL Correctly Found")
  include_directories(${OPENGL_INCLUDE_DIR})
else (OPENGL_FOUND)
  MESSAGE("OpenGL environment missing")
endif (OPENGL_FOUND)

# Output the version to the Version.h file.
configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/src/system.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/src/system.h"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glew-1.10.0/include)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(${DARKENTITY_PATH})