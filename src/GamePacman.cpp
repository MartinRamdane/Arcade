/*
** EPITECH PROJECT, 2023
** GamePacman.cpp
** File description:
** GamePacman
*/

#include "GamePacman.hpp"

GamePacman::GamePacman()
{
    areaWidth = 50;
    areaHeight = 20;
    gameStatus = IGameModule::GAME_STATUS::MENU;
    selectMenu = 1;
    int nbWalls = 1;
    int wallX = MARGIN_LEFT;
    int wallY = MARGIN_TOP;
    for (int i = 0; i < areaWidth; i++) {
        infos["wall" + std::to_string(nbWalls)] = createEntity("./res/snake/snake_wall.png", "█", "yellow", "", wallX, wallY, ENTITY_TYPE::SPRITE, 0, 0, 40);
        wallX++;
        nbWalls++;
    }
    wallX--;
    for (int i = 0; i < areaHeight; i++) {
        infos["wall" + std::to_string(nbWalls)] = createEntity("./res/snake/snake_wall.png", "█", "yellow", "", wallX, wallY, ENTITY_TYPE::SPRITE, 0, 0, 40);
        wallY++;
        nbWalls++;
    }
    wallX = MARGIN_LEFT;
    for (int i = 0; i < areaWidth; i++) {
        infos["wall" + std::to_string(nbWalls)] = createEntity("./res/snake/snake_wall.png", "█", "yellow", "", wallX, wallY, ENTITY_TYPE::SPRITE, 0, 0, 40);
        wallX++;
        nbWalls++;
    }
    wallY = MARGIN_TOP; wallX = MARGIN_LEFT;
    for (int i = 0; i < areaHeight; i++) {
        infos["wall" + std::to_string(nbWalls)] = createEntity("./res/snake/snake_wall.png", "█", "yellow", "", wallX, wallY, ENTITY_TYPE::SPRITE, 0, 0, 40);
        wallY++;
        nbWalls++;
    }
}

GamePacman::~GamePacman()
{
}

extern "C" IGameModule *create() {
    return new GamePacman();
}

extern "C" void destroy(IGameModule *display) {
    delete display;
}

extern "C" const char *getType() {
    const char *type = "Game";
    return type;
}