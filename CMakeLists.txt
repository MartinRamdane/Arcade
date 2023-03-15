cmake_minimum_required(VERSION 3.16)

project(arcade VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
include_directories(/usr/local/include)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -lncurses")
set(SRC_FILES main.cpp
              core.cpp
              LibMenu.cpp)
add_subdirectory(src)
set(CMAKE_SHARED_LIBRARY_PREFIX "arcade_")
set(CMAKE_SHARED_LIBRARY_SUFFIX ".so")
link_directories(/usr/local/lib)
add_library(ncurses SHARED src/DisplayNcurse.cpp)
add_library(foo SHARED src/foo.cpp)
add_library(foogame SHARED src/foogame.cpp)
# utilisez le chemin complet pour la bibliothèque SFML
add_library(sfml SHARED src/DisplaySfml.cpp)
set_target_properties(ncurses PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../lib/)
set_target_properties(foo PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../lib/)
set_target_properties(foogame PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../lib/)
set_target_properties(sfml PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../lib/)
# spécifiez le chemin complet de la bibliothèque SFML ici
target_link_libraries(sfml PRIVATE /usr/local/lib/libsfml-graphics-d.3.0.0.dylib /usr/local/lib/libsfml-window-d.3.0.0.dylib /usr/local/lib/libsfml-system-d.3.0.0.dylib)
target_link_libraries(${PROJECT_NAME} PRIVATE dl)
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../
)
target_link_libraries(${PROJECT_NAME} PRIVATE dl)
