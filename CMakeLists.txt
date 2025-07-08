cmake_minimum_required(VERSION 3.10)
project(ksc)
project(ksm)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(ksc src/ksc/main.cpp)
add_executable(ksm src/ksm/main.cpp)