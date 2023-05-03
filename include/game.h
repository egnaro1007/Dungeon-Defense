#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "entity.hpp"
class Game
{
private:
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    Mix_Music* music = NULL;
    int gameScore = 0;
    bool bgm = true;
public:
    Game();
    ~Game();
    int startMenu(int argc, char** argv);
    int gameStart(int argc, char** argv);
    int gameOver(int argc, char** argv);

    void returnGameScore(int score);
    void renderBackground(SDL_Texture* p_texture);
};