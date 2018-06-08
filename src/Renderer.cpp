#include"Renderer.h"
#include"Texture.h"


extern Texture *BlockTexture;

// In case you don't have VAOs, you can still render pretty much in the same way. Just remove the VAO calls and remember to always reset the
//    vertex format before drawing. I.e.: glVertexAttribPointer.

//===================================================================================================================================================
//__________________________________ VERTEX BUFFER CLASS _____________________________________________________________________________________________

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &ID);
}
VertexBuffer::VertexBuffer(Vec3 *Vertexdata,GLsizei vcount)
            : ElementCount(vcount),
              ID(0) 
{
    Data = new Vec3[vcount];
    Data = Vertexdata;

    glGenBuffers(1 , &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
        glBufferData(GL_ARRAY_BUFFER, ElementCount * sizeof(Vec3), Vertexdata, GL_STATIC_DRAW) ; 
    glBindBuffer(GL_ARRAY_BUFFER,0);
}
void VertexBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glVertexAttribPointer(VERTEX_ATTRIB, 3, GL_FLOAT, GL_FALSE, 0,  (char *) NULL);
        glVertexPointer( 3, GL_FLOAT, 0, (char *) NULL);
            glEnableClientState(GL_VERTEX_ARRAY);
}
void VertexBuffer::Unbind(){
            glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER,0);
}

//===================================================================================================================================================
//__________________________________ INDEX BUFFER CLASS _____________________________________________________________________________________________


IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &ID);
}
IndexBuffer::IndexBuffer(GLuint *data, GLsizei count)
           : ElementCount(count),
             ID(0)
{
        Data = new GLuint[count];
        Data = data;

        glGenBuffers(1,&ID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}
void IndexBuffer::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ID);
        glIndexPointer(GL_FLOAT, 0, (void *) NULL);
        glEnableClientState(GL_INDEX_ARRAY);
}
void IndexBuffer::Unbind()
{
        glDisableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}


//===================================================================================================================================================
//__________________________________ TEXTURE BUFFER CLASS _____________________________________________________________________________________________
TextureBuffer::~TextureBuffer()
{
    delete(Image);
    glDeleteBuffers(1, &ID);   
}
TextureBuffer::TextureBuffer(Texture *img, Vec2 *data,  GLsizei count)
             : ElementCount(count) 
{
    Data = new Vec2[count];
    Data = data;

    Image = img;
  
// This creates the UV Buffer
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vec2) * count , data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void TextureBuffer::Bind()
{
    Image->Bind();
    glBindBuffer(GL_ARRAY_BUFFER, ID);
        glTexCoordPointer(2, GL_FLOAT, 0, (char *) NULL);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}
void TextureBuffer::Unbind()
{
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER,0);
}
 

//===================================================================================================================================================
//__________________________________ COLOR BUFFER CLASS _____________________________________________________________________________________________
ColorBuffer::~ColorBuffer()
{
        glDeleteBuffers(1, &ID);
}

