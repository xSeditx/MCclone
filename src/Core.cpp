   
#include"core.h"

int Block::BlockCount = 0;
// You are going to see a bit of a mess here as I just setup the Batcher to handle all the Vertices and have not cleaned out the Code I am not really using
// This means you are going to see multiple forms of buffers and Arrays all carrying the same data, I just finished getting that up and running when I started playing 
// With the buffer objects



Block::~Block()
{
    delete(Vertices); 
    delete(Indices );
    delete(Textures); 
    delete(BlockData);
    delete(Normals  );
}


// Each Block is made of seperate buffers for each attribute so that later on I can build a mess from whatever forms of data
// I desire being Textures, Colors, Vertices etc... The batcher takes all that data, Offsets the position of the Vertex and renders
// it into a single Draw call. Its still far from finished as it does not manage textures or anything but it was an experiment
// I performed after I found I could not perform instancing using glDrawElementsArrays() due to the version of OpenGL I am using


Block::Block(Vec3 pos, MetaData &blockdata)
     : Position(pos) ,  
       VertexCount(0),
       ID(BlockCount++)
{
//f_TRACE(Print("Block Constructor"));

    GLfloat size = (blockdata.Size);

    Vec3 V[] = 
    {                                                   
            Vec3(-size,-size, size), // FRONT    // 0                                             
            Vec3( size,-size, size),             // 1                                    
            Vec3( size, size, size),             // 2                                    
            Vec3(-size, size, size),             // 3                                    
                                                                                     
            Vec3( size, size, size), // RIGHT    // 4    2                                        
            Vec3( size, size,-size),             // 5                                    
            Vec3( size,-size,-size),             // 6                                    
            Vec3( size,-size, size),             // 7    1                                
                                                        
            Vec3(-size,-size,-size), // BACK     // 8                                            
            Vec3( size,-size,-size),             // 9    6                               
            Vec3( size, size,-size),             // 10   5                                
            Vec3(-size, size,-size),             // 11
                                                    
            Vec3(-size,-size,-size), // LEFT     // 12   8                                        
            Vec3(-size,-size, size),             // 13   7                              
            Vec3(-size, size, size),             // 14   3                                
            Vec3(-size, size,-size),             // 15  11                                
                                                       
            Vec3( size, size, size), // TOP      // 16   2                                      
            Vec3(-size, size, size),             // 17   3                                
            Vec3(-size, size,-size),             // 18   11                                
            Vec3( size, size,-size),             // 19   5                                
                                                        
            Vec3(-size,-size,-size), // BOTTOM   // 20   8                                   
            Vec3( size,-size,-size),             // 21   9                          
            Vec3( size,-size, size),             // 22   1                          
            Vec3(-size,-size, size),             // 23   0                               
    };

    Vec2 UVs[] = 
    {                                                   
            Vec2(0.00f, 0.66f),  // FRONT  // 0                                             
            Vec2(0.00f, 0.33f),            // 1                                             
            Vec2(0.25f, 0.33f),            // 2                                             
            Vec2(0.25f, 0.66f),            // 3                                             
                                                          
            Vec2(0.25f, 0.33f),  // RIGHT  // 4                                             
            Vec2(0.50f, 0.33f),            // 5                                             
            Vec2(0.50f, 0.00f),            // 6                                             
            Vec2(0.25f, 0.00f),            // 7                                             
                                           
            Vec2(0.75f, 0.66f),  // BACK   // 8                                             
            Vec2(0.75f, 0.33f),            // 9                                             
            Vec2(0.50f, 0.33f),            // 10                                             
            Vec2(0.50f, 0.66f),            // 11
                                            
            Vec2(0.50f, 1.00f),  // LEFT   // 12                                             
            Vec2(0.25f, 1.00f),            // 13                                             
            Vec2(0.25f, 0.66f),            // 14                                             
            Vec2(0.50f, 0.66f),            // 15                                             
 
            Vec2(0.25f, 0.33f),  // TOP    // 16                                             
            Vec2(0.25f, 0.66f),            // 17                                             
            Vec2(0.50f, 0.66f),            // 18                                             
            Vec2(0.50f, 0.33f),            // 19     

            Vec2(0.75f, 0.66f),  // BOTTOM // 20                                             
            Vec2(0.75f, 0.33f),            // 21                                             
            Vec2(1.00f, 0.33f),            // 22                                             
            Vec2(1.00f, 0.66f),            // 23                 
    };

    GLuint Indexdata[]=
    { 
        0,1,2,    0,2,3,     // FRONT
        6,5,4,    4,7,6,     // RIGHT 
        10,9,8,   8,11,10,   // BACK
        12,13,14, 12,14,15,  // LEFT
        18,17,16, 16,19,18,  // TOP
        20,21,22, 20,22,23   // BOTTOM
    };
    
// Color stuff should start here, been removed temporarily 

    Vec3 NormalData[24];

    for_loop(Index, 24)
    {
        float x = V[Index].x;
        float y = V[Index].y;
        float z = V[Index].z;

        float  magnitude = sqrt(Squared(x) + Squared(y) + Squared(z));

        if (magnitude != 0)
        {
            x /= magnitude;
            y /= magnitude;
            z /= magnitude;
        }
        NormalData[Index] =   Vec3(x,y,z); //  Vec3(RANDOM(2)-1,RANDOM(2)-1,RANDOM(2)-1);//
    }

    for_loop(Index, 24)
    {
        VertexList.push_back(V[Index]);
        TextureCoords.push_back(UVs[Index]);
        NormalList.push_back(NormalData[Index]);
    }

    for_loop(Index, 36)
    {
        IndexList.push_back(Indexdata[Index]);
    }

// Averages all the normals so Each Faces Vertices have normals facing straight out to prevent interpolation of the light
// Across the block

// for(int Index = 0; Index < 24 ; Index += 4)
// {
//     Vec3 Norm =  NormalData[Index]   +
//                  NormalData[Index+1] +
//                  NormalData[Index+2] +
//                  NormalData[Index+3];
//
//     Norm /= 4; 
//
//     NormalData[Index]   = Norm;
//     NormalData[Index+1] = Norm;
//     NormalData[Index+2] = Norm;
//     NormalData[Index+3] = Norm;
//
// }
//

    
   Vertices = new VertexBuffer(&VertexList[0], 24);
   Indices  = new IndexBuffer (&IndexList[0] , 36);

   if(blockdata.Type == Dirt)   Textures = new TextureBuffer(BlockTexture , &TextureCoords[0], 24);
   if(blockdata.Type == Stone)  Textures = new TextureBuffer(StoneTexture , &TextureCoords[0], 24);
   Normals  = new NormalBuffer (Norms, 24);

   VAO = new VAOBuffer();

   VAO->Attach(Vertices);
   VAO->Attach(Indices);
   VAO->Attach(Normals);
   VAO->Attach(Textures);


   std::memcpy(&UV     ,          &UVs,  sizeof(UVs));
   std::memcpy(&Indice ,     Indexdata,  sizeof(Indexdata));
   std::memcpy(&Norms  ,   &NormalData,  sizeof(NormalData));
   std::memcpy(&Verts  ,            &V,  sizeof(V));




}

