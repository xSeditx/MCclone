#include"Lights.h"
#include "gtc/matrix_transform.hpp"
#include "Texture.h"

extern Shader *ShadowShader;
// VERY BASIC LIGHTING SYSTEM I PLAN ON EXTENDED AS I WORK ON THE SHADOW MAKER
 int LightSource::NumberOfLights;
extern Texture *ShadowTexture;
//----------------------- ----------------------------------
LightSource::~LightSource()
{
    Print("LightSource Destructor Called");
}
 

void LightSource::Delete()
{
 //   delete(Shadow);  

//This needs to be altered If I attempt to delete the shader if errors so perhaps I should handle the loading and deletions inside of the light
// But then I might have multiple lights using the same shader attempting to delete it. The shader Delete function might have to look at
// Pointer validity before being able to delete it.
}

LightSource::LightSource(Shader &shader, Vec4 pos, float alight, float dlight, float slight)
{
        LightSource Light(  shader,
                            pos,
                            Vec3(  alight,  alight,  alight),
                            Vec3(  dlight,  dlight,  dlight),
                            Vec3(  slight,  slight,  slight)
                          );
}                                                  

LightSource::LightSource(Shader &shader, Vec4 pos, RGBf alight, RGBf dlight, RGBf slight)
            : LightNumber(NumberOfLights++)
{       
    GLfloat a[] = { alight.r,  alight.g,  alight.b,     1};
    GLfloat d[] = { dlight.r,  dlight.g,  dlight.b,     1};
    GLfloat s[] = { slight.r,  slight.g,  slight.b,     1};
    GLfloat p[] = {    pos.x,     pos.y,     pos.z, pos.w};
                                          
    glEnable(GL_LIGHTING);  
    glEnable(GL_LIGHT0 + LightNumber);
    glLightf(GL_LIGHT0 + LightNumber, GL_POSITION, *p);
        
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    
    glLightfv(GL_LIGHT0 + LightNumber, GL_AMBIENT , a);
    glLightfv(GL_LIGHT0 + LightNumber, GL_DIFFUSE , d);
    glLightfv(GL_LIGHT0 + LightNumber, GL_SPECULAR, s);
    
    LightModel();
 
    SetPosition(Vec3(pos.x,pos.y,pos.z), Vec3(pos.x,pos.y,pos.z));

    Shadow = new ShadowMap(shader, 512, 512);
}
ShadowMap::ShadowMap(Shader &shader, unsigned int width, unsigned int height)
    :Width(width), Height(height)
{
    FBuffer = new FrameBuffer(shader, 640, 480);
  //  glGenTextures(1, &Map);
  //  glBindTexture(GL_TEXTURE_2D, Map);
  //      glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, Width, Height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
  //
  //   // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  //   // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  //   //
  //   // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  //   // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  //
  //      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  //      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  //    
  //      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  //      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);       
  //       
            glGenFramebuffersEXT(1, &FBO); 
            glBindFramebufferEXT(GL_FRAMEBUFFER, FBO);

    glGenTextures(1, &Map);
    glBindTexture(GL_TEXTURE_2D, Map);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
      
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
    //    glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
    
        glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, Width, Height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);



            glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, Map, 0);

            glDrawBuffer(GL_NONE); // No color buffer is drawn to //  
           glReadBuffer(GL_NONE);// Not in original tutorial required to complete the framebuffer else the error occures
            
            GLenum Status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER);
            if (Status != GL_FRAMEBUFFER_COMPLETE)  printf("FB error, status: 0x%x\n", Status);
    
            MakeTestQuad();
        glBindFramebufferEXT(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);


}

void ShadowMap::Bind()
{
    ShadowRender.Enable();
        glBindFramebufferEXT(GL_DRAW_FRAMEBUFFER, FBO);
}
void ShadowMap::Unbind()
{
        glBindFramebufferEXT(GL_DRAW_FRAMEBUFFER, 0);
    ShadowRender.Disable();
}

ShadowMap::ShadowMap(){}
ShadowMap::~ShadowMap(){Print("ShadowMap Destructor");}


void ShadowMap::MakeTestQuad()
{
    Position = Vec3(0,0,0);
    Rotation = Vec3(0,0,0);

    float Size = 10;
    Vec3 quad[] = 
    {
        Vec3( Size,  -10.0f,  Size),
        Vec3(-Size,  -10.0f,  Size),
        Vec3(-Size,  -10.0f, -Size),
        Vec3( Size,  -10.0f, -Size),
    };

    Vec4 color[] = 
    {
        Vec4(  0.0f,  0.0f, 0.0f,   0.0f),
        Vec4(  0.0f,  0.0f, 0.0f,   0.0f),
        Vec4(  0.0f,  0.0f, 0.0f,   0.0f),
        Vec4(  0.0f,  0.0f, 0.0f,   0.0f),
    };

    GLuint quadIB[] = 
    {
        0,1,2,  0,2,3
    };
    Vec2 UVs[] = 
    {
        Vec2(0.0f, 1.0f),
        Vec2(0.0f, 0.0f),
        Vec2(1.0f, 0.0f),
        Vec2(1.0f, 1.0f)
    };

    TestQuad    = new VertexBuffer(quad,4);
    TestQuadIBO = new IndexBuffer(quadIB,6);

    glGenBuffers(1, &TexCoordsID);
        glBindBuffer(GL_ARRAY_BUFFER, TexCoordsID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vec2) * 4 , UVs, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}



