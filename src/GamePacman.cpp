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
    int nbWalls = 1, nbFoods = 1, nbPower = 1, nbBarrer = 1;
    playerDir = UNDEFINED;
    std::ifstream file("./res/pacman/pacmanMap.txt");
    std::vector<std::string> lignes;
    int x = 0; int y = 0;
    if (file.is_open()) {
        std::string ligne;
        while (std::getline(file, ligne)) {
            std::vector<char> ligne_chars(ligne.begin(), ligne.end());
            gameMap.push_back(ligne_chars);
        }
        file.close();
    }

    // Utilisation des lignes
    for (auto ligne : gameMap) {
        for (auto c : ligne) {
            if (c == '#') {
                infos["wall" + std::to_string(nbWalls)] = createEntity("./res/pacman/pacman_wall.png", "█", "blue", "blue", x, y, ENTITY_TYPE::SPRITE, 0, 0, 40);
                nbWalls++;
            }
            if (c == 'P') {
                infos["player"] = createEntity("./res/pacman/pacman_Right.png", "C", "yellow", "", x, y, ENTITY_TYPE::SPRITE, 0, 0, 40);
                spawnPos["player"] = std::make_tuple(x, y);
            }
            if (c == 'B') {
                infos["blinky"] = createEntity("./res/pacman/blinky_right.png", "A", "white", "red", x, y, ENTITY_TYPE::SPRITE, 0, 0, 40);
                spawnPos["blinky"] = std::make_tuple(x, y);
            }
            if (c == 'I') {
                infos["inky"] = createEntity("./res/pacman/inky_up.png", "A", "white", "cyan", x, y, ENTITY_TYPE::SPRITE, 0, 0, 40);
                spawnPos["inky"] = std::make_tuple(x, y);
            }
            if (c == 'R') {
                infos["pinky"] = createEntity("./res/pacman/pinky_up.png", "A", "white", "magenta", x, y, ENTITY_TYPE::SPRITE, 0, 0, 40);
                spawnPos["pinky"] = std::make_tuple(x, y);
            }
            if (c == 'C') {
                infos["clyde"] = createEntity("./res/pacman/clyde_up.png", "A", "white", "orange", x, y, ENTITY_TYPE::SPRITE, 0, 0, 40);
                spawnPos["clyde"] = std::make_tuple(x, y);
            }
            if (c == '.') {
                infos["food" + std::to_string(nbFoods)] = createEntity("./res/pacman/pacman_food.png", ".", "yellow", "black", x, y, ENTITY_TYPE::SPRITE, 0, 0, 40);
                nbFoods++;
            }
            if (c == '*') {
                infos["power" + std::to_string(nbPower)] = createEntity("./res/pacman/pacman_Power.png", "●", "yellow", "black", x, y, ENTITY_TYPE::SPRITE, 0, 0, 40);
                nbPower++;
            }
            if (c == '-') {
                infos["barrer" + std::to_string(nbBarrer)] = createEntity("./res/pacman/pacman_barrer.png", "―", "yellow", "black", x, y, ENTITY_TYPE::SPRITE, 0, 0, 40);
                nbBarrer++;
            }
            x++;
        }
        y++;
        x = 0;
    }
    infos["scoreText"] = createEntity("", "Score: ", "white", "", 2, y + 1, ENTITY_TYPE::TEXT, 0, y, 30);
    infos["score"] = createEntity("", std::to_string(score), "white", "", 10, y + 1, ENTITY_TYPE::TEXT, 15, y, 30);
    infos["score"].toUpdate = true;
}

GamePacman::~GamePacman()
{
}

void GamePacman::resetGame() {
    for (auto &info: infos) {
        if (info.first.find("food") == 0) {
            infos[info.first].toUpdate = true;
            infos[info.first].text = ".";
            infos[info.first].file = "./res/pacman/pacman_food.png";
        }
    }
    infos["player"].x = std::get<0>(spawnPos["player"]);
    infos["player"].y = std::get<1>(spawnPos["player"]);
    infos["blinky"].x = std::get<0>(spawnPos["blinky"]);
    infos["blinky"].y = std::get<1>(spawnPos["blinky"]);
    infos["inky"].x = std::get<0>(spawnPos["inky"]);
    infos["inky"].y = std::get<1>(spawnPos["inky"]);
    infos["pinky"].x = std::get<0>(spawnPos["pinky"]);
    infos["pinky"].y = std::get<1>(spawnPos["pinky"]);
    infos["clyde"].x = std::get<0>(spawnPos["clyde"]);
    infos["clyde"].y = std::get<1>(spawnPos["clyde"]);
}

