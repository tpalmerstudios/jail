cmake_minimum_required (VERSION 3.21)
project (jail LANGUAGES CXX)

add_compile_options("-Wextra" "-ggdb")

set (SRC_DIR "${PROJECT_SOURCE_DIR}/src/")
set (INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include/")

set (ENGINE_DIR "${PROJECT_SOURCE_DIR}/JailEngine/")
add_subdirectory (JailEngine)

file (GLOB HEADER_FILES "${INCLUDE_DIR}/*.h")
file (GLOB SRC_FILES "${SRC_DIR}/*.cpp")
file (GLOB ENGINE_SRC_FILES "${ENGINE_DIR}/src/*.cpp")

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/")
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
if (EXISTS "${CMAKE_CURRENT_BINARY_DIR}/bin/compile_commands.json")
  EXECUTE_PROCESS (COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_BINARY_DIR}/bin/compile_commands.json
    ${CMAKE_CURRENT_SOURCE_DIR}/bin/compile_commands.json)
endif ()

add_executable (jail ${HEADER_FILES} ${SRC_FILES} ${ENGINE_SRC_FILES})

set_target_properties (JailEngine PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(jail PUBLIC "${ENGINE_DIR}/include/" "${INCLUDE_DIR}")
target_link_libraries(jail PUBLIC JailEngine)

