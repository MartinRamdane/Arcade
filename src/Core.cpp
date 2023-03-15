/*
** EPITECH PROJECT, 2023
** Core.cpp
** File description:
** Korr
*/

#include "Core.hpp"

Core::Core(std::string lib) : _lib(lib)
{
}

Core::~Core()
{
}

void Core::init() {
    getLibs();
    LibMenu *menu = startMenu();
    DLLoader<IGameModule> *game = new DLLoader<IGameModule>(menu->getGameChoice());
    _game = game->getInstance();
    _username = menu->getUsername();
    _game->startGame(_username);
    DLLoader<IDisplayModule> *graph2 = new DLLoader<IDisplayModule>(menu->getGraphChoice());
    _display = graph2->getInstance();
    _display->init();
}

void Core::getLibs() {
    std::string path = "./lib/";
    for (const auto &entry:std::filesystem::directory_iterator(path)) {
        std::string file = entry.path();
        if (file.substr(file.find_last_of(".") + 1) == "so") {
            void *handle = dlopen(file.c_str(), RTLD_LAZY);
            if (!handle) {
                fprintf(stderr, "%s\n", dlerror());
                exit(84);
            }
            dlerror();
            std::string type = ((std::string(*)(void))dlsym(handle, "getType"))();
            char *error;
            if ((error = dlerror()) != NULL)  {
                fprintf(stderr, "%s\n", error);
                exit(84);
            }

            dlclose(handle);
            if (type == "Game") {
                games.push_back(file);
            } else if (type == "Graphic") {
                graphs.push_back(file);
            }
        }
    }
}

LibMenu *Core::startMenu() {
    DLLoader<IDisplayModule> *graph = new DLLoader<IDisplayModule>(_lib);
    _display = graph->getInstance();
    LibMenu *menu = new LibMenu(games, graphs);
    menu->init();
    _display->init();
    while (menu->isFinished() == false) {
        menu->update(_display->getEvent());
        _display->update(menu->getInfos());
        _display->draw();
    }
    return menu;
}

void Core::mainloop() {
    while (_game->isGameOver() == false) {
        _display->update(_game->getInfos());
        _display->draw();
        _game->update(_display->getEvent());
    }
}
