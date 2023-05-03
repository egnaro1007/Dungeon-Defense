#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/bar.hpp"

bar::bar(int p_x, int p_y, SDL_Texture* p_texture, int p_textureWidth, int p_textureHeight, int p_scale, unsigned int p_maxValue) {
    x = p_x;
    y = p_y;
    
    texture = p_texture;
    textureWidth = p_textureWidth;
    textureHeight = p_textureHeight;
    scale = p_scale;

    value = 0;
    maxValue = p_maxValue;
}

bar::~bar() {}

void bar::render(SDL_Renderer* renderer) {
    if (maxValue == 0) return;    
    if (value == 0) return;
    SDL_Rect src = {0, 0, textureWidth, textureHeight};

    for (unsigned int i = 0; i < value; i++) {
        SDL_Rect dest;
        dest.x = x + (i * textureWidth * scale);
        dest.y = y;
        dest.w = textureWidth * scale;
        dest.h = textureHeight * scale;
        SDL_RenderCopy(renderer, texture, &src, &dest);
    }
}

void bar::setValue(int p_value) {
    if (p_value <= 0) value = 0;
    else if (p_value >= maxValue) value = maxValue;
    else value = p_value;
}

unsigned int bar::getValue() {
    return value;
}