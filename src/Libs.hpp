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
        class Error : public std::exception {
            public:
                Error(std::string const &message) : _message(message) {}
                const char *what() const noexcept override { return _message.c_str(); }
            private:
                std::string _message;
        };
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
