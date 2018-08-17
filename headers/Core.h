#pragma once

#include "Window.h"
#include "Renderer.h"
#include "Texture.h"

#define CHUNK_SIZE   30
#define MAX_OBJECTS  1000


enum BlockType
{
        Grass,
        Dirt,
        BedRock,
        Stone
};

// So I can include a pointer and do not have to move all the information associated with the Blocks around as I 
// manipulate and create them
// Might cause problems with pointers in which custom copy and move constructors need be used.

struct MetaData 
{
    MetaData(GLfloat size, BlockType type) : Size(size), Type(type) {}
    GLfloat Size;
    BlockType Type;
};

class Mesh
{
public:
    Mesh(){}

    Vec3 Position;

    VAOBuffer VAO;
    GLuint VertexCount;

    virtual void Bind(){}
    virtual void Unbind(){}
    virtual void Render(){}
    virtual void OnUpdate(){}
};


class Block :public Mesh
{
public:

   ~Block();
    Block(){}
    Block(Vec3 pos, MetaData &data);

    int ID;

    Vec3 Position,
         Rotation;

    Matrix Transform;

    GLuint VertexCount;

    std::vector<Vec3>    VertexList;
    std::vector<Vec3>    NormalList;
    std::vector<Vec2>    TextureCoords;


    Vec3     Verts[24];
    Vec3     Norms[24];
    Vec2        UV[24];

    std::vector<GLuint>  IndexList;
    GLuint               Indice[36];
    IndexBuffer         *Indices;

    VertexBuffer   *Vertices;
    NormalBuffer   *Normals;
    TextureBuffer  *Textures;

    VAOBuffer      *VAO;

    MetaData       *BlockData;

//   SOMETHING IS CORRUPTED WITH THE COLOR BUFFER STUFF. WHEN I ATTEMPT TO MEMCPY THE COLOR OVER 
//    IT NULLIFIES THE SIZE OF MY INDEXBUFFER FOR WHATEVER REASON AS A RESULT I AM TURNING IT OFF SINCE I DO NOT USE IT AND IT 
//    IS PISSING ME OFF
//    std::vector<Vec4>   ColorList;
//    Vec3                Color[24]; 
//    ColorBuffer           *Colors;
//


    void Bind();
    void Unbind();
    void Render();
    void OnUpdate();


static int BlockCount;

};






class Sphere : public Mesh
{
public:
     Vec3 Position;
     Vec3 Rotation;
     Vec3 Scale;

     int   Mesh_ID;

     float Radius;

public:// OpenGL Stuff

     Sphere(){}  
     Sphere(Vec3 pos, float radius, int sectors);

     Vec3  Vertices[648];
     GLuint Indices[972];
     RGBf  Colors  [648];

     GLuint VertexCount;
     GLuint ColorCount;

     VAOBuffer VAO;

     Shader *SHADER;

     void Set_Position(float x, float y, float z)    {Position = Vec3(x,y,z);}
     void Set_Position(Vec3 pos)                     {Position = pos;}
     void Set_Rotation(float x, float y, float z)    {Rotation = Vec3(x,y,z);}
     void Rotate(float x, float y, float z); 
     void SetRotation(Vec3 rot)                      {Rotation = rot;}

     Vec3 Get_Position(){return Position;}
     Vec3 Get_Rotation(){return Rotation;}

     void Update();
     void Render();

// Static object list
public:
     static std::vector<Sphere*> SphereList;
     static unsigned int SphereCount;
};


// Remember I am going to have to add a Model Transform to make this work
class BatchRender
{
public:
    BatchRender(Texture *tex);
   ~BatchRender();

    GLuint ObjectCount;
    GLuint FirstObject;

    std::vector<Vec3>      PositionBuffers;
    std::vector<Vec3>      VertexBuffers;
    std::vector<GLuint>    IndexBuffers;
    std::vector<Vec2>      TextureBuffers;

    VertexBuffer   *Vertices;
    IndexBuffer    *Indices;
    ColorBuffer    *Colors;
    TextureBuffer  *Textures;
    MetaData       *BlockData;
    NormalBuffer   *Normals;

    GLuint VertexCount;
    GLuint IndexCount;
    GLuint TextureCount;
    Texture *BatchTexture;

    void Bind();
    void Unbind();

    void Build();
    void Submit(Block *object);
    void Render();
};


 


class Sky
{

public:

   ~Sky();
    Sky(Texture *skytext);

    int ID;

    Vec3 Position,
         Rotation;

    std::vector<Vec3>    VertexList;
    std::vector<Vec2>    TextureCoords;


    Vec3     Verts[24];
    Vec3     Norms[24];
    Vec2        UV[24];

    std::vector<GLuint>  IndexList;
    GLuint               Indice[36];

    IndexBuffer         *Indices;


    VertexBuffer   *Vertices;
    TextureBuffer  *Textures;

    VAOBuffer      *VAO;
    MetaData       *BlockData;

    void Bind();
    void Unbind();
    void Render(Vec3 rotation);
    void OnUpdate();

};


