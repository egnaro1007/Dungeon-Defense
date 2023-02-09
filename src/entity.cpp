#include <SDL2/SDL.h>
#include "../include/entity.hpp"

void Entity::setTexture(SDL_Texture* p_texture, int p_frame_width, int p_frame_height) {
    texture = p_texture;
    frame = 0;
    frame_width = p_frame_width;
    frame_height = p_frame_height;

    setFrame(0);
}

void Entity::setFrame(int p_frame) {
    frame = p_frame;
    src.x = frame * frame_width;
    src.y = 0;
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

    if (curentFrame.y > 1080) curentFrame.y -= 951;
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