/*
** EPITECH PROJECT, 2023
** DisplaySfml.cpp
** File description:
** DisplaySfml
*/

#include "DisplaySfml.hpp"

DisplaySfml::DisplaySfml()
{
}

DisplaySfml::~DisplaySfml()
{
    window.close();
}

void DisplaySfml::init() {
    sf::VideoMode video({1000, 900});
    window.create(video, "Arcade-SFML");
    window.setFramerateLimit(60);
    if (!font.loadFromFile("arial.ttf"))
        throw "Error on loading Font";
}

void DisplaySfml::stop() {
    printf("Closing window\n");
    window.close();
}

void DisplaySfml::update(std::map<std::string, IGameModule::Entity> entities) {
    for (auto &entity : entities) {
        if (entity.second.text != "" || texts[entity.first].getString() != "") {
            texts[entity.first].setFont(font);
            texts[entity.first].setString(entity.second.text);
            texts[entity.first].setCharacterSize(40);
            texts[entity.first].setFillColor(colors[entity.second.color]);
            texts[entity.first].setPosition({entity.second.x * 20, entity.second.y * 50});
            backgroundColors[entity.first] = sf::RectangleShape(sf::Vector2f(texts[entity.second.text].getLocalBounds().width, texts[entity.second.text].getLocalBounds().height));
            backgroundColors[entity.first].setSize(sf::Vector2f(1.2f * backgroundColors[entity.second.text].getSize().x, 1.3f * backgroundColors[entity.second.text].getSize().y));
            backgroundColors[entity.first].setPosition(texts[entity.second.text].getPosition());
            backgroundColors[entity.first].setFillColor(colors[entity.second.background_color]);
        }
    }
}

void DisplaySfml::draw() {
    window.clear();
    for (auto &background: backgroundColors) {
        window.draw(background.second);
    }
    for (auto &text: texts) {
        window.draw(text.second);
    }
    window.display();
}

void DisplaySfml::drawElement(IGameModule::Entity element) {

}

std::string DisplaySfml::getEvent() {
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed)
            return (keys[event.key.code]);
    }
    return "";
}

const std::string &DisplaySfml::getName() const {
    return displayName;
}

std::map<sf::Keyboard::Key, std::string> DisplaySfml::keys = {
    {sf::Keyboard::A, "a"},
    {sf::Keyboard::B, "b"},
    {sf::Keyboard::C, "c"},
    {sf::Keyboard::D, "d"},
    {sf::Keyboard::E, "e"},
    {sf::Keyboard::F, "f"},
    {sf::Keyboard::G, "g"},
    {sf::Keyboard::H, "h"},
    {sf::Keyboard::I, "i"},
    {sf::Keyboard::J, "j"},
    {sf::Keyboard::K, "k"},
    {sf::Keyboard::L, "l"},
    {sf::Keyboard::M, "m"},
    {sf::Keyboard::N, "n"},
    {sf::Keyboard::O, "o"},
    {sf::Keyboard::P, "p"},
    {sf::Keyboard::Q, "q"},
    {sf::Keyboard::R, "r"},
    {sf::Keyboard::S, "s"},
    {sf::Keyboard::T, "t"},
    {sf::Keyboard::U, "u"},
    {sf::Keyboard::V, "v"},
    {sf::Keyboard::W, "w"},
    {sf::Keyboard::X, "x"},
    {sf::Keyboard::Y, "y"},
    {sf::Keyboard::Z, "z"},
    {sf::Keyboard::Space, " "},
    {sf::Keyboard::Backspace, "BACKSPACE"},
    {sf::Keyboard::Enter, "ENTER"},
    {sf::Keyboard::Escape, "ESCAPE"},
    {sf::Keyboard::Up, "UP"},
    {sf::Keyboard::Down, "DOWN"},
    {sf::Keyboard::F1, "F1"},
    {sf::Keyboard::F2, "F2"},
    {sf::Keyboard::Tab, "\t"}
};

std::map<std::string, sf::Color> DisplaySfml::colors = {
    {"red", sf::Color::Red},
    {"green", sf::Color::Green},
    {"blue", sf::Color::Blue},
    {"yellow", sf::Color::Yellow},
    {"magenta", sf::Color::Magenta},
    {"cyan", sf::Color::Cyan},
    {"white", sf::Color::White},
    {"black", sf::Color::Black},
    {"transparent", sf::Color::Transparent}
};

extern "C" IDisplayModule* create() {
    return new DisplaySfml();
}

extern "C" void destroy(IDisplayModule* obj) {
    delete obj;
}

extern "C" std::string getType() {
    return "Graphic";
}