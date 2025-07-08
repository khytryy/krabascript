cmake_minimum_required(VERSION 3.10)
project(krabascript)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add source files
file(GLOB_RECURSE KSC_SOURCES src/ksc/*.cpp)
file(GLOB_RECURSE KSM_SOURCES src/ksm/*.cpp)

add_executable(ksc ${KSC_SOURCES})

add_executable(ksm ${KSM_SOURCES})