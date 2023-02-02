#include "define.h"

class Entity 
{
public:
    Entity(int p_x, int p_y, int p_w, int p_h, SDL_Texture* p_texture);

    void init(int x_init, int y_init, int w_init, int h_init);
    int getX();
    int getY();
    int getW();
    int getH();
    SDL_Texture* getTexture();
    SDL_Rect getCurentFrame();

    int getBottom();
    void move(int x_move, int y_move);
private:
    int x;
    int y;
    int w;
    int h;
    
    SDL_Texture* texture;
    SDL_Rect curentFrame;
};

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


int Entity::getBottom() {
    return curentFrame.y + curentFrame.h;
}

void Entity::move(int x_move, int y_move) {
    curentFrame.x += x_move;
    curentFrame.y += y_move;
}