void Block::Bind()
{
    VAO->Bind();
}
void Block::Unbind()
{
     VAO->Unbind();   
}
void Block::Render()
{
//f_TRACE(Print("Block Render"));  // A Debug Option I designed a while ago that I can turn on and it informs me what functions are being called
// Normal Render
// Displays the Summed Normals acros a polygon. Needs a bit of work but currently need to work on my Batch Render;

    Vec3 Pos1, Pos2, Offset;

    glBegin(GL_LINES);
        for(int Index = 0; Index < 36; Index++)
        {
        
            Pos1   = VertexList[IndexList[Index]]  + Position;
            Offset = Norms[IndexList[Index]];
 
            Pos2 = Pos1 + Offset;
            glVertex3f(Pos1.x, Pos1.y, Pos1.z);
            glVertex3f(Pos2.x, Pos2.y, Pos2.z);
        }
    glEnd();
 

    glPushMatrix();
    
        glTranslatef(Position.x, Position.y, Position.z);
        glRotatef(Rotation.x, 1.0f, 0.0f, 0.0f);
        glRotatef(Rotation.y, 0.0f, 1.0f, 0.0f);
        glRotatef(Rotation.z, 0.0f, 0.0f, 1.0f);

        Bind();
            glDrawElements(GL_TRIANGLES, Indices->ElementCount , GL_UNSIGNED_INT, nullptr);
        Unbind();
    glPopMatrix();
}



