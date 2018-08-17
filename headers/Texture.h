#pragma once
#include"Window.h"



// CONVERT THIS NAME TO SOMETHING LIKE IMAGE SINCE IT DOES NOT MAKE A TEXTURE BUT INSTEAD LOADS AN IMAGE
// THE TEXTUREBUFFER SHOULD EITHER BECOME TEXTURE OR PROB EVEN BETTER CALLED UV_BUFFER OR SOMETHING AND HAVE 
// A TEXTURE CLASS WHICH IS ITSELF A COMBINATION OF THE IMAGE AND THE TEXTURE COORDS SO THAT THEY CAN BE LOADED
// AND UNLOADED AT THE SAME TIME OR SEPERATELY AS NEEDED.


class Texture
{
public:
        Texture();
       ~Texture();
        Texture(const char *filename);
        Texture(GLenum param, const char *filename);
       
        GLuint ID;
       
        GLubyte header[54];
        GLuint  dataPos;
       
        GLuint  Width,
                Height,
                ImageSize;
       
        GLubyte *Data;
       
        GLuint ElementCount;
       
        GLubyte* LoadBMP      (const char *filename);
       
        void SetWH(float width, float height);
        void GenColorTexture(float W, float H);
        void GenDepthTexture(float W, float H);
        void Bind();
        void Unbind();
};


 