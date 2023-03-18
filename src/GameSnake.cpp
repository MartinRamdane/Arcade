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
    int wallX = MARGIN_LEFT;
    int wallY = MARGIN_TOP;
    for (int i = 0; i < areaWidth; i++) {
        infos["wall" + std::to_string(nbWalls)] = createEntity("./res/snake/snake_wall.png", "█", "white", "", wallX, wallY, ENTITY_TYPE::SPRITE, 0, 0, 40);
        wallX++;
        nbWalls++;
    }
    wallX--;
    for (int i = 0; i < areaHeight; i++) {
        infos["wall" + std::to_string(nbWalls)] = createEntity("./res/snake/snake_wall.png", "█", "white", "", wallX, wallY, ENTITY_TYPE::SPRITE, 0, 0, 40);
        wallY++;
        nbWalls++;
    }
    wallX = MARGIN_LEFT;
    for (int i = 0; i < areaWidth; i++) {
        infos["wall" + std::to_string(nbWalls)] = createEntity("./res/snake/snake_wall.png", "█", "white", "", wallX, wallY, ENTITY_TYPE::SPRITE, 0, 0, 40);
        wallX++;
        nbWalls++;
    }
    wallY = MARGIN_TOP; wallX = MARGIN_LEFT;
    for (int i = 0; i < areaHeight; i++) {
        infos["wall" + std::to_string(nbWalls)] = createEntity("./res/snake/snake_wall.png", "█", "white", "", wallX, wallY, ENTITY_TYPE::SPRITE, 0, 0, 40);
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
    score = 0;
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
    infos["playerHead"] = createEntity("./res/snake/snakeHead_right.png", ">", "white", "green", (areaWidth / 2 + 2), (areaHeight / 2 + 1), ENTITY_TYPE::SPRITE_TEXT, 0, 0, 40);
    infos["playerPart1"] = createEntity("", "o", "white", "green", (areaWidth / 2 + 1), (areaHeight / 2 + 1), ENTITY_TYPE::SPRITE_TEXT, 0, 0, 40);
    infos["playerPart2"] = createEntity("", "o", "white", "green", (areaWidth / 2), (areaHeight / 2 + 1), ENTITY_TYPE::SPRITE_TEXT, 0, 0, 40);
    infos["playerPart3"] = createEntity("", "o", "white", "green", (areaWidth / 2 - 1), (areaHeight / 2 + 1), ENTITY_TYPE::SPRITE_TEXT, 0, 0, 40);
    infos["showScoreLabel"] = createEntity("", "Score ", "white", "", MARGIN_LEFT, 1, ENTITY_TYPE::TEXT, 0, 0, 40);
    infos["showScore"] = createEntity("", std::to_string(score), "white", "", MARGIN_LEFT + 9, 1, ENTITY_TYPE::TEXT, MARGIN_LEFT + 14, 0, 40);
    playerDir = RIGHT;
    spawnMeal();
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
    infos["gameTitle"] = createEntity("./res/snake/snake_logo.png", "███████ ███    ██  █████  ██   ██ ███████", "white", "", (areaWidth / 2 - 19), (areaHeight / 2 - 7 + MARGIN_TOP), ENTITY_TYPE::SPRITE, (areaWidth / 2), (areaHeight / 2 - 3 + MARGIN_TOP), 40);
    infos["gameTitle2"] = createEntity("", "██      ████   ██ ██   ██ ██  ██  ██     ", "white", "", (areaWidth / 2 - 19), (areaHeight / 2 - 6 + MARGIN_TOP), ENTITY_TYPE::NONE, 0, 0, 40);
    infos["gameTitle3"] = createEntity("", "███████ ██ ██  ██ ███████ █████   █████  ", "white", "", (areaWidth / 2 - 19), (areaHeight / 2 - 5 + MARGIN_TOP), ENTITY_TYPE::NONE, 0, 0, 40);
    infos["gameTitle4"] = createEntity("", "     ██ ██  ██ ██ ██   ██ ██  ██  ██     ", "white", "", (areaWidth / 2 - 19), (areaHeight / 2 - 4 + MARGIN_TOP), ENTITY_TYPE::NONE, 0, 0, 40);
    infos["gameTitle5"] = createEntity("", "███████ ██   ████ ██   ██ ██   ██ ███████", "white", "", (areaWidth / 2 - 19), (areaHeight / 2 - 3 + MARGIN_TOP), ENTITY_TYPE::NONE, 0, 0, 40);
    infos["playButton"] = createEntity("./res/snake/snake_buttonHover.png", "Play", "yellow", "white", (areaWidth / 2 - 1), (areaHeight / 2 + 2 + MARGIN_TOP), ENTITY_TYPE::SPRITE_TEXT, (areaWidth / 2), (areaHeight / 2 + 2 + MARGIN_TOP), 40);
    infos["quitButton"] = createEntity("./res/snake/snake_button.png", "Quit", "white", "", (areaWidth / 2 - 1), (areaHeight / 2 + 4 + MARGIN_TOP), ENTITY_TYPE::SPRITE_TEXT, (areaWidth / 2), (areaHeight / 2 + 4 + MARGIN_TOP), 40);
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
    infos.erase("showScoreLabel");
    infos.erase("showScore");
    infos["looseTitle"] = createEntity("./res/snake/snake_loose.png", " ██████   ██████         ██ ", "white", "", (areaWidth / 2 - 12), (areaHeight / 2 - 7 + MARGIN_TOP), ENTITY_TYPE::SPRITE, (areaWidth / 2), (areaHeight / 2 - 4 + MARGIN_TOP), 40);
    infos["looseTitle2"] = createEntity("", "██       ██           ██  ██", "white", "", (areaWidth / 2 - 12), (areaHeight / 2 - 6 + MARGIN_TOP), ENTITY_TYPE::NONE, 0, 0, 40);
    infos["looseTitle3"] = createEntity("", "██   ███ ██   ███         ██", "white", "", (areaWidth / 2 - 12), (areaHeight / 2 - 5 + MARGIN_TOP), ENTITY_TYPE::NONE, 0, 0, 40);
    infos["looseTitle4"] = createEntity("", "██    ██ ██    ██     ██  ██", "white", "", (areaWidth / 2 - 12), (areaHeight / 2 - 4 + MARGIN_TOP), ENTITY_TYPE::NONE, 0, 0, 40);
    infos["looseTitle5"] = createEntity("", " ██████   ██████         ██ ", "white", "", (areaWidth / 2 - 12), (areaHeight / 2 - 3 + MARGIN_TOP), ENTITY_TYPE::NONE, 0, 0, 40);
    infos["username"] = createEntity("", this->username, "white", "", (areaWidth / 2 - (this->username.length() / 2) + 1), (areaHeight / 2 - 1 + MARGIN_TOP), ENTITY_TYPE::TEXT, (areaWidth / 2 - username.length()), (areaHeight / 2 - 2 + MARGIN_TOP), 40);
    infos["score"] = createEntity("", std::to_string(score), "white", "", (areaWidth / 2 - (std::to_string(score).length() / 2) + 1), (areaHeight / 2 + MARGIN_TOP), ENTITY_TYPE::TEXT, (areaWidth / 2 - std::to_string(score).length()), (areaHeight / 2 - 1 + MARGIN_TOP), 40);
    infos["retryButton"] = createEntity("./res/snake/snake_buttonHover.png", "Retry", "yellow", "white", (areaWidth / 2 - 1), (areaHeight / 2 + 2 + MARGIN_TOP), ENTITY_TYPE::SPRITE_TEXT, (areaWidth / 2), (areaHeight / 2 + 2 + MARGIN_TOP), 40);
    infos["quitButton"] = createEntity("./res/snake/snake_button.png", "Quit", "white", "", (areaWidth / 2 - 1), (areaHeight / 2 + 4 + MARGIN_TOP), ENTITY_TYPE::SPRITE_TEXT, (areaWidth / 2), (areaHeight / 2 + 4 + MARGIN_TOP), 40);
}

