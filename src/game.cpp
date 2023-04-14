#include "../include/game.h"
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

enum _STATUS_ {
    _STATUS_PREVIOUS_ = 0,
    _STATUS_WALK_LEFT_ = 3,
    _STATUS_WALK_RIGHT_ = 4,
    _STATUS_ATTACK_LEFT_ = 5,
    _STATUS_ATTACK_RIGHT_ = 6
};

// Utils.cpp
SDL_Texture* loadImage(SDL_Renderer* renderer, const char* file);
void frameDelayy();
bool spriteDelayCheck();

// void renderEverything(Entity entity[]);
// bool collisionCheck(Entity &p_entity, platform &p_platform, int &nextMoveDistanceX, int &nextMoveDistanceY);
bool platformCollisionCheck(Entity &p_entity, std::vector<platform> &p_platform, int nextMoveDistanceX, int nextMoveDistanceY);
bool attackCheck(Entity &p_attacker, Entity &p_opponent, int attackRangeX, int attackRangeY, int direction);


Game::Game() {
    // Init SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "Init SDL failed: " << SDL_GetError() << "\n";
        SDL_Quit();
    }
    
    window = SDL_CreateWindow("Test window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _SCREEN_WIDTH_, _SCREEN_HEIGHT_, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED /*|| SDL_RENDERER_PRESENTVSYNC*/);
}

Game::~Game() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}




int Game::gameStart(int argc, char** argv)
{
    if (window == NULL) return 2;
    if (renderer == NULL) return 3;
    
// Init SDL here

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    
    // Load music
    Mix_Music* music = Mix_LoadMUS("assets/background.mp3");
    // Load texture
    SDL_Texture* background = loadImage(renderer, "assets/background.png");
    SDL_Texture* human_run = loadImage(renderer, "assets/human/run.png");
    SDL_Texture* human_idle = loadImage(renderer, "assets/human/idle.png");
    SDL_Texture* human_attack = loadImage(renderer, "assets/human/attack.png");
    SDL_Texture* pig_run = loadImage(renderer, "assets/pig/run.png");

    // Load level's platform
    std::vector<platform> levelPlaform = loadLevel("level.dat");

    // Init entity
    //Entity entities[3];

    Human player;
    player.init(human_idle, 8, 78, 58, 37*3, 29*3, 100, 100); 

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
    

    /* START GAME */
    

    // Play music
    Mix_PlayMusic(music, -1);
    // Declare running variable
    bool running = true;
    SDL_Event event;
    srand(time(NULL));
    // Main loop
    while (running) 
    {
        // frameDelayy();
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
       

    // PIG

        // Pig spawns
        Uint32 now = SDL_GetTicks();
        if (now - lastTimeSpawn > spawnTime) {
            // After spawnTime ms
            // Spawn a new pig
            Pig newPig;
            if (rand() % 2 == 0) newPig.init(pig_run, 6, 19, 22, 19*4, 22*4, 100, 100);
            else newPig.init(pig_run, 6, 19, 22, 19*4, 22*4, 1820, 100);
            pigs.push_back(newPig);
            // Reset timer
            lastTimeSpawn = now;
            spawnTime = rand() % _SPAWN_TIME_MAX_ + _SPAWN_TIME_MIN_;
        }
        
        unsigned int numberOfPigs = pigs.size();
        for (unsigned int i = 0; i < numberOfPigs; i++) {
            // Move pig
            pigs[i].updateLocation();
            // Delete pig when it's out of screen
            if (pigs[i].getCurentFrame().y > 1080) pigs.erase(pigs.begin() + i); // pig.move(0, -950);
            // Check collision with platform to set falling state
            if (!platformCollisionCheck(pigs[i], levelPlaform, 0, _MAIN_CHARACTER_GRAVITY_)) {
                pigs[i].setFallingState(true);
            }
            else {
                pigs[i].setFallingState(false);
            }


            // Check collision with player's attack
            int playerAttackRangeX = player.getCurentFrame().w;
            int playerAttackRangeY = 0;
            int direction = player.getStatus();
            if (!player.isFalling() && player.attackCooldown() && attackCheck(player, pigs[i], playerAttackRangeX, playerAttackRangeY, direction)) {
                pigs.erase(pigs.begin() + i);
            }
        }

        
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

    // PLAYER

        // player.updateSprite();
        if (player.attackCooldown()) {
        //     // player.setSize(37*3*2, 29*3*2);
        // player.setTexture(human_attack, 78, 58, 3);
        //     // SDL_Rect position = player.getCurentFrame();
        //     // position.x -= 37*3;
        //     // position.w *= 2;
        //     // position.h *= 2;
        //     // SDL_RenderCopy(renderer, human_attack, NULL, &position);
            if (player.getStatus() == _STATUS_WALK_LEFT_) {
                player.setStatus(_STATUS_ATTACK_LEFT_);
                player.setTexture(human_attack, 78, 58, 3);
            }
            else if (player.getStatus() == _STATUS_WALK_RIGHT_) {
                player.setStatus(_STATUS_ATTACK_RIGHT_);
                player.setTexture(human_attack, 78, 58, 3);
            }
        }
        else {
        //     // player.setSize(37*3, 29*3);
        // player.setTexture(human_idle, 78, 58, 11);
            if (player.getStatus() == _STATUS_ATTACK_LEFT_) {
                player.setStatus(_STATUS_WALK_LEFT_);
                player.setTexture(human_idle, 78, 58, 3);
            }
            else if (player.getStatus() == _STATUS_ATTACK_RIGHT_) {
                player.setStatus(_STATUS_WALK_RIGHT_);
                player.setTexture(human_idle, 78, 58, 3);
            }
        }

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
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            running = false;
                            break;
                        case SDLK_a:
                            // player.runLeft();
                            player.setStatus(_STATUS_WALK_LEFT_);
                            player.move(-_MAIN_CHARACTER_VELOCITY_, 0);
                            player.setTexture(human_run, 78, 58, 8);
                            break;
                        case SDLK_d:
                            player.runRight();
                            player.setTexture(human_run, 78, 58, 8);
                            break;
                        case SDLK_w:
                            // if (!player.isFalling()) {
                            //     player.move(0, -10);
                            // }
                            if (!player.isFalling()){
                                player.jump();
                            }
                            break;
                        case SDLK_SPACE:
                        if (event.key.repeat == 0){
                            player.attack();
                            break;
                        }
                    }
                    break;                                                                                             
                }
                case SDL_KEYUP:
                {
                    player.setTexture(human_idle, 78, 58, 11);
                    break;
                }
            }
        }
        //std::cout << "X: " << dest.x << " Y: " << dest.y << std::endl;


    // RENDER

        // Clear screen
        SDL_RenderClear(renderer);
        // Render background
        renderBackground(background);
        // Render pigs
        for (unsigned int i = 0; i < numberOfPigs; i++) pigs[i].render(renderer);
            //render(pig);
        // Render player
        // render(player);
        player.render(renderer);

        SDL_RenderPresent(renderer);
    }
    return 0;
}

// void Game::render(Entity &p_entity) {
//     SDL_Rect src = p_entity.getSrc();

//     SDL_Rect dest = p_entity.getCurentFrame();
//     dest.x -= 9*3;
//     dest.y -= 15*3;
//     dest.w += 41*3;
//     dest.h += 29*3;

//     SDL_RenderCopy(renderer, p_entity.getTexture(), &src, &dest);
// }

void Game::renderBackground(SDL_Texture* p_texture) {
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