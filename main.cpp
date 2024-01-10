#include <iostream>
#include <SDL2/SDL.h>
#include "color.h"
#include "Screen.h"
#include "Line2D.h"
#include "Star2D.h"

const int SCREEN_WIDTH = 224, SCREEN_HEIGHT = 288;
const int MAGNIFICATION = 3;
using namespace std;

int main(int argc, char* argv[]){
    Screen theScreen;
    theScreen.Init(SCREEN_WIDTH, SCREEN_HEIGHT, 2);
    Star2D star(Vec2D(100,100), 60);
    theScreen.Draw(star, Color::White());
    theScreen.SwapScreen();


    SDL_Event sdlEvent;
    bool running = true;
    while(running){
        while(SDL_PollEvent(&sdlEvent)){
            switch(sdlEvent.type){
                case SDL_QUIT:
                running = false;
                break;
            }
        }
        theScreen.Draw(star, Color::White());
        theScreen.SwapScreen();
        star.Rotate(-0.0001);
    }

    return 0;
}