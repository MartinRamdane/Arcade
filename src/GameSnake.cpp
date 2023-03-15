/*
** EPITECH PROJECT, 2023
** GameSnake.cpp
** File description:
** GameSnake
*/

#include "GameSnake.hpp"

GameSnake::GameSnake() : areaWidth(50), areaHeight(20)
{
    gameStatus = IGameModule::GAME_STATUS::MENU;
    selectMenu = 1;
    hasMeal = true;
    int nbWalls = 1;
    int wallX = 2;
    int wallY = 1;
    for (int i = 0; i < areaWidth; i++) {
        infos["wall" + std::to_string(nbWalls)] = createEntity("", "█", "white", "", wallX, wallY, false);
        wallX++;
        nbWalls++;
    }
    wallX--;
    for (int i = 0; i < areaHeight; i++) {
        infos["wall" + std::to_string(nbWalls)] = createEntity("", "█", "white", "", wallX, wallY, false);
        wallY++;
        nbWalls++;
    }
    wallX = 2;
    for (int i = 0; i < areaWidth; i++) {
        infos["wall" + std::to_string(nbWalls)] = createEntity("", "█", "white", "", wallX, wallY, false);
        wallX++;
        nbWalls++;
    }
    wallY = 1; wallX = 2;
    for (int i = 0; i < areaHeight; i++) {
        infos["wall" + std::to_string(nbWalls)] = createEntity("", "█", "white", "", wallX, wallY, false);
        wallY++;
        nbWalls++;
    }
    initMenu();
}

GameSnake::~GameSnake()
{
}

void GameSnake::startGame(std::string username)
{
    this->username = username;
}

void GameSnake::initGame()
{
    playerPart = 4;
    infos.erase("username");
    infos.erase("score");
    infos.erase("looseTitle");
    infos.erase("looseTitle2");
    infos.erase("looseTitle3");
    infos.erase("looseTitle4");
    infos.erase("looseTitle5");
    infos.erase("retryButton");
    infos.erase("gameTitle");
    infos.erase("playButton");
    infos.erase("quitButton");
    infos.erase("gameTitle2");
    infos.erase("gameTitle3");
    infos.erase("gameTitle4");
    infos.erase("gameTitle5");
    infos["playerHead"] = createEntity("", ">", "white", "green", (areaWidth / 2 + 2), (areaHeight / 2 + 1), false);
    infos["playerPart1"] = createEntity("", "o", "white", "green", (areaWidth / 2 + 1), (areaHeight / 2 + 1), false);
    infos["playerPart2"] = createEntity("", "o", "white", "green", (areaWidth / 2), (areaHeight / 2 + 1), false);
    infos["playerPart3"] = createEntity("", "o", "white", "green", (areaWidth / 2 - 1), (areaHeight / 2 + 1), false);
    playerDir = RIGHT;
    spawnMeal();
}

bool GameSnake::checkCollision()
{
    if (infos["playerHead"].x == 2 || infos["playerHead"].x == areaWidth + 1 || infos["playerHead"].y == 1 || infos["playerHead"].y == areaHeight + 1) {
        return true;
    }
    for (int i = 1; i < playerPart; i++) {
        if (infos["playerHead"].x == infos["playerPart" + std::to_string(i)].x && infos["playerHead"].y == infos["playerPart" + std::to_string(i)].y) {
            return true;
        }
    }
    return false;
}


void GameSnake::update(std::string key)
{
    if (gameStatus == IGameModule::GAME_STATUS::MENU) {
        updateMenu(key);
    } else if (gameStatus == IGameModule::GAME_STATUS::IN_GAME) {
        updateGame(key);
    } else if (gameStatus == IGameModule::GAME_STATUS::FINISHED) {
        updateLoose(key);
    }
}

