#pragma once

#include"Window.h"
#include<vector>
#include"Shader.h"

struct Vertex
{
        Vec3 Position;
        Vec3 Normals;
        Vec2 TexCoords;
};

struct Texture
{
        GLuint ID;
        const char *type;
};

class Mesh
{
    public:
        std::vector<Vertex> Vertices;
        std::vector<GLuint> Indices;
        std::vector<Texture> Textures;
        
        Mesh(){}
        Mesh(std::vector<Vertex>vertices,std::vector<GLuint> indices, std::vector<Texture>textures);
        
        void Render(Shader shader);
        
        GLuint VBO,
               EBO;
        
        void SetupMesh();
        
      // uniform sampler2D Texture_diffuse1;
      // uniform sampler2D Texture_diffuse2;
      // uniform sampler2D Texture_diffuse3;
      // uniform sampler2D Texture_specular1;
      // uniform sampler2D Texture_specular2;
        
        std::vector < Vec3 > out_vertices;
        std::vector < Vec2 > out_uvs;
        std::vector < Vec3 > out_normals;
        bool LoadModel(const char* path);
};