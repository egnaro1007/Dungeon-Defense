#pragma once

#include <SDL2/SDL.h>

class Entity 
{
public:
    void init(SDL_Texture* p_texture, int p_numberOfFrame, int p_frame_width, int p_frame_height, int p_width, int p_height, int p_x, int p_y);

    void setTexture(SDL_Texture* p_texture, int p_frame_width, int p_frame_height, int p_numberOfFrame);
    void setFrame(int p_frame);
    void setSize(int p_width, int p_height);
    void gotoXY(int p_x, int p_y);
    void move(int x_move, int y_move);
    void setStatus(unsigned int p_status);

    void runLeft();
    void runRight();
    void setFallingState(bool state);

    SDL_Texture* getTexture();
    SDL_Rect getSrc();
    SDL_Rect getCurentFrame();

    int getTop();
    int getBottom();
    int getLeft();
    int getRight();

    unsigned int getStatus();

    bool atTheLeft();
    bool isFalling();

    
    void updateSprite();
    void render(SDL_Renderer* renderer, int topCalibration, int bottomCalibration, int leftCalibration, int rightCalibration);

    
    // lát nữa bỏ cái này xuống dưới
    unsigned int prevStatus;
private:
    SDL_Texture* texture;

    int frame;
    int numberOfFrame;
    int frame_width;
    int frame_height;
    
    SDL_Rect src;
    SDL_Rect curentFrame;

    bool falling;
    unsigned int status;
    Uint32 lastTimeSprite = 0;
    // 0 - stand 
    // 1 - jump
    // 2 - fall
    // 3 - walk left
    // 4 - walk right
};


class Human : public Entity
{
public:
    void jump();
    void attack();
    bool attackCooldown();
    void update();

    void scoreUp();
    unsigned int getScore();

    void hurt();
    bool hurtCooldown();
    unsigned int getHp();
private:
    unsigned int score = 0;
    unsigned int hp = 3;
    Uint32 lastTimeAttack = 0;
    Uint32 lastTimeHurt = 0;
};


class Pig : public Entity
{
public:
    void updateLocation();
};