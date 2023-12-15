#include "ScreenBuffer.h"
#include <iostream>
#include <SDL2/SDL.h>

ScreenBuffer::ScreenBuffer(): mSurface(nullptr){}
ScreenBuffer::ScreenBuffer(const ScreenBuffer& screenBuffer){
    mSurface = SDL_CreateRGBSurfaceWithFormat(0, screenBuffer.mSurface->w, screenBuffer.mSurface->h, 0, screenBuffer.mSurface->format->format);
    SDL_BlitSurface(screenBuffer.mSurface, nullptr, mSurface, nullptr);
}

ScreenBuffer::~ScreenBuffer(){
    if(mSurface){
        SDL_FreeSurface(mSurface);
    }
}

ScreenBuffer& ScreenBuffer::operator=(const ScreenBuffer& screenBuffer){
    if(this == &screenBuffer){
        return *this;
    }
    if(mSurface != nullptr){
        SDL_FreeSurface(mSurface);
        mSurface = nullptr;
    }
    if(screenBuffer.mSurface != nullptr){
        mSurface = SDL_CreateRGBSurfaceWithFormat(0, screenBuffer.mSurface->w, screenBuffer.mSurface->h, 0, screenBuffer.mSurface->format->format);
        SDL_BlitSurface(screenBuffer.mSurface, nullptr, mSurface, nullptr);
    }

    return *this;
}

void ScreenBuffer::Init(uint32_t format, uint32_t width, uint32_t h){

}
    

void ScreenBuffer::Clear(const Color& c){

}

//function to put a pixel of a certain color at a certain location on surface
void ScreenBuffer::SetPixel(const Color& color, int x, int y){
    //create exclusive access to surface (Good for multithreading)
    SDL_LockSurface(mSurface);

    //Get direction all the pixels we need using pointer(noptrWindowSurface is 1d array of all the pixels)
    uint32_t * pixels = (uint32_t*)mSurface->pixels;
    //y is row, x is column
    size_t index = GetIndex(y, x);

    pixels[index] = color.GetPixelColor();

    SDL_UnlockSurface(mSurface);
}

//Will get index index at r and c
uint32_t ScreenBuffer::GetIndex(int r, int c){
    //convert 1d array to 2d array
    return r * mSurface->w + c;
}