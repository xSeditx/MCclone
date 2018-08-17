
#include"Window.h"
#include"Texture.h"
#include"Renderer.h"
#include<vector>



//     0        GL_TEXTURE_CUBE_MAP_POSITIVE_X        Right  
//     1	    GL_TEXTURE_CUBE_MAP_NEGATIVE_X        Left
//     2	    GL_TEXTURE_CUBE_MAP_POSITIVE_Y        Top
//     3	    GL_TEXTURE_CUBE_MAP_NEGATIVE_Y        Bottom
//     4	    GL_TEXTURE_CUBE_MAP_POSITIVE_Z        Back
//     5	    GL_TEXTURE_CUBE_MAP_NEGATIVE_Z        Front


class Shader;

class SkyBox
{
    enum
    {
        Right, 
        Left, 
        Top, 
        Bottom,
        Back, 
        Front, 
    }Face;

public:

    SkyBox(Shader &shader);
    SkyBox(Texture *sky);

    GLuint ID;

    Vec3 Position,
         Rotation;


    Shader CubemapShader;
    // Texture FaceTexture[6];

    GLuint FaceTexture[6];

    VAOBuffer      *VAO;
    Texture       Image;
    void Bind();
    void Unbind();
    void Render(Vec3 rotation);
    void OnUpdate();
};
