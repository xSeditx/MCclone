#include"Skybox.h"

//   Layer           Number  Cubemap face          Orientation
//____________________________________________________________   
//                                                            
//     0        GL_TEXTURE_CUBE_MAP_POSITIVE_X        Right  
//     1	    GL_TEXTURE_CUBE_MAP_NEGATIVE_X        Left
//     2	    GL_TEXTURE_CUBE_MAP_POSITIVE_Y        Top
//     3	    GL_TEXTURE_CUBE_MAP_NEGATIVE_Y        Bottom
//     4	    GL_TEXTURE_CUBE_MAP_POSITIVE_Z        Back
//     5	    GL_TEXTURE_CUBE_MAP_NEGATIVE_Z        Front



SkyBox::SkyBox(Shader &shader)
{
            glActiveTexture(GL_TEXTURE0);
    CubemapShader = shader;
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, ID);


//============================================================================================================================
//                     Fucking Excessive Loading Mechanics. Need to figure a cleaner way to do this in the future.                                                                                   
//============================================================================================================================
    Image.Data = Image.LoadBMP("Sky4.BMP");
    glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_X + Left, 
                  0, GL_RGB, 512, 512, 0, GL_RGB, GL_UNSIGNED_BYTE,  Image.Data );
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);  


    Image.Data = Image.LoadBMP("Sky2.BMP");
    glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_X + Right, 
                  0, GL_RGB, 512, 512, 0, GL_RGB, GL_UNSIGNED_BYTE,  Image.Data );
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);  


    Image.Data = Image.LoadBMP("Sky1.BMP");
    glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_X + Front, 
                  0, GL_RGB, 512, 512, 0, GL_RGB, GL_UNSIGNED_BYTE,  Image.Data );
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);  


    Image.Data = Image.LoadBMP("Sky3.BMP");
    glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_X + Back, 
                  0, GL_RGB, 512, 512, 0, GL_RGB, GL_UNSIGNED_BYTE,  Image.Data );
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);  


    Image.Data = Image.LoadBMP("Sky5.BMP");
    glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_X + Top, 
                  0, GL_RGB, 512, 512, 0, GL_RGB, GL_UNSIGNED_BYTE,  Image.Data );
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);  


    Image.Data = Image.LoadBMP("Sky6.BMP");
    glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_X + Bottom, 
                  0, GL_RGB, 512, 512, 0, GL_RGB, GL_UNSIGNED_BYTE,  Image.Data );
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);  
//============================================================================================================================
//============================================================================================================================


    GLfloat size = (200);

    Vec3 VertexData[] = 
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
    VAO = new VAOBuffer();
    VAO->Vertices = new VertexBuffer(&VertexData[0], 24);
    VAO->Indices  = new IndexBuffer (&Indexdata[0] , 36);
    VAO->Textures = nullptr;
}


SkyBox::SkyBox(Texture *sky){}

int ID;

Vec3 Position,
     Rotation;

VAOBuffer      *VAO;



void SkyBox::Render(Vec3 rotation)
{
//glBindTexture(GL_TEXTURE_2D, 0);
glLoadIdentity();
//glDepthMask(GL_FALSE);
Bind();
CubemapShader.Enable();
rotation.y = -rotation.y;
rotation.x = -rotation.x;
 
CubemapShader.SetUniform3f("CameraPosition", rotation);

//glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
glDrawElements(GL_TRIANGLES, VAO->Indices->ElementCount, GL_UNSIGNED_INT, nullptr);
glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
//glActiveTexture(GL_TEXTURE0);
Unbind();
CubemapShader.Disable();
//glDepthMask(GL_TRUE);
}


void SkyBox::Bind()
{
    VAO->Bind();
}
void SkyBox::Unbind()
{
    VAO->Unbind();
}




    //FaceTexture[Front]  = Texture(); // "Sky1.BMP"
    //FaceTexture[Right]  = Texture(); // "Sky2.BMP"
    //FaceTexture[Back]   = Texture(); // "Sky3.BMP"
    //FaceTexture[Left]   = Texture(); // "Sky4.BMP"
    //FaceTexture[Top]    = Texture(); // "Sky5.BMP"
    //FaceTexture[Bottom] = Texture(); // "Sky6.BMP"
   //  FaceTexture[Front].Data =  FaceTexture->LoadBMP("Sky2.BMP"); // GL_TEXTURE_CUBE_MAP_POSITIVE_X //  Right