/*
** EPITECH PROJECT, 2023
** DisplayNcurse.cpp
** File description:
** DisplayNcurse
*/

#include "DisplayNcurse.hpp"

DisplayNcurse::DisplayNcurse() : displayName("ncurse")
{
}

DisplayNcurse::~DisplayNcurse()
{
}

void DisplayNcurse::init() {
    initscr();
    curs_set(0);
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
}

void DisplayNcurse::update(std::map<std::string, IGameModule::Entity> entities) {
    this->entities = entities;
}

void DisplayNcurse::draw() {
    halfdelay(2);
    clear();
    for (auto &entity : entities) {
        mvprintw(entity.second.y, entity.second.x, entity.second.text.c_str());
    }
    refresh();
}

std::string DisplayNcurse::getEvent() {
    return std::to_string(getch());
}

const std::string &DisplayNcurse::getName() const {
    return displayName;
}


void DisplayNcurse::stop() {
    endwin();
}

extern "C" IDisplayModule* create() {
    return new DisplayNcurse();
}

extern "C" void destroy(IDisplayModule* obj) {
    delete obj;
}

extern "C" std::string getType() {
    return "Graphic";
}
