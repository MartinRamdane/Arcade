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

#define MARGIN_TOP 3
#define MARGIN_LEFT 2

class GamePacman: public AGameModule {
    public:
        GamePacman();
        ~GamePacman();
        void startGame(std::string username){};
        bool isGameOver() {return false;};
        void update(std::string key){};
        void initGame(){};
        void initLoose(){};
        void initMenu(){};
        void updateGame(std::string key){};
        void updateMenu(std::string key){};
        void updateLoose(std::string key){};
        bool checkCollision(){};

    private:
};

#endif /* !GAME_PACMAN_INCLUDE */
