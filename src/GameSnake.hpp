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
#include <memory>
#include <iostream>
#include <string>
#include <fstream>
#include <map>

#define MARGIN_TOP 3
#define MARGIN_LEFT 2

#define SNAKE_H_BODY "./res/snake/snakeBody_horizontal.png"
#define SNAKE_V_BODY "./res/snake/snakeBody_vertical.png"
#define SNAKE_A_LD "./res/snake/snakeBodyAngle_leftDown.png"
#define SNAKE_A_LU "./res/snake/snakeBodyAngle_leftUp.png"
#define SNAKE_A_RD "./res/snake/snakeBodyAngle_rightDown.png"
#define SNAKE_A_RU "./res/snake/snakeBodyAngle_rightUp.png"
#define SNAKE_H_UP "./res/snake/snakeHead_up.png"
#define SNAKE_H_DOWN "./res/snake/snakeHead_down.png"
#define SNAKE_H_LEFT "./res/snake/snakeHead_left.png"
#define SNAKE_H_RIGHT "./res/snake/snakeHead_right.png"

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
        void initArea();
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
        int playerPart = 4;
        bool hasMeal;
        DIRECTION playerDir;
        DIRECTION oldDir;
};

#endif /* !HEADER_GAMESNAKE */
