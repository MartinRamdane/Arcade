/*
** EPITECH PROJECT, 2023
** DisplaySdl.cpp
** File description:
** DisplaySdl
*/

#include "DisplaySdl2.hpp"

DisplaySdl::DisplaySdl()
{
}

DisplaySdl::~DisplaySdl()
{
}

void DisplaySdl::init(std::map<std::string, IGameModule::Entity> &entities) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
        throw;
    }
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);
    window = SDL_CreateWindow("Arcade-SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 530, 595, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);
    font = TTF_OpenFont("./res/pixel.ttf", 18);
    for (auto &entity : entities) {
        if (entity.second.type == IGameModule::TEXT || entity.second.type == IGameModule::SPRITE_TEXT) {
            createText(entity.first, entity.second);
        }
        if (entity.second.type == IGameModule::SPRITE) {
            createSprite(entity.first, entity.second);
        }
        entity.second.toUpdate = false;
    }
}

void DisplaySdl::stop() {
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    IMG_Quit();
}

void DisplaySdl::update(std::map<std::string, IGameModule::Entity> &entities) {
    for (auto &entity : entities) {
        if (entity.second.toUpdate) {
            if (entity.second.type == IGameModule::TEXT || entity.second.type == IGameModule::SPRITE_TEXT) {
                (entities.find(entity.first) != entities.end()) ? updateText(entity.first, entity.second) : createText(entity.first, entity.second);
            }
            if (entity.second.type == IGameModule::SPRITE) {
                (entities.find(entity.first) != entities.end()) ? updateSprite(entity.first, entity.second) : createSprite(entity.first, entity.second);
            }
        }
        entity.second.toUpdate = false;
    }
}

void DisplaySdl::draw() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    for (auto &text: texts) {
        SDL_QueryTexture(text.second.texture, NULL, NULL, &text.second.rect.w, &text.second.rect.h);
        SDL_RenderCopy(renderer, text.second.texture, NULL, &text.second.rect);
    }
    for (auto &sprite: sprites) {
        SDL_RenderCopy(renderer, sprite.second.texture, NULL, &sprite.second.rect);
    }
    SDL_RenderPresent(renderer);
}

std::string DisplaySdl::getEvent() {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            SDL_Quit();
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    return std::string("UP");
                case SDLK_DOWN:
                    return std::string("DOWN");
                case SDLK_LEFT:
                    return std::string("LEFT");
                case SDLK_RIGHT:
                    return std::string("RIGHT");
                case 27:
                    return std::string("ESCAPE");
                case 8:
                    return std::string("BACKSPACE");
                case 13:
                    return std::string("ENTER");
            }
            return std::string(1, event.key.keysym.sym);
        }
    }
    return "";
}

void DisplaySdl::createText(std::string name, IGameModule::Entity entity) {
    SDL_Color color = colors[entity.color];
    Text text;
    text.surface = TTF_RenderText_Shaded(font, entity.text.c_str(), color, colors[entity.background_color]);
    text.texture = SDL_CreateTextureFromSurface(renderer, text.surface);
    text.rect = { (int)entity.x * 10, (int)entity.y * 30, 0, 0 };
    texts[name] = text;
}

void DisplaySdl::updateText(std::string name, IGameModule::Entity entity) {
    texts[name].rect = { (int)entity.x * 10, (int)entity.y * 30, 0, 0 };
    SDL_Color color = colors[entity.color];
    texts[name].surface = TTF_RenderText_Shaded(font, entity.text.c_str(), color, colors[entity.background_color]);
    texts[name].texture = SDL_CreateTextureFromSurface(renderer, texts[name].surface);
}

void DisplaySdl::createSprite(std::string name, IGameModule::Entity entity) {
    if (entity.file == "" || entity.xSprite == -1 || entity.ySprite == -1)
        return;
    Sprite sprite;
    sprite.surface = IMG_Load(entity.file.c_str());
    sprite.texture = SDL_CreateTextureFromSurface(renderer, sprite.surface);
    sprite.rect = { (int)entity.xSprite * 10, (int)entity.ySprite * 30, sprite.surface->w, sprite.surface->h};
    SDL_FreeSurface(sprite.surface);
    sprites[name] = sprite;
}



void DisplaySdl::updateSprite(std::string name, IGameModule::Entity entity) {
    // sprites[name].rect = { 0, 0, 400, 300 };
    // SDL_RenderCopy(renderer, sprites[name].texture, NULL, &sprites[name].rect);
}

std::map<std::string, SDL_Color> DisplaySdl::colors = {
    {"red", {255, 0, 0, 255}},
    {"green", {0, 255, 0, 255}},
    {"blue", {0, 0, 255, 255}},
    {"white", {255, 255, 255, 255}},
    {"black", {0, 0, 0, 255}},
    {"yellow", {255, 255, 0, 255}},
    {"cyan", {0, 255, 255, 255}},
    {"magenta", {255, 0, 255, 255}},
    {"gray", {128, 128, 128, 255}},
    {"grey", {128, 128, 128, 255}},
    {"silver", {192, 192, 192, 255}},
    {"maroon", {128, 0, 0, 255}},
    {"olive", {128, 128, 0, 255}},
    {"purple", {128, 0, 128, 255}},
    {"teal", {0, 128, 128, 255}},
    {"navy", {0, 0, 128, 255}},
    {"orange", {255, 165, 0, 255}},
    {"brown", {165, 42, 42, 255}},
    {"pink", {255, 192, 203, 255}},
    {"lime", {0, 255, 0, 255}},
    {"fuchsia", {255, 0, 255, 255}},
    {"aqua", {0, 255, 255, 255}},
    {"transparent", {0, 0, 0, 0}},
};

const std::string &DisplaySdl::getName() const {
    return _name;
}

extern "C" std::shared_ptr<IDisplayModule> create() {
    return std::make_shared<DisplaySdl>();
}

extern "C" const char *getType() {
    const char *type = "Graphic";
    return type;
}