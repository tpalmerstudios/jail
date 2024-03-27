cmake_minimum_required (VERSION 3.21)
project (JailEngine LANGUAGES CXX)

set (INCLUDE_DIR, "${PROJECT_SOURCE_DIR}/include/")
set (SRC_DIR, "${PROJECT_SOURCE_DIR}/src/")


file (GLOB ENGINE_HEADER_FILES "${INCLUDE_DIR}/*.h")
file (GLOB SRC_FILES "${SRC_DIR}/*.cpp")

add_library (JailEngine)

target_sources (JailEngine PUBLIC ${ENGINE_HEADER_FILES})


