//#define GLEW_STATIC
//#include <GL/glew.h>

#include"Window.h"
#include"Camera.h"
#include"Core.h"
#include"Texture.h"
#include"Renderer.h"
#include"Shader.h"
#include"Lights.h"

std::vector<Block*> Chunk;


Texture *BlockTexture,
        *StoneTexture, 
        *ShadowTexture;


Camera Camera1;
bool View = false;


/// I also explictly handled this before in the main loop for debug reasons, I have a tiny persistant error with the 
//keyboard and mouse  I have yet to fix so the callback leads to delayed response right now.


void Keydown  (GLushort Keycode, GLushort ScanCode, GLushort Modifier)
{
// --------------------- Handle Input ---------------------------------------------
        if(SCREEN->KEY_BOARD.Key == GLFW_KEY_SPACE)
        {
             View = !View;
             if (View == true) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE );
             if (View == false)    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL );
             Sleep(200);
        }
         
        if(SCREEN->KEY_BOARD.Key == GLFW_KEY_RIGHT)
        {
            Camera1.MoveRight(.2);
        } 
        if(SCREEN->KEY_BOARD.Key == GLFW_KEY_LEFT)
        {
            Camera1.MoveLeft(.2);
        }
        if(SCREEN->KEY_BOARD.Key == GLFW_KEY_DOWN)
        { 
            Camera1.MoveForward(.2);
        }
        if(SCREEN->KEY_BOARD.Key == GLFW_KEY_UP) 
        {
             Camera1.MoveBack(.2);
        }
  
}



void main()
{

    float Angle = 0;
    float OLDMX = 0, OLDMY = 0;
    Window MainWin(0,0,640,480,"Test OpenGL Window");
           MainWin.Callbacks.SetOnKeyHold(Keydown);
           
    BlockTexture  = new Texture("Kait.bmp");
    StoneTexture  = new Texture("Stone.bmp");
    ShadowTexture = new Texture();
//-----------------------------------------------------------------------
    const GLubyte *extensions = glGetString( GL_EXTENSIONS );
    Print(extensions);
    Print( "OpenGL Version: "  ; Print(glGetString(GL_VERSION)));
    Print( "Renderer: "        ; Print(    glGetString(GL_RENDERER)));
    Print( "Current Context: " ; Print(wglGetCurrentContext()));
 //-- Just Information Scope --------------------------------------------
        
        
        BatchRender Batcher;
        
        Vec3 Data[4] = {
            Vec3(-10,10,-10),
            Vec3( 10,10,-10),
            Vec3( 10,10, 10),
            Vec3(-10,10, 10),
        };
        GLuint IndData[] = {
            0,1,2 , 0,2,3
        };
        
        VertexBuffer Plane(Data,4);
        IndexBuffer PlanIndex(IndData,6);
        
        Camera1.Position = Vec3(0,0,-33);
        Camera1.Rotation = Vec3(-180,180,0);
        Chunk.reserve(CHUNK_SIZE*CHUNK_SIZE);
        int ZIndex = 0;
        
        for_loop(YIndex, CHUNK_SIZE)
        {
            for_loop(XIndex, CHUNK_SIZE)
            {
                Block *B = new Block(Vec3(XIndex*5.001, ZIndex * 2.001f, YIndex * 5.001), MetaData(1, Stone));
                Batcher.Submit(B);
                Chunk.emplace_back(B);
    
            }
        }
        ZIndex+=1;
        for_loop(YIndex, CHUNK_SIZE)
        {
            for_loop(XIndex, CHUNK_SIZE)
            {
                Block *B = new Block(Vec3(XIndex*5.001, ZIndex * 2.001f, YIndex * 5.001), MetaData(1, Dirt));
                Batcher.Submit(B);
                Chunk.emplace_back(*&B);
            }
        }
        
        Batcher.Init();
        
        // glEnable(GL_CULL_FACE); 
        // glCullFace(GL_BACK);
        
        
        float Brightness = .5;
        LightSource Light(Vec4(10,7,10,0),
                          Vec3(Brightness,Brightness,Brightness),
                          Vec3(Brightness,Brightness,Brightness),
                          Vec3(Brightness,Brightness,Brightness));
        Light.CreateShadowMap();
        
        
        Shader m_Shader("basic.vert", 
                        "basic.frag");
        
        
        Shader ShadowShader("Shadow.vert", 
                            "Shadow.frag");
        m_Shader.Disable();
        ShadowShader.Disable();  // Just making sure everything is off at the start



        Vec2 SUVs[] = {
                     Vec2(.00f, 1.00f),
                     Vec2(0.00f, 0.00f),
                     Vec2(1.00f, 0.00f),
                     Vec2(1.00f, 1.00f)
        };
        GLuint PlaneUV;
        glGenBuffers(1, &PlaneUV);
        glBindBuffer(GL_ARRAY_BUFFER, PlaneUV);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vec2) * 4 , SUVs, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);


 

