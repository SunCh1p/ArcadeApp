#include <iostream>
#include <SDL2/SDL.h>
#include "color.h"
#include "Screen.h"
#include "Line2D.h"

const int SCREEN_WIDTH = 224, SCREEN_HEIGHT = 288;
const int MAGNIFICATION = 3;
using namespace std;

int main(int argc, char* argv[]){
    Screen theScreen;
    theScreen.Init(SCREEN_WIDTH, SCREEN_HEIGHT, 2);
    Line2D line = {Vec2D(0,0), Vec2D(SCREEN_WIDTH, SCREEN_HEIGHT)};
    theScreen.Draw(line, Color::White());
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
    }

    return 0;
}