ColorBuffer::ColorBuffer(Vec4 *ColorData, GLsizei count)
           : ElementCount(count),
             ID(0)
{
    Data = new Vec4[count];
    Data = ColorData;

    glGenBuffers(1 , &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
        glBufferData(GL_ARRAY_BUFFER,ElementCount * sizeof(Vec4), ColorData, GL_STATIC_DRAW) ; 
    glBindBuffer(GL_ARRAY_BUFFER,0);// Unbind BUFFER_ID since its now bound to the ID;
}
ColorBuffer::ColorBuffer(Vec3 *ColorData, GLsizei count)
           : ElementCount(count),
             ID(0)
{
    glGenBuffers(1 , &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
        glBufferData(GL_ARRAY_BUFFER,ElementCount * sizeof(Vec3), ColorData, GL_STATIC_DRAW) ; 
    glBindBuffer(GL_ARRAY_BUFFER,0);// Unbind BUFFER_ID since its now bound to the ID;
}
void ColorBuffer::Bind()
{
    glBindBuffer(GL_COLOR_ARRAY, ID);// GL_ARRAY_BUFFER
        glColorPointer( 3, GL_FLOAT, 0, (char *) NULL);
            glEnableClientState(GL_COLOR_ARRAY);
}
void ColorBuffer::Unbind(){
            glDisableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER,0);
} 
 

//===================================================================================================================================================
//__________________________________ NORMAL BUFFER CLASS _____________________________________________________________________________________________

NormalBuffer::~NormalBuffer()
{
    glDeleteBuffers(1, &ID);
}
NormalBuffer::NormalBuffer(Vec3 *NormalData, GLsizei count)
            : ElementCount(count),
              ID(0)
{
    glGenBuffers(1 , &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
        glBufferData(GL_ARRAY_BUFFER, ElementCount * sizeof(Vec3), NormalData, GL_STATIC_DRAW) ; 
    glBindBuffer(GL_ARRAY_BUFFER,0); 
}
void NormalBuffer::Bind()
                
{
    glBindBuffer(GL_ARRAY_BUFFER, ID); // 
        glNormalPointer(GL_FLOAT, 0, (void *) NULL);
            glEnableClientState(GL_NORMAL_ARRAY);
}
void NormalBuffer::Unbind()
{
        glDisableClientState(GL_NORMAL_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER,0);
}









FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffersEXT(1, &ID);
}
FrameBuffer::FrameBuffer(Shader *shader)
{
    Position = Vec3(0,0,0);
    Rotation = Vec3(0,0,0);

    FBShader = shader;

    float Size = 10;
    Vec3 quad[] = 
    {
        Vec3( Size,  -10.0f,  Size),
        Vec3(-Size,  -10.0f,  Size),
        Vec3(-Size,  -10.0f, -Size),
        Vec3( Size,  -10.0f, -Size),
    };

    Vec4 color[] = 
    {
        Vec4(  0.0f,  0.0f, 0.0f,   0.0f),
        Vec4(  0.0f,  0.0f, 0.0f,   0.0f),
        Vec4(  0.0f,  0.0f, 0.0f,   0.0f),
        Vec4(  0.0f,  0.0f, 0.0f,   0.0f),
    };

    GLuint quadIB[] = 
    {
        0,1,2,  0,2,3
    };
    Vec2 UVs[] = 
    {
        Vec2(0.0f, 1.0f),
        Vec2(0.0f, 0.0f),
        Vec2(1.0f, 0.0f),
        Vec2(1.0f, 1.0f)
    };

    TestQuad    = new VertexBuffer(quad,4);
    TestQuadIBO = new IndexBuffer(quadIB,6);


    glGenFramebuffersEXT(1,&ID);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, ID);
  
        glGenTextures(1, &TextureID);
        glBindTexture(GL_TEXTURE_2D, TextureID);
            glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, 640, 640, 0, GL_RGB, GL_UNSIGNED_INT, NULL);
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            
            glFramebufferTexture2DEXT (GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, TextureID, 0);
            
            if( glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT) != GL_FRAMEBUFFER_COMPLETE_EXT)
            {
                std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
                glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0); 
            }
        glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0); 

    glGenBuffers(1, &TexCoordsID);
        glBindBuffer(GL_ARRAY_BUFFER, TexCoordsID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vec2) * 4 , UVs, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
 


void FrameBuffer::Bind()
{
    FBShader->Enable();
    glBindFramebufferEXT(GL_FRAMEBUFFER, ID);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_ACCUM_BUFFER_BIT);
}

void FrameBuffer::Unbind()
{
    FBShader->Disable();
    glBindFramebufferEXT(GL_FRAMEBUFFER, 0);
}
void FrameBuffer::Render()
{
    glPushMatrix();
        glMatrixMode(GL_MODELVIEW);
    
        glTranslatef(Position.x,
                     Position.y, 
                     Position.z);
        glRotatef(Rotation.x, 1.0f, 0.0f, 0.0f);
        glRotatef(Rotation.y, 0.0f, 1.0f, 0.0f);
        glRotatef(Rotation.z, 0.0f, 0.0f, 1.0f);
    
        TestQuad->Bind();
            TestQuadIBO->Bind();
            
            glBindTexture(GL_TEXTURE_2D, TextureID);
            
                glBindBuffer(GL_ARRAY_BUFFER, TexCoordsID);
                glTexCoordPointer(2, GL_FLOAT, 0, (char *) NULL);
                glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                    
                    glDrawElements(GL_TRIANGLES, TestQuadIBO->ElementCount , GL_UNSIGNED_INT, nullptr);
                    
                glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindTexture(GL_TEXTURE_2D, 0);
            
            TestQuadIBO->Unbind();
        TestQuadIBO->Unbind();       
    glPopMatrix();
}

void FrameBuffer::PositionQuad(Vec3 pos)
{
    Position = pos;
}
void FrameBuffer::RotateQuad(Vec3 rot)
{
    Rotation = rot;
}





//===================================================================================================================================================
//__________________________________ Experimental BUFFER CLASS ____________________________________________________________________________________________
// Going to possibly Simulate a VAO in software to make future compatibility easier

//===================================================================================================================================================
//__________________________________ RENDERER CLASS _________________________________________________________________________________________________
void Renderer::Push(mat4 Mat4){
        Transformation_Stack.push_back(Mat4);
}
 mat4 Renderer::Pop(){
        mat4 ret = Transformation_Stack.back();
        Transformation_Stack.pop_back();
        return ret;
}
 

 
Renderable3D::Renderable3D() // CREATE
{
     Vertices = nullptr;
     Textures = nullptr;
     Colors   = nullptr;
     Normals  = nullptr;
     Indices  = nullptr;
}
Renderable3D::~Renderable3D() // DELETE
{
    if( Vertices ) delete(Vertices);
    if( Textures ) delete(Textures);
    if( Colors   ) delete(Colors  );
    if( Normals  ) delete(Normals );
    if( Indices  ) delete(Indices );
}





