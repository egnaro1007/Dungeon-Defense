#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int _FPS_ = 240;
const int _ANIMATION_PER_SECOND_ = 10;
const int _MAIN_CHARACTER_VELOCITY_ = 20; // pixel per second

// Load texture from image file
SDL_Texture* loadImage(const char* file);
// Lock FPS
void frameDelayy();
// Delay between sprite animation
bool spriteDelayCheck();


SDL_Texture* loadImage(SDL_Renderer* renderer, const char* file)
{
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, file);
    if (texture == NULL) std::cout << "Unable to load image " << file << "!\nSDL_image Error: " << IMG_GetError() << "\n";
    return texture;
}


const int frameDelay = 1000 / _FPS_;
const Uint32 FrameStart = SDL_GetTicks();
const Uint32 frameTime = SDL_GetTicks() - FrameStart;
void frameDelayy() {
    if (frameDelay > frameTime) {
        SDL_Delay(frameDelay - frameTime);
    }
}


const int animationDelay = 1000 / _ANIMATION_PER_SECOND_;
Uint32 lastTimeAnimation = 0;
bool spriteDelayCheck() {
   Uint32 now = SDL_GetTicks();
    if (now - lastTimeAnimation > animationDelay) {
        lastTimeAnimation = now;
        return true;
    }
    return false;
}
