#pragma once
#include<vector>
#include"Window.h"
#include"glm.hpp"
#include"Texture.h"
#include"Shader.h"

 

#define VERTEX_ATTRIB     0
#define NORMAL_ATTRIB     1
#define TEXTURE_ATTRIB    2
#define COLOR_ATTRIB      3

#define BUFFER_OFFSET(i)   ((char *)NULL + (i))

#define MAX_OBJECTS    10000


using namespace std;
using namespace glm;

struct Vertex
{
    Vec3 Position;
    Vec3 Normals;
    Vec2 Uv;
};


class VertexBuffer{
    public:
        VertexBuffer(){}
       ~VertexBuffer();
        VertexBuffer(Vec3 *Vertexdata, GLsizei count);

        GLuint ID;
        GLint  ElementCount; 

        Vec3  *Data;

        void Bind();
        void Unbind();

        void Lock(GLenum access);
        void Unlock();

        GLfloat *Read();
        void Write(GLuint pos, GLfloat data);

        void Rebuild();
};  


class ColorBuffer
{
   public:
        ColorBuffer(){}
       ~ColorBuffer();
        ColorBuffer(Vec3 *ColorData, GLsizei count);
        ColorBuffer(Vec4 *ColorData, GLsizei count);

        GLuint ID;
        GLint  ElementCount; 

        Vec4 *Data;

    public:
        void Bind();
        void Unbind();
};
class NormalBuffer
{
    public:
        NormalBuffer(){}
       ~NormalBuffer();
        NormalBuffer(Vec3 *NormalData, GLsizei count);

        GLuint ID;
        GLint  ElementCount; 
        Vec3  *Data;

    public:
        void Bind();
        void Unbind();
};


class IndexBuffer
{
    public:
        IndexBuffer(){}
       ~IndexBuffer();
        IndexBuffer(GLuint *data, GLsizei count);

        GLuint ID;
        GLuint ElementCount;
        GLuint *Data;

    public:
        void Bind();
        void Unbind();
};

class TextureBuffer
{
public:
    TextureBuffer();
   ~TextureBuffer();
    TextureBuffer(Texture &img, Vec2 *UVdata, GLsizei count);

    GLuint ID;
    GLuint ElementCount;

    Vec2    *Data;
    Texture Image;
public:

    void Bind();
    void Unbind();
};






class RenderBuffer
{
public:
    RenderBuffer(){}
   ~RenderBuffer();
    RenderBuffer(Shader &shader, GLuint Width, GLuint Height);
    RenderBuffer(Shader &shader ); // FUTURE AFTER RB CLASS IS FINISHED

    Shader RBShader;

    GLuint ID;

    GLuint TexCoordsID;

    void Bind();
    void Unbind();
    void Render();

    void PositionQuad(Vec3 pos);
    void RotateQuad(Vec3 rot);

private:
    void MakeTestQuad();

    GLsizei Width,Height;
    GLsizei WindowWidth,WindowHeight;

    VertexBuffer  *TestQuad;
    IndexBuffer   *TestQuadIBO;

    Vec3 Position, Rotation;
};










class FrameBuffer
{
public:
//    FrameBuffer(){}
   ~FrameBuffer();
    FrameBuffer(Shader &shader, GLuint Width, GLuint Height);
    FrameBuffer(Shader &shader, RenderBuffer rendernb); // FUTURE AFTER RB CLASS IS FINISHED


    Shader FBShader;

    GLuint ID;

    Texture ColorTexture;
    Texture DepthTexture;

    void Bind();
    void Unbind();
    void Render();

    void PositionQuad(Vec3 pos);
    void RotateQuad(Vec3 rot);

    void AttachRenderBuffer(RenderBuffer *rbuffer);
    void AttachTextureBuffer(Texture *texture);
private:
    void MakeTestQuad();

    GLsizei Width,Height;
    GLsizei WindowWidth,WindowHeight;

    VertexBuffer  *TestQuad;
    IndexBuffer   *TestQuadIBO;

    GLuint TexCoordsID;
    Vec3 Position, Rotation;

    GLubyte DrawBufferCount;
};



// ADD ALL VARIOUS BUFFERS TO A SINGLE BUFFER VERTEX, INDEX, COLOR, TEXTURE, NORMALS etc... 
// Into a single Buffer for their type, Bind each buffer than call  Draw Instances


//1.	Uniform Buffer Objects
//2.	Texture Buffer Objects
//3.	Instanced_arrays_ARB

//=============================================================================================================================================
//_______________________________________________________________________________________________________________________________________________________________

//1. pbuffer extension initialization
//2. pbuffer creation
//3. pbuffer binding
//4. pbuffer destruction. 

class PBuffer
{
    PBuffer(){}
    ~PBuffer(){}
    PBuffer( GLuint width, GLuint height);



      GLuint width;
      GLuint height;
};



class VAOBuffer
{
public:
        VAOBuffer();
       ~VAOBuffer(){}

       VertexBuffer    *Vertices;
       IndexBuffer     *Indices;
       NormalBuffer    *Normals;
       TextureBuffer   *Textures;
       ColorBuffer     *Colors;

       void Attach(VertexBuffer  *vertices);
       void Attach(IndexBuffer   *indices);
       void Attach(NormalBuffer  *normals);
       void Attach(TextureBuffer *textures);
       void Attach(ColorBuffer   *color);

       void Bind();
       void Unbind();
};