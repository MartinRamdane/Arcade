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

void DisplayNcurse::init(std::map<std::string, IGameModule::Entity> &entites) {
    setlocale(LC_ALL, "");
    initscr();
    curs_set(0);
    cbreak();
    noecho();
    start_color();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    texts = entites;
}

void DisplayNcurse::update(std::map<std::string, IGameModule::Entity> &entities) {
    texts = entities;
}

void DisplayNcurse::draw() {
    halfdelay(2);
    clear();
    int i = 2;
    for (auto &entity : texts) {
        init_pair(i, colors[entity.second.color], colors[entity.second.background_color]);
        attron(COLOR_PAIR(i));
        mvprintw(entity.second.y, entity.second.x, entity.second.text.c_str());
        attroff(COLOR_PAIR(i));
        i++;
    }
    refresh();
}

std::string DisplayNcurse::getEvent() {
    int input = getch();
    switch (input) {
        case KEY_UP:
            return std::string("UP");
        case KEY_DOWN:
            return std::string("DOWN");
        case KEY_LEFT:
            return std::string("LEFT");
        case KEY_RIGHT:
            return std::string("RIGHT");
        case 27:
            return std::string("ESCAPE");
        case 127:
            return std::string("BACKSPACE");
        case 10:
            return std::string("ENTER");
    }
    std::string s(1, input);
    return s;
}

const std::string &DisplayNcurse::getName() const {
    return displayName;
}

void DisplayNcurse::stop() {
    endwin();
}

std::map<std::string, int> DisplayNcurse::colors = {
    {"red", COLOR_RED},
    {"green", COLOR_GREEN},
    {"yellow", COLOR_YELLOW},
    {"blue", COLOR_BLUE},
    {"magenta", COLOR_MAGENTA},
    {"cyan", COLOR_CYAN},
    {"white", COLOR_WHITE},
    {"black", COLOR_BLACK},
    {"", COLOR_BLACK}
};

extern "C" IDisplayModule *create() {
    return new DisplayNcurse();
}

extern "C" void destroy(IDisplayModule *display) {
    delete display;
}

extern "C" const char *getType() {
    const char *type = "Graphic";
    return type;
}