// As stated above, All experimental below. I don't really use it right now but for rendering the scene quickly to get an Image
// to the FBO it made it quick and easy.
// I am sooner or later going to have a system setup that manages all the different batches with different textures and other states
// but for not this is sufficient for testing other aspects of the engine.


BatchRender::BatchRender(Texture *texture)
    :ObjectCount(0),
    FirstObject(0),
     IndexCount(0), 
    VertexCount(0), 
    TextureCount(0), BatchTexture(texture)
{
}
BatchRender::~BatchRender()
{
}

void BatchRender::Bind()
{
    Vertices->Bind();
    Textures->Bind();
     Indices->Bind();
}
void BatchRender::Unbind()
{
    Vertices->Unbind();
    Textures->Unbind();
     Indices->Unbind();
}

void BatchRender::Render()
{
    glPushMatrix();
        Bind();
            glDrawElements(GL_TRIANGLES, Indices->ElementCount , GL_UNSIGNED_INT, nullptr);
        Unbind();
    glPopMatrix();
}
void BatchRender::Submit(Block *object)
{
    if(object->Vertices->ID < FirstObject) FirstObject = object->Vertices->ID;
    
    ObjectCount++;

    PositionBuffers.push_back(object->Position);

    std::vector<Vec3> TransformedVerts;
    std::vector<GLuint> TransformedIndices;
    std::vector<Vec2> TransformedUV;

    for_loop(Index, 24)
    {
        TransformedVerts.push_back(object->VertexList[Index] + object->Position);
    }

    for_loop(Index, 36)
    {
        TransformedIndices.push_back(object->IndexList[Index] + VertexCount);
    }

    IndexBuffers.insert(  IndexBuffers.end(),    TransformedIndices.begin(),     TransformedIndices.end());
    VertexBuffers.insert( VertexBuffers.end(),  TransformedVerts.begin(),    TransformedVerts.end());
    TextureBuffers.insert(TextureBuffers.end(), object->TextureCoords.begin(), object->TextureCoords.end());
  
    VertexCount  += 24;
    IndexCount += 36;
}
void BatchRender::Build()
{
    Vertices = new VertexBuffer  (&VertexBuffers[0], VertexCount);
    Indices  = new IndexBuffer   (&IndexBuffers[0], IndexCount);
    Textures = new TextureBuffer (BatchTexture, &TextureBuffers[0], VertexCount);
}






