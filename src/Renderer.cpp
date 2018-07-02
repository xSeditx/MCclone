#include"Renderer.h"
#include"Texture.h"

extern Texture *BlockTexture;

// [ TIP: ]
// In case you don't have VAOs, you can still render pretty much in the same way. Just remove the VAO calls and remember
// to always reset the vertex format before drawing. I.e.: glVertexAttribPointer.

//==================================================================================================================================================
//__________________________________ VERTEX BUFFER CLASS ___________________________________________________________________________________________

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
        glBufferData(GL_ARRAY_BUFFER, ElementCount * sizeof(Vec3), Vertexdata, GL_DYNAMIC_DRAW) ; 
    glBindBuffer(GL_ARRAY_BUFFER,0);
}
void VertexBuffer::Bind()
{
  //  glEnableVertexAttribArray(VERTEX_ATTRIB);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
        glVertexPointer( 3, GL_FLOAT, 0, (char *) NULL);
            glEnableClientState(GL_VERTEX_ARRAY);
         _GL(glVertexAttribPointer(VERTEX_ATTRIB, 3, GL_FLOAT, GL_FALSE, 0,  (char *) NULL));
       
}
void VertexBuffer::Unbind(){

          glDisableClientState(GL_VERTEX_ARRAY);
   // glDisableVertexAttribArray(VERTEX_ATTRIB);
    glBindBuffer(GL_ARRAY_BUFFER,0);
}

void VertexBuffer::Lock(GLenum access)
{
        Data = (Vec3 *)glMapBuffer(ID, access);
}
void VertexBuffer::Unlock()
{
        glUnmapBuffer(ID);
}

void VertexBuffer::Rebuild()
{    //glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexPositions), &fNewData[0]);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
        glBufferSubData(GL_ARRAY_BUFFER, 0,ElementCount * sizeof(Vec3), Data) ; 
    glBindBuffer(GL_ARRAY_BUFFER,0);
}

//==================================================================================================================================================
//__________________________________ INDEX BUFFER CLASS ____________________________________________________________________________________________

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
  //  glEnableVertexAttribArray();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ID);
        glIndexPointer(GL_FLOAT, 0, (void *) NULL);
        glEnableClientState(GL_INDEX_ARRAY);
}
void IndexBuffer::Unbind()
{
        glDisableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}


//==================================================================================================================================================
//__________________________________ TEXTURE BUFFER CLASS __________________________________________________________________________________________
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

//glEnableVertexAttribArray(TEXTURE_ATTRIB);
      glBindBuffer(GL_ARRAY_BUFFER, ID);      

//glVertexAttribPointer(TEXTURE_ATTRIB, 2, GL_FLOAT, GL_FALSE, 0,  (char *) NULL);
        glTexCoordPointer(2, GL_FLOAT, 0, (char *) NULL);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}
void TextureBuffer::Unbind()
{
      //  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableVertexAttribArray(TEXTURE_ATTRIB);
    glBindBuffer(GL_ARRAY_BUFFER,0);
}
 

//==================================================================================================================================================
//__________________________________ COLOR BUFFER CLASS ____________________________________________________________________________________________
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
        glBufferData(GL_ARRAY_BUFFER, ElementCount * sizeof(Vec4), ColorData, GL_STATIC_DRAW) ; 
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
 

//==================================================================================================================================================
//__________________________________ NORMAL BUFFER CLASS ___________________________________________________________________________________________

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


//==================================================================================================================================================
//__________________________________ FRAME BUFFER CLASS ____________________________________________________________________________________________

// There are two types of framebuffer-attachable images; texture images and renderbuffer images. If an image of a texture 
//     object is attached to a framebuffer, OpenGL performs "render to texture". And if an image of a renderbuffer object is
//     attached to a framebuffer, then OpenGL performs "offscreen rendering".

// Texture = Read
// RenderBuffer = Offscreen Rendering


// Attach different Textures or Render buffer with Different Bitmask to get different colors
// Depth and Stencil buffer is also an Option.

// Use: Multiple ColorBuffers   [ GL_COLOR_ATTACHMENT0,n....., ] 
// One Depth attachment point   [ GL_DEPTH_ATTACHMENT   ]
// One Stencil attachment point [ GL_STENCIL_ATTACHMENT ]

// Notice that the framebuffer object itself does not have any image storage(array) in it, 
// but it has only multiple attachment points.

