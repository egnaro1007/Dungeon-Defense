#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "entity.hpp"
class Game
{
private:
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
public:
    Game();
    ~Game();
    int gameStart(int argc, char** argv);
    void renderBackground(SDL_Texture* p_texture);
};