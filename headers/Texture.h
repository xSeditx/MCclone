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

    void Bind();
    void Unbind();
};


 