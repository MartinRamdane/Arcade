cmake_minimum_required(VERSION 3.16)

project(arcade VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
if(APPLE)
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -lncurses -I/usr/local/Cellar/sfml/2.5.1_2/include -L/usr/local/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-window -lsfml-system")
elseif(UNIX)
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -lncurses -lsfml-graphics -lsfml-window -lsfml-system -lSDL2 -lSDL2_ttf")
endif()
set(SRC_FILES main.cpp
    Core.cpp
    LibMenu.cpp)
add_subdirectory(src)
set(CMAKE_SHARED_LIBRARY_PREFIX "arcade_")
set(CMAKE_SHARED_LIBRARY_SUFFIX ".so")
add_library(ncurses SHARED src/DisplayNcurse.cpp)
add_library(foo SHARED src/foo.cpp)
add_library(foogame SHARED src/foogame.cpp)
add_library(snake SHARED src/GameSnake.cpp
                        src/AGameModule.cpp)
add_library(sfml SHARED src/DisplaySfml.cpp)
if(APPLE)
    include_directories(/opt/homebrew/Cellar/sdl2/2.26.4/include)
    link_directories(/opt/homebrew/Cellar/sdl2/2.26.4/lib)
    include_directories(/opt/homebrew/Cellar/sdl2_ttf/2.20.2/include)
    link_directories(/opt/homebrew/Cellar/sdl2_ttf/2.20.2/lib)
endif()
add_library(sdl2 SHARED src/DisplaySdl2.cpp)
set_target_properties(ncurses PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../lib/)
set_target_properties(foo PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../lib/)
set_target_properties(foogame PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../lib/)
set_target_properties(sfml PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../lib/)
set_target_properties(snake PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../lib/)
set_target_properties(sdl2 PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../lib/)
target_link_libraries(${PROJECT_NAME} PRIVATE dl)
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../
)
target_link_libraries(${PROJECT_NAME} PRIVATE dl)
target_link_libraries(sdl2 PRIVATE SDL2 SDL2_ttf)

