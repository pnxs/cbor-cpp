# project
cmake_minimum_required(VERSION 3.12)
project(cborcpp VERSION 0.1.0 LANGUAGES CXX)
set(TARGET_NAME cborcpp)
set(EXPORT_NAME CBOR-CPP)

add_library(${TARGET_NAME} STATIC)
add_library(${EXPORT_NAME}::${EXPORT_NAME} ALIAS ${TARGET_NAME})

# properties
target_sources(${TARGET_NAME}
    PRIVATE
        src/encoder.cpp
        src/decoder.cpp
        src/input.cpp
        src/listener_debug.cpp
        src/output_dynamic.cpp
        src/output_static.cpp
        src/buffer.cpp
)
target_include_directories(${TARGET_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)
target_compile_features(${TARGET_NAME}
    PUBLIC
        cxx_std_14
)
target_compile_options(${TARGET_NAME}
    PRIVATE
        $<$<AND:$<CXX_COMPILER_ID:GNU>,$<NOT:$<BOOL:${CMAKE_CXX_FLAGS}>>>:-O2 -Wall -Wextra -Wpedantic -Werror -Wno-deprecated-declarations>
)
#set_property(TARGET ${TARGET_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
#target_compile_definitions(${TARGET_NAME}
# <none>
#)
#target_link_libraries(${TARGET_NAME}
# <none>
#)

# install
include(GNUInstallDirs)
set_target_properties(${TARGET_NAME} PROPERTIES EXPORT_NAME ${EXPORT_NAME})

install(TARGETS ${TARGET_NAME}
    EXPORT ${TARGET_NAME}-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(EXPORT ${TARGET_NAME}-targets
    NAMESPACE ${EXPORT_NAME}::
    FILE
        ${EXPORT_NAME}Targets.cmake
    DESTINATION
        ${CMAKE_INSTALL_LIBDIR}/cmake/${EXPORT_NAME}
)
install(FILES
    ${CMAKE_SOURCE_DIR}/cmake/${EXPORT_NAME}Config.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${EXPORT_NAME}
)
install(DIRECTORY
    ${CMAKE_CURRENT_SOURCE_DIR}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cborcpp
    PATTERN "*.h"
)

# tests
add_executable(${TARGET_NAME}-tests
    src/tests.cpp
)