GLuint frameBuffer;
glGenFramebuffersEXT(1, &frameBuffer);
glBindFramebufferEXT(GL_FRAMEBUFFER, frameBuffer);

GLuint texColorBuffer;
glGenTextures(1, &texColorBuffer);
glBindTexture(GL_TEXTURE_2D, texColorBuffer);



glTexImage2D
    (GL_TEXTURE_2D, 0, GL_RGB, 640, 480, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

glFramebufferTexture2DEXT
    (GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);

if(glCheckFramebufferStatusEXT(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
{
	std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebufferEXT(GL_FRAMEBUFFER, 0); 
}

    glBindFramebufferEXT(GL_FRAMEBUFFER, 0); 

//GLuint rboDepthStencil;
//glGenRenderbuffersEXT(1, &rboDepthStencil);
//glBindRenderbufferEXT(GL_RENDERBUFFER, rboDepthStencil);
//glRenderbufferStorageEXT(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
//glFramebufferRenderbufferEXT(
//    GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rboDepthStencil
//);
//glBindRenderbufferEXT(GL_RENDERBUFFER,0);

        while(GAME_LOOP())
        {
            CLS(0xffffff);
     
            Angle++; if(Angle > 360)Angle = 0;
        
            if(SCREEN->KEY_BOARD.Key == GLFW_KEY_RIGHT){Camera1.MoveRight(.1);} 
            if(SCREEN->KEY_BOARD.Key == GLFW_KEY_LEFT){Camera1.MoveLeft(.1);}
            if(SCREEN->KEY_BOARD.Key == GLFW_KEY_DOWN){Camera1.MoveForward(.1);}
            if(SCREEN->KEY_BOARD.Key == GLFW_KEY_UP){Camera1.MoveBack(.1);}
        
            Camera1.Rotate((-(SCREEN->MOUSE.X - OLDMX)) , (SCREEN->MOUSE.Y - OLDMY) ) ;
            OLDMX = SCREEN->MOUSE.X; // MOUSE.MouseMove.X only works when the callback is being activated
            OLDMY = SCREEN->MOUSE.Y; // Must gather the true mousemovement here in this function 
            Camera1.Update();                             // <---- CAMERA                 
          //  Light.SetPosition(Vec3(std::cos(RADIANS(Angle)),0,sin(RADIANS(Angle))), Vec3(0, Camera1.Rotation.y,0));
        

glBindFramebufferEXT(GL_FRAMEBUFFER, frameBuffer);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Batcher.Render();


glBindFramebufferEXT(GL_FRAMEBUFFER, 0);







glPushMatrix();

glMatrixMode(GL_MODELVIEW);
glTranslatef(10.0,-7.0,10.0);

Plane.Bind();
    PlanIndex.Bind();
        glBindTexture(GL_TEXTURE_2D, texColorBuffer);

        glBindBuffer(GL_ARRAY_BUFFER, PlaneUV);
        glTexCoordPointer(2, GL_FLOAT, 0, (char *) NULL);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

            glDrawElements(GL_TRIANGLES, PlanIndex.ElementCount , GL_UNSIGNED_INT, nullptr);

        glBindBuffer(GL_ARRAY_BUFFER, 0);


        glBindTexture(GL_TEXTURE_2D, 0);
    PlanIndex.Unbind();
Plane.Unbind();

glPopMatrix();


            m_Shader.Enable();
#if 1
            for(auto &Block : Chunk)
            {
                Block->Render();
            }
#else
            Batcher.Render();
#endif
            m_Shader.Disable();

            // Print(Camera1.Position.x << Camera1.Position.y << Camera1.Position.z );
            // Print(Camera1.Rotation.x << " : " << Camera1.Rotation.y << ": " << Camera1.Rotation.z); 
            // Print(MainWin.FPS);

            SYNC();
      }

glDeleteFramebuffersEXT(1, &frameBuffer);
}