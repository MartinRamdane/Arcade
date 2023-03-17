/*
** EPITECH PROJECT, 2023
** Core.cpp
** File description:
** Korr
*/

#include "Core.hpp"

Core::Core(std::string lib)
{
    _lib = "./" + lib;
}

Core::~Core()
{
}

void Core::init() {
    getLibs();
    startMenu(_lib);
}

void Core::stop() {
    _display->stop();
    delete _graphLoader;
    delete _gameLoader;
    exit(0);
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
            std::string type = ((char *(*)(void))dlsym(handle, "getType"))();
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

void Core::startMenu(std::string lib) {
    _graphLoader = new DLLoader<IDisplayModule>(lib);
    it = std::find(graphs.begin(), graphs.end(), lib);
    _display = _graphLoader->getInstance();
    LibMenu *menu = new LibMenu(games, graphs);
    menu->init();
    _display->init();
    while (menu->isFinished() == false) {
        std::string event = _display->getEvent();
        if (event == "\t")
            switchLib();
        if (event == "-")
            stop();
        menu->update(event);
        _display->update(menu->getInfos());
        _display->draw();
    }
    _display->stop();
    _gameLoader = new DLLoader<IGameModule>(menu->getGameChoice());
    _game = _gameLoader->getInstance();
    _username = menu->getUsername();
    _game->startGame(_username);
    _graphLoader = new DLLoader<IDisplayModule>(menu->getGraphChoice());
    it = std::find(graphs.begin(), graphs.end(), menu->getGraphChoice());
    _display = _graphLoader->getInstance();
    _display->init();
}

void Core::switchLib() {
    _display->stop();
    delete _graphLoader;
    it++;
    if (it == graphs.end())
        it = graphs.begin();
    _graphLoader = new DLLoader<IDisplayModule>(*it);
    _display = _graphLoader->getInstance();
    _display->init();
}

void Core::mainloop() {
    while (_game->isGameOver() == false) {
        _display->update(_game->getInfos());
        _display->draw();
        std::string event = _display->getEvent();
        if (event == "\t")
            switchLib();
        if (event == "m")
            startMenu(*it);
        if (event == "-")
            stop();
        _game->update(event);
    }
}
