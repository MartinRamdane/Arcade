/*
** EPITECH PROJECT, 2023
** Libs.hpp
** File description:
** Libs
*/

#ifndef LIBS
    #define LIBS

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include "DLLoader.hpp"

class Libs {
    public:
        Libs(std::string path);
        ~Libs();
        std::vector<std::string> getGames();
        std::vector<std::string> getGraphs();

    private:
        std::vector<std::string> games;
        std::vector<std::string> graphs;
};

#endif /* !LIBS */
