cmake_minimum_required(VERSION 3.0)

project(Menli)

add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
)

set(SRC_DIR ./sources)

add_library(menli SHARED
    ${SRC_DIR}/graph.cpp
    ${SRC_DIR}/neurons.cpp
    ${SRC_DIR}/synapses.cpp
)
target_include_directories(menli PUBLIC include)
target_include_directories(menli PRIVATE sources)

target_compile_features(menli
    PRIVATE cxx_variadic_templates)

add_executable(menli.out
    ${SRC_DIR}/main.cpp
)
target_link_libraries(menli.out PUBLIC menli)


if (CMAKE_VERSION VERSION_LESS "3.1")
    add_definitions(-std=c++14)
else()
    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

