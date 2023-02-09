#include <SDL2/SDL.h>

class Entity 
{
public:
    void setTexture(SDL_Texture* p_texture, int p_frame_width, int p_frame_height);
    void setFrame(int p_frame);
    void setSize(int p_width, int p_height);
    void gotoXY(int p_x, int p_y);
    void move(int x_move, int y_move);

    SDL_Texture* getTexture();
    SDL_Rect getSrc();
    SDL_Rect getCurentFrame();

    int getTop();
    int getBottom();
    int getLeft();
    int getRight();
private:
    SDL_Texture* texture;

    int frame;
    int frame_width;
    int frame_height;
    
    SDL_Rect src;
    SDL_Rect curentFrame;
};