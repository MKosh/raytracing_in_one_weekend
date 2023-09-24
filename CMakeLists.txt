cmake_minimum_required(VERSION 3.19)

project(RTWeekend LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

set(SOURCE src/raytracing_in_one_weekend.cc)

include_directories(src)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(inOneWeekend ${SOURCE})

message(STATUS "Compiler ID: " ${CMAKE_CXX_COMPILER_ID})

set(DEBUG_OPTIONS "-Wall;-Wextra;-Wpedantic;-Werror;-g")
set(RELEASE_OPTIONS "-o3")

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  message("*** Using MS compiler")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  message("*** Using GNU compiler")
  # target_compile_options(inOneWeekend PRIVATE -Wall -Wextra -Wpedantic -Werror -g)
  target_compile_options(inOneWeekend PRIVATE "$<$<CONFIG:DEBUG>:${DEBUG_OPTIONS}>")
  target_compile_options(inOneWeekend PRIVATE "$<$<CONFIG:RELEASE>:${RELEASE_OPTIONS}>")
endif()


