#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class bar {
    private:
        int x;
        int y;
        int scale;

        unsigned int value;
        unsigned int maxValue;

        SDL_Texture* texture;
        int textureWidth;
        int textureHeight;
    public:
        bar(int p_x, int p_y, SDL_Texture* p_texture, int p_textureWidth, int p_textureHeight, int p_scale, unsigned int p_maxValue);
        ~bar();
        void render(SDL_Renderer* renderer);
        void setValue(int p_value);
        unsigned int getValue();
};