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
//     Image = new Texture("Test.bmp");
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





