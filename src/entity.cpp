#include <SDL2/SDL.h>
#include "../include/entity.hpp"

#include <iostream>

enum _STATUS_ {
    _STATUS_PREVIOUS_ = 0,
    _STATUS_WALK_LEFT_ = 3,
    _STATUS_WALK_RIGHT_ = 4,
    _STATUS_ATTACK_LEFT_ = 5,
    _STATUS_ATTACK_RIGHT_ = 6
};

const int _ANIMATION_PER_SECOND_ = 10;

bool spriteDelayCheck();

void Entity::init (SDL_Texture* p_texture, int p_numberOfFrame, int p_frame_width, int p_frame_height, int p_width, int p_height, int p_x, int p_y) {
    setTexture(p_texture, p_frame_width, p_frame_height, p_numberOfFrame);
    setFrame(0);
    setSize(p_width, p_height);
    gotoXY(p_x, p_y);
    if (p_x < 1920 / 2) {
        status = _STATUS_WALK_RIGHT_;
        prevStatus = _STATUS_WALK_RIGHT_;
    }
    else {
        status = _STATUS_WALK_LEFT_;
        prevStatus = _STATUS_WALK_LEFT_;
    }
}

void Entity::setTexture(SDL_Texture* p_texture, int p_frame_width, int p_frame_height, int p_numberOfFrame) {
    texture = p_texture;
    frame_width = p_frame_width;
    frame_height = p_frame_height;
    numberOfFrame = p_numberOfFrame;
}

void Entity::setFrame(int p_frame) {
    frame = p_frame;
    src.x = frame * frame_width;
    // src.y = 0;
    if (status == _STATUS_WALK_LEFT_ || status == _STATUS_ATTACK_LEFT_) src.y = frame_height * 0;
    else if (status == _STATUS_WALK_RIGHT_ || status == _STATUS_ATTACK_RIGHT_) src.y = frame_height * 1;
    else src.y = frame_height * 2;
    src.w = frame_width;
    src.h = frame_height;
}

void Entity::setSize(int p_width, int p_height) {
    curentFrame.w = p_width;
    curentFrame.h = p_height;
}
void Entity::gotoXY(int p_x, int p_y) {
    curentFrame.x = p_x;
    curentFrame.y = p_y;
}
void Entity::move(int x_move, int y_move) {
    curentFrame.x += x_move;
    curentFrame.y += y_move;

    // if (curentFrame.y > 1080) curentFrame.y -= 951;
}
void Entity::setStatus(unsigned int p_status) {
    if (p_status == status) return;
    if (p_status == _STATUS_PREVIOUS_) {
        status = prevStatus;
    }
    else {
        prevStatus = status;
        status = p_status;
    }
}

int _VELOCITY_ = 10;
void Entity::runLeft() {
    setStatus(_STATUS_WALK_LEFT_);
    move(-_VELOCITY_, 0);
}
void Entity::runRight() {
    setStatus(_STATUS_WALK_RIGHT_);
    move(_VELOCITY_, 0);
}
void Entity::setFallingState(bool state) {
    falling = state;
}



SDL_Texture* Entity::getTexture() {
    return texture;
}
SDL_Rect Entity::getSrc() {
    return src;
}
SDL_Rect Entity::getCurentFrame() {
    return curentFrame;
}

int Entity::getTop() {
    return curentFrame.y;
}
int Entity::getLeft() {
    return curentFrame.x;
}
int Entity::getBottom() {
    return curentFrame.y + curentFrame.h;
}
int Entity::getRight() {
    return curentFrame.x + curentFrame.w;
}
bool Entity::isFalling() {
    return falling;
}

unsigned int Entity::getStatus() {
    return status;
}

void Entity::updateSprite() {
    const int spriteTime = 1000 / _ANIMATION_PER_SECOND_;
    Uint32 now = SDL_GetTicks();
    // Check time, if time is not enough, don't update sprite
    if (now - lastTimeSprite < spriteTime) return;
    // Update sprite                                                                        
    if (frame < numberOfFrame - 1) { 
        frame++;
    }
    else {
        frame = 0;
    }
    setFrame(frame);
    lastTimeSprite = now;
}

void Entity::render(SDL_Renderer* renderer, int topCalibration, int bottomCalibration, int leftCalibration, int rightCalibration) {

    SDL_Rect src = getSrc();

    SDL_Rect dest = getCurentFrame();
    dest.x -= leftCalibration;
    dest.y -= topCalibration;
    dest.w += leftCalibration + rightCalibration;
    dest.h += topCalibration + bottomCalibration;

    SDL_RenderCopy(renderer, getTexture(), &src, &dest);
}



void Human::jump() {
    setFallingState(true);
    move(0, -300);
}
bool Human::attackCooldown() {
    Uint32 cooldownTime = 300;//ms
    Uint32 now = SDL_GetTicks();
    if (now - lastTimeAttack < cooldownTime) return true;
    return false;
}
void Human::attack(){
    if (attackCooldown()) return;
    if (hurtCooldown()) return;
    lastTimeAttack = SDL_GetTicks();
}
void Human::scoreUp() {
    score++;
}
unsigned int Human::getScore() {
    return score;
}
void Human::hurt() {
    if (hurtCooldown()) return;
    lastTimeHurt = SDL_GetTicks();
    hp--;
    std::cout << "Ouch!" << std::endl;
}
unsigned int Human::getHp() {
    return hp;
}
bool Human::hurtCooldown() {
    Uint32 cooldownTime = 500;//ms
    Uint32 now = SDL_GetTicks();
    if (now - lastTimeHurt < cooldownTime) return true;
    return false;
}


void Pig::updateLocation() {
    // updateSprite();
    if (!isFalling()) {
        switch (getStatus()){
        case _STATUS_WALK_RIGHT_: 
            move(2, 0);
            if (getRight() > 1920 - 130) {
                setStatus(_STATUS_WALK_LEFT_);
            }
            break;
        case _STATUS_WALK_LEFT_:
            move(-2, 0);
            if (getLeft() < 130) {
                setStatus(_STATUS_WALK_RIGHT_);
            }
            break;
        default:
            return;
        };
    }
    else {
        move(0, 2);
    }
}