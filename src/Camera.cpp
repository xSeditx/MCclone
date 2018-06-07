//                                                                                                                          
//                          OPENGL 2.0 Abstraction API
//                               January 24 2018
//                              -----------------                                                                           
//                                                                                                                          
//                             CANERA HANDLING LIB                                                                     
//==========================================================================================================================



#include "Camera.h"
#include "Window.h"
//#include <GLFW/glfw3.h> 
#include "gtc/matrix_transform.hpp"

Camera::Camera()
      :
      Position(0,0,0),
      Rotation(0,0,0),
      Speed(1)
{
       // glm::vec4 Position = glm::vec4(glm::vec3(0.0), 1.0);
       // Transform = glm::mat4(1.0);
       // Transform[4] = glm::vec4(1.0, 1.0, 0.0, 1.0);
       // glm::vec4 Transformed = Model * Position;
}

void Camera::MoveForward(const float &speed)
{
    Speed = speed;
float  SIN_X = sin(RADIANS( Rotation.x  - 90));
            Position.x -= (cos(RADIANS(Rotation.y - 90)) * SIN_X) * Speed;
            Position.y -=  cos(RADIANS(Rotation.x - 90)) * speed;
            Position.z -= (sin(RADIANS(Rotation.y - 90)) * SIN_X) * Speed;
}
void Camera::MoveBack(const float &speed)
{
        Speed = speed;
float  SIN_X = sin(RADIANS( Rotation.x  - 90));
            Position.x += (cos(RADIANS(Rotation.y - 90))* SIN_X) * Speed;
            Position.y +=  cos(RADIANS(Rotation.x - 90))* speed;
            Position.z += (sin(RADIANS(Rotation.y - 90))* SIN_X) * Speed;
}
void Camera::MoveLeft(const float &speed)
{
            Speed = speed;
            Position.x +=  cos(RADIANS(Rotation.y - 0)) * Speed;
            Position.z +=  sin(RADIANS(Rotation.y - 0)) * Speed;
}
void Camera::MoveRight(const float &speed)
{
            Speed = speed;
            Position.x += cos(RADIANS(Rotation.y - 180)) * Speed;
            Position.z += sin(RADIANS(Rotation.y - 180)) * Speed;
}
void Camera::Rotate(float x,float y)
{
        Rotation.y += (x * .8);  
        Rotation.x += (y * .8);
}
void Camera::Update()
{
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
//  ROTATE the Camera  
        glRotatef(Rotation.x ,  1.0f,  0.0f,  0.0f);
        glRotatef(Rotation.y ,  0.0f,  1.0f,  0.0f);
        glRotatef(Rotation.z ,  0.0f,  0.0f,  1.0f);
//  Move Camera into Position       
        glTranslatef(Position.x, 0., 0.);
        glTranslatef(  0., Position.y,   0.);
        glTranslatef(  0.,   0., Position.z);
}



//
//
//
//void Camera::Setup()
//{
//    Projection = glm::project(Vec3(0,0,0),Matrix(1.0f), Matrix(1.0f),  Vec4(0.0f,ScreenDimensions.x,0.0f, ScreenDimensions.y));//  0.0f, ScreenDimensions.x, 0.0f, ScreenDimensions.y, -1.0f, 1.0f);
//    glm::mat4 View = glm::mat4(1);
//    glm::mat4 Scale = glm::scale(glm::mat4(1), glm::vec3(Scale));
//    glm::mat4 Translate = glm::translate(glm::mat4(1), glm::vec3(-Position.x*Scale + ScreenDimensions.x / 2, -Position.y*Scale + ScreenDimensions.y / 2, 0)); 
//    glm::mat4 Model =  Translate * Scale;
//
//    Transform = Projection * View * Model;
//}
//


//
//
//Matrix Camera::Orthographic(float Left,float Right,float Top,float Bottom,float Near, float Far)
//{
//    Matrix result(1.0f);
//    
//    result[0][0] = 2.0f/ (Right - Left);
//    result[1][1] = 2.0f/ (Top - Bottom);
//    result[2][2] = 2.0f/ (Near - Far);
//    
//    result[0][3] = 1;//(Left + Right) / (Left - Right);
//    result[1][3] = (Bottom - Top) / (Bottom - Top);
//    result[2][3] = (Far - Near) / (Far - Near);
//    
//    return result;
//}
//// Matrix Camera::Perspective(float FOV,float Aspect_Ratio,float Near,float Far)
// {
// 	Matrix result(1.0f);
// 
// 	float q = 1.0f / (float)tan((.5 * (3.14159 / 180.0f))*FOV);
// 	float a = q / Aspect_Ratio;
// 
// 	float b = (Near + Far) / (Near - Far);
// 	float c = (2.0f * Near * Far) / (Near - Far);
// 
// 	result.elements[0 + 0 * 4] = a;
// 	result.elements[1 + 1 * 4] = q;
// 	result.elements[2 + 2 * 4] = b;
// 
// 	result.elements[3 + 2 * 4] = -1.0f;
//     result.elements[2 + 3 * 4] = c;
// 
// 	return result;
// }	   
// Matrix Camera::Rotation(float Angle,const Vec3& Axis)
// {
// 	Matrix result(1.0f);
// 
// 	float r = (float)(Angle  * (3.14159 / 180.0f));
// 	float c = cos(r);
// 	float s = sin(r);
// 	float omc = 1.0f - c;
// 
// 	float x = Axis.x;
// 	float y = Axis.y;
// 	float z = Axis.z;
// 
// 	result.elements[0 + 0 * 4] = x  * omc + c;
// 	result.elements[1 + 0 * 4] = y * x * omc + z * s;
// 	result.elements[2 + 0 * 4] = x * z * omc - y * s; 	
// 
// 	result.elements[0 + 1 * 4] = x * y * omc - z * s;
// 	result.elements[1 + 1 * 4] = y * omc + c;
// 	result.elements[2 + 1 * 4] = y * z * omc + x * s;
// 
// 	result.elements[0 + 2 * 4] = x * z * omc + y * s;
// 	result.elements[1 + 2 * 4] = y * z * omc + x * s;
// 	result.elements[2 + 2 * 4] = z * omc + c; 
// 
// 	return result;
// }
// Matrix Camera::Translation(const Vec3& Translation)
// {
// 	Matrix result(1.0f);
// 
// 	result.elements[0 + 3 * 4] = Translation.x;
// 	result.elements[1 + 3 * 4] = Translation.y;
// 	result.elements[2 + 3 * 4] = Translation.z;
// 
// 	return result;
// }
// Matrix Camera::Scale(const Vec3& Scale)
// {
// 	Matrix result(1.0f);
// 
// 	result.elements[0 + 0 * 4] = Scale.x;
// 	result.elements[1 + 1 * 4] = Scale.y;
// 	result.elements[2 + 2 * 4] = Scale.z;
// 
// 	return result;
// 
// }
//