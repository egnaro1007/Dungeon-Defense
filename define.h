#ifndef DEFINE_H
#define DEFINE_H

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>

#include "debug.hpp"

#define _SCREEN_WIDTH_ 1920
#define _SCREEN_HEIGHT_ 1080

const int _FPS_ = 10;

#define _FiLE_PATH_ "level.dat"

static SDL_Window* window = SDL_CreateWindow("Test window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _SCREEN_WIDTH_, _SCREEN_HEIGHT_, SDL_WINDOW_SHOWN);
static SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED /* | SDL_RENDERER_PRESENTVSYNC */);

SDL_Texture* loadImage(const char* file);


const int frameDelay = 1000 / _FPS_;

const Uint64 FrameStart = SDL_GetTicks64();
const int frameTime = SDL_GetTicks64() - FrameStart;
static void frameDelayy() {
    if (frameDelay > frameTime) {
        SDL_Delay(frameDelay - frameTime);
    }
}








SDL_Texture* loadImage(const char* file)
{
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, file);
    if (texture == NULL) crash(std::cout, "Load IMG", true);
    return texture;
}
#endif