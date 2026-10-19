cmake_minimum_required(VERSION 3.16)
project(host_inspector VERSION 2.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra)

add_executable(host_inspector host-inspector/main.cpp host-inspector/cpucollector.cpp)
