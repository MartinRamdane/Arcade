/*
** EPITECH PROJECT, 2023
** DisplaySfml.hpp
** File description:
** DisplaySfml
*/

#ifndef DISPLAY_SFML
    #define DISPLAY_SFML

#include "IDisplayModule.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <tuple>
#include <map>
#include <memory>

class DisplaySfml : public IDisplayModule {
    public:
        DisplaySfml();
        ~DisplaySfml();
        void init(std::map<std::string, IGameModule::Entity> &entities);
        void stop();
        void update(std::map<std::string, IGameModule::Entity> &entities);
        void draw();
        std::string getEvent();
        const std::string &getName() const;
        void createText(std::string name, IGameModule::Entity entity);
        void updateText(std::string name, IGameModule::Entity entity);
        void createSprite(std::string name, IGameModule::Entity entity);
        void updateSprite(std::string name, IGameModule::Entity entity);
        std::string getMouseEvent();

    private:
        std::string displayName = "sfml";
        std::unique_ptr<sf::RenderWindow> window;
        sf::Event event;
        std::map<std::string, std::unique_ptr<sf::Text>> texts;
        std::map<std::string, std::unique_ptr<sf::RectangleShape>> backgroundColors;
        std::map<std::string, std::tuple<std::shared_ptr<sf::Texture>, std::string>> textures;
        std::map<std::string,  std::unique_ptr<sf::Sprite>> sprites;
        static std::map<std::string, sf::Color> colors;
        static std::map<sf::Keyboard::Key, std::string> keys;
        sf::Font font;
};

#endif /* !DISPLAY_SFML */
