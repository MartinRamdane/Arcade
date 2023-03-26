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
#include <memory>
#include "IDisplayModule.hpp"
#include "IGameModule.hpp"
#include "LibMenu.hpp"
#include "DLLoader.hpp"
#include "Libs.hpp"

class Core {
    public:
        Core(std::string lib);
        ~Core();
        void init();
        void stop();
        void getLibs();
        void startMenu(std::string lib);
        void mainloop();
        void switchLib(IGameModule *lib);

    protected:
    private:
        std::string _lib;
        std::unique_ptr<IDisplayModule> _display;
        std::unique_ptr<IGameModule> _game;
        std::vector<std::string> games;
        std::vector<std::string> graphs;
        std::vector<std::string>::iterator it;
        std::string _username;
        std::unique_ptr<DLLoader<IGameModule>> _gameLoader;
        std::unique_ptr<DLLoader<IDisplayModule>> _graphLoader;
};

#endif /* !CLASS_CORE */
