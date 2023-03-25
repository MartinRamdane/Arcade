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
#include <memory>

class DisplayNcurse : public IDisplayModule {
    public:
        DisplayNcurse();
        ~DisplayNcurse();
        void init(std::map<std::string, IGameModule::Entity> &entites);
        void stop();
        void update(std::map<std::string, IGameModule::Entity> &entities);
        void draw();
        void drawElement(IGameModule::Entity element);
        std::string getEvent();
        std::string getMouseEvent();
        const std::string &getName() const;

    private:
        std::string displayName;
        static std::map<std::string, int> colors;
        std::map<std::string, IGameModule::Entity> texts;
};

#endif /* !DISPLAY_NCURSE */
