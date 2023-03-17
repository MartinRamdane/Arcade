/*
** EPITECH PROJECT, 2023
** AGameModule.cpp
** File description:
** AGameModule
*/

#include "AGameModule.hpp"

AGameModule::AGameModule()
{
}

AGameModule::~AGameModule()
{
}

std::map<std::string, IGameModule::Entity> AGameModule::getInfos()
{
    return infos;
}

IGameModule::Entity AGameModule::createEntity(std::string file, std::string text, std::string color, std::string background_color, float x, float y, ENTITY_TYPE type, float xSprite, float ySprite, int fontSize)
{
    IGameModule::Entity entity;
    entity.file = file;
    entity.text = text;
    entity.color = color;
    entity.background_color = background_color;
    entity.x = x;
    entity.y = y;
    if (xSprite == 0)
        entity.xSprite = x;
    else
        entity.xSprite = xSprite;
    if (ySprite == 0)
        entity.ySprite = y;
    else
        entity.ySprite = ySprite;
    entity.spriteColor = color;
    entity.type = type;
    entity.fontSize = fontSize;
    return entity;
}

IGameModule::GAME_STATUS AGameModule::getGameStatus()
{
    return gameStatus;
}
