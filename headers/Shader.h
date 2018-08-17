#pragma once
#include "Window.h"
#include<vector>

enum Uniformtype
{
    Float,
    Integer,
    Vector2,
    Vector3,
    Vector4,
    Matrix4
};


struct Uniform
{

    Uniform(Uniformtype type, char *name, void *value)
        :Type(type), Name(name), Value(value){}
    Uniform(){}

    Uniformtype Type;
    char *Name;
    void *Value;
};



class Shader{

    private:
       GLuint m_ShaderID;
       const char* m_Vertpath;
       const char* m_Fragpath;
       
    public:
        Shader(const char* vertPath, const char* fragPath);
        Shader();

       ~Shader();
       
       void Enable();
       void Disable();

       std::vector<Uniform> Uniforms;


       GLint GetUniformLocation(GLchar *);
       
       void  SetUniform1f    ( GLchar *name, float value);
       void  SetUniform1Int  ( GLchar *name,   int value);
             
       void  SetUniform2f    ( GLchar *name,  Vec2 &vector);
       void  SetUniform3f    ( GLchar *name,  Vec3 &vector);
       void  SetUniform4f    ( GLchar *name,  Vec4 &vector);
       void  SetUniformMat4  ( GLchar *name,  Matrix &matrix);
      
       void Delete();

       void AttachUniform(GLchar *name, Uniformtype type, void *variable);
private:
       GLuint Load();
};

extern void Load_Shader(GLenum t,const char* code, GLuint *id);