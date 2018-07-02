#include"Texture.h"
#include"Window.h"
#include"Renderer.h"


Texture::Texture()
       : ID(0), 
         Data(nullptr),
         Width(0),
         Height(0)
{
    
    glEnable(GL_TEXTURE_2D);  
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

Texture::Texture(GLenum param, const char *filename)
    : ID(0)
{   
    glEnable(GL_TEXTURE_2D);
    Data = LoadBMP(filename);
    if (param == GL_TEXTURE_CUBE_MAP)
    {
        glGenTextures(1,&ID); 
        glBindTexture(GL_TEXTURE_CUBE_MAP, ID); 
//      glActiveTexture(GL_TEXTURE0 + ID);
//      Sampling mode for blending textals
        
        glTexParameteri(param, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(param, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        
//      Texture Layout when sampling past texture
        glTexParameteri(param, GL_TEXTURE_WRAP_S, GL_REPEAT);   
        glTexParameteri(param, GL_TEXTURE_WRAP_T, GL_REPEAT);   
        glTexParameteri(param, GL_GENERATE_MIPMAP, GL_TRUE);
        
        glTexImage2D(param, 0, GL_RGB, Width, Height, 0, GL_BGR, GL_UNSIGNED_BYTE, Data);
        glBindTexture(GL_TEXTURE_CUBE_MAP,0);
    }
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


void Texture::SetWH(float width, float height)
{
    Width = width;
    Height = height;
}

void Texture::GenColorTexture(float W, float H)
{
    Width = W; Height = H;
    if(Width && Height == 0)
    {
        Print("Texture Size not Initialized");
        exit(0);
    }
       glGenTextures(1, &ID);
       glBindTexture(GL_TEXTURE_2D, ID);
           glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA , Width, Height, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);
           
           glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
           glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::GenDepthTexture(float W, float H)
{
    Width = W; Height = H;
    if(Width && Height == 0)
    {
        Print("Texture Size not Initialized");
        exit(0);
    }

    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
      
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
    //    glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
    
        glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, Width, Height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
}



