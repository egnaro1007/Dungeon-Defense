#include "../include/game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
//#include "../include/define.h"
#include "../include/entity.hpp"
// #include "../include/platform.hpp" // Đã bao gồm trong level.hpp
#include "../include/level.hpp"
#include "../include/text.hpp"
#include "../include/bar.hpp"

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
bool collisionCheckEtoE(Entity &p_entity1, Entity &p_entity2);
bool platformCollisionCheck(Entity &p_entity, std::vector<platform> &p_platform, int nextMoveDistanceX, int nextMoveDistanceY);
bool attackCheck(Entity &p_attacker, Entity &p_opponent, int attackRangeX, int attackRangeY, int direction);


Game::Game() {
    // Init SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "Init SDL failed: " << SDL_GetError() << "\n";
        SDL_Quit();
    }
    TTF_Init();
    
    window = SDL_CreateWindow("Dungeon Defense", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _SCREEN_WIDTH_, _SCREEN_HEIGHT_, SDL_WINDOW_SHOWN);
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

    SDL_RenderClear(renderer);
    
    // Load music
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    Mix_Music* music = Mix_LoadMUS("assets/background.mp3");
    // Load texture
    SDL_Texture* background = loadImage(renderer, "assets/background.png");
    SDL_Texture* human_run = loadImage(renderer, "assets/human/run.png");
    SDL_Texture* human_idle = loadImage(renderer, "assets/human/idle.png");
    SDL_Texture* human_attack = loadImage(renderer, "assets/human/attack.png");
    SDL_Texture* pig_run = loadImage(renderer, "assets/pig/run.png");
    SDL_Texture* heart = loadImage(renderer, "assets/status/heart.png");
    SDL_Texture* door = loadImage(renderer, "assets/status/door.png");

    // Load level's platform
    std::vector<platform> levelPlaform = loadLevel("level.dat");

    // Init entity
    //Entity entities[3];

    Human player;
    player.init(human_idle, 8, 78, 58, 37*3, 29*3, 960, 100); 

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

    // UI
    TextBox scoreTextBox("0", "font/slkscrb.ttf", 32, 255, 255, 255, 255, 960, 65);
    bar home(1150, 1010 , door, 48, 56, 1, 10);
    bar healthBar(550, 1010 , heart, 18, 14, 4, 3);
    

    /*TEST ZONE*/
    /*TEST ZONE*/


    /* START GAME */
    

    // Declare variables health
    int health = 10;
    home.setValue(health);
    // Play music
    Mix_PlayMusic(music, -1);
    // Declare running variable
    bool running = true;
    SDL_Event event;
    srand(time(NULL));
    // Main loop
    while (running) 
    {
        // Music
        if (bgm) Mix_ResumeMusic();
        else Mix_PauseMusic();

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
            if (rand() % 2 == 0) newPig.init(pig_run, 6, 38, 28, 19*4, 22*4, 100, 100);
            else newPig.init(pig_run, 6, 38, 28, 19*4, 22*4, 1820, 100);
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
            if (pigs[i].getCurentFrame().y > 1080) {
                pigs.erase(pigs.begin() + i);
                health--;
            }
            // Check collision with platform to set falling state
            if (!platformCollisionCheck(pigs[i], levelPlaform, 0, _MAIN_CHARACTER_GRAVITY_)) {
                pigs[i].setFallingState(true);
            }
            else {
                pigs[i].setFallingState(false);
            }

            // Check collision with player
            if (collisionCheckEtoE(player, pigs[i])) {
                player.hurt();
            }


            // Check collision with player's attack
            int playerAttackRangeX = player.getCurentFrame().w;
            int playerAttackRangeY = 0;
            int direction = player.getStatus();
            if (!player.isFalling() && player.attackCooldown() && attackCheck(player, pigs[i], playerAttackRangeX, playerAttackRangeY, direction)) {
                pigs.erase(pigs.begin() + i);
                player.scoreUp();
            }
        }


    // PLAYER

        // player.updateSprite();
        if (player.attackCooldown()) {
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
                            }
                            break;
                    }
                    break;                                                                                             
                }
                case SDL_KEYUP:
                {
                    if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_d) {
                        player.setTexture(human_idle, 78, 58, 3);
                    }
                }
            }
        }
        //std::cout << "X: " << dest.x << " Y: " << dest.y << std::endl;


    // UI UPDATE

        // Score
        scoreTextBox.setText(std::to_string(player.getScore()));
        // Health bar
        home.setValue(health);
        // Player's hp
        healthBar.setValue(player.getHp());


    // RENDER

        // Clear screen
        SDL_RenderClear(renderer);
        // Render background
        renderBackground(background);
        // Render score textbox
        scoreTextBox.render(renderer);
        // Render UI
        home.render(renderer);
        healthBar.render(renderer);
        // Render pigs
        for (unsigned int i = 0; i < numberOfPigs; i++) pigs[i].render(renderer, 6*4, 0, 10*4, 9*4);
            //render(pig);
        // Render player
        // render(player);
        player.render(renderer, 15*3, 14*3, 9*3, 32*3);

        SDL_RenderPresent(renderer);

        
        // Check game over
        if (player.getHp() <= 0) {
            running = false;
        }
        if (health <= 0) {
            running = false;
        }
    }
    returnGameScore(player.getScore());
    return 0;
}

