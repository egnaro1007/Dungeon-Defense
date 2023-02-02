#ifndef DEBUG_HPP
#define DEBUG_HPP
#include <iostream>
#include <SDL2/SDL.h>

// Chỉ đơn giản là để log
void crash(std::ostream& os, const std::string &msg, bool fatal) {
        os << "Your " << msg << " Sucks!\n";
        os << "Error: " << SDL_GetError() << std::endl;
        if (fatal) {
            std::cout << "Crash !!!!!!!!!!!!!!!!!!!";
            SDL_Quit();
            exit(1);
        }
}

// Chờ nhấn nút để đóng
void wait() {
    SDL_Event keyPress;
    while(true) {
        if (SDL_WaitEvent(&keyPress) != 0 && (keyPress.type == SDL_KEYDOWN || keyPress.type == SDL_QUIT))
            return;
        
        SDL_Delay(100);
    }
}
#endif