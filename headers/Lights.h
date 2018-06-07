// NEEDS MASSIVE WORK

#pragma once

#include "Window.h"
//#include "Vertex.h"


class ShadowMapFBO
{
    public:
        ShadowMapFBO();
       ~ShadowMapFBO();

        bool Init(unsigned int WindowWidth, unsigned int WindowHeight);
        
        void BindForWriting();
        void BindForReading(GLenum TextureUnit);

    private:
        GLuint m_fbo;
        GLuint m_shadowMap;
};






class LightSource{
public:
    LightSource(Vec4 pos, RGBf alight, RGBf dlight, RGBf slight);
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

     bool CreateShadowMap();
     GLuint ShadowBufferName;
     void CreateMatrices();
     bool ShadowsOn;
private:
    static int NumberOfLights;
};


