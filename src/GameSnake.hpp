/*
** EPITECH PROJECT, 2023
** GameSnake.hpp
** File description:
** GameSnake
*/

#ifndef HEADER_GAMESNAKE
    #define HEADER_GAMESNAKE

#include "AGameModule.hpp"
#include <vector>
#include <tuple>

class GameSnake: public AGameModule {
    public:
        enum DIRECTION {
            UP,
            DOWN,
            LEFT,
            RIGHT
        };
        GameSnake();
        ~GameSnake();
        void startGame(std::string username);
        bool isGameOver() {return false;};
        void update(std::string key);
        void moveSnake();
        void spawnMeal();
        void initGame();
        void initLoose();
        void initMenu();
        void updateGame(std::string key);
        void updateMenu(std::string key);
        void updateLoose(std::string key);
        bool checkCollision();

    protected:
    private:
        int areaWidth;
        int areaHeight;
        int score;
        int playerPart = 4;
        bool hasMeal;
        int selectMenu;
        DIRECTION playerDir;
};

#endif /* !HEADER_GAMESNAKE */
