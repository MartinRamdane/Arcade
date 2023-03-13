/*
** EPITECH PROJECT, 2023
** bar.hpp
** File description:
** ADislayModule
*/

#ifndef DISPLAY_MODULE_B
    #define DISPLAY_MODULE_B

#include "IDisplayModule.hpp"
#include <iostream>

class bar: public IDisplayModule {
    public :
        bar();
        ~bar();
        void init();
        void stop();
        const std::string &getName() const;
    private:
        std::string _name = "bar";
};

#endif /* !DISPLAY_MODULE_B */
