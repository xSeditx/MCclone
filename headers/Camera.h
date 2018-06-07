#pragma once


#include <iostream>
#include "Window.h"
//#include "glm.hpp"       

class Camera{
    public:
        Camera();
        
        Vec3 Position;
        Vec3 Rotation;

        Matrix Transform;
        Matrix Model, View, Projection;
        float Speed;
        
        void MoveForward(const float &Speed);
        void MoveBack(const float &speed);
        void MoveLeft(const float &Speed);
        void MoveRight(const float &Speed);
        void Rotate(float x,float y);
        void Update();

        void Setup();

        //Vec3 Scale;
        //Vec3 ScreenDimensions;

// Matrix  Orthographic(float Left,float Right,float Top,float Bottom,float Near, float Far);
// Matrix  Perspective(float FOV,float Aspect_Ratio,float Near,float Far);   
// Matrix  Rotation(float Angle,const Vec3& Axis);
// Matrix  Translation(const Vec3& Translation);
 //Matrix  Scale(const Vec3& Scale);

};