FrameBuffer::~FrameBuffer()
{
 //   if(&ColorTexture != nullptr) glDeleteTextures(1, &ColorTexture.ID);
  //  if(&DepthTexture != nullptr) glDeleteTextures(1, &DepthTexture.ID);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
    glDeleteFramebuffersEXT(1, &ID);
}



FrameBuffer::FrameBuffer(Shader *shader, GLuint  width, GLuint height)
    : Width(width),
      Height(height), DrawBufferCount(0)
{
    FBShader = shader;
    MakeTestQuad();

    glGenFramebuffersEXT(1,&ID);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, ID);
        
        ColorTexture.GenColorTexture(width, height);
          DepthTexture.GenDepthTexture(width, height);
           // RenderBuffer RB(shader,width,height);
//           Attach Color texture to FBO  && Attach depth texture to FBO

          //  AttachRenderBuffer(&RB);
            glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, ColorTexture.ID, 0);
     const GLenum draw_buffers[] = { GL_COLOR_ATTACHMENT0_EXT };
glDrawBuffers(sizeof(draw_buffers)/ sizeof(draw_buffers[0]), draw_buffers);       

            glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT , GL_TEXTURE_2D, DepthTexture.ID, 0);

            if( glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT) != GL_FRAMEBUFFER_COMPLETE_EXT)
            {
                std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
                glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0); 
                return;
            }
 
            DepthTexture.Unbind();
        ColorTexture.Unbind();
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0); 
}


void FrameBuffer::Bind()
{
    FBShader->Enable();

    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, ID);
        glClearColor(1,0,0,1.0f);
		glClearDepth(1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
     glDrawBuffer(GL_FRONT_AND_BACK);
        
}
void FrameBuffer::Unbind()
{

  //  glViewport(0,0,WindowWidth, WindowHeight);

    FBShader->Disable();
    glBindFramebufferEXT(GL_FRAMEBUFFER, 0);

}
void FrameBuffer::Render()
{
#if 1
glPushMatrix();
glMatrixMode(GL_PROJECTION);
glPushMatrix();
glLoadIdentity();
glMatrixMode(GL_MODELVIEW);
glPushMatrix();
glLoadIdentity();
glMatrixMode(GL_TEXTURE);
glPushMatrix();
glLoadIdentity();

glEnable(GL_TEXTURE_2D);

glBindTexture(GL_TEXTURE_2D,  ColorTexture.ID);
glBegin(GL_QUADS);
glTexCoord2f(0.0, 0.0); glVertex2f(-1.0, -1.0);
glTexCoord2f(0.0, 1.0); glVertex2f(-1.0,  -0.5);
glTexCoord2f(1.0, 1.0); glVertex2f( -0.5,  -0.5);
glTexCoord2f(1.0, 0.0); glVertex2f( -0.5, -1.0);
glEnd();

glBindTexture(GL_TEXTURE_2D, DepthTexture.ID);
glBegin(GL_QUADS);
glTexCoord2f(0.0, 0.0); glVertex2f(-0.5, -1.0);
glTexCoord2f(0.0, 1.0); glVertex2f(-0.5,  -0.5);
glTexCoord2f(1.0, 1.0); glVertex2f( -0.0,  -0.5);
glTexCoord2f(1.0, 0.0); glVertex2f( -0.0, -1.0);
glEnd();



glMatrixMode(GL_TEXTURE);
glPopMatrix(); 
glMatrixMode(GL_MODELVIEW);
glPopMatrix();
glMatrixMode(GL_PROJECTION);
glPopMatrix();
glMatrixMode(GL_MODELVIEW);
glPopMatrix();

glBindTexture(GL_TEXTURE_2D, 0);
#else
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
            
         // glBindTexture(GL_TEXTURE_2D, DepthTexture.ID);
            glBindTexture(GL_TEXTURE_2D, ColorTexture.ID);           
                glBindBuffer(GL_ARRAY_BUFFER, TexCoordsID);
                glTexCoordPointer(2, GL_FLOAT, 0, (char *) NULL);
                glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                    
                    glDrawElements(GL_TRIANGLES, TestQuadIBO->ElementCount , GL_UNSIGNED_INT, nullptr);
                    
                glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindTexture(GL_TEXTURE_2D, 0);
            
            TestQuadIBO->Unbind();
        TestQuadIBO->Unbind();       
    glPopMatrix();
#endif

}

