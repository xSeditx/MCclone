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

class Block
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



class BatchRender
{
public:
    BatchRender(Texture *tex);
   ~BatchRender();

    GLuint ObjectCount;
    GLuint FirstObject;

    std::vector<Vec3>      PositionBuffers;
    std::vector<Vec3>      VertexBuffers;
    std::vector<GLuint>  IndexBuffers;
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


