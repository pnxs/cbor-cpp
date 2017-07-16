cmake_minimum_required(VERSION 3.5)
project(cborcpp)

set(CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_STANDARD 14)

add_library(cborcpp-object OBJECT src/encoder.cpp
        src/decoder.cpp
        src/input.cpp
        src/listener_debug.cpp
        src/output_dynamic.cpp
        src/output_static.cpp
        src/buffer.cpp
        )

add_library(cborcpp INTERFACE)

target_sources(cborcpp
        INTERFACE
        $<TARGET_OBJECTS:cborcpp-object>
        )

target_include_directories(cborcpp
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        )

install(TARGETS cborcpp EXPORT cborcppConfig)
install(EXPORT cborcppConfig DESTINATION cmake)
export(TARGETS cborcpp FILE cborcppConfig.cmake)

add_executable(testing
        $<TARGET_PROPERTY:cborcpp-object,SOURCES>
        src/tests.cpp)

