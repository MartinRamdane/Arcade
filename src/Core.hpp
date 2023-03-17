/*
** EPITECH PROJECT, 2023
** Core.hpp
** File description:
** Core
*/

#ifndef CLASS_CORE
    #define CLASS_CORE

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include "DLLoader.hpp"
#include "IDisplayModule.hpp"
#include "IGameModule.hpp"
#include "LibMenu.hpp"

class Core {
    public:
        Core(std::string lib);
        ~Core();
        void init();
        void getLibs();
        void startMenu(std::string lib);
        void mainloop();
        void switchLib();

    protected:
    private:
        std::string _lib;
        IDisplayModule *_display;
        IGameModule *_game;
        std::vector<std::string> games;
        std::vector<std::string> graphs;
        std::vector<std::string>::iterator it;
        std::string _username;
        DLLoader<IGameModule> *_gameLoader;
        DLLoader<IDisplayModule> *_graphLoader;
};

#endif /* !CLASS_CORE */
