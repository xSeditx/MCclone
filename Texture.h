#pragma once
#include"Window.h"


class Texture
{
public:
        Texture();
       ~Texture();
        Texture(const char *filename);
       
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


 