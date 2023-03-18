/*
** EPITECH PROJECT, 2023
** IGameModule.hpp
** File description:
** IGameModule
*/

#ifndef IGAME_MODULE
    #define IGAME_MODULE

#include <iostream>
#include <string>
#include <map>

class IGameModule {
    public:
        enum GAME_STATUS {
            MENU,
            PAUSED,
            IN_GAME,
            FINISHED
        };

        enum ENTITY_TYPE {
            SPRITE,
            TEXT,
            SPRITE_TEXT,
            BACKGROUND,
            TEXTURE,
            NONE
        };

        struct Entity {
            std::string file;
            std::string text;
            int fontSize;
            std::string color;
            std::string background_color;
            std::string spriteColor;
            float x;
            float y;
            float xSprite;
            float ySprite;
            ENTITY_TYPE type;
            bool toUpdate;
        };

        virtual ~IGameModule () = default ;
        virtual void startGame(std::string username) = 0;
        virtual bool isGameOver() = 0;
        virtual void update(std::string key) = 0;
        virtual std::map<std::string, IGameModule::Entity> &getInfos() = 0;
        virtual IGameModule::Entity createEntity(std::string file, std::string text, std::string color, std::string background_color, float x, float y, ENTITY_TYPE type, float xSprite = 0, float ySprite = 0, int fontSize = 0) = 0;
        virtual IGameModule::GAME_STATUS getGameStatus() = 0;

    protected:
    private:
};

#endif /* !IGAME_MODULE */
