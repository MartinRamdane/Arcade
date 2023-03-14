/*
** EPITECH PROJECT, 2023
** LibMenu.hpp
** File description:
** LibMenu
*/

#ifndef LIB_MENU
    #define LIB_MENU

#include "IGameModule.hpp"
#include <iostream>
#include <map>
#include <vector>

class LibMenu {
    public:
        LibMenu(std::vector<std::string> games, std::vector<std::string> graphs);
        ~LibMenu();
        void init();
        bool isFinished();
        void update(std::string key);
        IGameModule::Entity createEntity(std::string file, std::string text, std::string color, std::string background_color, float x, float y, bool isSprite);
        std::map<std::string, IGameModule::Entity> getInfos();

    protected:
    private:
        std::map<std::string, IGameModule::Entity> infos;
        std::vector<std::string> games;
        std::vector<std::string> graphs;
        std::string graphChoice;
        std::string gameChoice;
        std::string username;
        std::map<std::string, IGameModule::Entity>::iterator it;
        int step;
};

#endif /* !LIB_MENU */
