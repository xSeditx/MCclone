#include"Texture.h"
#include"Window.h"
#include"Renderer.h"


Texture::Texture()
       : ID(0), Data(nullptr)
{
}
Texture::Texture(const char *filename)
    : ID(0)
{   
    glEnable(GL_TEXTURE_2D);
    Data = LoadBMP(filename);
  
    glGenTextures(1,&ID); 
    glBindTexture(GL_TEXTURE_2D, ID); // Or maybe GL_TEXTURE_BUFFER???
 // glActiveTexture(GL_TEXTURE0 + ID);
// Sampling mode for blending textals
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

// Texture Layout when sampling past texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);   
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
  
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_BGR, GL_UNSIGNED_BYTE, Data);
    glBindTexture(GL_TEXTURE_2D,0);
}

void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, ID);
}
void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{ 
    glDeleteTextures(1, &ID);
    if(Data != nullptr)
               delete(Data);
}
GLubyte* Texture::LoadBMP(const char *filename)
{
    FILE *File = fopen(filename,"rb");
    if(!File)
    {
        Print("Image Could Not Be Loaded");
        return 0;
    }

    if(fread(header,1,54,File)!=54)
    {
        Print("Not the Correct BMP format");
        return 0;
    }


    dataPos   = *(int*)&(header[0x0A]);
    ImageSize = *(int*)&(header[0x22]);
    Width     = *(int*)&(header[0x12]);
    Height    = *(int*)&(header[0x16]);

    ElementCount = ImageSize;
    if(ImageSize == 0) ImageSize = Width * Height * 3;
    if(dataPos   == 0) dataPos = 54;

    GLubyte *imagedata  = new GLubyte[ImageSize];

    fread(imagedata,1,ImageSize,File);
    fclose(File);

    return imagedata;
}
 
//
//
//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST); // ( NEW )
//