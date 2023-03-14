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
        LibMenu *startMenu();
        void mainloop();

    protected:
    private:
        std::string _lib;
        IDisplayModule *_display;
        IGameModule *_game;
        std::vector<std::string> games;
        std::vector<std::string> graphs;
        std::string _username;
};

#endif /* !CLASS_CORE */
