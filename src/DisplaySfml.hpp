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
#include <map>

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
        sf::RenderWindow window;
        sf::Event event;
        std::map<std::string, sf::Text> texts;
        std::map<std::string, sf::RectangleShape> backgroundColors;
        static std::map<std::string, sf::Color> colors;
        static std::map<sf::Keyboard::Key, std::string> keys;
        sf::Font font;
};

#endif /* !DISPLAY_SFML */
