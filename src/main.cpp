#include "../include/define.h"
#include "../include/entity.hpp"
//#include "../include/platform.hpp" // Đã bao gồm trong level.hpp
#include "../include/level.hpp"

void render(Entity &p_entity);
void renderEverything(Entity entity[]);
bool collisionCheck(Entity &p_entity, platform &p_platform, int &nextMoveDistanceX, int &nextMoveDistanceY);
bool platformCollisionCheck(Entity &p_entity, std::vector<platform> &p_platform, int &nextMoveDistanceX, int &nextMoveDistanceY);

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

    
    int _MAIN_CHARACTER_VELOCITY_ = 20;
    int _MAIN_CHARACTER_GRAVITY_ = 3; 
    int zero = 0;

    int count = 0;

    std::vector<platform> levelPlaform = loadLevel("level.dat");

    while (running) 
    {
        //frameDelayy();

        //std::cout << collisionCheck(entities[1], levelPlaform[0]);

        int i = 0;
        do {
            render(entities[i]);
            i++;
        } while (i < 3);
        
        // Rơi tự do
        // int fallDistance = _MAIN_CHARACTER_GRAVITY_;
        // for (platform p : levelPlaform) {
        //     if (entities[1].getBottom() + fallDistance >= p.top) {
        //         if (entities[1].getRight() > p.left && entities[1].getLeft() < p.right) {
        //             fallDistance = p.top - entities[1].getBottom();
        //         }
        //         std::cout << p.top << " " << p.bottom << " " << p.left << " " << p.right << std::endl;
        //     }
        // }
        // entities[1].move(0, fallDistance);

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
                        entities[1].move(0, -(_MAIN_CHARACTER_VELOCITY_));
                    }

                    if (keys[SDL_SCANCODE_S] && !platformCollisionCheck(entities[1], levelPlaform, zero, _MAIN_CHARACTER_VELOCITY_)) {
                        entities[1].move(0, _MAIN_CHARACTER_VELOCITY_);
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