bool GameSnake::checkCollision()
{
    if (infos["playerHead"].x == MARGIN_LEFT || infos["playerHead"].x == areaWidth + 1 || infos["playerHead"].y == MARGIN_TOP || infos["playerHead"].y == areaHeight + MARGIN_TOP) {
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
        infos["playButton"].file = "./res/snake/snake_buttonHover.png";
        infos["playButton"].spriteColor = "yellow";
        infos["playButton"].toUpdate = true;
        infos["quitButton"].color = "white";
        infos["quitButton"].background_color = "";
        infos["quitButton"].file = "./res/snake/snake_button.png";
        infos["quitButton"].spriteColor = "white";
        infos["quitButton"].toUpdate = true;
        selectMenu = 1;
    } else if (key == "DOWN" && infos["quitButton"].color == "white" && selectMenu == 1) {
        infos["quitButton"].color = "black";
        infos["quitButton"].background_color = "white";
        infos["quitButton"].file = "./res/snake/snake_buttonHover.png";
        infos["quitButton"].spriteColor = "yellow";
        infos["quitButton"].toUpdate = true;
        infos["playButton"].color = "white";
        infos["playButton"].background_color = "";
        infos["playButton"].file = "./res/snake/snake_button.png";
        infos["playButton"].spriteColor = "white";
        infos["playButton"].toUpdate = true;
        selectMenu = 2;
    }
    if (key == " " && selectMenu == 1) {
        initGame();
        gameStatus = IGameModule::GAME_STATUS::IN_GAME;
    } else if (key == " " && selectMenu == 2) {
        exit(0);
    }
}

