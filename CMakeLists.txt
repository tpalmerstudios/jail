cmake_minimum_required (VERSION 3.21)
project (jail LANGUAGES CXX)

set (SRC_DIR "${PROJECT_SOURCE_DIR}/src/")
set (INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include/")
set (SDL_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/external/SDL/include")

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build/")
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
file (GLOB_RECURSE HEADER_FILES "${INCLUDE_DIR}/*.h")
file (GLOB_RECURSE SRC_FILES "${SRC_DIR}/*.cpp")

if (EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json")
  EXECUTE_PROCESS (COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
    ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json)
endif ()

include_directories(${SDL_INCLUDE_DIRS})

add_executable (jail ${SRC_FILES} ${HEADER_FILES})

target_include_directories(jail PUBLIC "${INCLUDE_DIR}")
target_link_libraries(jail PUBLIC "${SDL_DIR}" SDL2)

#packageProject(
#  NAME ${PROJECT_NAME}
#  VERSION ${PROJECT_VERSION}
#  NAMESPACE ${PROJECT_NAME}
#  BINARY_DIR ${PROJECT_BINARY_DIR}
#  INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include
#  INCLUDE_DESTINATION include/${PROJECT_NAME}-${PROJECT_VERSION}
#  VERSION_HEADER "${VERSION_HEADER_LOCATION}"
#  COMPATIBILITY SameMajorVersion
#  DEPENDENCIES "sdl2"
#)
