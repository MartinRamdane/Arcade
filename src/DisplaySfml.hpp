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
        void init();
        void stop();
        void update(std::map<std::string, IGameModule::Entity> entities);
        void draw();
        void drawElement(IGameModule::Entity element);
        std::string getEvent();
        const std::string &getName() const;

    private:
        std::string displayName = "sfml";
        std::unique_ptr<sf::RenderWindow> window;
        sf::Event event;
        std::map<std::string, IGameModule::Entity> entities;
        std::map<std::string, sf::Text> texts;
        std::map<std::string, sf::RectangleShape> backgroundColors;
        std::map<std::string, std::tuple<std::shared_ptr<sf::Texture>, std::string>> textures;
        std::map<std::string, sf::Sprite> sprites;
        static std::map<std::string, sf::Color> colors;
        static std::map<sf::Keyboard::Key, std::string> keys;
        sf::Font font;
};

#endif /* !DISPLAY_SFML */
