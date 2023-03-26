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

        /**
        ** @brief Start the game, initialize the game and all the variables
        ** @param username The username of the player
        **/
        virtual void startGame(std::string username) = 0;

        /**
        ** @brief Must be called to know if the game is over
        ** @return true if the game is over, false otherwise
        **/
        virtual bool isGameOver() = 0;

        /**
        ** @brief Update the game, must be called every frame
        ** @param key The key pressed by the player
        **/
        virtual void update(std::string key) = 0;

        /**
        ** @brief Get the infos of the game, the entities to display
        ** @return A map of the entities to display
        **/
        virtual std::map<std::string, IGameModule::Entity> &getInfos() = 0;

        /**
        ** @brief Create an entity, an entity is an object to display
        ** @param file The path to the file of the entity if it's a sprite
        ** @param text The text to display if it's a text
        ** @param color The color of the text if it's a text
        ** @param background_color The background color of the text if it's a text
        ** @param x The x position of the entity
        ** @param y The y position of the entity
        ** @param type The type of the entity)
        ** @param xSprite The x position of the sprite if it's a sprite
        ** @param ySprite The y position of the sprite if it's a sprite
        ** @param fontSize The size of the font if it's a text
        ** @return The entity created
        **/
        virtual IGameModule::Entity createEntity(std::string file, std::string text, std::string color, std::string background_color, float x, float y, ENTITY_TYPE type, float xSprite = 0, float ySprite = 0, int fontSize = 0) = 0;

        /**
        ** @brief Get the status of the game, the status can be MENU, PAUSED, IN_GAME or FINISHED
        ** @return The status of the game
        **/
        virtual IGameModule::GAME_STATUS getGameStatus() = 0;

    protected:
    private:
};

#endif /* !IGAME_MODULE */