void GameSnake::updateLoose(std::string key)
{
    if (key == "UP" && infos["retryButton"].color == "white" && selectMenu == 2) {
        infos["retryButton"].color = "black";
        infos["retryButton"].background_color = "white";
        infos["retryButton"].file = "./res/snake/snake_buttonHover.png";
        infos["retryButton"].spriteColor = "yellow";
        infos["retryButton"].toUpdate = true;
        infos["quitButton"].color = "white";
        infos["quitButton"].background_color = "";
        infos["quitButton"].file = "./res/snake/snake_button.png";
        infos["quitButton"].spriteColor = "white";
        infos["quitButton"].toUpdate = true;
        selectMenu = 1;
    } else if (key == "DOWN" && infos["quitButton"].color == "white" && selectMenu == 1) {
        infos["quitButton"].color = "black";
        infos["quitButton"].background_color = "white";
        infos["quitButton"].file = "./res/snake/snake_buttonHover.png";
        infos["quitButton"].spriteColor = "yellow";
        infos["quitButton"].toUpdate = true;
        infos["retryButton"].color = "white";
        infos["retryButton"].background_color = "";
        infos["retryButton"].file = "./res/snake/snake_button.png";
        infos["retryButton"].spriteColor = "white";
        infos["retryButton"].toUpdate = true;
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
        infos["playerPart" + std::to_string(playerPart)] = createEntity("", "o", "white", "green", infos["playerPart" + std::to_string(playerPart - 1)].x, infos["playerPart" + std::to_string(playerPart - 1)].y, ENTITY_TYPE::SPRITE, 0, 0, 40);
        playerPart++;
    }
    if (key == "UP" && playerDir != UP && playerDir != DOWN) {
        if (playerDir == RIGHT)
            infos["playerHead"].x -= 1;
        else
            infos["playerHead"].x += 1;
        infos["playerHead"].y -= 1;
        infos["playerHead"].xSprite = infos["playerHead"].x;
        infos["playerHead"].ySprite = infos["playerHead"].y;
        infos["playerHead"].text = "⏶";
        infos["playerHead"].file = "./res/snake/snakeHead_up.png";
        infos["playerHead"].toUpdate = true;
        playerDir = UP;
    } else if (key == "DOWN" && playerDir != DOWN && playerDir != UP) {
        if (playerDir == RIGHT)
            infos["playerHead"].x -= 1;
        else
            infos["playerHead"].x += 1;
        infos["playerHead"].xSprite = infos["playerHead"].x;
        infos["playerHead"].y += 1;
        infos["playerHead"].ySprite = infos["playerHead"].y;
        infos["playerHead"].text = "⏷";
        infos["playerHead"].file = "./res/snake/snakeHead_down.png";
        infos["playerHead"].toUpdate = true;
        playerDir = DOWN;
    } else if (key == "LEFT" && playerDir != LEFT && playerDir!= RIGHT) {
        infos["playerHead"].text = "⏴";
        infos["playerHead"].file = "./res/snake/snakeHead_left.png";
        infos["playerHead"].toUpdate = true;
        playerDir = LEFT;
    } else if (key == "RIGHT" && playerDir != RIGHT && playerDir != LEFT) {
        infos["playerHead"].text = "⏵";
        infos["playerHead"].file = "./res/snake/snakeHead_right.png";
        infos["playerHead"].toUpdate = true;
        playerDir = RIGHT;
    }
    moveSnake();
}