bool GamePacman::checkCollision()
{
    for (auto &info: infos) {
        if (info.first.find("pinky") == 0 && !canKillGhost) {
            if (info.second.x == infos["player"].x && info.second.y == infos["player"].y) {
                return true;
            }
        }
        if (info.first.find("inky") == 0 && !canKillGhost) {
            if (info.second.x == infos["player"].x && info.second.y == infos["player"].y) {
                return true;
            }
        }
        if (info.first.find("blinky") == 0 && !canKillGhost) {
            if (info.second.x == infos["player"].x && info.second.y == infos["player"].y) {
                return true;
            }
        }
        if (info.first.find("clyde") == 0 && !canKillGhost) {
            if (info.second.x == infos["player"].x && info.second.y == infos["player"].y) {
                return true;
            }
        }
    }
    return false;
}

void GamePacman::update(std::string key)
{
    if (checkCollision()) {
        if (life > 0) {
            life--;
            resetGame();
            playerDir = UNDEFINED;
        } else {
            exit(84);
        }
    }
    eatAnimation = !eatAnimation;
    infos["player"].toUpdate = true;
    for (auto &info: infos) {
        if (info.first.find("food") == 0) {
            if (info.second.toUpdate)
                info.second.toUpdate = false;
            if (info.second.x == infos["player"].x && info.second.y == infos["player"].y && info.second.text == ".") {
                infos[info.first].toUpdate = true;
                infos["score"].toUpdate = true;
                infos[info.first].text = " ";
                infos[info.first].file = "./res/pacman/pacman_food_empty.png";
                foodScore ++;
                score += 10;
                infos["score"].text = std::to_string(score);
                break;
            }
        }
    }
    if (foodScore == 470) {
        resetGame();
        playerDir = UNDEFINED;
        infos["player"].text = "C";
    }
    if (key == "UP") {
        if (gameMap[infos["player"].y - 1][infos["player"].x] != '#') {
            playerDir = UP;
            infos["player"].text = "U";
            infos["player"].file = "./res/pacman/pacman_Up.png";
        }
    }
    if (key == "DOWN") {
        if (gameMap[infos["player"].y + 1][infos["player"].x] != '#') {
            playerDir = DOWN;
            infos["player"].text = "Ω";
            infos["player"].file = "./res/pacman/pacman_Down.png";
        }
    }
    if (key == "LEFT") {
        if (gameMap[infos["player"].y][infos["player"].x - 1] != '#') {
            playerDir = LEFT;
            infos["player"].text = "Ↄ";
            infos["player"].file = "./res/pacman/pacman_Left.png";
        }
    }
    if (key == "RIGHT") {
        if (gameMap[infos["player"].y][infos["player"].x + 1] != '#') {
            playerDir = RIGHT;
            infos["player"].text = "C";
            infos["player"].file = "./res/pacman/pacman_Right.png";
        }
    }
    if (eatAnimation) {
        infos["player"].file = "./res/pacman/pacman_noeat.png";
        infos["player"].text = "O";
    } else {
        if (playerDir == RIGHT) {
            infos["player"].file = "./res/pacman/pacman_Right.png";
            infos["player"].text = "C";
        }
        if (playerDir == LEFT) {
            infos["player"].file = "./res/pacman/pacman_Left.png";
            infos["player"].text = "Ↄ";
        }
        if (playerDir == UP) {
            infos["player"].file = "./res/pacman/pacman_Up.png";
            infos["player"].text = "U";
        }
        if (playerDir == DOWN) {
            infos["player"].file = "./res/pacman/pacman_Down.png";
            infos["player"].text = "Ω";
        }
    }
    movePlayer();
}

void GamePacman::movePlayer()
{
    if (playerDir == RIGHT) {
        if (gameMap[infos["player"].y][infos["player"].x + 1] != '#' && gameMap[infos["player"].y][infos["player"].x + 1] != '-') {
            infos["player"].x++;
            infos["player"].xSprite = infos["player"].x;
        }
    }
    if (playerDir == LEFT) {
        if (gameMap[infos["player"].y][infos["player"].x - 1] != '#' && gameMap[infos["player"].y][infos["player"].x - 1] != '-') {
            infos["player"].x--;
            infos["player"].xSprite = infos["player"].x;
        }
    }
    if (playerDir == UP) {
        if (gameMap[infos["player"].y - 1][infos["player"].x] != '#' && gameMap[infos["player"].y - 1][infos["player"].x] != '-') {
            infos["player"].y--;
            infos["player"].ySprite = infos["player"].y;
        }
    }
    if (playerDir == DOWN) {
        if (gameMap[infos["player"].y + 1][infos["player"].x] != '#' && gameMap[infos["player"].y + 1][infos["player"].x] != '-') {
            infos["player"].y++;
            infos["player"].ySprite = infos["player"].y;
        }
    }
    if (infos["player"].x == 0 && infos["player"].y == 11) {
        infos["player"].x = 52;
    } else if (infos["player"].x == 52 && infos["player"].y == 11) {
        infos["player"].x = 0;
    }
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