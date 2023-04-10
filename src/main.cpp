#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>
#include <ctime>
//#include "../include/define.h"
#include "../include/entity.hpp"
// #include "../include/platform.hpp" // Đã bao gồm trong level.hpp
#include "../include/level.hpp"

#define _SCREEN_WIDTH_ 1920
#define _SCREEN_HEIGHT_ 1080

#define _STATUS_JUMP_ 1
#define _STATUS_FALL_ 2
#define _STATUS_WALK_LEFT_ 3
#define _STATUS_WALK_RIGHT_ 4

// Utils.cpp
SDL_Texture* loadImage(SDL_Renderer* renderer, const char* file);
void frameDelayy();
bool spriteDelayCheck();

// Main.cpp
void render(Entity &p_entity);
void renderBackground(SDL_Texture* p_texture);
// void renderEverything(Entity entity[]);
// bool collisionCheck(Entity &p_entity, platform &p_platform, int &nextMoveDistanceX, int &nextMoveDistanceY);
bool platformCollisionCheck(Entity &p_entity, std::vector<platform> &p_platform, int nextMoveDistanceX, int nextMoveDistanceY);


// Create window and renderer
static SDL_Window* window = SDL_CreateWindow("Test window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _SCREEN_WIDTH_, _SCREEN_HEIGHT_, SDL_WINDOW_SHOWN);
static SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED /*|| SDL_RENDERER_PRESENTVSYNC*/);


int main(int argc, char** argv)
{
    // Init SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "Init SDL failed: " << SDL_GetError() << "\n";
        SDL_Quit();
        return 1;
    }
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    
    // Load music
    Mix_Music* music = Mix_LoadMUS("assets/background.mp3");
    // Load texture
    SDL_Texture* background = loadImage(renderer, "assets/background.png");
    SDL_Texture* human_run = loadImage(renderer, "assets/human/run.png");
    SDL_Texture* human_idle = loadImage(renderer, "assets/human/idle.png");
    SDL_Texture* pig_run = loadImage(renderer, "assets/pig/run.png");

    // Load level's platform
    std::vector<platform> levelPlaform = loadLevel("level.dat");

    // Init entity
    //Entity entities[3];

    Human player;
    player.init(human_idle, 8, 37, 29, 37*3, 29*3, 100, 100); 

    std::vector<Pig> pigs;

    // Pig newPig, newPig2;
    // newPig.init(pig_run, 19, 22, 19*4, 22*4, 100, 100);
    // newPig2.init(pig_run, 19, 22, 19*4, 22*4, 1820, 100);
    // pigs.push_back(newPig);
    // pigs.push_back(newPig2);

    // Declare variables
    int _MAIN_CHARACTER_VELOCITY_ = 20;
    int _MAIN_CHARACTER_GRAVITY_ = 3; 
    int zero = 0;
    int frame = 0;

    // Declare variables for pig spawn timer
    Uint32 lastTimeSpawn = 0;
    Uint32 spawnTime = 0;
    Uint32 _SPAWN_TIME_MIN_= 150;//ms
    Uint32 _SPAWN_TIME_MAX_= 1500;//ms
    

    // START GAME
    

    // Play music
    Mix_PlayMusic(music, -1);
    // Declare running variable
    bool running = true;
    SDL_Event event;
    // Main loop
    while (running) 
    {
        frameDelayy();
        SDL_RenderClear(renderer);
        renderBackground(background);
        // Mix_ResumeMusic();

        // if (spriteDelayCheck()) {
        //     if (frame < 7) {
        //         frame++;
        //     }
        //     else {
        //         frame = 0;
        //     }
        //     entities[1].setFrame(frame);
        // }
        // std::cout << collisionCheck(entities[1], levelPlaform[0]);

        player.updateSprite();
        render(player);


        // Pig spawns
        Uint32 now = SDL_GetTicks();
        if (now - lastTimeSpawn > spawnTime) {
            // After spawnTime ms
            // Spawn a new pig
            Pig newPig;
            newPig.init(pig_run, 6, 19, 22, 19*4, 22*4, 100, 100);
            pigs.push_back(newPig);
            // Reset timer
            lastTimeSpawn = now;
            spawnTime = rand() % _SPAWN_TIME_MAX_ + _SPAWN_TIME_MIN_;
        }
        
        unsigned int numberOfPigs = pigs.size();
        // std::cout << "Pig rendered: ";
        for (unsigned int i = 0; i < numberOfPigs; i++) {
            // Delete pig when it's out of screen
            if (pigs[i].getCurentFrame().y > 1080) pigs.erase(pigs.begin() + i); // pig.move(0, -950);
            // Check collision with platform to set falling state
            if (!platformCollisionCheck(pigs[i], levelPlaform, 0, _MAIN_CHARACTER_GRAVITY_)) {
                pigs[i].setFallingState(true);
            }
            else {
                pigs[i].setFallingState(false);
            }
            render(pigs[i]);
            pigs[i].updateLocation();
            // std::cout << i << ", ";
        }
        // std::cout << "\n";
        
        // render(pigs[0]);
        // pigs[0].updateLocation();
        
        // Falling

        // if (!platformCollisionCheck(pigs[0], levelPlaform, 0, _MAIN_CHARACTER_GRAVITY_)) {
        //     pigs[0].move(0, _MAIN_CHARACTER_GRAVITY_);
        //     pigs[0].setFallingState(true);
        // }
        // else {
        //     pigs[0].setFallingState(false);
        // }
        // else {
        //     pigs[0].setVelocityY(0);
        // }

        if (!platformCollisionCheck(player, levelPlaform, 0, _MAIN_CHARACTER_GRAVITY_)) {
            player.move(0, _MAIN_CHARACTER_GRAVITY_);
            player.setFallingState(true);
        }
        else {
            player.setFallingState(false);
        }
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                {
                    player.setTexture(human_run, 37, 29);
                    // std::cerr << "Key pressed: " << event.key.keysym.sym << std::endl;
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            running = false;
                            break;
                        case SDLK_a:
                            player.setStatus(_STATUS_WALK_LEFT_);
                            player.move(-_MAIN_CHARACTER_VELOCITY_, 0);
                            break;
                        case SDLK_d:
                            player.setStatus(_STATUS_WALK_RIGHT_);
                            player.move(_MAIN_CHARACTER_VELOCITY_, 0);
                            break;
                        case SDLK_w:
                            // if (!player.isFalling()) {
                            //     player.move(0, -10);
                            // }
                            if (!player.isFalling()){
                                player.jump();
                            }
                            break;
                        case SDLK_s:
                            player.move(0, _MAIN_CHARACTER_VELOCITY_);
                            break;
                    }                                                                                               
                }
            }
        }
        //std::cout << "X: " << dest.x << " Y: " << dest.y << std::endl;
        SDL_RenderPresent(renderer);
    }
    SDL_Quit();

    return 0;
}


void render(Entity &p_entity) {
    SDL_Rect src = p_entity.getSrc();

    SDL_Rect dest = p_entity.getCurentFrame();
    

    SDL_RenderCopy(renderer, p_entity.getTexture(), &src, &dest);
}

void renderBackground(SDL_Texture* p_texture) {
    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = _SCREEN_WIDTH_;
    src.h = _SCREEN_HEIGHT_;

    SDL_Rect dest;
    dest.x = 0;
    dest.y = 0;
    dest.w = _SCREEN_WIDTH_;
    dest.h = _SCREEN_HEIGHT_;

    SDL_RenderCopy(renderer, p_texture, &src, &dest);
}