int Game::startMenu(int argc, char** argv) 
{
    SDL_RenderClear(renderer);

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    Mix_Music* music = Mix_LoadMUS("assets/background2.mp3");

    SDL_Texture* menuBackground = loadImage(renderer, "assets/menu/background.png");
    SDL_Texture* menu = loadImage(renderer, "assets/menu/menu.png");
    SDL_Texture* arrow = loadImage(renderer, "assets/menu/arrow.png");
    SDL_Texture* instruction = loadImage(renderer, "assets/menu/instruction.png");

    int selectedOption = 1;
    // 1: start game
    // 2: instructions
    // 3: highscore
    // 4: exit
    const int numberOfOptions = 4;
    // selectedOption from 1 to [numberOfOptions]0
    
    Mix_PlayMusic(music, -1);
    bool running = true;
    bool selected = false;
    SDL_Event event;
    while (running) {
        if (bgm) Mix_ResumeMusic();
        else Mix_PauseMusic();
        SDL_PollEvent(&event);
            switch (event.type) {
                case SDL_QUIT:
                    return 1;
                case SDL_KEYDOWN:
                {
                    switch (event.key.keysym.sym) {
                        case SDLK_a:
                            bgm =  !bgm;
                            break;
                        case SDLK_w:
                            if (selectedOption > 1) {
                                selectedOption--;
                            }
                            break;
                        case SDLK_s:
                            if (selectedOption < numberOfOptions) {
                                selectedOption++;
                            }
                            break;
                        case SDLK_SPACE:
                            selected = true;
                            break;
                        case SDLK_ESCAPE:
                            if (selected == false) return 1;
                            if (selected == true) selected = false;
                            break;
                            
                    }                                                                                        
                }
            }
        

        SDL_RenderClear(renderer);
        renderBackground(menuBackground);
        
        if (selected) {
            switch (selectedOption) {
                case 1:
                    running = false;
                    break;
                case 2:
                    renderBackground(instruction);
                    break;
                case 3:
                    std::cout << "Funtion in development" << std::endl;
                    selected = false;
                    break;
                case 4:
                    return 1;
            }
        }
        else {
            renderBackground(menu);
            SDL_Rect arrowDest = { 935, 375, 58, 43 };
            switch (selectedOption) {
                case 1:
                    arrowDest.y = 375;
                    break;
                case 2 ... 4:
                    arrowDest.y = 375 + 115 + 94*(selectedOption-2);
                    break;
            }
            SDL_RenderCopy(renderer, arrow, NULL, &arrowDest);
        }
        
        SDL_RenderPresent(renderer);
    }
    return 0;
}


int Game::gameOver(int argc, char** argv)
{
    SDL_RenderClear(renderer);
    // Load music
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    // Load texture
    Mix_Music* music = Mix_LoadMUS("assets/background2.mp3");
    SDL_Texture* menuBackground = loadImage(renderer, "assets/menu/background.png");
    SDL_Texture* gameOver = loadImage(renderer, "assets/menu/gameover.png");
    // Load highscore
    std::ifstream getHighscoreFile;
    getHighscoreFile.open("high.score", std::ios::in);
    int highscore;
    getHighscoreFile >> highscore;
    getHighscoreFile.close();
    // Init textbox
    TextBox titleTextBox("", "font/slkscre.ttf", 48, 255, 255, 255, 255, 960, 347);
    TextBox scoreTextBox("", "font/slkscre.ttf", 64, 0, 0, 0, 255, 1133, 530);
    
    // Update textbox
    if (gameScore > highscore) {
        titleTextBox.setText("NEW HIGHSCORE !!!");
        std::ofstream writeHighscoreFile;
        writeHighscoreFile.open("high.score", std::ios::trunc);
        writeHighscoreFile << gameScore;
        writeHighscoreFile.close();
    }
    else {
        titleTextBox.setText("GAME OVER"); 
    }
    scoreTextBox.setText(std::to_string(gameScore));

    Mix_PlayMusic(music, -1);
    bool running = true;
    SDL_Event event;
    while (running)
    {
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                return 1;
            case SDL_KEYDOWN:
            {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        return 0;
                }
            }
        }
        
        SDL_RenderClear(renderer);
        renderBackground(menuBackground);
        renderBackground(gameOver);
        titleTextBox.render(renderer);
        scoreTextBox.render(renderer);
        SDL_RenderPresent(renderer);
    }
    return 0;
}


void Game::returnGameScore(int p_score) {
    gameScore = p_score;
}

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