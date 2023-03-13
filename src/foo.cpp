/*
** EPITECH PROJECT, 2023
** foo
** File description:
** foo
*/

#include "foo.hpp"

foo::foo()
{
}

foo::~foo()
{
}

void foo::init()
{
    std::cout << "foo init" << std::endl;
}

void foo::stop()
{
    std::cout << "foo stop" << std::endl;
}

const std::string &foo::getName() const
{
    return _name;
}

extern "C" IDisplayModule* create() {
    printf("new foo\n");
    return new foo();
}

extern "C" void destroy(IDisplayModule* obj) {
    printf("destroy foo\n");
    delete obj;
}
