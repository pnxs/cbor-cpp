cmake_minimum_required(VERSION 3.5)
project(cborcpp)

set(CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_STANDARD 14)

add_library(cborcpp OBJECT src/encoder.cpp
        src/decoder.cpp
        src/input.cpp
        src/listener_debug.cpp
        src/output_dynamic.cpp
        src/output_static.cpp
        src/buffer.cpp
        )

target_include_directories(cborcpp
        PUBLIC
            src
        )

add_executable(testing
        $<TARGET_PROPERTY:cborcpp,SOURCES>
        src/tests.cpp)
