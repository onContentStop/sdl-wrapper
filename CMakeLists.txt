﻿# CMakeLists.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(TOPDIR ${CMAKE_CURRENT_SOURCE_DIR})
message("Exporting compile commands")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Helpers)

add_subdirectory("Helpers")

# Include sub-projects.
project ("SDL_wrapper")
add_subdirectory ("SDL_wrapper")

project(LazyFoo)
add_subdirectory("LazyFoo")

