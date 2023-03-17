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

void LibMenu::init() {
    int x = 4;
    int y = 3;
    int i = 0;
    infos["GameList"] = createEntity("", "Games list:", "white", "", 2, 1, IGameModule::ENTITY_TYPE::TEXT, 0, 0, 30);
    for (auto &game : games) {
        if (i == 0)
            infos[game] = createEntity("", game, "black", "white", x, y, IGameModule::ENTITY_TYPE::TEXT, 0, 0, 30);
        else
            infos[game] = createEntity("", game, "white", "", x, y, IGameModule::ENTITY_TYPE::TEXT, 0, 0, 30);
        y += 1;
        i++;
    }
    i = 0;
    y += 1;
    infos["GraphList"] = createEntity("", "Graph list:", "white", "", 2, y, IGameModule::ENTITY_TYPE::TEXT, 0, 0, 30);
    y += 2;
    for (auto &graph : graphs) {
        infos[graph] = createEntity("", graph, "white", "", x, y, IGameModule::ENTITY_TYPE::TEXT, 0, 0, 30);
        y += 1;
        i++;
    }
    y += 1;
    infos["Username:"] = createEntity("", "Username:", "white", "", 2, y, IGameModule::ENTITY_TYPE::TEXT, 0, 0, 30);
    y += 1;
    infos["Username"] = createEntity("", "", "white", "", x, y, IGameModule::ENTITY_TYPE::TEXT, 0, 0, 30);
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
        infos[gameChoice].spriteColor = "white";
        infos[gameChoice].background_color = "";
        infos[games[0]].color = "black";
        infos[games[0]].spriteColor = "black";
        infos[games[0]].background_color = "white";
        infos[graphs[select]].color = "white";
        infos[graphs[select]].spriteColor = "white";
        infos[graphs[select]].background_color = "";
        select = 0;
        step--;
        return;
    }
    if (key == "UP" && select > 0) {
        infos[list[select]].color = "white";
        infos[list[select]].spriteColor = "white";
        infos[list[select]].background_color = "";
        select--;
        infos[list[select]].color = "black";
        infos[list[select]].spriteColor = "black";
        infos[list[select]].background_color = "white";
    }
    if (key == "DOWN" && select < (int)list.size() - 1) {
        infos[list[select]].color = "white";
        infos[list[select]].spriteColor = "white";
        infos[list[select]].background_color = "";
        select++;
        infos[list[select]].color = "black";
        infos[list[select]].spriteColor = "black";
        infos[list[select]].background_color = "white";
    }
    if (key == " ") {
        toFill = infos[list[select]].text;
        infos[list[select]].color = "black";
        infos[list[select]].spriteColor = "black";
        infos[list[select]].background_color = "yellow";
        if (step == 1) {
            infos[graphs[0]].color = "black";
            infos[graphs[0]].spriteColor = "black";
            infos[graphs[0]].background_color = "white";
        }
        if (step == 2) {
            infos["InputIndicator"] = createEntity("", "|", "white", "", xSave, ySave, IGameModule::ENTITY_TYPE::TEXT, 0, 0, 30);
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
        xSave = infos["InputIndicator"].x;
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
