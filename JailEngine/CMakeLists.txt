cmake_minimum_required (VERSION 3.21)
project (JailEngine LANGUAGES CXX)

set (INCLUDE_DIR, "${PROJECT_SOURCE_DIR}/include/")

file (GLOB ENGINE_HEADER_FILES "${INCLUDE_DIR}/*.h")

add_library (JailEngine)

target_sources (JailEngine PUBLIC ${ENGINE_HEADER_FILES})


