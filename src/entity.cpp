#include <SDL2/SDL.h>
#include "../include/entity.hpp"

Entity::Entity(int p_x, int p_y, int p_w, int p_h, SDL_Texture* p_texture) {
    x = p_x;
    y = p_y;
    w = p_w;
    h = p_h;

    texture = p_texture;

    curentFrame.x = x;
    curentFrame.y = y;
    curentFrame.w = w;
    curentFrame.h = h;
}

void Entity::init(int x_init, int y_init, int w_init, int h_init) {
    curentFrame.x = x_init;
    curentFrame.y = y_init;
    curentFrame.w = w_init;
    curentFrame.h = h_init;
}

int Entity::getX() {
    return x;
}
int Entity::getY() {
    return y;
}
int Entity::getW() {
    return w;
}
int Entity::getH() {
    return h;
}
SDL_Texture* Entity::getTexture() {
    return texture;
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

void Entity::move(int x_move, int y_move) {
    curentFrame.x += x_move;
    curentFrame.y += y_move;
}