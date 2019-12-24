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
set_property(TARGET cborcpp-object PROPERTY POSITION_INDEPENDENT_CODE ON)

add_library(cborcpp INTERFACE)

target_sources(cborcpp
        INTERFACE
        $<TARGET_OBJECTS:cborcpp-object>
        )

target_include_directories(cborcpp
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        )

install(TARGETS cborcpp 
    EXPORT cborcpp-config
)

install(EXPORT cborcpp-config
    FILE cborcpp-config.cmake
    NAMESPACE cborcpp::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cborcpp
)

install(
    FILES
        ${CMAKE_BINARY_DIR}/cmake/cborcpp-config.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cborcpp
)

export(EXPORT cborcpp-config
   FILE ${CMAKE_BINARY_DIR}/cmake/cborcpp-config.cmake
   NAMESPACE cborcpp::
)
#export(TARGETS cborcpp FILE cborcppConfig.cmake)

add_executable(testing
        $<TARGET_PROPERTY:cborcpp-object,SOURCES>
        src/tests.cpp)

