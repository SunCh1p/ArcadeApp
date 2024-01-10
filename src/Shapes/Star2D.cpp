#include "Star2D.h"
#include "Utils.h"

Star2D::Star2D(Vec2D center, float diameter){
    if(diameter < EPSILON){
        mp1 = Vec2D::Zero;
        mp2 = Vec2D::Zero;
        mp3 = Vec2D::Zero;
        mp4 = Vec2D::Zero;
        mp5 = Vec2D::Zero;
    }
    else{
        mCenter = center;
        mDiameter = diameter;
        float radius = diameter/2;
        mp1 = Vec2D(center.GetX(), center.GetY()+radius);
        mp2 = mp1.RotationResult(1.25664, center);
        mp3 = mp2.RotationResult(1.25664, center);
        mp4 = mp3.RotationResult(1.25664, center);
        mp5 = mp4.RotationResult(1.25664, center);
    }
    
};

void Star2D::Rotate(float angle){
    mp1.Rotate(angle, mCenter);
    mp2.Rotate(angle, mCenter);
    mp3.Rotate(angle, mCenter);
    mp4.Rotate(angle, mCenter);
    mp5.Rotate(angle, mCenter);
}