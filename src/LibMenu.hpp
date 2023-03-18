/*
** EPITECH PROJECT, 2023
** LibMenu.hpp
** File description:
** LibMenu
*/

#ifndef LIB_MENU
    #define LIB_MENU

#include "AGameModule.hpp"
#include <iostream>
#include <map>
#include <vector>
#include <map>

class LibMenu : public AGameModule {
    public:
        LibMenu(std::vector<std::string> games, std::vector<std::string> graphs);
        ~LibMenu();
        void startGame(std::string username){this->username = username;};
        bool isGameOver(){return false;};
        void init();
        bool isFinished();
        void update(std::string key);
        void handleKeys(std::vector<std::string> list, std::string key, std::string &toFill);
        void inputUser(std::string key);
        std::string getGameChoice() { return gameChoice; };
        std::string getGraphChoice() { return graphChoice; };
        std::string getUsername() { return username; };

    protected:
    private:
        std::vector<std::string> games;
        std::vector<std::string> graphs;
        std::string graphChoice;
        std::string gameChoice;
        std::string username;
        int ySave = 0;
        int xSave = 4;
        int step;
        int select;
};

#endif /* !LIB_MENU */
