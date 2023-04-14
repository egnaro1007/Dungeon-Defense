#pragma once
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class TextBox {
    private:
        std::string text;
        TTF_Font* font;
        unsigned int size;
        SDL_Color color;

        int posX;
        int posY;
    public:
        TextBox(std::string p_text, std::string font_path, unsigned int p_size, Uint8 r, Uint8 g, Uint8 b, Uint8 a, int p_x, int p_y);

        void render(SDL_Renderer* renderer);

        void setText(std::string p_text);
        void setFont(TTF_Font* p_font);
        void setSize(unsigned int p_size);
        void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
        void setPosition(int p_x, int p_y);

        std::string getText();
};