#pragma once
#include"Window.h"
#include<vector>



class Mesh
{
    public:


    std::vector < Vec3 > out_vertices;
    std::vector < Vec2 > out_uvs;
    std::vector < Vec3 > out_normals;
    bool LoadModel(const char* path);
};