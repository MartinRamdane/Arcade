/*
** EPITECH PROJECT, 2023
** Libs.cpp
** File description:
** Libs
*/

#include "Libs.hpp"

Libs::Libs(std::string path)
{
    if (!std::filesystem::exists(path)) {
        throw Error("Path doesn't exist");
    }
    for (const auto &entry:std::filesystem::directory_iterator(path)) {
        std::string file = entry.path();
        if (file.substr(file.find_last_of(".") + 1) == "so") {
            void *handle = dlopen(file.c_str(), RTLD_LAZY);
            if (!handle) {
                throw Error("Error on loading library");
            }
            dlerror();
            std::string type = ((char *(*)(void))dlsym(handle, "getType"))();
            char *error;
            if ((error = dlerror()) != NULL)  {
                throw Error("Error on getting library type");
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

Libs::~Libs()
{
}

std::vector<std::string> Libs::getGames()
{
    return games;
}

std::vector<std::string> Libs::getGraphs()
{
    return graphs;
}