void GameSnake::spawnMeal()
{
    int x = rand() % areaWidth + MARGIN_LEFT;
    int y = rand() % areaHeight + MARGIN_TOP;
    for (int i = 1; i < playerPart; i++) {
        if ((x == infos["playerPart" + std::to_string(i)].x && y == infos["playerPart" + std::to_string(i)].y) || (x == infos["playerHead"].x && y == infos["playerHead"].y)) {
            spawnMeal();
            return;
        }
    }
    infos.erase("showScore");
    infos.erase("showScoreLabel");
    infos["showScoreLabel"] = createEntity("", "Score ", "white", "", MARGIN_LEFT, 1, ENTITY_TYPE::TEXT, 0, 0, 40);
    infos["showScore"] = createEntity("", std::to_string(score), "white", "", MARGIN_LEFT + 9, 1, ENTITY_TYPE::TEXT, MARGIN_LEFT + 14, 0, 40);
    infos["meal"] = createEntity("./res/snake/snake_meal.png", "*", "white", "red", x, y, ENTITY_TYPE::SPRITE, 0, 0, 40);
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
    infos["playerPart1"].toUpdate = true;
    for (int i = 2, y = 0; i < playerPart; i++, y++) {
        infos["playerPart" + std::to_string(i)].x = std::get<0>(prevPartPos[y]);
        infos["playerPart" + std::to_string(i)].y = std::get<1>(prevPartPos[y]);
        infos["playerPart" + std::to_string(i)].toUpdate = true;
    }
    if (playerDir == UP) {
        infos["playerHead"].y -= 1;
        infos["playerHead"].ySprite = infos["playerHead"].y;
    }
    if (playerDir == DOWN) {
        infos["playerHead"].y += 1;
        infos["playerHead"].ySprite = infos["playerHead"].y;
    }
    if (playerDir == LEFT) {
        infos["playerHead"].x -= 1;
        infos["playerHead"].xSprite = infos["playerHead"].x;
    }
    if (playerDir == RIGHT) {
        infos["playerHead"].x += 1;
        infos["playerHead"].xSprite = infos["playerHead"].x;
    }
    infos["playerHead"].toUpdate = true;
}

extern "C" IGameModule* create() {
    return new GameSnake();
}

extern "C" void destroy(IGameModule* obj) {
    delete obj;
}

extern "C" char *getType() {
    char *type = strdup("Game");
    return type;
}