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

class Core {
    public:
        Core();
        ~Core();
        void init();

    protected:
    private:
        std::vector<std::string> games;
        std::vector<std::string> graphs;
};

#endif /* !CLASS_CORE */
