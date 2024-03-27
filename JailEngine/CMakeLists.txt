cmake_minimum_required (VERSION 3.21)
project (JailEngine LANGUAGES CXX)

add_compile_options("-Wextra" "-ggdb")

find_package (OpenGL REQUIRED)
find_package (GLEW REQUIRED)

set (INCLUDE_DIR, "${PROJECT_SOURCE_DIR}/include/")
set (SRC_DIR, "${PROJECT_SOURCE_DIR}/src/")

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/")
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (EXISTS "${CMAKE_CURRENT_BINARY_DIR}/bin/compile_commands.json")
  EXECUTE_PROCESS (COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_BINARY_DIR}/bin/compile_commands.json
    ${CMAKE_CURRENT_SOURCE_DIR}/bin/compile_commands.json)
endif ()

file (GLOB ENGINE_HEADER_FILES "${INCLUDE_DIR}/*.h")
file (GLOB SRC_FILES "${SRC_DIR}/*.cpp")

add_library (JailEngine)

target_sources (JailEngine PUBLIC ${ENGINE_HEADER_FILES})


