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
    combo = 1;
    elapsed_seconds = 0;
    int nbWalls = 1, nbFoods = 1, nbPower = 1;
    nbBarrer = 1;
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
    gameMapOrigin = gameMap;
    for (auto ligne : gameMap) {
        for (auto c : ligne) {
            if (c == '#') {
                infos["wall" + std::to_string(nbWalls)] = createEntity("./res/pacman/pacman_wall.png", "█", "blue", "blue", x, y, ENTITY_TYPE::SPRITE, 0, 0, 40);
                nbWalls++;
            }
            // if (c == 'P') {
            //     infos["player"] = createEntity("./res/pacman/pacman_Right.png", "C", "yellow", "", x, y, ENTITY_TYPE::SPRITE, 0, 0, 40);
            //     spawnPos["player"] = std::make_tuple(x, y);
            // }
            // if (c == 'B') {
            //     infos["blinky"] = createEntity("./res/pacman/blinky_right.png", "A", "white", "red", x, y, ENTITY_TYPE::SPRITE, 0, 0, 40);
            //     spawnPos["blinky"] = std::make_tuple(x, y);
            // }
            // if (c == 'I') {
            //     infos["inky"] = createEntity("./res/pacman/inky_up.png", "A", "white", "cyan", x, y, ENTITY_TYPE::SPRITE, 0, 0, 40);
            //     spawnPos["inky"] = std::make_tuple(x, y);
            // }
            // if (c == 'R') {
            //     infos["pinky"] = createEntity("./res/pacman/pinky_up.png", "A", "white", "magenta", x, y, ENTITY_TYPE::SPRITE, 0, 0, 40);
            //     spawnPos["pinky"] = std::make_tuple(x, y);
            // }
            // if (c == 'C') {
            //     infos["clyde"] = createEntity("./res/pacman/clyde_up.png", "A", "white", "orange", x, y, ENTITY_TYPE::SPRITE, 0, 0, 40);
            //     spawnPos["clyde"] = std::make_tuple(x, y);
            // }
            if (c == '.') {
                infos["a_food" + std::to_string(nbFoods)] = createEntity("./res/pacman/pacman_food.png", ".", "yellow", "black", x, y, ENTITY_TYPE::SPRITE, 0, 0, 40);
                nbFoods++;
            }
            if (c == '*') {
                infos["a_power" + std::to_string(nbPower)] = createEntity("./res/pacman/pacman_Power.png", "●", "yellow", "black", x, y, ENTITY_TYPE::SPRITE, 0, 0, 40);
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
    // infos["scoreText"] = createEntity("", "Score: ", "white", "", 2, y + 1, ENTITY_TYPE::TEXT, 0, y, 30);
    // infos["score"] = createEntity("", std::to_string(score), "white", "", 17, y + 1, ENTITY_TYPE::TEXT, 15, y, 30);
    // infos["score"].toUpdate = true;
    initMenu();
}

GamePacman::~GamePacman()
{
}


void GamePacman::initMenu() {
    resetGame();
    infos.erase("z_retryButton");
    infos.erase("z_quitButton");
    infos.erase("z_retryButton");
    infos.erase("z_quitButton");
    infos.erase("z_username");
    infos.erase("z_yourScore");
    infos.erase("scoreText");
    infos.erase("score");
    infos.erase("blinky");
    infos.erase("inky");
    infos.erase("pinky");
    infos.erase("clyde");
    infos.erase("player");
    infos.erase("z_highScore_username");
    infos.erase("Z_highScore");
    infos.erase("z_best5");
    infos.erase("z_best4");
    infos.erase("z_best3");
    infos.erase("z_best2");
    infos.erase("z_best");
    infos.erase("z_username");
    infos.erase("z_yourScore");
    infos.erase("z_highScore_username");
    infos.erase("z_highScore");
    infos["z_title5"] = createEntity("./res/pacman/title.png", "██████   █████   ██████ ███    ███  █████  ███    ██", "white", "", 1, 2, ENTITY_TYPE::SPRITE, 26, 6, 50);
    infos["z_title4"] = createEntity("", "██   ██ ██   ██ ██      ████  ████ ██   ██ ████   ██", "white", "", 1, 3, ENTITY_TYPE::NONE, 25, 5, 50);
    infos["z_title3"] = createEntity("", "██████  ███████ ██      ██ ████ ██ ███████ ██ ██  ██", "white", "", 1, 4, ENTITY_TYPE::NONE, 25, 5, 50);
    infos["z_title2"] = createEntity("", "██      ██   ██ ██      ██  ██  ██ ██   ██ ██  ██ ██", "white", "", 1, 5, ENTITY_TYPE::NONE, 25, 5, 50);
    infos["z_title"] = createEntity("", "██      ██   ██  ██████ ██      ██ ██   ██ ██   ████", "white", "", 1, 6, ENTITY_TYPE::NONE, 25, 5, 50);
    infos["z_playButton"] = createEntity("./res/snake/snake_buttonHover.png", "Play", "black", "white", (areaWidth / 2), (areaHeight / 2 + 2 + MARGIN_TOP), ENTITY_TYPE::SPRITE_TEXT, (areaWidth / 2), (areaHeight / 2 + 2 + MARGIN_TOP), 40);
    infos["z_quitButton"] = createEntity("./res/snake/snake_button.png", "Quit", "white", "", (areaWidth / 2), (areaHeight / 2 + 5 + MARGIN_TOP), ENTITY_TYPE::SPRITE_TEXT, (areaWidth / 2), (areaHeight / 2 + 5 + MARGIN_TOP), 40);
}

void GamePacman::initGame() {
    score = 0; life = 2;
    infos.erase("z_title5");
    infos.erase("z_title4");
    infos.erase("z_title3");
    infos.erase("z_title2");
    infos.erase("z_title");
    infos.erase("z_playButton");
    infos.erase("z_quitButton");
    infos.erase("z_best5");
    infos.erase("z_best4");
    infos.erase("z_best3");
    infos.erase("z_best2");
    infos.erase("z_best");
    infos.erase("z_retryButton");
    infos.erase("z_quitButton");
    infos.erase("z_retryButton");
    infos.erase("z_quitButton");
    infos.erase("z_username");
    infos.erase("z_yourScore");
    infos.erase("z_highScore_username");
    infos.erase("Z_highScore");
    int x = 0; int y = 0;
    for (auto ligne : gameMap) {
        for (auto c : ligne) {
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
            x++;
        }
        y++;
        x = 0;
    }
    infos["scoreText"] = createEntity("", "Score: ", "white", "", 2, y + 1, ENTITY_TYPE::TEXT, 0, y, 30);
    infos["score"] = createEntity("", std::to_string(score), "white", "", 17, y + 1, ENTITY_TYPE::TEXT, 15, y, 30);
    infos["score"].toUpdate = true;
}

void GamePacman::initLoose() {
    resetGame();
    infos.erase("scoreText");
    infos.erase("score");
    infos.erase("blinky");
    infos.erase("inky");
    infos.erase("pinky");
    infos.erase("clyde");
    infos.erase("player");
    infos["z_best5"] = createEntity("./res/pacman/best.png", "██████  ███████ ███████ ████████", "white", "", 10, 2, ENTITY_TYPE::SPRITE, 26, 5, 50);
    infos["z_best4"] = createEntity("", "██   ██ ██      ██         ██", "white", "", 10, 3, ENTITY_TYPE::NONE, 25, 5, 50);
    infos["z_best3"] = createEntity("", "██████  █████   ███████    ██", "white", "", 10, 4, ENTITY_TYPE::NONE, 25, 5, 50);
    infos["z_best2"] = createEntity("", "██   ██ ██           ██    ██", "white", "", 10, 5, ENTITY_TYPE::NONE, 25, 5, 50);
    infos["z_best"] = createEntity("", "██████  ███████ ███████    ██", "white", "", 10, 6, ENTITY_TYPE::NONE, 25, 5, 50);
    infos["z_retryButton"] = createEntity("./res/snake/snake_buttonHover.png", "Retry", "black", "white", (areaWidth / 2) - 1, (areaHeight / 2 + 2 + MARGIN_TOP), ENTITY_TYPE::SPRITE_TEXT, (areaWidth / 2), (areaHeight / 2 + 2 + MARGIN_TOP), 40);
    infos["z_quitButton"] = createEntity("./res/snake/snake_button.png", "Quit", "white", "", (areaWidth / 2), (areaHeight / 2 + 5 + MARGIN_TOP), ENTITY_TYPE::SPRITE_TEXT, (areaWidth / 2), (areaHeight / 2 + 5 + MARGIN_TOP), 40);
    infos["z_username"] = createEntity("", this->username, "white", "", (areaWidth / 2 - (this->username.length() / 2) - 2), (areaHeight / 2 - 2 + MARGIN_TOP) + 1, ENTITY_TYPE::TEXT, (areaWidth / 2 - username.length() + 1), 0, 30);
    infos["z_yourScore"] = createEntity("", std::to_string(score), "white", "", infos["z_username"].x + 5 + this->username.length(), (areaHeight / 2 - 2 + MARGIN_TOP) + 1, ENTITY_TYPE::TEXT, 0, 0, 30);
    std::ifstream file(("./saves/snake/" + this->username + ".save").c_str());
    if (!file.good()) {
        std::ofstream file(("./saves/snake/" + this->username + ".save").c_str());
        file << score;
        file.close();
    } else {
        std::string line;
        std::getline(file, line);
        if (std::stoi(line) < score) {
            std::ofstream file(("./saves/snake/" + this->username + ".save").c_str());
            file << score;
            file.close();
        }
    }
    std::vector<std::pair<std::string, int>> scores;
    for (const auto &entry:std::filesystem::directory_iterator("./saves/snake/")) {
        std::ifstream file(entry.path());
        std::string line;
        std::getline(file, line);
        scores.push_back(std::make_pair(entry.path().filename().string().substr(0, entry.path().filename().string().length() - 5), std::stoi(line)));
    }
    std::sort(scores.begin(), scores.end(), [](const std::pair<std::string, int> &left, const std::pair<std::string, int> &right) {
        return left.second > right.second;
    });
    infos["z_highScore_username"] = createEntity("", scores[0].first, "white", "", (areaWidth / 2 - (10 / 2) + 1), (areaHeight / 2 - 3 + MARGIN_TOP - 1) - 1, ENTITY_TYPE::TEXT, 0, 0, 30);
    infos["z_highScore"] = createEntity("", std::to_string(scores[0].second), "white", "", (areaWidth / 2 - (10 / 2) + 1) + 10 + (int)std::to_string(scores[0].second).size(), (areaHeight / 2 - 3 + MARGIN_TOP - 1) - 1, ENTITY_TYPE::TEXT, 0, 0, 30);
}

void GamePacman::update(std::string key) {
    if (gameStatus == MENU) {
        updateMenu(key);
    } else if (gameStatus == IGameModule::GAME_STATUS::IN_GAME) {
        updateGame(key);
    } else if (gameStatus == IGameModule::GAME_STATUS::FINISHED) {
        updateLoose(key);
    }
}

void GamePacman::updateMenu(std::string key) {
    if (key == "UP" && infos["z_playButton"].color == "white" && selectMenu == 2) {
        infos["z_playButton"].color = "black";
        infos["z_playButton"].background_color = "white";
        infos["z_playButton"].file = "./res/snake/snake_buttonHover.png";
        infos["z_playButton"].spriteColor = "yellow";
        infos["z_playButton"].toUpdate = true;
        infos["z_quitButton"].color = "white";
        infos["z_quitButton"].background_color = "";
        infos["z_quitButton"].file = "./res/snake/snake_button.png";
        infos["z_quitButton"].spriteColor = "white";
        infos["z_quitButton"].toUpdate = true;
        selectMenu = 1;
    } else if (key == "DOWN" && infos["z_quitButton"].color == "white" && selectMenu == 1) {
        infos["z_quitButton"].color = "black";
        infos["z_quitButton"].background_color = "white";
        infos["z_quitButton"].file = "./res/snake/snake_buttonHover.png";
        infos["z_quitButton"].spriteColor = "yellow";
        infos["z_quitButton"].toUpdate = true;
        infos["z_playButton"].color = "white";
        infos["z_playButton"].background_color = "";
        infos["z_playButton"].file = "./res/snake/snake_button.png";
        infos["z_playButton"].spriteColor = "white";
        infos["z_playButton"].toUpdate = true;
        selectMenu = 2;
    }
    if ((key == " " && selectMenu == 1) || key == "z_playButton") {
        initGame();
        gameStatus = IGameModule::GAME_STATUS::IN_GAME;
    } else if ((key == " " && selectMenu == 2) || key == "z_quitButton") {
        exit(0);
    }
}

void GamePacman::updateLoose(std::string key) {
    if (key == "UP" && infos["z_retryButton"].color == "white" && selectMenu == 2) {
        infos["z_retryButton"].color = "black";
        infos["z_retryButton"].background_color = "white";
        infos["z_retryButton"].file = "./res/snake/snake_buttonHover.png";
        infos["z_retryButton"].spriteColor = "yellow";
        infos["z_retryButton"].toUpdate = true;
        infos["z_quitButton"].color = "white";
        infos["z_quitButton"].background_color = "";
        infos["z_quitButton"].file = "./res/snake/snake_button.png";
        infos["z_quitButton"].spriteColor = "white";
        infos["z_quitButton"].toUpdate = true;
        selectMenu = 1;
    } else if (key == "DOWN" && infos["z_quitButton"].color == "white" && selectMenu == 1) {
        infos["z_quitButton"].color = "black";
        infos["z_quitButton"].background_color = "white";
        infos["z_quitButton"].file = "./res/snake/snake_buttonHover.png";
        infos["z_quitButton"].spriteColor = "yellow";
        infos["z_quitButton"].toUpdate = true;
        infos["z_retryButton"].color = "white";
        infos["z_retryButton"].background_color = "";
        infos["z_retryButton"].file = "./res/snake/snake_button.png";
        infos["z_retryButton"].spriteColor = "white";
        infos["z_retryButton"].toUpdate = true;
        selectMenu = 2;
    }
    if ((key == " " && selectMenu == 1) || key == "z_retryButton") {
        initGame();
        gameStatus = IGameModule::GAME_STATUS::IN_GAME;
    } else if ((key == " " && selectMenu == 2) || key == "z_quitButton") {
        selectMenu = 1;
        initMenu();
        gameStatus = IGameModule::GAME_STATUS::MENU;
    }
}
void GamePacman::resetGame() {
    for (auto &info: infos) {
        if (info.first.find("a_food") == 0) {
            infos[info.first].toUpdate = true;
            infos[info.first].text = ".";
            infos[info.first].file = "./res/pacman/pacman_food.png";
        }
        if (info.first.find("a_power") == 0) {
            infos[info.first].toUpdate = true;
            infos[info.first].text = "●";
            infos[info.first].file = "./res/pacman/pacman_Power.png";
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
    // sprite
    infos["player"].xSprite = std::get<0>(spawnPos["player"]);
    infos["player"].ySprite = std::get<1>(spawnPos["player"]);
    infos["blinky"].toUpdate = true;
    infos["inky"].toUpdate = true;
    infos["pinky"].toUpdate = true;
    infos["clyde"].toUpdate = true;
    infos["blinky"].xSprite = std::get<0>(spawnPos["blinky"]);
    infos["blinky"].ySprite = std::get<1>(spawnPos["blinky"]);
    infos["inky"].xSprite = std::get<0>(spawnPos["inky"]);
    infos["inky"].ySprite = std::get<1>(spawnPos["inky"]);
    infos["pinky"].xSprite = std::get<0>(spawnPos["pinky"]);
    infos["pinky"].ySprite = std::get<1>(spawnPos["pinky"]);
    infos["clyde"].xSprite = std::get<0>(spawnPos["clyde"]);
    infos["clyde"].ySprite = std::get<1>(spawnPos["clyde"]);
    infos["blinky"].file = "./res/pacman/blinky_right.png";
    infos["inky"].file = "./res/pacman/inky_up.png";
    infos["pinky"].file = "./res/pacman/pinky_up.png";
    infos["clyde"].file = "./res/pacman/clyde_up.png";
    isGhostScared["blinky"] = false;
    isGhostScared["inky"] = false;
    isGhostScared["pinky"] = false;
    isGhostScared["clyde"] = false;
    canKillGhost = false;
    lastPositions.clear();
    gameMap = gameMapOrigin;
}

bool GamePacman::checkCollision()
{
    for (auto &info: infos) {
        if (info.first.find("pinky") == 0) {
            if ((info.second.x == infos["player"].x && info.second.y == infos["player"].y) || (info.second.xSprite == infos["player"].xSprite && info.second.ySprite == infos["player"].ySprite)) {
                if (isGhostScared["pinky"] == false) {
                    return true;
                } else {
                    combo += 2;
                    score = score + (100 * combo);
                    infos["score"].toUpdate = true;
                    infos["score"].text = std::to_string(score + combo);
                    infos["pinky"].toUpdate = true;
                    infos["pinky"].x = std::get<0>(spawnPos["pinky"]);
                    infos["pinky"].y = std::get<1>(spawnPos["pinky"]);
                    infos["pinky"].xSprite = std::get<0>(spawnPos["pinky"]);
                    infos["pinky"].ySprite = std::get<1>(spawnPos["pinky"]);
                    infos["pinky"].file = "./res/pacman/pinky_up.png";
                    infos["pinky"].text = "A";
                    isGhostScared["pinky"] = false;
                    return false;
                }
            }
        }
        if (info.first.find("inky") == 0) {
            if ((info.second.x == infos["player"].x && info.second.y == infos["player"].y) || (info.second.xSprite == infos["player"].xSprite && info.second.ySprite == infos["player"].ySprite)) {
                if (isGhostScared["inky"] == false) {
                    return true;
                } else {
                    combo += 2;
                    score = score + (100 * combo);
                    infos["score"].toUpdate = true;
                    infos["score"].text = std::to_string(score + combo);
                    infos["inky"].toUpdate = true;
                    infos["inky"].x = std::get<0>(spawnPos["inky"]);
                    infos["inky"].y = std::get<1>(spawnPos["inky"]);
                    infos["inky"].xSprite = std::get<0>(spawnPos["inky"]);
                    infos["inky"].ySprite = std::get<1>(spawnPos["inky"]);
                    infos["inky"].file = "./res/pacman/inky_up.png";
                    infos["inky"].text = "A";
                    isGhostScared["inky"] = false;
                    return false;
                }
            }
        }
        if (info.first.find("blinky") == 0) {
            if ((info.second.x == infos["player"].x && info.second.y == infos["player"].y) || (info.second.xSprite == infos["player"].xSprite && info.second.ySprite == infos["player"].ySprite)) {
                if (isGhostScared["blinky"] == false) {
                    return true;
                } else {
                    combo += 2;
                    score = score + (100 * combo);
                    infos["score"].toUpdate = true;
                    infos["score"].text = std::to_string(score + combo);
                    infos["blinky"].toUpdate = true;
                    infos["blinky"].x = std::get<0>(spawnPos["blinky"]);
                    infos["blinky"].y = std::get<1>(spawnPos["blinky"]);
                    infos["blinky"].xSprite = std::get<0>(spawnPos["blinky"]);
                    infos["blinky"].ySprite = std::get<1>(spawnPos["blinky"]);
                    infos["blinky"].file = "./res/pacman/blinky_right.png";
                    infos["blinky"].text = "A";
                    isGhostScared["blinky"] = false;
                    return false;
                }
            }
        }
        if (info.first.find("clyde") == 0 ) {
            if ((info.second.x == infos["player"].x && info.second.y == infos["player"].y) || (info.second.xSprite == infos["player"].xSprite && info.second.ySprite == infos["player"].ySprite)) {
                if (isGhostScared["clyde"] == false) {
                    return true;
                } else {
                    combo += 2;
                    score = score + (100 * combo);
                    infos["score"].toUpdate = true;
                    infos["score"].text = std::to_string(score + combo);
                    infos["clyde"].toUpdate = true;
                    infos["clyde"].x = std::get<0>(spawnPos["clyde"]);
                    infos["clyde"].y = std::get<1>(spawnPos["clyde"]);
                    infos["clyde"].xSprite = std::get<0>(spawnPos["clyde"]);
                    infos["clyde"].ySprite = std::get<1>(spawnPos["clyde"]);
                    infos["clyde"].file = "./res/pacman/clyde_up.png";
                    infos["clyde"].text = "A";
                    isGhostScared["clyde"] = false;
                    return false;
                }
            }
        }
    }
    return false;
}

void GamePacman::clearGameMapPos(char toClear) {
    int x = 0; int y = 0;
    for (auto line: gameMap) {
        for (auto &c: line) {
            if (c == toClear) {
                gameMap[y][x] = ' ';
            }
            x++;
        }
        x = 0;
        y++;
    }
}

void GamePacman::ghostChased(std::string ghost, char ghostSym) {
    int dx = infos["player"].x - infos[ghost].x;
    int dy = infos["player"].y - infos[ghost].y;
    int nextX = infos[ghost].x;
    int nextY = infos[ghost].y;

    if (abs(dx) > abs(dy)) {
        nextX += (dx > 0) ? 1 : -1;
    } else {
        nextY += (dy > 0) ? 1 : -1;
    }

    bool isNextPositionValid = true;
    std::queue<std::pair<int, int>> tempQueue = lastPositions[ghost];
    while (!tempQueue.empty()) {
        if (tempQueue.front().first == nextX && tempQueue.front().second == nextY) {
            isNextPositionValid = false;
            break;
        }
        tempQueue.pop();
    }

    if (isNextPositionValid && gameMap[nextY][nextX] != '#' && gameMap[nextY][nextX] != 'I' && gameMap[nextY][nextX] != 'R' && gameMap[nextY][nextX] != 'C') {
        infos[ghost].x = nextX;
        infos[ghost].y = nextY;
        lastPositions[ghost].push(std::make_pair(nextX, nextY));
        if (lastPositions[ghost].size() > 3) {
            lastPositions[ghost].pop();
        }
    } else {
        bool canMoveUp = gameMap[infos[ghost].y - 1][infos[ghost].x] == '.' || gameMap[infos[ghost].y - 1][infos[ghost].x] == ' ';
        bool canMoveDown = gameMap[infos[ghost].y + 1][infos[ghost].x] == '.' || gameMap[infos[ghost].y + 1][infos[ghost].x] == ' ';
        bool canMoveLeft = gameMap[infos[ghost].y][infos[ghost].x - 1] == '.' || gameMap[infos[ghost].y][infos[ghost].x - 1] == ' ';
        bool canMoveRight = gameMap[infos[ghost].y][infos[ghost].x + 1] == '.' || gameMap[infos[ghost].y][infos[ghost].x + 1] == ' ';
        int nbPosValid = canMoveDown + canMoveLeft + canMoveRight + canMoveUp;
        if (canMoveUp || canMoveDown || canMoveLeft || canMoveRight) {
            while (true) {
                int randDirection = rand() % 4;
                if (randDirection == 0 && canMoveUp) {
                    if (!isGhostScared[ghost])
                        infos[ghost].file = "./res/pacman/" + ghost + "_up.png";
                    nextX = infos[ghost].x;
                    nextY = infos[ghost].y - 1;
                } else if (randDirection == 1 && canMoveDown) {
                    if (!isGhostScared[ghost])
                        infos[ghost].file = "./res/pacman/" + ghost + "_down.png";
                    nextX = infos[ghost].x;
                    nextY = infos[ghost].y + 1;
                } else if (randDirection == 2 && canMoveLeft) {
                    if (!isGhostScared[ghost])
                        infos[ghost].file = "./res/pacman/" + ghost + "_left.png";
                    nextX = infos[ghost].x - 1;
                    nextY = infos[ghost].y;
                } else if (randDirection == 3 && canMoveRight) {
                    if (!isGhostScared[ghost])
                        infos[ghost].file = "./res/pacman/" + ghost + "_right.png";
                    nextX = infos[ghost].x + 1;
                    nextY = infos[ghost].y;
                } else {
                    continue;
                }

                isNextPositionValid = true;
                tempQueue = lastPositions[ghost];
                while (!tempQueue.empty()) {
                    if ((tempQueue.front().first == nextX && tempQueue.front().second == nextY) && nbPosValid > 1) {
                        isNextPositionValid = false;
                        break;
                    }
                    tempQueue.pop();
                }

                if (isNextPositionValid) {
                    infos[ghost].x = nextX;
                    infos[ghost].y = nextY;
                    lastPositions[ghost].push(std::make_pair(nextX, nextY));
                    if (lastPositions[ghost].size() > 3) {
                        lastPositions[ghost].pop();
                    }
                    break;
                }
            }
        }
    }
    clearGameMapPos(ghostSym);
    gameMap[infos[ghost].y][infos[ghost].x] = ghostSym;
    infos[ghost].xSprite = infos[ghost].x;
    infos[ghost].ySprite = infos[ghost].y;
    infos[ghost].toUpdate = true;
}

void GamePacman::setHighScores() {
    std::ifstream file(("./saves/pacman/" + this->username + ".save").c_str());
    if (!file.good()) {
        std::ofstream file(("./saves/pacman/" + this->username + ".save").c_str());
        file << score;
        file.close();
    } else {
        std::string line;
        std::getline(file, line);
        if (std::stoi(line) < score) {
            std::ofstream file(("./saves/pacman/" + this->username + ".save").c_str());
            file << score;
            file.close();
        }
    }
    for (const auto &entry:std::filesystem::directory_iterator("./saves/pacman/")) {
        std::ifstream file(entry.path());
        std::string line;
        std::getline(file, line);
        scores.push_back(std::make_pair(entry.path().filename().string().substr(0, entry.path().filename().string().length() - 5), std::stoi(line)));
    }
    std::sort(scores.begin(), scores.end(), [](const std::pair<std::string, int> &left, const std::pair<std::string, int> &right) {
        return left.second > right.second;
    });
    // TO DO: Display high scores
}

void GamePacman::updateGame(std::string key)
{
    if (key == "r") {
        infos["score"].toUpdate = true;
        score = 0;
        infos["score"].text = std::to_string(score);
        resetGame();
        playerDir = UNDEFINED;
    }
    eatAnimation = !eatAnimation;
    infos["player"].toUpdate = true;
    for (auto &info: infos) {
        if (info.first.find("a_food") == 0) {
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
        if (info.first.find("a_power") == 0) {
            if (info.second.x == infos["player"].x && info.second.y == infos["player"].y && info.second.text == "●") {
                infos[info.first].toUpdate = true;
                infos["score"].toUpdate = true;
                infos[info.first].text = " ";
                infos[info.first].file = "./res/pacman/pacman_food_empty.png";
                score += 50;
                infos["score"].text = std::to_string(score);
                canKillGhost = true;
                infos["clyde"].toUpdate = true;
                infos["pinky"].toUpdate = true;
                infos["inky"].toUpdate = true;
                infos["blinky"].toUpdate = true;
                infos["clyde"].file = "./res/pacman/ghost_scared.png";
                infos["pinky"].file = "./res/pacman/ghost_scared.png";
                infos["inky"].file = "./res/pacman/ghost_scared.png";
                infos["blinky"].file = "./res/pacman/ghost_scared.png";
                infos["clyde"].text = "S";
                infos["pinky"].text = "S";
                infos["inky"].text = "S";
                infos["blinky"].text = "S";
                isGhostScared["blinky"] = true;
                isGhostScared["inky"] = true;
                isGhostScared["pinky"] = true;
                isGhostScared["clyde"] = true;
                startClock = std::chrono::steady_clock::now();
                break;
            }
        }
    }
    if (canKillGhost) {
        auto current = std::chrono::steady_clock::now();
        elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(current - startClock).count();
        if (elapsed_seconds >= 8) {
            blinkGhostScared = !blinkGhostScared;
            for (auto &ghost: isGhostScared) {
                if (ghost.second) {
                    if (blinkGhostScared) {
                        infos[ghost.first].toUpdate = true;
                        infos[ghost.first].file = "./res/pacman/ghost_waiting.png";
                        infos[ghost.first].text = "A";
                    } else {
                        infos[ghost.first].toUpdate = true;
                        infos[ghost.first].file = "./res/pacman/ghost_scared.png";
                        infos[ghost.first].text = "S";
                    }
                }
            }
        }
        if (elapsed_seconds >= 10) {
            infos["clyde"].toUpdate = true;
            infos["inky"].toUpdate = true;
            infos["pinky"].toUpdate = true;
            infos["blinky"].toUpdate = true;
            infos["clyde"].file = "./res/pacman/clyde_right.png";
            infos["blinky"].file = "./res/pacman/blinky_right.png";
            infos["inky"].file = "./res/pacman/inky_right.png";
            infos["pinky"].file = "./res/pacman/pinky_right.png";
            infos["clyde"].text = "A";
            infos["pinky"].text = "A";
            infos["inky"].text = "A";
            infos["blinky"].text = "A";
            isGhostScared["blinky"] = false;
            isGhostScared["inky"] = false;
            isGhostScared["pinky"] = false;
            isGhostScared["clyde"] = false;
            canKillGhost = false;
            combo = 1;
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
    if (playerDir != UNDEFINED) {
        ghostChased("blinky", 'B');
        ghostChased("inky", 'I');
        ghostChased("pinky", 'R');
        ghostChased("clyde", 'C');
    }
    if (checkCollision()) {
        if (life > 0) {
            life--;
            resetGame();
            playerDir = UNDEFINED;
        } else {
            setHighScores();
            initLoose();
            gameStatus = FINISHED;
            playerDir = UNDEFINED;
        }
    }
}

void GamePacman::startGame(std::string username){
    this->username = username;
}

void GamePacman::checkIfMoveToGhost(int x, int y, std::string ghostName, char ghostSym) {
    if (gameMap[y][x] == ghostSym) {
        if (!isGhostScared[ghostName]) {
            if (life > 0) {
                life--;
                resetGame();
                playerDir = UNDEFINED;
            } else {
                setHighScores();
                setHighScores();
                initLoose();
                gameStatus = FINISHED;
                playerDir = UNDEFINED;
            }
        } else {
            combo += 2;
            score = score + (100 * combo);
            infos["score"].toUpdate = true;
            infos["score"].text = std::to_string(score + combo);
            infos[ghostName].toUpdate = true;
            infos[ghostName].x = std::get<0>(spawnPos[ghostName]);
            infos[ghostName].y = std::get<1>(spawnPos[ghostName]);
            infos[ghostName].xSprite = std::get<0>(spawnPos[ghostName]);
            infos[ghostName].ySprite = std::get<1>(spawnPos[ghostName]);
            infos[ghostName].file = "./res/pacman/" + ghostName + "_up.png";
            infos[ghostName].text = "A";
            isGhostScared[ghostName] = false;
        }
    }
}

void GamePacman::movePlayer()
{
    if (playerDir == RIGHT) {
        checkIfMoveToGhost(infos["player"].x + 1, infos["player"].y, "blinky", 'B');
        checkIfMoveToGhost(infos["player"].x + 1, infos["player"].y, "inky", 'I');
        checkIfMoveToGhost(infos["player"].x + 1, infos["player"].y, "pinky", 'R');
        checkIfMoveToGhost(infos["player"].x + 1, infos["player"].y, "clyde", 'C');
        if (gameMap[infos["player"].y][infos["player"].x + 1] != '#' && gameMap[infos["player"].y][infos["player"].x + 1] != '-') {
            gameMap[infos["player"].y][infos["player"].x] = ' ';
            gameMap[infos["player"].y][infos["player"].x + 1] = 'P';
            infos["player"].x++;
            infos["player"].xSprite = infos["player"].x;
        }
    }
    if (playerDir == LEFT) {
        checkIfMoveToGhost(infos["player"].x - 1, infos["player"].y, "blinky", 'B');
        checkIfMoveToGhost(infos["player"].x - 1, infos["player"].y, "inky", 'I');
        checkIfMoveToGhost(infos["player"].x - 1, infos["player"].y, "pinky", 'R');
        checkIfMoveToGhost(infos["player"].x - 1, infos["player"].y, "clyde", 'C');
        if (gameMap[infos["player"].y][infos["player"].x - 1] != '#' && gameMap[infos["player"].y][infos["player"].x - 1] != '-') {
            gameMap[infos["player"].y][infos["player"].x] = ' ';
            gameMap[infos["player"].y][infos["player"].x - 1] = 'P';
            infos["player"].x--;
            infos["player"].xSprite = infos["player"].x;
        }
    }
    if (playerDir == UP) {
        checkIfMoveToGhost(infos["player"].x, infos["player"].y - 1, "blinky", 'B');
        checkIfMoveToGhost(infos["player"].x, infos["player"].y - 1, "inky", 'I');
        checkIfMoveToGhost(infos["player"].x, infos["player"].y - 1, "pinky", 'R');
        checkIfMoveToGhost(infos["player"].x, infos["player"].y - 1, "clyde", 'C');
        if (gameMap[infos["player"].y - 1][infos["player"].x] != '#' && gameMap[infos["player"].y - 1][infos["player"].x] != '-') {
            gameMap[infos["player"].y][infos["player"].x] = ' ';
            gameMap[infos["player"].y - 1][infos["player"].x] = 'P';
            infos["player"].y--;
            infos["player"].ySprite = infos["player"].y;
        }
    }
    if (playerDir == DOWN) {
        checkIfMoveToGhost(infos["player"].x, infos["player"].y + 1, "blinky", 'B');
        checkIfMoveToGhost(infos["player"].x, infos["player"].y + 1, "inky", 'I');
        checkIfMoveToGhost(infos["player"].x, infos["player"].y + 1, "pinky", 'R');
        checkIfMoveToGhost(infos["player"].x, infos["player"].y + 1, "clyde", 'C');
        if (gameMap[infos["player"].y + 1][infos["player"].x] != '#' && gameMap[infos["player"].y + 1][infos["player"].x] != '-') {
            gameMap[infos["player"].y][infos["player"].x] = ' ';
            gameMap[infos["player"].y + 1][infos["player"].x] = 'P';
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