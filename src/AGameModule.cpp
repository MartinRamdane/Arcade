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

IGameModule::Entity AGameModule::createEntity(std::string file, std::string text, std::string color, std::string background_color, float x, float y, bool isSprite)
{
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

IGameModule::GAME_STATUS AGameModule::getGameStatus()
{
    return gameStatus;
}