Sky::Sky(Texture *skytext)
{

//f_TRACE(Print("Block Constructor"));

    GLfloat size = 200;

    Vec3 V[] = 
    {                                                   
            Vec3(-size,-size, size), // FRONT    // 0                                             
            Vec3( size,-size, size),             // 1                                    
            Vec3( size, size, size),             // 2                                    
            Vec3(-size, size, size),             // 3                                    
                                                                                     
            Vec3( size, size, size), // RIGHT    // 4    2                                        
            Vec3( size, size,-size),             // 5                                    
            Vec3( size,-size,-size),             // 6                                    
            Vec3( size,-size, size),             // 7    1                                
                                                        
            Vec3(-size,-size,-size), // BACK     // 8                                            
            Vec3( size,-size,-size),             // 9    6                               
            Vec3( size, size,-size),             // 10   5                                
            Vec3(-size, size,-size),             // 11
                                                    
            Vec3(-size,-size,-size), // LEFT     // 12   8                                        
            Vec3(-size,-size, size),             // 13   7                              
            Vec3(-size, size, size),             // 14   3                                
            Vec3(-size, size,-size),             // 15  11                                
                                                       
            Vec3( size, size, size), // TOP      // 16   2                                      
            Vec3(-size, size, size),             // 17   3                                
            Vec3(-size, size,-size),             // 18   11                                
            Vec3( size, size,-size),             // 19   5                                
                                                        
            Vec3(-size,-size,-size), // BOTTOM   // 20   8                                   
            Vec3( size,-size,-size),             // 21   9                          
            Vec3( size,-size, size),             // 22   1                          
            Vec3(-size,-size, size),             // 23   0                               
    };
#if 0
    Vec2 UVs[] = 
    {                                                   
            Vec2(0.00f, 0.66f),  // FRONT  // 0                                             
            Vec2(0.00f, 0.33f),            // 1                                             
            Vec2(0.25f, 0.33f),            // 2                                             
            Vec2(0.25f, 0.66f),            // 3                                             
                                                          
            Vec2(0.25f, 0.33f),  // RIGHT  // 4                                             
            Vec2(0.50f, 0.33f),            // 5                                             
            Vec2(0.50f, 0.00f),            // 6                                             
            Vec2(0.25f, 0.00f),            // 7                                             
                                           
            Vec2(0.75f, 0.66f),  // BACK   // 8                                             
            Vec2(0.75f, 0.33f),            // 9                                             
            Vec2(0.50f, 0.33f),            // 10                                             
            Vec2(0.50f, 0.66f),            // 11
                                            
            Vec2(0.50f, 1.00f),  // LEFT   // 12                                             
            Vec2(0.25f, 1.00f),            // 13                                             
            Vec2(0.25f, 0.66f),            // 14                                             
            Vec2(0.50f, 0.66f),            // 15                                             
 
            Vec2(0.25f, 0.33f),  // TOP    // 16                                             
            Vec2(0.25f, 0.66f),            // 17                                             
            Vec2(0.50f, 0.66f),            // 18                                             
            Vec2(0.50f, 0.33f),            // 19     

            Vec2(0.75f, 0.66f),  // BOTTOM // 20                                             
            Vec2(0.75f, 0.33f),            // 21                                             
            Vec2(1.00f, 0.33f),            // 22                                             
            Vec2(1.00f, 0.66f),            // 23                 
    };
#else
    Vec2 UVs[] =
    {
        Vec2(0.00f, 1.00f),                                    
        Vec2(0.33f, 1.00f),                           
        Vec2(0.33f, 0.50f),                                      
        Vec2(0.00f, 0.50f),                         

        Vec2(0.33f, 0.50f),                                        
        Vec2(0.66f, 0.50f),              
        Vec2(0.66f, 1.00f),                                  
        Vec2(0.33f, 1.00f),            
                                   

        Vec2(1.00f, 1.00f),            
        Vec2(0.66f, 1.00f),             
        Vec2(0.66f, 0.50f),                        
        Vec2(1.00f, 0.50f),  

        Vec2(0.00f, 0.50f),  // LEFT   // 12                                             
        Vec2(0.33f, 0.50f),            // 13                                             
        Vec2(0.33f, 0.00f),            // 14                                             
        Vec2(0.00f, 0.00f),            // 15  
                  
         
        Vec2(0.67f, 0.50f),  // BOTTOM // 20    
        Vec2(0.67f, 0.00f),            // 22                                             
        Vec2(1.00f, 0.00f),            // 23   
        Vec2(1.00f, 0.50f),            // 21       



        Vec2(0.66f, 0.50f),            // 17    
        Vec2(0.66f, 0.00f),            // 18     
        Vec2(0.345f, 0.00f),            // 19         
        Vec2(0.345f, 0.50f),  // TOP    // 16     
};
#endif
    GLuint Indexdata[]=
    { 
        0,1,2,    0,2,3,     // FRONT
        6,5,4,    4,7,6,     // RIGHT 
        10,9,8,   8,11,10,   // BACK
        12,13,14, 12,14,15,  // LEFT
        18,17,16, 16,19,18,  // TOP
        20,21,22, 20,22,23   // BOTTOM
    };


    for_loop(Index, 24)
    {
        VertexList.push_back(V[Index]);
        TextureCoords.push_back(UVs[Index]);

    }

    for_loop(Index, 36)
    {
        IndexList.push_back(Indexdata[Index]);
    }


    
   Vertices = new VertexBuffer(&VertexList[0], 24);
   Indices  = new IndexBuffer (&IndexList[0] , 36);

   Textures = new TextureBuffer(skytext , &TextureCoords[0], 24);


   VAO = new VAOBuffer();

   VAO->Attach(Vertices);
   VAO->Attach(Indices);
   VAO->Attach(Textures);


   std::memcpy(&UV     ,          &UVs,  sizeof(UVs));
   std::memcpy(&Indice ,     Indexdata,  sizeof(Indexdata));
   std::memcpy(&Verts  ,            &V,  sizeof(V));




}


