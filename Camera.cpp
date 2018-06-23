//                                                                                                                          
//                          OPENGL 2.0 Abstraction API
//                               January 24 2018
//                              -----------------                                                                           
//                                                                                                                          
//                             CANERA HANDLING LIB                                                                     
//==========================================================================================================================
 //'world space' and 'camera/view space'.




#include "Camera.h"
#include "Window.h"
//#include <GLFW/glfw3.h> 
#include "gtc/matrix_transform.hpp"

//(30, 640.0 / 480.0, 1, 1000);

Camera::Camera()
      :
      Position(0,0,0),
      Rotation(0,0,0),
      Speed(1)
{
    ProjectionMatrix = glm::perspective(30.0f, 640.0f / 480.0f, .1f, 1000.0f);
    
    float V[] = 
    {
        0.0f,  0.0f,  0.0f,  0.0f,
        0.0f,  0.0f,  0.0f,  0.0f,
        0.0f,  0.0f,  0.0f,  0.0f,
        0.0f,  0.0f,  0.0f,  1.0f
    };
    
    ViewMatrix = glm::make_mat4(V);

           // glm::vec4 Position = glm::vec4(glm::vec3(0.0), 1.0);
           // Transform = glm::mat4(1.0);
           // Transform[4] = glm::vec4(1.0, 1.0, 0.0, 1.0);
           // glm::vec4 Transformed = Model * Position;
}

void Camera::MoveForward(const float &speed)
{
    Speed = speed;
    float  SIN_X = sin(RADIANS(Rotation.x - 90));
    Position.x -= (cos(RADIANS(Rotation.y - 90)) * SIN_X) * Speed;
    Position.y -=  cos(RADIANS(Rotation.x - 90)) * speed;
    Position.z -= (sin(RADIANS(Rotation.y - 90)) * SIN_X) * Speed;
}
void Camera::MoveBack(const float &speed)
{
    Speed = speed;
    float  SIN_X = sin(RADIANS(Rotation.x - 90));
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
//        glRotatef(Rotation.z ,  0.0f,  0.0f,  1.0f);

//  Move Camera into Position       
        glTranslatef(
                      Position.x,
                      Position.y,
                      Position.z
                    );


// ======== NEW SHIT ===============================================
    float V[] = 
    {
        0.0f,  0.0f,  0.0f,  0.0f,
        0.0f,  0.0f,  0.0f,  0.0f,
        0.0f,  0.0f,  0.0f,  0.0f,
        0.0f,  0.0f,  0.0f,  1.0f
    };
    ViewMatrix = glm::make_mat4(V);

    float T[] = 
    {
        0.0f,  0.0f,  0.0f,  Position.x,
        0.0f,  0.0f,  0.0f,  Position.y,
        0.0f,  0.0f,  0.0f,  Position.z,
        0.0f,  0.0f,  0.0f,  1.0f
    };
    TranslationMatrix = glm::make_mat4(T);

    float R[] = 
    {
        0.0f,  0.0f,  0.0f,  0.0f,
        0.0f,  0.0f,  0.0f,  0.0f,
        0.0f,  0.0f,  0.0f,  0.0f,
        0.0f,  0.0f,  0.0f,  1.0f
    };
    RotationMatrix = glm::make_mat4(V);

    ViewMatrix = RotationMatrix * TranslationMatrix;

}


Matrix Camera::LookAt(Vec3& eye, Vec3& target, Vec3& upDir)
{
Matrix ret;
return ret;
}



//Matrix Camera::MakeView(Vec3& eye, Vec3& target, Vec3& upDir)
//{
//
//    GLfloat tilt = 0.0f;
//    GLfloat  bearing =  0.0f;
//    
//    glm::vec3 upVector = glm::vec3(0, 1, 0);
//    
//    Transform = glm::rotate(glm::mat4(),bearing, upVector); // rotate around to a given bearing: yaw
//    glm::vec3 pitchVector = glm::vec3(1, 0, 0); // Define the 'look up' axis, should be orthogonal to the up axis
//    
//    Transform = glm::rotate(Transform, tilt, pitchVector); // rotate around to the required head tilt: pitch
//    ViewMatrix = glm::inverse(Transform);    // now get the view matrix by taking the camera inverse
//    
//    return ViewMatrix;
//}
//



void Camera::UpdateView()
{

    glm::mat4 Temp;
    Vec3 RvX =  Vec3( 1, 0, 0);
    Vec3 RvY =  Vec3( 0, 1, 0);
    Vec3 RvZ =  Vec3( 0, 0, 1);

    Temp = glm::rotate(Temp, glm::radians(Rotation.x), RvX);
    Temp = glm::rotate(Temp, glm::radians(Rotation.y), RvY);
    Temp = glm::rotate(Temp, glm::radians(Rotation.z), RvZ);

    ViewMatrix = glm::translate(Temp, glm::vec3(-Position.x, -Position.y, -Position.z));


    ModelViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
}




