#include "define.h"
#include "entity.hpp"
#include "level.hpp"

#include "debug.hpp"

void render(Entity &p_entity);
void renderEverything(Entity entity[]);

int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) crash(std::cout, "Init", true);

    
    bool running = true;
    SDL_Event event;
    SDL_Event event1;

    SDL_Texture* background = NULL;
    SDL_Texture* character = NULL;
    background = loadImage("assets/background.png");
    character = loadImage("assets/character.png");

    Entity entities[3] = {
        Entity (0, 0, 1920, 1080, background), 
        Entity (0, 0, 77, 25, character), 
        Entity (0, 0, 37, 25, character)};

    
    entities[0].init(0, 0, _SCREEN_WIDTH_, _SCREEN_HEIGHT_);
    entities[1].init(100, 100, 37*3, 25*3);
    entities[2].init(200, 200, 37, 25);

    
    const int _MAIN_CHARACTER_VELOCITY_ = 20;
    const int _MAIN_CHARACTER_GRAVITY_ = 3; 

    int count = 0;

    std::vector<plaform> levelPlaform = loadLevel(_FiLE_PATH_);

    while (running) 
    {
        //frameDelayy();

        int i = 0;
        do {
            render(entities[i]);
            i++;
        } while (i < 3);
        
        // Rơi tự do
        int fallDistance = _MAIN_CHARACTER_GRAVITY_;
        for (plaform p : levelPlaform) {
            // std::cout<<entities[1].getBottom() <<std::endl;
            // std::cout<<fallDistance <<std::endl;
            // std::cout << std::endl;
            if (entities[1].getBottom() + fallDistance >= p.top) {
                fallDistance = p.top - entities[1].getBottom();//std::cout << p.top << std::endl;
            }
        }


        entities[1].move(0, fallDistance);

std::cout << "y: " << entities[1].getCurentFrame().y << std::endl;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    SDL_PumpEvents();
                    const Uint8 *keys = SDL_GetKeyboardState(NULL);
                    if (keys[SDL_SCANCODE_ESCAPE]) {
                        running = false;
                    }


                    if (keys[SDL_SCANCODE_W]) {
                        entities[1].move(0, -(_MAIN_CHARACTER_VELOCITY_ * 10));
                    }

                    

                    if (keys[SDL_SCANCODE_A]) {
                        entities[1].move(-_MAIN_CHARACTER_VELOCITY_, 0);
                    }
                    if (keys[SDL_SCANCODE_D]) {
                        entities[1].move(_MAIN_CHARACTER_VELOCITY_, 0);
                    }
                    break;
            }
        }
        //std::cout << "X: " << dest.x << " Y: " << dest.y << std::endl;
        SDL_RenderPresent(renderer);
    }
    SDL_Quit();

    return 0;
}


void render(Entity &p_entity) {
    SDL_Rect src;
    src.x = p_entity.getX();
    src.y = p_entity.getY();
    src.w = p_entity.getW();
    src.h = p_entity.getH();

    SDL_Rect dest = p_entity.getCurentFrame();
    

    SDL_RenderCopy(renderer, p_entity.getTexture(), &src, &dest);
}
