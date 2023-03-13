/*
** EPITECH PROJECT, 2023
** bar
** File description:
** bar
*/

#include "bar.hpp"

bar::bar()
{
}

bar::~bar()
{
}

void bar::init()
{
    std::cout << "bar init" << std::endl;
}

void bar::stop()
{
    std::cout << "bar stop" << std::endl;
}

const std::string &bar::getName() const
{
    return _name;
}

extern "C" IDisplayModule* create() {
    printf("new bar\n");
    return new bar();
}

extern "C" void destroy(IDisplayModule* obj) {
    printf("destroy bar\n");
    delete obj;
}
