cmake_minimum_required(VERSION 3.16)

project(arcade VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(SRC_FILES main.cpp
    Core.cpp
    LibMenu.cpp
    AGameModule.cpp
    Libs.cpp)
add_subdirectory(src)
set(CMAKE_SHARED_LIBRARY_PREFIX "arcade")
set(CMAKE_SHARED_LIBRARY_SUFFIX ".so")
add_library(_ncurses SHARED src/DisplayNcurse.cpp)
add_library(_snake SHARED src/GameSnake.cpp
                        src/AGameModule.cpp)
if (APPLE)
    include_directories(/usr/local/Cellar/sfml/2.5.1_2/include)
    link_directories(/usr/local/Cellar/sfml/2.5.1_2/lib)
endif()
add_library(_sfml SHARED src/DisplaySfml.cpp)
if(APPLE)
    include_directories(/usr/local/Cellar/sdl2/2.26.4/include)
    link_directories(/usr/local/Cellar/sdl2/2.26.4/lib)
    include_directories(/usr/local/Cellar/sdl2_image/2.6.3/include)
    link_directories(/usr/local/Cellar/sdl2_image/2.6.3/lib)
    include_directories(/usr/local/Cellar/sdl2_ttf/2.20.2/include)
    link_directories(/usr/local/Cellar/sdl2_ttf/2.20.2/lib)
endif()
add_library(_sdl2 SHARED src/DisplaySdl2.cpp)
set_target_properties(_ncurses PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../lib/)
set_target_properties(_sfml PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../lib/)
set_target_properties(_snake PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../lib/)
set_target_properties(_sdl2 PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../lib/)
target_link_libraries(${PROJECT_NAME} PRIVATE dl)
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../
)
target_link_libraries(${PROJECT_NAME} PRIVATE dl)
target_link_libraries(_sdl2 PRIVATE SDL2 SDL2_ttf SDL2_image)
target_link_libraries(_sfml PRIVATE sfml-graphics sfml-window sfml-system)
target_link_libraries(_ncurses PRIVATE ncurses)
