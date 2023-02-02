#include <SDL2/SDL.h>

class platform {
    public:
        platform(int p_top, int p_bottom, int p_left, int p_right):
            top(p_top),
            bottom(p_bottom),
            left(p_left),
            right(p_right) {};

        platform():
            top(0),
            bottom(0),
            left(0),
            right(0) {};

        int top;
        int bottom;
        int left;
        int right;

        SDL_Rect getBoudingBox();
};