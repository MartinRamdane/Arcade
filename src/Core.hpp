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

class Core {
    public:
        Core();
        ~Core();
        void init();

    protected:
    private:
        std::vector<std::string> _games;
        std::vector<std::string> _graphs;
};

#endif /* !CLASS_CORE */