void Camera::KeyPressed(const unsigned char key)
{
  float dx = 0; //how much we strafe on x
  float dz = 0; //how much we walk on z
  switch (key)
  {
    case 'w':
    {
      dz = 2;
      break;
    }
 
    case 's':
    {
      dz = -2;
      break;
    }
    case 'a':
    {
      dx = -2;
      break;
    }
 
    case 'd':
    {
      dx = 2;
      break;
    }
   default:
     break;
  }
   
  glm::mat4 mat = ViewMatrix;

  //row major < - DAFUQ
  glm::vec3 forward(mat[0][2], mat[1][2], mat[2][2]);
  glm::vec3 strafe( mat[0][0], mat[1][0], mat[2][0]);
  
  const float speed = 0.12f;
 
  EyeVector += (-dz * forward + dx * strafe) * speed;
  UpdateView();
}



void Camera::MouseMove(int dx, int dy)
{
    const float mouseX_Sensitivity = 0.25f;
    const float mouseY_Sensitivity = 0.25f;

    //note that yaw and pitch must be converted to radians.
    //this is done in UpdateView() by glm::rotate
    yaw   += mouseX_Sensitivity * dx;
    pitch += mouseY_Sensitivity * dy;

    UpdateView();
}


















//  glm::mat4 CameraMatrix = glm::lookAt(
//  glm::vec3(cameraPosition.X,cameraPosition.Y,cameraPosition.Z), // camera, in world space
//  glm::vec3(cameraTarget.X,cameraTarget.Y,cameraTarget.Z),   // direction vector eye + Dir
//  glm::vec3(upVector.X,upVector.Y,upVector.Z) 
//  );
//  
//   RightX      RightY      RightZ      0
//   UpX         UpY         UpZ         0
//   LookX       LookY       LookZ       0
//   PosX        PosY        PosZ        1
//   
//   0           1           2           3
//   4           5           6           7
//   8           9           10          11
//   12          13          14          15
//   
//  float m[16] = {0,4,8,12,1,5,9,13,2,6,10,14,3,7,11,15};

//  | ux vx -nx -eyex |  VIEW_MATRIX
//  | uy vy -ny -eyey |
//  | uz vz -nz -eyez |
//  | 0  0    0     1 |


//Vec3 forward = eye - target;//// compute the forward vector from target to eye
//forward = glm::normalize(forward);      // make unit length
 

//Vec3 left = glm::cross(upDir, forward); // //// compute the left vector
//left = glm::normalize(left);

//Vec3 up = glm::cross(forward, left);  //// recompute the orthonormal up vector


//Matrix matrix;
//matrix =  glm::mat4(1.0);
//
///    // set rotation part, inverse rotation matrix: M^-1 = M^T for Euclidean transform
///    matrix[0][0] = left.x;
///    matrix[4] = left.y;
///    matrix[8] = left.z;
///    matrix[1] = up.x;
///    matrix[5] = up.y;
///    matrix[9] = up.z;
///    matrix[2] = forward.x;
///    matrix[6] = forward.y;
///    matrix[10]= forward.z;
///
///    // set translation part
///    matrix[12]= -left.x * eye.x - left.y * eye.y - left.z * eye.z;
///    matrix[13]= -up.x * eye.x - up.y * eye.y - up.z * eye.z;
///    matrix[14]= -forward.x * eye.x - forward.y * eye.y - forward.z * eye.z;
///
///    return matrix;



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


//float Inv[] = {
//    1.0f, 0.0f ,0.0f ,-1.0f,
//    0.0f, 1.0f ,0.0f ,-1.0f,
//    0.0f, 0.0f ,1.0f ,-1.0f,
//    0.0f, 0.0f ,0.0f , 1.0f
//};                

//glm::mat4 InversionMatrix = Array_to_Mat4(Inv);




// 
// 
// 
// glm::mat4 ViewMatrix(glm::vec3 Position, glm::vec3 Rotation)
// {
//     glm::mat4 Temp;
//     Temp = glm::rotate(Temp, glm::radians(Rotation.x), { 1, 0, 0 });
//     Temp = glm::rotate(Temp, glm::radians(Rotation.y), { 0, 1, 0 });
//     Temp = glm::rotate(Temp, glm::radians(Rotation.z), { 0, 0, 1 });
// 
//     Temp = glm::translate(Temp, glm::vec3(-Position.x, -Position.y, -Position.z));
// 
//     return Temp;
// }