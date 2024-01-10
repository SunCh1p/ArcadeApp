#ifndef SHAPES_STARS2D_H_
#define SHAPES_STARS2D_H_

#include "Line2D.h"

class Star2D{
    public: 
        //constructors
        Star2D(): Star2D(Vec2D(0,0), 0){};
        Star2D(Vec2D center,  float diameter);

        inline const Vec2D& GetCenter() const{return mCenter;}
        inline const float& GetDiameter() const{return mDiameter;}
        inline void SetCenter(Vec2D& center){mCenter = center;}
        inline void SetDiameter(const float& diameter){mDiameter = diameter;}
        inline const Vec2D& GetP1() const{return mp1;}
        inline const Vec2D& GetP2() const{return mp2;}
        inline const Vec2D& GetP3() const{return mp3;}
        inline const Vec2D& GetP4() const{return mp4;}
        inline const Vec2D& GetP5() const{return mp5;}

        void Rotate(float angle);
    private:
        Vec2D mCenter;
        float mDiameter;
        Vec2D mp1, mp2, mp3, mp4, mp5;
};

#endif