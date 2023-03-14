/*
** EPITECH PROJECT, 2023
** DisplayNcurse.hpp
** File description:
** DisplayNcurse
*/

#ifndef DISPLAY_NCURSE
    #define DISPLAY_NCURSE

#include "IDisplayModule.hpp"
#include <ncurses.h>
#include <iostream>
#include <string>

class DisplayNcurse : public IDisplayModule {
    public:
        DisplayNcurse();
        ~DisplayNcurse();
        void init();
        void stop();
        void update(std::map<std::string, IGameModule::Entity> entities);
        void draw();
        void drawElement(IGameModule::Entity element);
        std::string getEvent();
        const std::string &getName() const;

    private:
        std::string displayName;
        std::map<std::string, IGameModule::Entity> entities;
};

#endif /* !DISPLAY_NCURSE */
