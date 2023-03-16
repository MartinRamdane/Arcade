cmake_minimum_required(VERSION 3.16)

project(arcade VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -lncurses -I/usr/local/Cellar/sfml/2.5.1_2/include -L/usr/local/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-window -lsfml-system")
set(SRC_FILES main.cpp
Core.cpp
LibMenu.cpp)
add_subdirectory(src)
set(CMAKE_SHARED_LIBRARY_PREFIX "arcade_")
set(CMAKE_SHARED_LIBRARY_SUFFIX ".so")
add_library(ncurses SHARED src/DisplayNcurse.cpp)
add_library(foo SHARED src/foo.cpp)
add_library(foogame SHARED src/foogame.cpp)
# utilisez le chemin complet pour la bibliothèque SFML
# include_directories(/usr/local/include)
# link_directories(/usr/local/lib)
add_library(sfml SHARED src/DisplaySfml.cpp)
set_target_properties(ncurses PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../lib/)
set_target_properties(foo PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../lib/)
set_target_properties(foogame PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../lib/)
set_target_properties(sfml PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../lib/)
# spécifiez le chemin complet de la bibliothèque SFML ici libsfml-graphics.2.5.1
#target_link_libraries(sfml PRIVATE /usr/local/lib/libsfml-graphics.2.5.1.dylib /usr/local/lib/libsfml-window.2.5.1.dylib /usr/local/lib/libsfml-system.2.5.1.dylib /usr/local/Cellar/freetype)
target_link_libraries(${PROJECT_NAME} PRIVATE dl)
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../
)
target_link_libraries(${PROJECT_NAME} PRIVATE dl)
