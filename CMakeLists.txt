cmake_minimum_required(VERSION 3.16)

project(arcade VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(SRC_FILES main.cpp)
add_subdirectory(src)
add_library(foo SHARED src/foo.cpp)
add_library(bar SHARED src/bar.cpp)
set_target_properties(foo PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../lib/)
set_target_properties(bar PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../lib/)
target_link_libraries(${PROJECT_NAME} PRIVATE dl)
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../
)
target_link_libraries(${PROJECT_NAME} PRIVATE dl)