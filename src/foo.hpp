/*
** EPITECH PROJECT, 2023
** foo.hpp
** File description:
** ADislayModule
*/

#ifndef DISPLAY_MODULE_A
    #define DISPLAY_MODULE_A

#include "IDisplayModule.hpp"
#include <iostream>

class foo: public IDisplayModule {
    public :
        foo();
        ~foo();
        void init();
        void stop();
        const std::string &getName() const;
    private:
        std::string _name = "foo";
};

#endif /* !DISPLAY_MODULE_A */
