/*
** EPITECH PROJECT, 2023
** GamePacman.hpp
** File description:
** GamePacman
*/

#ifndef GAME_PACMAN_INCLUDE
    #define GAME_PACMAN_INCLUDE

#include "AGameModule.hpp"
#include <vector>
#include <tuple>
#include <memory>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <memory>

#define MARGIN_TOP 3
#define MARGIN_LEFT 2

class GamePacman: public AGameModule {
    public:
        enum DIRECTION {
            UP,
            DOWN,
            LEFT,
            RIGHT,
            UNDEFINED
        };
        GamePacman();
        ~GamePacman();
        void startGame(std::string username){};
        bool isGameOver() {return false;};
        void update(std::string key);
        void initGame(){};
        void initLoose(){};
        void initMenu(){};
        void updateGame(std::string key){};
        void updateMenu(std::string key){};
        void updateLoose(std::string key){};
        void movePlayer();
        bool checkCollision();
        void resetGame();

    private:
        std::vector<std::vector<char>> gameMap;
        GamePacman::DIRECTION playerDir;
        int foodScore;
        std::map<std::string, std::tuple<int, int>> spawnPos;
        bool canKillGhost;
        bool eatAnimation;
        int life = 2;
};

#endif /* !GAME_PACMAN_INCLUDE */
