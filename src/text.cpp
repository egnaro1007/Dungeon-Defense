#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../include/text.hpp"
#include <iostream>

TextBox::TextBox(std::string p_text, std::string font_path, unsigned int p_size, Uint8 r, Uint8 g, Uint8 b, Uint8 a, int p_x = 0, int p_y = 0) {
    text = p_text;
    font = TTF_OpenFont(font_path.c_str(), p_size);
    if (font == NULL) std::cout << "Unable to load font " << font_path << "!\nSDL_ttf Error: "
     << TTF_GetError() << "\n";
    size = p_size;
    color = {r, g, b, a};
    posX = p_x;
    posY = p_y;
}

void TextBox::render(SDL_Renderer* renderer) {
    SDL_Surface* surfaceMessage = //TTF_RenderText_Solid(font, text.c_str(), color);
        TTF_RenderText_Blended(font, text.c_str(), color);
    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_FreeSurface(surfaceMessage);

    SDL_Rect dest;
    SDL_QueryTexture(message, NULL, NULL, &dest.w, &dest.h);
    dest.x = posX - dest.w / 2;
    dest.y = posY - dest.h / 2;
    SDL_RenderCopy(renderer, message, NULL, &dest);

    SDL_DestroyTexture(message);
}


void TextBox::setText(std::string p_text) {
    text = p_text;
}

void TextBox::setFont(TTF_Font* p_font) {
    font = p_font;
}

void TextBox::setSize(unsigned int p_size) {
    size = p_size;
}

void TextBox::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    color = {r, g, b, a};
}

void TextBox::setPosition(int p_x, int p_y) {
    // This position is center alignment
    posX = p_x;
    posY = p_y;
}

std::string TextBox::getText() {
    return text;
}