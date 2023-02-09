#include "../include/define.h"
#include "../include/entity.hpp"
//#include "../include/platform.hpp" // Đã bao gồm trong level.hpp
#include "../include/level.hpp"

void render(Entity &p_entity);
void renderBackground(SDL_Texture* p_texture);
void renderEverything(Entity entity[]);
bool collisionCheck(Entity &p_entity, platform &p_platform, int &nextMoveDistanceX, int &nextMoveDistanceY);
bool platformCollisionCheck(Entity &p_entity, std::vector<platform> &p_platform, int &nextMoveDistanceX, int &nextMoveDistanceY);

int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) crash(std::cout, "Init", true);

    
    bool running = true;
    SDL_Event event;
    SDL_Event event1;

    SDL_Texture* background = loadImage("assets/background.png");
    SDL_Texture* human_run = loadImage("assets/human/run.png");
    SDL_Texture* human_idle = loadImage("assets/human/idle.png");

    Entity entities[3];

    
    
    entities[1].setTexture(human_idle, 78, 29); 
    entities[1].gotoXY(100, 100); 
    entities[1].setSize(78*3, 25*3);

    //std::cout << entities[1].getSrc().x << " " << entities[1].getSrc().y << " " << entities[1].getSrc().w << " " << entities[1].getSrc().h << std::endl;
    
    int _MAIN_CHARACTER_VELOCITY_ = 20;
    int _MAIN_CHARACTER_GRAVITY_ = 3; 
    int zero = 0;

    int frame = 0;

    std::vector<platform> levelPlaform = loadLevel("level.dat");

    while (running) 
    {
        frameDelayy();
        SDL_RenderClear(renderer);
        renderBackground(background);

        if (animationDelayCheck()) {
            if (frame < 7) {
                frame++;
            }
            else {
                frame = 0;
            }
            entities[1].setFrame(frame);
        }
        //std::cout << collisionCheck(entities[1], levelPlaform[0]);

        render(entities[1]);
        
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
                    {entities[1].setTexture(human_run, 78, 29);
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
                    break;}
                case SDL_KEYUP:
                    entities[1].setTexture(human_idle, 78, 29);
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
    SDL_Rect src = p_entity.getSrc();

    SDL_Rect dest = p_entity.getCurentFrame();
    

    SDL_RenderCopy(renderer, p_entity.getTexture(), &src, &dest);
}

void renderBackground(SDL_Texture* p_texture) {
    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = _SCREEN_WIDTH_;
    src.h = _SCREEN_HEIGHT_;

    SDL_Rect dest;
    dest.x = 0;
    dest.y = 0;
    dest.w = _SCREEN_WIDTH_;
    dest.h = _SCREEN_HEIGHT_;

    SDL_RenderCopy(renderer, p_texture, &src, &dest);
}