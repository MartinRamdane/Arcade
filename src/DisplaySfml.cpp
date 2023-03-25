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
    if (!font.loadFromFile("./res/pixel.ttf"))
        throw "Error on loading Font";
    for (auto &entity : entities) {
        if (entity.second.type == IGameModule::ENTITY_TYPE::SPRITE || entity.second.type == IGameModule::ENTITY_TYPE::SPRITE_TEXT) {
            createSprite(entity.first, entity.second);
        }
        if (entity.second.type == IGameModule::ENTITY_TYPE::SPRITE_TEXT || entity.second.type == IGameModule::ENTITY_TYPE::TEXT) {
            createText(entity.first, entity.second);
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
            if (entity.second.type == IGameModule::ENTITY_TYPE::SPRITE || entity.second.type == IGameModule::ENTITY_TYPE::SPRITE_TEXT) {
                (sprites.find(entity.first) != sprites.end()) ? updateSprite(entity.first, entity.second) : createSprite(entity.first, entity.second);
            }
            if (entity.second.type == IGameModule::ENTITY_TYPE::TEXT || entity.second.type == IGameModule::ENTITY_TYPE::SPRITE_TEXT) {
                (texts.find(entity.first) != texts.end()) ? updateText(entity.first, entity.second) : createText(entity.first, entity.second);
            }
            entity.second.toUpdate = false;
        }
    }
    for (auto it = texts.begin(); it != texts.end();) {
        if (entities.find(it->first) == entities.end()) {
            it = texts.erase(it);
            backgroundColors.erase(it->first);
        } else {
            ++it;
        }
    }
    for (auto it = sprites.begin(); it != sprites.end();) {
        if (entities.find(it->first) == entities.end()) {
            it = sprites.erase(it);
            backgroundColors.erase(it->first);
        } else {
            ++it;
        }
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
        if (event.type == sf::Event::MouseButtonPressed)
            return getMouseEvent();
    }
    return "";
}

std::string DisplaySfml::getMouseEvent() {
    if (event.mouseButton.button == sf::Mouse::Left) {
        float x = event.mouseButton.x;
        float y = event.mouseButton.y;
        for (auto &sprite: sprites) {
            if (sprite.second->getGlobalBounds().contains(x, y))
                return sprite.first;
        }
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

void DisplaySfml::createText(std::string name, IGameModule::Entity entity) {
    texts[name] = std::make_unique<sf::Text>();
    texts[name]->setFont(font);
    texts[name]->setString(entity.text);
    texts[name]->setCharacterSize(entity.fontSize);
    if (entity.type == IGameModule::TEXT)
        texts[name]->setFillColor(colors[entity.color]);
    if (std::get<0>(textures[name]))
        texts[name]->setPosition(sf::Vector2f(sprites[name]->getPosition().x + sprites[name]->getLocalBounds().width / 2 - texts[name]->getLocalBounds().width / 2 - sprites[name]->getOrigin().x, sprites[name]->getPosition().y + sprites[name]->getLocalBounds().height / 2 - texts[name]->getLocalBounds().height / 2 - sprites[name]->getOrigin().y));
    else
        texts[name]->setPosition({entity.xSprite * 20, entity.ySprite * 50});
    if (entity.background_color == "") {
        if (backgroundColors.find(name) != backgroundColors.end())
            backgroundColors.erase(name);
        return;
    }
    if (entity.type!= IGameModule::TEXT)
        return;
    backgroundColors[name] = std::make_unique<sf::RectangleShape>();
    backgroundColors[name]->setSize(sf::Vector2f(texts[name]->getLocalBounds().width * 1.1f, texts[name]->getLocalBounds().height * 1.4f));
    backgroundColors[name]->setFillColor(colors[entity.background_color]);
    backgroundColors[name]->setPosition({texts[name]->getPosition().x - texts[name]->getLocalBounds().width * 0.05f, texts[name]->getPosition().y - texts[name]->getLocalBounds().height * 0.2f});
}

void DisplaySfml::createSprite(std::string name, IGameModule::Entity entity) {
    if (entity.file == "" || entity.xSprite == -1 || entity.ySprite == -1)
        return;
    std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
    textures[name] = std::make_tuple(texture, entity.file);
    if (!texture->loadFromFile(entity.file))
        throw "Error on loading texture";
    sprites[name] = std::make_unique<sf::Sprite>();
    sprites[name]->setOrigin(sf::Vector2f(texture->getSize().x / 2, texture->getSize().y / 2));
    sprites[name]->setTexture(*std::get<0>(textures[name]), true);
    sprites[name]->setPosition({entity.xSprite * 20, entity.ySprite * 50});
}

void DisplaySfml::updateText(std::string name, IGameModule::Entity entity) {
    texts[name]->setString(entity.text);
    texts[name]->setCharacterSize(entity.fontSize);
    if (entity.type == IGameModule::TEXT)
        texts[name]->setFillColor(colors[entity.color]);
    if (std::get<0>(textures[name]))
        texts[name]->setPosition(sf::Vector2f(sprites[name]->getPosition().x + sprites[name]->getLocalBounds().width / 2 - texts[name]->getLocalBounds().width / 2 - sprites[name]->getOrigin().x, sprites[name]->getPosition().y + sprites[name]->getLocalBounds().height / 2 - texts[name]->getLocalBounds().height / 2 - sprites[name]->getOrigin().y));
    else
        texts[name]->setPosition({entity.xSprite * 20, entity.ySprite * 50});
    if (entity.background_color == "") {
        if (backgroundColors.find(name) != backgroundColors.end())
            backgroundColors.erase(name);
        return;
    }
    if (entity.type != IGameModule::TEXT)
        return;
    if (backgroundColors.find(name) == backgroundColors.end())
        backgroundColors[name] = std::make_unique<sf::RectangleShape>();
    backgroundColors[name]->setSize(sf::Vector2f(texts[name]->getLocalBounds().width * 1.1f, texts[name]->getLocalBounds().height * 1.4f));
    backgroundColors[name]->setFillColor(colors[entity.background_color]);
    backgroundColors[name]->setPosition({texts[name]->getPosition().x - texts[name]->getLocalBounds().width * 0.05f, texts[name]->getPosition().y - texts[name]->getLocalBounds().height * 0.2f});
}

void DisplaySfml::updateSprite(std::string name, IGameModule::Entity entity) {
    if (std::get<1>(textures[name]) != entity.file && entity.file != "") {
        std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
        textures[name] = std::make_tuple(texture, entity.file);
        if (!texture->loadFromFile(entity.file))
            throw "Error on loading texture";
    }
    sprites[name]->setTexture(*std::get<0>(textures[name]), true);
    sprites[name]->setPosition({entity.xSprite * 20, entity.ySprite * 50});
}

extern "C" IDisplayModule *create() {
    return new DisplaySfml();
}

extern "C" void destroy(IDisplayModule *display) {
    delete display;
}

extern "C" const char *getType() {
    const char *type = "Graphic";
    return type;
}