void GameSnake::updateMenu(std::string key)
{
    if (key == "UP" && infos["playButton"].color == "white" && selectMenu == 2) {
        infos["playButton"].color = "black";
        infos["playButton"].background_color = "white";
        infos["quitButton"].color = "white";
        infos["quitButton"].background_color = "";
        selectMenu = 1;
    } else if (key == "DOWN" && infos["quitButton"].color == "white" && selectMenu == 1) {
        infos["quitButton"].color = "black";
        infos["quitButton"].background_color = "white";
        infos["playButton"].color = "white";
        infos["playButton"].background_color = "";
        selectMenu = 2;
    }
    if (key == " " && selectMenu == 1) {
        initGame();
        gameStatus = IGameModule::GAME_STATUS::IN_GAME;
    } else if (key == " " && selectMenu == 2) {
        exit(0);
    }
}

void GameSnake::initLoose()
{
    infos.erase("playerHead");
    infos.erase("meal");
    for (int i = 1; i < playerPart; i++) {
        infos.erase("playerPart" + std::to_string(i));
    }
    infos.erase("retryButton");
    infos.erase("gameTitle");
    infos.erase("playButton");
    infos.erase("quitButton");
    infos.erase("gameTitle2");
    infos.erase("gameTitle3");
    infos.erase("gameTitle4");
    infos.erase("gameTitle5");
    infos["looseTitle"] = createEntity("", " ██████   ██████         ██ ", "white", "", (areaWidth / 2 - 12), (areaHeight / 2 - 7), false);
    infos["looseTitle2"] = createEntity("", "██       ██           ██  ██", "white", "", (areaWidth / 2 - 12), (areaHeight / 2 - 6), false);
    infos["looseTitle3"] = createEntity("", "██   ███ ██   ███         ██", "white", "", (areaWidth / 2 - 12), (areaHeight / 2 - 5), false);
    infos["looseTitle4"] = createEntity("", "██    ██ ██    ██     ██  ██", "white", "", (areaWidth / 2 - 12), (areaHeight / 2 - 4), false);
    infos["looseTitle5"] = createEntity("", " ██████   ██████         ██ ", "white", "", (areaWidth / 2 - 12), (areaHeight / 2 - 3), false);
    infos["username"] = createEntity("", this->username, "white", "", (areaWidth / 2 - (this->username.length() / 2) + 1), (areaHeight / 2 - 1), false);
    infos["score"] = createEntity("", std::to_string(score), "white", "", (areaWidth / 2 - (std::to_string(score).length() / 2) + 1), (areaHeight / 2), false);
    infos["retryButton"] = createEntity("", "Retry", "black", "white", (areaWidth / 2 - 1), (areaHeight / 2 + 2), false);
    infos["quitButton"] = createEntity("", "Quit", "white", "", (areaWidth / 2 - 1), (areaHeight / 2 + 4), false);
}

void GameSnake::updateLoose(std::string key)
{
    if (key == "UP" && infos["retryButton"].color == "white" && selectMenu == 2) {
        infos["retryButton"].color = "black";
        infos["retryButton"].background_color = "white";
        infos["quitButton"].color = "white";
        infos["quitButton"].background_color = "";
        selectMenu = 1;
    } else if (key == "DOWN" && infos["quitButton"].color == "white" && selectMenu == 1) {
        infos["quitButton"].color = "black";
        infos["quitButton"].background_color = "white";
        infos["retryButton"].color = "white";
        infos["retryButton"].background_color = "";
        selectMenu = 2;
    }
    if (key == " " && selectMenu == 1) {
        initGame();
        gameStatus = IGameModule::GAME_STATUS::IN_GAME;
    } else if (key == " " && selectMenu == 2) {
        selectMenu = 1;
        initMenu();
        gameStatus = IGameModule::GAME_STATUS::MENU;
    }
}

