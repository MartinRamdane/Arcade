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

void DisplaySfml::init(std::map<std::string, IGameModule::Entity> &entities) {
    sf::VideoMode video({1060, 1190});
    window = std::make_unique<sf::RenderWindow>(video, "Arcade-SFML");
    window->setFramerateLimit(30);
    if (!font.loadFromFile("./res/pixel.ttf"))
        throw "Error on loading Font";
    for (auto &entity : entities) {
        if (entity.second.type == IGameModule::ENTITY_TYPE::SPRITE) {
            sprites[entity.first] = createSprite(entity.first, entity.second.file, entity.second.xSprite, entity.second.ySprite);
        } else if (entity.second.type == IGameModule::ENTITY_TYPE::SPRITE_TEXT || entity.second.type == IGameModule::ENTITY_TYPE::TEXT) {
            texts[entity.first] = createText(entity.first, entity.second.text, entity.second.color, entity.second.background_color, entity.second.x, entity.second.y, entity.second.fontSize);
        }
        entity.second.toUpdate = false;
    }
}

void DisplaySfml::stop() {
    window->close();
}

void DisplaySfml::update(std::map<std::string, IGameModule::Entity> &entities) {
    for (auto &entity : entities) {
        if (entity.second.toUpdate) {
            if (entity.second.type == IGameModule::ENTITY_TYPE::SPRITE) {
                sprites[entity.first] = createSprite(entity.first, entity.second.file, entity.second.xSprite, entity.second.ySprite);
            } else if (entity.second.type == IGameModule::ENTITY_TYPE::SPRITE_TEXT || entity.second.type == IGameModule::ENTITY_TYPE::TEXT) {
                texts[entity.first] = createText(entity.first, entity.second.text, entity.second.color, entity.second.background_color, entity.second.x, entity.second.y, entity.second.fontSize);
            }
            entity.second.toUpdate = false;
        }
    }
    for (auto &text: texts) {
        if (entities.find(text.first) == entities.end()) {
            texts.erase(text.first);
            backgroundColors.erase(text.first);
        }
    }
    for (auto &sprite: sprites) {
        if (entities.find(sprite.first) == entities.end())
            sprites.erase(sprite.first);
    }
}

void DisplaySfml::draw() {
    window->clear();
    for (auto &background: backgroundColors)
        window->draw(*background.second);
    for (auto &sprite: sprites)
        window->draw(*sprite.second);
    for (auto &text: texts)
        window->draw(*text.second);
    window->setActive();
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

std::unique_ptr<sf::Text> DisplaySfml::createText(std::string name, std::string _text, std::string color, std::string background_color, float x, float y, int fontSize) {
    std::unique_ptr<sf::Text> text = std::make_unique<sf::Text>();
    text->setFont(font);
    text->setString(_text);
    text->setCharacterSize(fontSize);
    text->setFillColor(colors[color]);
    text->setPosition({x * 20, y * 50});
    if (background_color == "") {
        if (backgroundColors.find(name) != backgroundColors.end())
            backgroundColors.erase(name);
        return text;
    }
    backgroundColors[name] = std::make_unique<sf::RectangleShape>();
    backgroundColors[name]->setSize(sf::Vector2f(text->getLocalBounds().width * 1.1f, text->getLocalBounds().height * 1.4f));
    backgroundColors[name]->setFillColor(colors[background_color]);
    backgroundColors[name]->setPosition({text.get()->getPosition().x - text->getLocalBounds().width * 0.05f, text.get()->getPosition().y - text->getLocalBounds().height * 0.2f});
    return text;
}

std::unique_ptr<sf::Sprite> DisplaySfml::createSprite(std::string name, std::string file, float x, float y) {
    std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
    textures[name] = std::make_tuple(texture, file);
    if (!texture->loadFromFile(file))
        throw "Error on loading texture";
    std::unique_ptr<sf::Sprite> sprite = std::make_unique<sf::Sprite>();
    sprite->setOrigin(sf::Vector2f(texture->getSize().x / 2, texture->getSize().y / 2));
    sprite->setTexture(*std::get<0>(textures[name]), true);
    sprite->setPosition({x * 20, y * 50});
    return sprite;
}

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