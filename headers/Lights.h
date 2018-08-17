// NEEDS MASSIVE WORK

#pragma once

#include "Window.h"
//#include "Vertex.h"
#include"Renderer.h"

class ShadowMap
{
    public:
        ShadowMap();
        ShadowMap(Shader &shader, unsigned int width, unsigned int height);
       ~ShadowMap();
        
        void BindForWriting();

        void BindForReading(GLenum TextureUnit);

        GLuint FBO;
        GLuint Map;

        GLuint Width, 
               Height;

        Shader ShadowRender;

        FrameBuffer *FBuffer;

        void Bind();
        void Unbind();

        void Render();

        void PositionQuad(Vec3 pos) { Position = pos; }
        void RotateQuad(Vec3 rot)   { Rotation = rot; }
       
private:
    void MakeTestQuad();

    VertexBuffer  *TestQuad;
    IndexBuffer   *TestQuadIBO;

    GLuint TexCoordsID;
    Vec3   Position, 
           Rotation;
};



class LightSource{
public:
   ~LightSource();
    LightSource(Shader &shader, Vec4 pos, RGBf alight, RGBf dlight, RGBf slight);
    LightSource(Shader &shader, Vec4 pos, float brightness, float dlight, float slight);

    Vec3 Position;
    RGBf Color;

    enum{
        Spotlight,
        Ambient,
        Directional
    }Type;

    GLint LightNumber;

    void SetAmbient(RGBAf color);
    void SetSpecular(RGBAf color);
    void SetDiffuse(RGBAf color);
    void SetPosition(Vec3 position, Vec3 direction);

    void CreateMatrices();
    
    void Render();

    ShadowMap *Shadow;

    void UpdateStart();
    void UpdateEnd();
    void Delete();
private:
    static int NumberOfLights;

    void LightModel();
    IndexBuffer  Indices;
    VertexBuffer Vertices;
};