void ShadowMap::Render()
{

    glPushMatrix();
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
            glLoadIdentity();
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
                glLoadIdentity();
                glMatrixMode(GL_TEXTURE);
                glPushMatrix();
                    glLoadIdentity();
                    
                    glEnable(GL_TEXTURE_2D);
                    
                    glBindTexture(GL_TEXTURE_2D,Map);
                    glBegin(GL_QUADS);
                        glTexCoord2f(0.0, 0.0); glVertex2f( -1.0, -1.0);
                        glTexCoord2f(0.0, 1.0); glVertex2f( -1.0, -0.5);
                        glTexCoord2f(1.0, 1.0); glVertex2f( -0.5, -0.5);
                        glTexCoord2f(1.0, 0.0); glVertex2f( -0.5, -1.0);
                    glEnd();
                    
                    glBindTexture(GL_TEXTURE_2D, Map);
                    glBegin(GL_QUADS);
                        glTexCoord2f(0.0, 0.0); glVertex2f(-0.5, -1.0);
                        glTexCoord2f(0.0, 1.0); glVertex2f(-0.5,  -0.5);
                        glTexCoord2f(1.0, 1.0); glVertex2f( -0.0,  -0.5);
                        glTexCoord2f(1.0, 0.0); glVertex2f( -0.0, -1.0);
                    glEnd();
                    
                    glMatrixMode(GL_TEXTURE);
                glPopMatrix(); 
                glMatrixMode(GL_MODELVIEW);
            glPopMatrix();
            glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void LightSource::CreateMatrices()
{
     glm::vec3 lightInvDir = glm::vec3(0.5f,2,2);
 
     // Compute the MVP matrix from the light's point of view
     glm::mat4 depthProjectionMatrix = glm::ortho<float>(-10,10,-10,10,-10,20);
     glm::mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(0,0,0), glm::vec3(0,1,0));
     glm::mat4 depthModelMatrix = glm::mat4(1.0);
     glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;
    
     // Send our transformation to the currently bound shader,
     // in the "MVP" uniform
     glUniformMatrix4fv(1, 1, GL_FALSE, &depthMVP[0][0]);
glm::mat4 biasMatrix(
0.5, 0.0, 0.0, 0.0,
0.0, 0.5, 0.0, 0.0,
0.0, 0.0, 0.5, 0.0,
0.5, 0.5, 0.5, 1.0
);
glm::mat4 depthBiasMVP = biasMatrix*depthMVP;

}

///https://www.khronos.org/opengl/wiki/Framebuffer_Object_Extension_Examples



void LightSource::Render()
{
   glPushMatrix();

        glBegin(GL_TRIANGLES);
            glVertex3f(Position.x,Position.y, Position.z);
            glVertex3f(Position.x+1,Position.y+1, Position.z+1);
            glVertex3f(Position.x-1,Position.y-1, Position.z);
        glEnd();

        Shadow->Render();


//        glTranslatef(Position.x, 
//                     Position.y,
//                     Position.z);
//
//        Vertices.Bind();
//            Indices.Bind();
//                glDrawElements(GL_TRIANGLES, Indices.ElementCount, GL_FLOAT, nullptr);
//            Indices.Unbind();
//        Vertices.Unbind();
  glPopMatrix();
}

void LightSource::LightModel()
{

    float size = 1;
    Vec3 V[] = 
    {                                                   
            Vec3(-size,-size, size), // FRONT    // 0                                             
            Vec3( size,-size, size),             // 1                                    
            Vec3( size, size, size),             // 2                                    
            Vec3(-size, size, size),             // 3                                    
                                                                                     
            Vec3( size, size, size), // RIGHT    // 4    2                                        
            Vec3( size, size,-size),             // 5                                    
            Vec3( size,-size,-size),             // 6                                    
            Vec3( size,-size, size),             // 7    1                                
                                                        
            Vec3(-size,-size,-size), // BACK     // 8                                            
            Vec3( size,-size,-size),             // 9    6                               
            Vec3( size, size,-size),             // 10   5                                
            Vec3(-size, size,-size),             // 11
                                                    
            Vec3(-size,-size,-size), // LEFT     // 12   8                                        
            Vec3(-size,-size, size),             // 13   7                              
            Vec3(-size, size, size),             // 14   3                                
            Vec3(-size, size,-size),             // 15  11                                
                                                       
            Vec3( size, size, size), // TOP      // 16   2                                      
            Vec3(-size, size, size),             // 17   3                                
            Vec3(-size, size,-size),             // 18   11                                
            Vec3( size, size,-size),             // 19   5                                
                                                        
            Vec3(-size,-size,-size), // BOTTOM   // 20   8                                   
            Vec3( size,-size,-size),             // 21   9                          
            Vec3( size,-size, size),             // 22   1                          
            Vec3(-size,-size, size),             // 23   0                               
    };


    GLuint Indexdata[]=
    { 
        0,1,2,    0,2,3,     // FRONT
        6,5,4,    4,7,6,     // RIGHT 
        10,9,8,   8,11,10,   // BACK
        12,13,14, 12,14,15,  // LEFT
        18,17,16, 16,19,18,  // TOP
        20,21,22, 20,22,23   // BOTTOM
    };


    Vertices = VertexBuffer(V, 24);
    Indices = IndexBuffer(Indexdata,36);
}








void LightSource::UpdateStart()
{
}
void LightSource::UpdateEnd()
{
}





void LightSource::SetAmbient(RGBAf color)
{
    glLightfv(GL_LIGHT0+LightNumber, GL_AMBIENT, &color[0]);
}
void LightSource::SetSpecular(RGBAf color)
{
    glLightfv(GL_LIGHT0+LightNumber, GL_SPECULAR,&color[0]);
}
void LightSource::SetDiffuse(RGBAf color)
{
    glLightfv(GL_LIGHT0+LightNumber, GL_DIFFUSE,&color[0]);
}
void LightSource::SetPosition(Vec3 position, Vec3 direction)
{
    Position = position;
    glLightfv(GL_LIGHT0 + LightNumber, GL_POSITION, &position[0]);
}
