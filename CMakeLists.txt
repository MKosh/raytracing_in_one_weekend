cmake_minimum_required(VERSION 3.1)

project(RTWeekend LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

set(SOURCE src/raytracing_in_one_weekend.cc src/vec3.h)

include_directories(src)

message(STATUS "Compiler ID: " ${CMAKE_CXX_COMPILER_ID})

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  message("*** Using MS compiler")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  message("*** Using GNU compiler")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(inOneWeekend ${SOURCE})
