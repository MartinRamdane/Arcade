/*
** EPITECH PROJECT, 2023
** DisplaySdl.hpp
** File description:
** DisplaySdl
*/

#ifndef DISPLAY_SDL
    #define DISPLAY_SDL

#include "IDisplayModule.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <map>

class DisplaySdl : public IDisplayModule {

    public:

    struct Text {
        SDL_Surface* surface;
        SDL_Texture* texture;
        SDL_Rect rect;
    };

        DisplaySdl();
        ~DisplaySdl();
        void init();
        void stop();
        void update(std::map<std::string, IGameModule::Entity> entities);
        void draw();
        std::string getEvent();
        const std::string &getName() const;

    private:
        std::string displayName = "sdl";
        SDL_Window* window;
        SDL_Event event;
        SDL_Renderer* renderer;
        std::map<std::string, Text> texts;
        TTF_Font* font;
        static std::map<std::string, SDL_Color> colors;
};

#endif /* !DISPLAY_SDL */
