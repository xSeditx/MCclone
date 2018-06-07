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

        void Bind();
        void Unbind();
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

    public:
        void Bind();
        void Unbind();
};

class TextureBuffer
{
public:
    TextureBuffer();
   ~TextureBuffer();
    TextureBuffer(Texture *img, Vec2 *UVdata, GLsizei count);

    GLuint ID;
    GLuint ElementCount;

    Texture *Image;
public:
    void Bind();
    void Unbind();
};









 
class Renderable3D
{
    Renderable3D();
   ~Renderable3D();


    VertexBuffer   *Vertices;
    TextureBuffer  *Textures;
    ColorBuffer    *Colors;
    NormalBuffer   *Normals;
    IndexBuffer    *Indices;


    Shader ShaderProgram;
};









class Renderer{
public: 
     
     void Submit();
     void Flush_Renderer();

   private:
       vector<mat4> Transformation_Stack;

       void Push(mat4 Mat4);
       mat4 Pop();
};

 









// ADD ALL VARIOUS BUFFERS TO A SINGLE BUFFER VERTEX, INDEX, COLOR, TEXTURE, NORMALS etc... 
// Into a single Buffer for their type, Bind each buffer than call  Draw Instances



//
//1.	Uniform Buffer Objects
//2.	Texture Buffer Objects
//3.	Instanced_arrays_ARB
//
//
//
/*

//=============================================================================================================================================
//_______________________________________________________________________________________________________________________________________________________________



//=============================================================================================================================================
//________________TEST STRUCTURES TO HANDLE THE VAO Issues___________________________________________________________________________________________________________________________

struct VertexFormat
{
  bool enabled;
  int attribute_index;
  float data_type; //Is f32, f64, or int32.
  int num_components;
  bool normalized;
  GLenum type;
  int binding;    //The `bindings` index this attribute gets its data from.
  int *offset;
};

struct VertexBufferBinding// Mesh
{
  Buffer buffer;// VBO
  int  *offset; // Number of Vertices 
  int  *stride;
  int instancing;
};

struct VertexArrayObject
{
  VertexFormat formats[16];
  VertexBufferBinding bindings[16];
};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





// Renderable2d = BatchSprite
class Renderable2D{
public:
    Renderable2D::Renderable2D();
    Renderable2D::~Renderable2D();

    Vec3 Position;
    Vec2 Size;
    Vec4 Color;
    vector<VertexData> VertexArray;
    IndexBuffer *IBO;
    GLuint VBO;

    unsigned int IndexCount;
    Shader &SHADER;


};



class Renderer2D{
public:
    virtual void submit(const Renderable2D *renderable);
    virtual void flush();
};














#define RENDERER_MAX_SPRITES 10000
#define RENDERER_VERTEX_SIZE   sizeof(VertexData)
#define RENDERER_SPRITE_SIZE RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE RENDERER_MAX_SPRITES * 6
struct VertexData{
    Vec3 Vertex;
    Vec3 Color;
}; // 28 Bytes Currently
 


class BatchRender2D: public Renderer2D{
private:
    //VertexArray VAO;
    IndexBuffer IBO;
    GLsizei IndexCount;
    GLuint VBO;
public:
    void submit(const Renderable2D *BatchSprite) override;
    void flush() override;

};




BatchSprite::BatchSprite(){}

BatchSprite::~BatchSprite(){
    delete(IBO);
}




void BatchSprite::Init(){
    
}
*/