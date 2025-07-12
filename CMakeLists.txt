cmake_minimum_required(VERSION 3.10)
project(krabascript)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE KSC_SOURCES "src/ks compiler/*.cpp")

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBZIP REQUIRED libzip)
include_directories(${LIBZIP_INCLUDE_DIRS})
link_directories(${LIBZIP_LIBRARY_DIRS})

add_executable(krabascript ${KSC_SOURCES})

target_link_libraries(krabascript ${LIBZIP_LIBRARIES})