#pragma once

#include "Window.h"
#include "Renderer.h"
#include "Texture.h"

#define CHUNK_SIZE   6
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
    MetaData(GLshort size, BlockType type) : Size(size), Type(type) {}
    GLshort Size;
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

    std::vector<Vec3> VertexList;
    Vec3     Verts[24];

    std::vector<Vec3> NormalList;
    Vec3     Norms[24];

    std::vector<Vec4> ColorList;
    Vec3     Color[24];

    std::vector<GLuint>IndexList;
    GLuint Indice[36];

    std::vector<Vec2> TextureCoords;
    Vec2     UV[24];


    VertexBuffer   *Vertices;
    IndexBuffer    *Indices;
    ColorBuffer    *Colors;
    TextureBuffer  *Textures;
    MetaData       *BlockData;
    NormalBuffer   *Normals;


    void Bind();
    void Unbind();
    void Render();
    void OnUpdate();



static int BlockCount;

};



class BatchRender
{
public:
    BatchRender();
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
    
    void Bind();
    void Unbind();

    void Init();
    void Submit(Block *object);
    void Render();
};