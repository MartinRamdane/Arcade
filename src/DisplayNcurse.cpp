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
    mousemask(ALL_MOUSE_EVENTS, NULL);
    texts = entites;
}

void DisplayNcurse::update(std::map<std::string, IGameModule::Entity> &entities) {
    texts = entities;
}

void DisplayNcurse::draw() {
    clear();
    int i = 2;
    for (auto &entity : texts) {
        std::tuple<std::string, std::string> color_entity_pair = std::make_tuple(entity.second.color, entity.second.background_color);
        auto color_it = colors_map.find(color_entity_pair);

        if (color_it == colors_map.end()) {
            init_pair(i, colors[entity.second.color], colors[entity.second.background_color]);
            colors_map[color_entity_pair] = i;
            i++;
        }

        attron(COLOR_PAIR(colors_map[color_entity_pair]));
        mvprintw(entity.second.y, entity.second.x, entity.second.text.c_str());
        attroff(COLOR_PAIR(colors_map[color_entity_pair]));
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
        case KEY_MOUSE:
            return getMouseEvent();
    }
    std::string s(1, input);
    return s;
}

std::string DisplayNcurse::getMouseEvent() {
    MEVENT event;
    if (getmouse(&event) == OK) {
        if (event.bstate & BUTTON1_CLICKED) {
            int x = event.x;
            int y = event.y;
            for (auto &entity : texts) {
                if (x >= entity.second.x && x <= entity.second.x + entity.second.text.size() && y == entity.second.y) {
                    return entity.first;
                }
            }
        }
    }
    return std::string("");
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
    {"orange", 208},
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
