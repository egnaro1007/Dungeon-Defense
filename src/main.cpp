#include <SDL2/SDL.h>
#include "../include/game.h"

#include <iostream>
int main(int argc, char** argv)
{
    bool running = true;
    Game* game = new Game();
    while (running) {
        // Run game
        if (game->startMenu(argc, argv) == 1) {
            running = false;
            break;
        } 
        int exitCode = game->gameStart(argc, argv);

        // Return exit code
        std::cout << "Exit code: " << exitCode << '\n';
        switch (exitCode)
        {
        case 0:
            std::cout << "Game exited successfully.\n";
            break;
        case 2:
            std::cout << "Window could not be created!\n";
            break;
        case 3:
            std::cout << "Renderer could not be created!\n";
            break;
        
        default:
            std::cout << "Unknown error!\n";
            break;
        }
        running = false;
    }
    game->~Game();
    free(game);    

    SDL_Quit();
    return 0;
}