void Sky::Render(Vec3 rot)
{
//
//
//  
//      glTranslatef(Position.x, Position.y, Position.z);

//
    
    glPushMatrix();
    glLoadIdentity();
     glRotatef( 180, 1.0f, 0.0f, 0.0f);

       glRotatef(  rot.x, 1.0f, 0.0f, 0.0f);
       glRotatef( -rot.y, 0.0f, 1.0f, 0.0f);

    // glRotatef(rot.x, 0.0f, 1.0f, 0.0f);


        VAO->Bind();
            glDrawElements(GL_TRIANGLES, Indices->ElementCount , GL_UNSIGNED_INT, nullptr);
        VAO->Unbind();

        glPopMatrix();

}

//    GLfloat Alpha = 0; // Fix this to work off of 24 Vertices in the future. May need it for Simulated lighting.
//
//    Vec4 A = Vec4(GL_Color(0)  ,  GL_Color(0)  ,  GL_Color(  0),   GL_Color(Alpha)),   // 0
//         B = Vec4(GL_Color(255),  GL_Color(0)  ,  GL_Color(  0),   GL_Color(Alpha)),   // 1
//         C = Vec4(GL_Color(0)  ,  GL_Color(255),  GL_Color(  0),   GL_Color(Alpha)),   // 2
//         D = Vec4(GL_Color(0)  ,  GL_Color(0)  ,  GL_Color(255),   GL_Color(Alpha)),   // 3 
//         E = Vec4(GL_Color(255),  GL_Color(255),  GL_Color(  0),   GL_Color(Alpha)),   // 5
//         F = Vec4(GL_Color(255),  GL_Color(0)  ,  GL_Color(255),   GL_Color(Alpha)),   // 6
//         G = Vec4(GL_Color(0)  ,  GL_Color(255),  GL_Color(255),   GL_Color(Alpha)),   // 8
//         H = Vec4(GL_Color(255),  GL_Color(255),  GL_Color(255),   GL_Color(Alpha));   // 11 
//
//
//#if 1
//     Vec4 ColorBuff[] = 
//     {
//         A,B,C,D,
//         C,E,F,B,
//         G,F,E,H, 
//         G,B,D,H,                               
//         C,D,H,E,
//         G,F,B,A,
//     };
//#else 
//     Vec4 ColorBuff[] = 
//     {
//         Vec4(1.0,2.0,3.0,4.0)
//     };
//#endif

//   ColorList.push_back(ColorBuff[Index]);

//   Colors   = new ColorBuffer (&ColorList[0] , 24);
//   std::memcpy(&Color ,    &ColorBuff,  sizeof(ColorBuff));  


//~ destructor
//     delete(Colors  ); 