void FrameBuffer::PositionQuad(Vec3 pos)
{
    Position = pos;
}
void FrameBuffer::RotateQuad(Vec3 rot)
{
    Rotation = rot;
}
void FrameBuffer::MakeTestQuad()
{
    Position = Vec3(0,0,0);
    Rotation = Vec3(0,0,0);

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

    glGenBuffers(1, &TexCoordsID);
        glBindBuffer(GL_ARRAY_BUFFER, TexCoordsID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vec2) * 4 , UVs, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void FrameBuffer::AttachRenderBuffer(RenderBuffer *rbuffer)
{
    glFramebufferRenderbufferEXT(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, rbuffer->ID);
}


void FrameBuffer::AttachTextureBuffer(Texture *texture)
{
    glBindFramebufferEXT(GL_FRAMEBUFFER, ID);
    texture->Bind();
    if(texture->Width != Width || texture->Height != Height)
    {
        Print( "Error Line:" << __LINE__);
        Print( "Can not Attach Texture to FrameBuffer Object Number : " << ID);
        return;
    }
//    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, texture.Width, texture.Height, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + DrawBufferCount, texture->ID, 0);
}













//glRenderbufferStorageMultisample() creates a renderbuffer image for multisample anti-aliasing rendering mode.


//==================================================================================================================================================
//__________________________________ RENDER BUFFER CLASS ___________________________________________________________________________________________
RenderBuffer::~RenderBuffer()
{
    glBindRenderbufferEXT(GL_RENDERBUFFER, 0);
    glDeleteRenderbuffersEXT(1, &ID);
}
RenderBuffer::RenderBuffer(Shader *shader, GLuint width, GLuint height)
    : Width(width),
      Height(height)
{
    RBShader = shader;
    MakeTestQuad();

    glGenRenderbuffersEXT(1,&ID);
    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, ID);
    glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_RGBA, Width, Height);        
//           Attach Color texture to FBO  && Attach depth texture to FBO
//            glRenderbufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, ColorTexture.ID, 0);
//            glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT , GL_TEXTURE_2D, DepthTexture.ID, 0);
//            if( glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT) != GL_FRAMEBUFFER_COMPLETE_EXT)
//            {
//                std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
//                glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0); 
//            }
        
  //  glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0); 
}
void RenderBuffer::Bind()
{
 
    RBShader->Enable();
    glBindRenderbufferEXT(GL_RENDERBUFFER, ID);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
 
        
}

void RenderBuffer::Unbind()
{

    RBShader->Disable();
    glBindRenderbufferEXT(GL_RENDERBUFFER, 0);
}
void RenderBuffer::Render()
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
            
//           glBindTexture(GL_TEXTURE_2D, DepthTexture.ID);
            
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

void RenderBuffer::PositionQuad(Vec3 pos)
{
    Position = pos;
}
void RenderBuffer::RotateQuad(Vec3 rot)
{
    Rotation = rot;
}
void RenderBuffer::MakeTestQuad()
{
    Position = Vec3(0,0,0);
    Rotation = Vec3(0,0,0);

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

    glGenBuffers(1, &TexCoordsID);
        glBindBuffer(GL_ARRAY_BUFFER, TexCoordsID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vec2) * 4 , UVs, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}








//1. pbuffer extension initialization
//2. pbuffer creation
//3. pbuffer binding
//4. pbuffer destruction. 







VAOBuffer::VAOBuffer()
{
        Vertices = nullptr;
        Normals  = nullptr;
        Textures = nullptr;
        Indices  = nullptr;
}


void VAOBuffer::Attach(VertexBuffer  *vertices)
{


    Vertices = vertices;
}
void VAOBuffer::Attach(IndexBuffer   *indices)
{

    Indices = indices;
}
void VAOBuffer::Attach(NormalBuffer  *normals)
{
    Normals = normals;
}
void VAOBuffer::Attach(TextureBuffer *texture)
{
    Textures = texture;
}
void VAOBuffer::Bind()
{
      if(Vertices)  Vertices->Bind();
      if(Indices)    Indices->Bind();
      if(Normals)    Normals->Bind();
      if(Textures)  Textures->Bind();
}
void VAOBuffer::Unbind()
{
      if(Vertices)  Vertices->Unbind();
      if(Indices)    Indices->Unbind();
      if(Normals)    Normals->Unbind();
      if(Textures)  Textures->Unbind();
}