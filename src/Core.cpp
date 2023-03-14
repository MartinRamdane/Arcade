/*
** EPITECH PROJECT, 2023
** Core.cpp
** File description:
** Core
*/

#include "Core.hpp"

Core::Core(std::string lib) : _lib(lib)
{
}

Core::~Core()
{
}

void Core::init() {
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
    for (auto game :games)
        std::cout << "game: " << game << std::endl;
    for (auto graph :graphs)
        std::cout << "graph: " << graph << std::endl;

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
    std::cout << "game: " << menu->getGameChoice() << std::endl;
    std::cout << "graph: " << menu->getGraphChoice() << std::endl;
    std::cout << "username: " << menu->getUsername() << std::endl;
}