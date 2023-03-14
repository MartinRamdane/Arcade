/*
** EPITECH PROJECT, 2023
** LibMenu.cpp
** File description:
** LibMenu
*/

#include "LibMenu.hpp"

LibMenu::LibMenu(std::vector<std::string> games, std::vector<std::string> graphs)
{
    this->games = games;
    this->graphs = graphs;
    graphChoice = "";
    gameChoice = "";
}

LibMenu::~LibMenu()
{
}

IGameModule::Entity LibMenu::createEntity(std::string file, std::string text, std::string color, std::string background_color, float x, float y, bool isSprite) {
    IGameModule::Entity entity;
    entity.file = file;
    entity.text = text;
    entity.color = color;
    entity.background_color = background_color;
    entity.x = x;
    entity.y = y;
    entity.isSprite = isSprite;
    return entity;
}

void LibMenu::init() {
    int x = 3;
    int y = 2;
    int i = 0;
    infos["GameList"] = createEntity("", "Games list:", "white", "", 0, 0, false);
    for (auto &game : games) {
        if (i == 0)
            infos[game] = createEntity("", game, "black", "white", x, y, false);
        else
            infos[game] = createEntity("", game, "white", "", x, y, false);
        y += 1;
        i++;
    }
    i = 0;
    y += 1;
    infos["GraphList"] = createEntity("", "Graph list:", "white", "", 0, y, false);
    y += 2;
    for (auto &graph : graphs) {
        if (i == 0)
            infos[graph] = createEntity("", graph, "black", "white", x, y, false);
        else
            infos[graph] = createEntity("", graph, "white", "", x, y, false);
        y += 1;
        i++;
    }
    y += 1;
    infos["Username"] = createEntity("", "Set username", "white", "", 0, y, false);
    y += 2;
    // put user input here
    it = infos.begin();
    it++;
}

bool LibMenu::isFinished() {
    if (graphChoice != "" && gameChoice != "" && username != "")
        return true;
    return false;
}

void LibMenu::update(std::string key) {
    if (key == "UP") {
        if (it == infos.begin())
            it = infos.end();
        it--;
    }
}

std::map<std::string, IGameModule::Entity> LibMenu::getInfos() {
    return infos;
}

