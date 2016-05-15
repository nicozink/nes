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

set(CMAKE_BUILD_TYPE Debug)

# Set user specified flags.
if (MSVC)
set(CMAKE_CXX_FLAGS "-DGLEW_STATIC -D_USE_MATH_DEFINES")
else ()
set(CMAKE_CXX_FLAGS "-DGLEW_STATIC -D_USE_MATH_DEFINES -DDEBUG -g -Wall -O0 -std=c++0x")
endif()

set(SRC_MAIN
  ${CMAKE_CURRENT_SOURCE_DIR}/src/librocket/gui_renderer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/librocket/system_interface.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/display.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/renderer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/nes_emulator.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/system.cpp
)

set(SRC_GLEW
  ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glew-1.10.0/glew.cpp
)

if (${OPERATING_SYSTEM} EQUAL ${WINDOWS_ENUM})
  if (${COMPILER} EQUAL ${VISUAL_STUDIO_ENUM})
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/windows/VS2012/include)
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/windows/VS2012/lib)

    file(COPY
      ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/windows/VS2012/SDL.dll
      DESTINATION ${CMAKE_BINARY_DIR}/bin/Debug)
    file(COPY
      ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/windows/VS2012/SDL.dll
      DESTINATION ${CMAKE_BINARY_DIR}/bin/Release)
  elseif (${COMPILER} EQUAL ${MINGW_ENUM})
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/windows/MinGW/include)
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/windows/MinGW/lib)
	
    file(COPY
      ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/windows/MinGW/SDL.dll
      DESTINATION ${CMAKE_BINARY_DIR}/bin)
    
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/librocket/include)
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/librocket/mingw/lib)
	
    file(COPY
      ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/librocket/mingw/bin/libRocketControls.dll
      DESTINATION ${CMAKE_BINARY_DIR}/bin)
      
    file(COPY
      ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/librocket/mingw/bin/libRocketCore.dll
      DESTINATION ${CMAKE_BINARY_DIR}/bin)
     
    file(COPY
      ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/librocket/mingw/bin/libRocketDebugger.dll
      DESTINATION ${CMAKE_BINARY_DIR}/bin)
  endif ()
endif (${OPERATING_SYSTEM} EQUAL ${WINDOWS_ENUM})

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

# Copy resources
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/resources"
  DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glew-1.10.0/include)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_library(LIB_GLEW ${SRC_GLEW})

ADD_EXECUTABLE(
  nes
  ${SRC_MAIN})
  
TARGET_LINK_LIBRARIES(nes SDL LIB_GLEW RocketCore ${OPENGL_LIBRARIES})