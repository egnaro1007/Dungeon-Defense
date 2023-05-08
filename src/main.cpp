#include <SDL2/SDL.h>
#include "../include/game.h"

#include <iostream>
int main(int argc, char** argv)
{
    bool running = true;
    Game game;
    int exitCode = 0;
    while (running) {
        // Run game
        exitCode = game.startMenu(argc, argv);
        if (exitCode == 0) exitCode = game.gameStart(argc, argv);
        if (exitCode == 0) exitCode = game.gameOver(argc, argv);
        if (exitCode != 0) running = false;
    }

// Return exit code
    std::cout << "Exit code: " << exitCode << '\n';
    switch (exitCode)
    {
    case 0:
        std::cout << "Game exited successfully.\n";
        break;
    case 1:
        std::cout << "User exited game.\n";
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

    SDL_Quit();
    return 0;
}