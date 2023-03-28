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
    exit(0);
}

void Core::getLibs() {
    Libs libs("./lib/");
    games = libs.getGames();
    graphs = libs.getGraphs();
}

void Core::startMenu(std::string lib) {
    _graphLoader = std::make_unique<DLLoader<IDisplayModule>>(lib);
    for (auto ite = graphs.begin(); ite != graphs.end(); ite++) {
        if (*ite == lib) {
            it = ite;
            break;
        }
    }
    _display = std::unique_ptr<IDisplayModule>(_graphLoader->getInstance());
    std::unique_ptr<LibMenu> menu = std::make_unique<LibMenu>(games, graphs);
    menu->init();
    _display->init(menu->getInfos());
    while (menu->isFinished() == false) {
        std::string event = _display->getEvent();
        if (event == "\t")
            switchLib(menu.get());
        if (event == "-")
            stop();
        menu->update(event);
        _display->update(menu->getInfos());
        _display->draw();
    }
    _display->stop();
    _gameLoader = std::make_unique<DLLoader<IGameModule>>(menu->getGameChoice());
    _game = std::unique_ptr<IGameModule>(_gameLoader->getInstance());
    _username = menu->getUsername();
    _game->startGame(_username);
    _graphLoader.release();
    _graphLoader = std::make_unique<DLLoader<IDisplayModule>>(menu->getGraphChoice());
    for (auto ite = graphs.begin(); ite != graphs.end(); ite++) {
        if (*ite == menu->getGraphChoice()) {
            it = ite;
            break;
        }
    }
    _display.release();
    _display = std::unique_ptr<IDisplayModule>(_graphLoader->getInstance());
    _display->init(_game->getInfos());
}

void Core::switchLib(IGameModule *lib) {
    _display->stop();
    _graphLoader.release();
    it++;
    if (it == graphs.end())
        it = graphs.begin();
    _graphLoader = std::make_unique<DLLoader<IDisplayModule>>(*it);
    _display.release();
    _display = std::unique_ptr<IDisplayModule>(_graphLoader->getInstance());
    _display->init(lib->getInfos());
}

void Core::mainloop() {
    while (_game->isGameOver() == false) {
        _display->update(_game->getInfos());
        _display->draw();
        std::string event = _display->getEvent();
        if (event == "\t")
            switchLib(_game.get());
        if (event == "m") {
            _display->stop();
            _graphLoader.release();
            _display.release();
            _gameLoader.release();
            _game.release();
            startMenu(*it);
        }
        if (event == "-")
            stop();
        std::this_thread::sleep_for(std::chrono::milliseconds(64));
        _game->update(event);
    }
}
