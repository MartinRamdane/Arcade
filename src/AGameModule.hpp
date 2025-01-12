/*
** EPITECH PROJECT, 2023
** AGameModule.hpp
** File description:
** AGameModule
*/

#ifndef HEADER_AGAMEMODULE
    #define HEADER_AGAMEMODULE

#include "IGameModule.hpp"
#include <map>
#include <chrono>
#include <thread>

class AGameModule : public IGameModule {
    public:
        AGameModule();
        ~AGameModule();
        std::map<std::string, IGameModule::Entity> &getInfos();
        IGameModule::Entity createEntity(std::string file, std::string text, std::string color, std::string background_color, float x, float y, ENTITY_TYPE type, float xSprite, float ySprite, int fontSize);
        IGameModule::GAME_STATUS getGameStatus();

    protected:
        std::string username;
        std::map<std::string, IGameModule::Entity> infos;
        IGameModule::GAME_STATUS gameStatus;
        int areaWidth;
        int areaHeight;
        int score;
        int selectMenu;
    private:
};

#endif /* !HEADER_AGAMEMODULE */
