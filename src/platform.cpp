
#include "../include/platform.hpp"

SDL_Rect platform::getBoudingBox() {
    SDL_Rect box;
    box.x = left;
    box.y = top;
    box.w = right - left;
    box.h = bottom - top;
    return box;
}