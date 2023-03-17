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
    window->close();
}

void DisplaySfml::init() {
    sf::VideoMode video({1060, 1190});
    window = std::make_unique<sf::RenderWindow>(video, "Arcade-SFML");
    window->setFramerateLimit(30);
    if (!font.loadFromFile("./res/pixel.ttf"))
        throw "Error on loading Font";
}

void DisplaySfml::stop() {
    window->close();
}

void DisplaySfml::update(std::map<std::string, IGameModule::Entity> entities) {
    this->entities = entities;
    for (auto &entity : entities) {
        if (entity.second.file != "" && (entity.second.type == IGameModule::ENTITY_TYPE::SPRITE || entity.second.type == IGameModule::ENTITY_TYPE::SPRITE_TEXT) && ((std::get<1>(textures[entity.first]) != entities[entity.first].file) || ((sprites[entity.first].getPosition().x != entities[entity.first].xSprite) || (sprites[entity.first].getPosition().y != entities[entity.first].ySprite)))) {
            sf::Texture* texture = new sf::Texture();
            textures[entity.first] = std::make_tuple(std::shared_ptr<sf::Texture>(texture), entity.second.file);
            if (!texture->loadFromFile(entity.second.file))
                throw "Error on loading texture";
            sprites[entity.first].setOrigin(sf::Vector2f(texture->getSize().x / 2, texture->getSize().y / 2));
            sprites[entity.first].setTexture(*std::get<0>(textures[entity.first]), true);
            sprites[entity.first].setPosition({entity.second.xSprite * 20, entity.second.ySprite * 50});
        }
        if ((entity.second.text != "" && (entity.second.type == IGameModule::ENTITY_TYPE::SPRITE_TEXT || entity.second.type == IGameModule::ENTITY_TYPE::TEXT)) || texts[entity.first].getString() != "") {
            texts[entity.first].setFont(font);
            texts[entity.first].setString(entity.second.text);
            texts[entity.first].setCharacterSize(entity.second.fontSize);
            texts[entity.first].setFillColor(colors[entity.second.spriteColor]);
            if (std::get<0>(textures[entity.first]))
                texts[entity.first].setPosition(sf::Vector2f(sprites[entity.first].getPosition().x + sprites[entity.first].getLocalBounds().width / 2 - texts[entity.first].getLocalBounds().width / 2 - sprites[entity.first].getOrigin().x, sprites[entity.first].getPosition().y + sprites[entity.first].getLocalBounds().height / 2 - texts[entity.first].getLocalBounds().height / 2 - sprites[entity.first].getOrigin().y));
            else
                texts[entity.first].setPosition({entity.second.xSprite * 20, entity.second.ySprite * 50});
            backgroundColors[entity.first] = sf::RectangleShape(sf::Vector2f(texts[entity.second.text].getLocalBounds().width, texts[entity.second.text].getLocalBounds().height));
            backgroundColors[entity.first].setSize(sf::Vector2f(1.2f * backgroundColors[entity.second.text].getSize().x, 1.3f * backgroundColors[entity.second.text].getSize().y));
            backgroundColors[entity.first].setPosition(sf::Vector2f(texts[entity.second.text].getPosition().x - 0.1f * backgroundColors[entity.second.text].getSize().x, texts[entity.second.text].getPosition().y - 0.15f * backgroundColors[entity.second.text].getSize().y));
            backgroundColors[entity.first].setFillColor(colors[entity.second.background_color]);
        }
    }
}

void DisplaySfml::draw() {
    window->clear();
    for (auto &background: backgroundColors) {
        auto it = entities.find(background.first);
        if (it != entities.end())
            window->draw(background.second);
    }
    for (auto &sprite: sprites) {
        auto it = entities.find(sprite.first);
        if (it != entities.end())
            window->draw(sprite.second);
    }
    for (auto &text: texts) {
        auto it = entities.find(text.first);
        if (it != entities.end())
            window->draw(text.second);
    }
    window->display();
}

std::string DisplaySfml::getEvent() {
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window->close();
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
    {sf::Keyboard::Tab, "\t"},
    {sf::Keyboard::Equal, "-"}
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

extern "C" char *getType() {
    char *type = strdup("Graphic");
    return type;
}