void GameSnake::initMenu()
{
    infos.erase("username");
    infos.erase("score");
    infos.erase("retryButton");
    infos.erase("looseTitle");
    infos.erase("quitButton");
    infos.erase("looseTitle2");
    infos.erase("looseTitle3");
    infos.erase("looseTitle4");
    infos.erase("looseTitle5");
    infos["gameTitle"] = createEntity("", "███████ ███    ██  █████  ██   ██ ███████", "white", "", (areaWidth / 2 - 19), (areaHeight / 2 - 7), false);
    infos["gameTitle2"] = createEntity("", "██      ████   ██ ██   ██ ██  ██  ██     ", "white", "", (areaWidth / 2 - 19), (areaHeight / 2 - 6), false);
    infos["gameTitle3"] = createEntity("", "███████ ██ ██  ██ ███████ █████   █████  ", "white", "", (areaWidth / 2 - 19), (areaHeight / 2 - 5), false);
    infos["gameTitle4"] = createEntity("", "     ██ ██  ██ ██ ██   ██ ██  ██  ██     ", "white", "", (areaWidth / 2 - 19), (areaHeight / 2 - 4), false);
    infos["gameTitle5"] = createEntity("", "███████ ██   ████ ██   ██ ██   ██ ███████", "white", "", (areaWidth / 2 - 19), (areaHeight / 2 - 3), false);
    infos["playButton"] = createEntity("", "Play", "black", "white", (areaWidth / 2 - 1), (areaHeight / 2 + 2), false);
    infos["quitButton"] = createEntity("", "Quit", "white", "", (areaWidth / 2 - 1), (areaHeight / 2 + 4), false);
}

void GameSnake::updateGame(std::string key)
{
    if (checkCollision() == true) {
        initLoose();
        gameStatus = IGameModule::GAME_STATUS::FINISHED;
        return;
    }
    if (infos["playerHead"].x == infos["meal"].x && infos["playerHead"].y == infos["meal"].y) {
        hasMeal = false;
        score += 10;
        infos.erase("meal");
        spawnMeal();
        infos["playerPart" + std::to_string(playerPart)] = createEntity("", "o", "white", "green", infos["playerPart" + std::to_string(playerPart - 1)].x, infos["playerPart" + std::to_string(playerPart - 1)].y, false);
        playerPart++;
    }
    if (key == "UP" && playerDir != UP) {
        infos["playerHead"].x -= 1;
        infos["playerHead"].y -= 2;
        infos["playerHead"].text = "⏶";
        playerDir = UP;
    } else if (key == "DOWN" && playerDir != DOWN) {
        infos["playerHead"].x -= 1;
        infos["playerHead"].y += 2;
        infos["playerHead"].text = "⏷";
        playerDir = DOWN;
    } else if (key == "LEFT" && playerDir != LEFT) {
        infos["playerHead"].text = "⏴";
        playerDir = LEFT;
    } else if (key == "RIGHT" && playerDir != RIGHT) {
        infos["playerHead"].text = "⏵";
        playerDir = RIGHT;
    }
    moveSnake();
}

void GameSnake::spawnMeal()
{
    int x = rand() % areaWidth + 2;
    int y = rand() % areaHeight + 1;
    infos["meal"] = createEntity("", "*", "white", "red", x, y, false);
    hasMeal = true;
}

void GameSnake::moveSnake()
{
    int prevX = infos["playerHead"].x;
    int prevY = infos["playerHead"].y;
    std::vector<std::tuple<int, int>> prevPartPos;
    for (int i = 1; i + 1 < playerPart; i++) {
        std::tuple <int, int> pos = std::make_tuple(infos["playerPart" + std::to_string(i)].x, infos["playerPart" + std::to_string(i)].y);
        prevPartPos.push_back(pos);
    }
    infos["playerPart1"].x = prevX;
    infos["playerPart1"].y = prevY;
    for (int i = 2, y = 0; i < playerPart; i++, y++) {
        infos["playerPart" + std::to_string(i)].x = std::get<0>(prevPartPos[y]);
        infos["playerPart" + std::to_string(i)].y = std::get<1>(prevPartPos[y]);
    }
    if (playerDir == UP) {
        infos["playerHead"].y -= 1;
    }
    if (playerDir == DOWN) {
        infos["playerHead"].y += 1;
    }
    if (playerDir == LEFT) {
        infos["playerHead"].x -= 1;
    }
    if (playerDir == RIGHT) {
        infos["playerHead"].x += 1;
    }
}

extern "C" IGameModule* create() {
    return new GameSnake();
}

extern "C" void destroy(IGameModule* obj) {
    delete obj;
}

extern "C" std::string getType() {
    return "Game";
}