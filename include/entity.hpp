#include <SDL2/SDL.h>

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

    int getTop();
    int getBottom();
    int getLeft();
    int getRight();
    void move(int x_move, int y_move);
private:
    int x;
    int y;
    int w;
    int h;
    
    SDL_Texture* texture;
    SDL_Rect curentFrame;
};