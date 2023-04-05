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
    SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
        throw;
    }
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);
    window = SDL_CreateWindow("Arcade-SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 432, 400, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
    renderer = SDL_CreateRenderer(window, -1, 0);
    font = TTF_OpenFont("./res/pixel.ttf", 30);
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

void DisplaySdl::stop() {
    for (auto &sprite : sprites) {
        SDL_FreeSurface(sprite.second.surface);
        SDL_DestroyTexture(std::get<0>(textures[sprite.first]));
    }
    for (auto &text : texts) {
        SDL_FreeSurface(text.second.surface);
        SDL_DestroyTexture(text.second.texture);
    }
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
        } else {
            ++it;
        }
    }
    for (auto it = sprites.begin(); it != sprites.end();) {
        if (entities.find(it->first) == entities.end()) {
            it = sprites.erase(it);
        } else {
            ++it;
        }
    }
}

void DisplaySdl::draw() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    for (auto &sprite: sprites) {
        SDL_RenderCopy(renderer, std::get<0>(textures[sprite.first]), NULL, &sprite.second.rect);
    }
    for (auto &text: texts) {
        SDL_QueryTexture(text.second.texture, NULL, NULL, &text.second.rect.w, &text.second.rect.h);
        SDL_RenderCopy(renderer, text.second.texture, NULL, &text.second.rect);
    }
    SDL_RenderPresent(renderer);
}

std::string DisplaySdl::getEvent() {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            SDL_Quit();
        if (event.type == SDL_MOUSEBUTTONDOWN)
            return getMouseEvent();
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

std::string DisplaySdl::getMouseEvent() {
    if (event.button.button == SDL_BUTTON_LEFT) {
        float x = event.button.x;
        float y = event.button.y;
        for (auto &sprite: sprites) {
            if (x*2 >= sprite.second.rect.x - (sprite.second.rect.w/2) && x*2 <= sprite.second.rect.x + (sprite.second.rect.w/2) && y*2 >= sprite.second.rect.y - (sprite.second.rect.h/2) && y*2 <= sprite.second.rect.y + (sprite.second.rect.h/2)) {
                return sprite.first;
            }
        }
    }
    return "";
}

void DisplaySdl::createText(std::string name, IGameModule::Entity entity) {
    SDL_Color color = colors[entity.color];
    Text text;
    if (entity.type != IGameModule::TEXT)
        color = {255, 255, 255, 255};
    if (entity.type != IGameModule::TEXT)
        text.surface = TTF_RenderText_Shaded(font, entity.text.c_str(), color, {0, 0, 0, 255});
    else
        text.surface = TTF_RenderText_Shaded(font, entity.text.c_str(), color, colors[entity.background_color]);
    text.texture = SDL_CreateTextureFromSurface(renderer, text.surface);
    text.rect = { (int)entity.x * 14, (int)entity.y * 31, 0, 0 };
    texts[name] = text;
}

void DisplaySdl::updateText(std::string name, IGameModule::Entity entity) {
    texts[name].rect ={ (int)entity.x * 14, (int)entity.y * 31, 0, 0 };
    SDL_Color color = colors[entity.color];
    if (entity.type != IGameModule::TEXT)
        color = {255, 255, 255, 255};
    if (entity.type != IGameModule::TEXT)
        texts[name].surface = TTF_RenderText_Shaded(font, entity.text.c_str(), color, {0, 0, 0, 255});
    else
        texts[name].surface = TTF_RenderText_Shaded(font, entity.text.c_str(), color, colors[entity.background_color]);
    texts[name].texture = SDL_CreateTextureFromSurface(renderer, texts[name].surface);
}

void DisplaySdl::createSprite(std::string name, IGameModule::Entity entity) {
    if (entity.file == "" || entity.xSprite == -1 || entity.ySprite == -1)
        return;
    Sprite sprite;
    sprite.surface = IMG_Load(entity.file.c_str());
    textures[name] = std::make_tuple(SDL_CreateTextureFromSurface(renderer, sprite.surface), entity.file);
    sprite.rect = { (int)((entity.xSprite * 16) - (sprite.surface->w /4/2)), (int)((entity.ySprite * 32) - (sprite.surface->h /4)), (int)(sprite.surface->w /4), (int)(sprite.surface->h /2)};
    sprites[name] = sprite;
}



void DisplaySdl::updateSprite(std::string name, IGameModule::Entity entity) {
   if (std::get<1>(textures[name]) != entity.file && entity.file != "") {
        sprites.erase(name);
        textures.erase(name);
        createSprite(name, entity);
    }
    sprites[name].rect = { (int)((entity.xSprite *16) - (sprites[name].surface->w /4/2)), (int)((entity.ySprite *32) - (sprites[name].surface->h /4)), (int)(sprites[name].surface->w /4), (int)(sprites[name].surface->h /2)};
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

extern "C" IDisplayModule *create() {
    return new DisplaySdl();
}

extern "C" void destroy(IDisplayModule *display) {
    delete display;
}

extern "C" const char *getType() {
    const char *type = "Graphic";
    return type;
}