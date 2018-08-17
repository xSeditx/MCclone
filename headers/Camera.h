#pragma once


#include <iostream>
#include "Window.h"
//#include "glm.hpp"       

// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;


#if 0
class Camera
{
public:
        Camera();
        Camera(Vec3 position, Vec3 rotation);

        Vec3 Position,
             Front,
             Up,
             Right,
             PitchVector,
             Facing,
             WorldUp;

        Matrix ViewMatrix,
               ModelViewProjectionMatrix;


        float Yaw, 
              Pitch;

        float Speed;

        void Move(const float &speed);
        void MoveLeft(const float &speed);
        void MoveRight(const float &speed);
        void Rotate(float x,float y, float z);
        void Update();


static Matrix Perspective;
static Matrix Orthographic;

void Init(Window win);
};





#else

class Camera{
    public:
        Camera();
        
        Vec3 Position;
        Vec3 Rotation;

        Vec3  Forward, Up, Right;
        Vec3  ForwardRotated, RightRotated;

        Matrix RotationMatrix;
        Matrix TranslationMatrix;
      
        Matrix ModelMatrix, 
               ViewMatrix, 
               ProjectionMatrix;

        Matrix ViewProjectionMatrix;

        Vec3 CameraPosition, CameraRotation;
glm::vec3 cameraTarget;  
glm::vec3 cameraDirection;       
Vec3 CameraUp, CameraRight;

        float AspectRatio; 
        float Near,Far, FOV;
        float Speed;
        
        void MoveForward(const float &Speed);
        void MoveBack(const float &speed);
        void MoveLeft(const float &Speed);
        void MoveRight(const float &Speed);
        void Rotate(float x,float y);
        void Update();
      
        Matrix LookAt(Vec3& eye, Vec3& target, Vec3& upDir);


//Matrix Camera::UpdateView(Vec3& eye, Vec3& target, Vec3& upDir);


void Camera::UpdateView();

void Camera::KeyPressed(const unsigned char key);
void Camera::MouseMove(int dx, int dy);

Vec3    EyeVector;
GLfloat roll, 
        pitch,
        yaw;
       
        void Setup();

        //Vec3 Scale;
        //Vec3 ScreenDimensions;
	glm::mat4 projection() const;

	// Returns only the tranlation matrix
	glm::mat4 translation() const;

	// Returns only the rotation matrix
	glm::mat4 rotation() const;

// Matrix  Orthographic(float Left,float Right,float Top,float Bottom,float Near, float Far);
// Matrix  Perspective(float FOV,float Aspect_Ratio,float Near,float Far);   
// Matrix  Rotation(float Angle,const Vec3& Axis);
// Matrix  Translation(const Vec3& Translation);
 //Matrix  Scale(const Vec3& Scale);

};
#endif 


