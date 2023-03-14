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
        void update(std::map<std::string, IGameModule::Entity> entities) {};
        void draw() {};
        std::string getEvent() {};
        const std::string &getName() const;
    private:
        std::string _name = "bar";
};

#endif /* !DISPLAY_MODULE_B */
