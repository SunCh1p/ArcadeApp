#include "screen.h"
#include "Vec2D.h"
#include "Line2D.h"
#include "Star2D.h"
#include <cmath>
#include <SDL2/SDL.h>
#include <cassert>
Screen::Screen(): mWidth(0), mHeight(0), moptrWindow(nullptr), mnoptrWindowSurface(nullptr){}
Screen::~Screen(){
    if(moptrWindow){
        SDL_DestroyWindow(moptrWindow);
        moptrWindow = nullptr;
    }
    SDL_Quit();
}

SDL_Window* Screen::Init(uint32_t w, uint32_t h, uint32_t mag){
    if(SDL_Init(SDL_INIT_VIDEO)){
        std::cout << "Error SDL_Init Failed" << std::endl;
        return nullptr;
    }
    mWidth = w;
    mHeight = h;

    moptrWindow = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWidth * mag, mHeight* mag, 0);
    if(moptrWindow){
        mnoptrWindowSurface = SDL_GetWindowSurface(moptrWindow);
        SDL_PixelFormat* pixelFormat = mnoptrWindowSurface->format;
        Color::InitColorFormat(pixelFormat);
        mClearColor = Color::Black();
        mBackBuffer.Init(pixelFormat->format, mWidth, mHeight);
        mBackBuffer.Clear(mClearColor);
    }
    return moptrWindow;
}

void Screen::SwapScreen(){
    assert(moptrWindow);
    if(moptrWindow){
        ClearScreen();
        SDL_BlitScaled(mBackBuffer.GetSurface(), nullptr, mnoptrWindowSurface, nullptr);
        SDL_UpdateWindowSurface(moptrWindow);
        mBackBuffer.Clear(mClearColor);
    }
}
void Screen::Draw(int x, int y, const Color& color){
    assert(moptrWindow);
    if(moptrWindow){
        mBackBuffer.SetPixel(color, x, y); 
    }
}
void Screen::Draw(const Vec2D& point, const Color& color){
    assert(moptrWindow);
    if(moptrWindow){
        mBackBuffer.SetPixel(color, point.GetX(), point.GetY()); 
    }
}

void Screen::Draw(const Line2D& line, const Color& color){
    assert(moptrWindow);
    if(moptrWindow){
        int dx, dy;
        int x0 = roundf(line.GetP0().GetX());
        int y0 = roundf(line.GetP0().GetY());
        int x1 = roundf(line.GetP1().GetX());
        int y1 = roundf(line.GetP1().GetY());

        dx = x1-x0;
        dy = y1-y0;
        signed const char ix((dx > 0) - (dx < 0)); //evaluate to 1 or -1
        signed const char iy((dy > 0) - (dy < 0));

        dx = abs(dx)*2;
        dy = abs(dy)*2;

        Draw(x0, y0, color);
        if(dx >= dy){
            //go along in the x
            int d = dy - dx/2;
            while(x0 != x1){
                if(d >= 0){
                    d -= dx;
                    y0 += iy;
                }
                d += dy;
                x0 += ix;
                Draw(x0, y0, color);
            }
        }
        else{
            //go along in y
            int d = dx - dy/2;
            while(y0 != y1){
                if(d >= 0){
                    d -= dy;
                    x0 += ix;
                }
                d += dx;
                y0 += iy;
                Draw(x0, y0, color);
            }
        }
    }
}

void Screen::Draw(const Star2D& star, const Color& color){
    if(star.GetDiameter() == 0){
        return;
    }
    Line2D line1(star.GetP1(), star.GetP3());
    Line2D line2(star.GetP3(), star.GetP5());
    Line2D line3(star.GetP5(), star.GetP2());
    Line2D line4(star.GetP2(), star.GetP4());
    Line2D line5(star.GetP4(), star.GetP1());
    Draw(star.GetCenter(), Color::Red());
    Draw(line1, Color::White());
    Draw(line2, Color::White());
    Draw(line3, Color::White());
    Draw(line4, Color::White());
    Draw(line5, Color::White());

}

void Screen::ClearScreen(){
    assert(moptrWindow);
    if(moptrWindow){
        SDL_FillRect(mnoptrWindowSurface, nullptr, mClearColor.GetPixelColor());
    }
}