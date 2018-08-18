#pragma once

#include<string>
#include<fstream>
#include<vector>
#include<strstream>
#include"Window.h"



class  FileUtils
{
	public:
        static std::string read_file(const char* filepath)
        {
            FILE *file = fopen(filepath,"rt");
            
            fseek(file,0,SEEK_END);
            
            unsigned long length = ftell(file);
            
            char *data = new char[length + 1];
            memset(data, 0, length +1);
            
            fseek(file,0,SEEK_SET);
            fread(data,1,length,file);
            
            fclose(file);
            
            std::string result(data);
            delete[] data;
            return result;
        }


char *FileData;

        static void Load_OBJ(const char *filename)
        {
        
           std::ifstream file(filename);
           std::vector<Vec3> verts;
           while (!file.eof())
           {
                char line[128];
                file.getline(line, 128);
            
                std::strstream s;
                s << line;
                char junk;
            
                if (line[0] == 'v')
                {
                    Vec3 v;
                    s >> junk >> v.x >> v.y >> v.z;
                    verts.push_back(v);
                }
            
                if (line[0] == 'f')
                {
                    int file[4];
                    s >> junk >> file[0] >> file[1] >> file[2] >> file[3];
                    
                   // meshShip.tris.push_back({ verts[f[0]-1], verts[f[1]-1], verts[f[2]-1], 0.0f, 0.0f, 0.0f, FG_YELLOW });
                  //  meshShip.tris.push_back({ verts[f[0]-1], verts[f[2]-1], verts[f[3]-1], 0.0f, 0.0f, 0.0f, FG_YELLOW });
                }
            }
        }


};



//bool loadOBJ( const char * path, std::vector < glm::vec3 > & out_vertices, std::vector < glm::vec2 > & out_uvs, std::vector < glm::vec3 > & out_normals)
 //   );



//    // ====================================================== Using the Data ==============================================================
//    
//    // Read our .obj file
//    std::vector< Vec3 > vertices;
//    std::vector< Vec2 > uvs;
//    std::vector< Vec3 > normals; // Won't be used at the moment.
//    bool res = LoadModel("cube.obj", vertices, uvs, normals);
//     
//    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vec3), &vertices[0], GL_STATIC_DRAW);
//    
//    


// NOT FUNCTIONING YET
