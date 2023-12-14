#include <iostream>
#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 224, SCREEN_HEIGHT = 288;
using namespace std;

//function to put a pixel of a certain color at a certain location on surface
void SetPixel(SDL_Surface* noptrWindowSurface, uint32_t color, int x, int y);

//Will get index index at r and c
size_t GetIndex(SDL_Surface* noptrSurface, int r, int c);

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

    std::cout << "The window pixel format is: " << SDL_GetPixelFormatName(pixelFormat->format);

    uint32_t color = 0xFF0000;

    //draw on the screen
    SetPixel(noptrWindowSurface, color, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);

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

//function to put a pixel of a certain color at a certain location on surface
void SetPixel(SDL_Surface* noptrWindowSurface, uint32_t color, int x, int y){
    //create exclusive access to surface (Good for multithreading)
    SDL_LockSurface(noptrWindowSurface);

    //Get direction all the pixels we need using pointer(noptrWindowSurface is 1d array of all the pixels)
    uint32_t * pixels = (uint32_t*)noptrWindowSurface->pixels;
    //y is row, x is column
    size_t index = GetIndex(noptrWindowSurface, y, x);

    pixels[index] = color;

    SDL_UnlockSurface(noptrWindowSurface);
}

//Will get index index at r and c
size_t GetIndex(SDL_Surface* noptrSurface, int r, int c){
    //convert 1d array to 2d array
    return r * noptrSurface->w + c;
}