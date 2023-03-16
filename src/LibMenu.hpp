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
#include <map>

class LibMenu {
    public:
        LibMenu(std::vector<std::string> games, std::vector<std::string> graphs);
        ~LibMenu();
        void init();
        bool isFinished();
        void update(std::string key);
        IGameModule::Entity createEntity(std::string file, std::string text, std::string color, std::string background_color, float x, float y, IGameModule::ENTITY_TYPE type);
        std::map<std::string, IGameModule::Entity> getInfos();
        void handleKeys(std::vector<std::string> list, std::string key, std::string &toFill);
        void inputUser(std::string key);
        std::string getGameChoice() { return gameChoice; };
        std::string getGraphChoice() { return graphChoice; };
        std::string getUsername() { return username; };

    protected:
    private:
        std::map<std::string, IGameModule::Entity> infos;
        std::vector<std::string> games;
        std::vector<std::string> graphs;
        std::string graphChoice;
        std::string gameChoice;
        std::string username;
        int ySave = 0;
        int xSave = 3;
        int step;
        int select;
};

#endif /* !LIB_MENU */
