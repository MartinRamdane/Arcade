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
    step = 1;
    ySave = 0;
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
        infos[graph] = createEntity("", graph, "white", "", x, y, false);
        y += 1;
        i++;
    }
    y += 1;
    infos["Username:"] = createEntity("", "Username:", "white", "", 0, y, false);
    y += 1;
    infos["Username"] = createEntity("", "", "white", "", x, y, false);
    ySave = y;
}

bool LibMenu::isFinished() {
    if (graphChoice != "" && gameChoice != "" && username != "")
        return true;
    return false;
}

void LibMenu::handleKeys(std::vector<std::string> list, std::string key, std::string &toFill) {
    if (key == "ESCAPE" && step > 1) {
        infos[gameChoice].color = "white";
        infos[gameChoice].background_color = "";
        infos[games[0]].color = "black";
        infos[games[0]].background_color = "white";
        infos[graphs[select]].color = "white";
        infos[graphs[select]].background_color = "";
        select = 0;
        step--;
        return;
    }
    if (key == "UP" && select > 0) {
        infos[list[select]].color = "white";
        infos[list[select]].background_color = "";
        select--;
        infos[list[select]].color = "black";
        infos[list[select]].background_color = "white";
    }
    if (key == "DOWN" && select < (int)list.size() - 1) {
        infos[list[select]].color = "white";
        infos[list[select]].background_color = "";
        select++;
        infos[list[select]].color = "black";
        infos[list[select]].background_color = "white";
    }
    if (key == " ") {
        toFill = infos[list[select]].text;
        infos[list[select]].color = "black";
        infos[list[select]].background_color = "yellow";
        if (step == 1) {
            infos[graphs[0]].color = "black";
            infos[graphs[0]].background_color = "white";
        }
        if (step == 2) {
            infos["InputIndicator"] = createEntity("", "|", "white", "", 3, ySave, false);
        }
        step++;
        select = 0;
    }
}

void LibMenu::inputUser(std::string key) {
    if (key == "ESCAPE") {
        infos[graphChoice].color = "white";
        infos[graphChoice].background_color = "";
        infos[graphs[0]].color = "black";
        infos[graphs[0]].background_color = "white";
        select = 0;
        step--;
        return;
    }
    if (key == "ENTER" && infos["Username"].text.size() > 0) {
        username = infos["Username"].text;
        return;
    }
    if (key == "BACKSPACE" && infos["Username"].text.size() > 0) {
        infos["Username"].text.pop_back();
        infos["InputIndicator"].x -= 1;
    }
    if (((key >= "a" && key <= "z") || (key >= "A" && key <= "Z") || (key >= "0" && key <= "9") || key == "_" || key == "-") && (key != "BACKSPACE")) {
        infos["Username"].text += key;
        infos["InputIndicator"].x += 1;
    }
}

void LibMenu::update(std::string key) {
    if (step == 1) {
        handleKeys(games, key, gameChoice);
    }
    else if (step == 2) {
        handleKeys(graphs, key, graphChoice);
    }
    else if (step == 3) {
        inputUser(key);
        static bool blink = false;
        blink = !blink;
        if (blink) {
            infos["InputIndicator"].color = "black";
        } else {
            infos["InputIndicator"].color = "white";
        }
    }
}

std::map<std::string, IGameModule::Entity> LibMenu::getInfos() {
    return infos;
}

