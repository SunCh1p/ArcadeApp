#include <iostream>
#include <SDL2/SDL.h>
#include "color.h"
#include "ScreenBuffer.h"

const int SCREEN_WIDTH = 224, SCREEN_HEIGHT = 288;
using namespace std;

int main(int argc, char* argv[]){
    //initialize sdl video
    if(SDL_Init(SDL_INIT_VIDEO)){
        std::cout << "Error SDL_Init Failed" << std::endl;
        return 1;
    }

    SDL_Window* optrWindow = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    if(optrWindow == nullptr){
        std::cout << "Could not reate window, get error: " << SDL_GetError() << std::endl;
        return 1;
    }

    //create SDL surface - 2D array of pixels
    SDL_Surface* noptrWindowSurface =SDL_GetWindowSurface(optrWindow);


    //pixel formats are how the system interprets values we give it.
    //pixel format may vary depending on system
    SDL_PixelFormat* pixelFormat = noptrWindowSurface->format;
    Color::InitColorFormat(pixelFormat);
    ScreenBuffer screenBuffer;
    screenBuffer.Init(pixelFormat->format, noptrWindowSurface->w, noptrWindowSurface->h);
    screenBuffer.SetPixel(Color::Blue(), SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    SDL_BlitSurface(screenBuffer.GetSurface(), nullptr, noptrWindowSurface, nullptr);


    //display whats drawn on the surface;
    SDL_UpdateWindowSurface(optrWindow);

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

    SDL_DestroyWindow(optrWindow);
    SDL_Quit();
    return 0;
}