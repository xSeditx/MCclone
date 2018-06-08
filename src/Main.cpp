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
    Window MainWin(0,0,640,640,"Test OpenGL Window");
           MainWin.Callbacks.SetOnKeyHold(Keydown);
    SCREEN->MOUSE.X = 0; SCREEN->MOUSE.Y = 0; // Have no idea why if this is not Initialized (AGAIN) to zero it returns
                                              // #IND throwing all my Rendering off since it reads the Mouse position to position the Camera
                                              // Only if mouse is not in borders of window during load though

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
        
      //  glEnable(GL_CULL_FACE); 
     //   glCullFace(GL_BACK);
        
        
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

 
        FrameBuffer *FB = new FrameBuffer(&m_Shader);
                     FB->PositionQuad(Vec3(10, 5.5,10));
        

        
        while(GAME_LOOP())
        {
            CLS();

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

FB->Bind();
#    if 0
         for(auto &Block : Chunk)
         {
             Block->Render();
         }
#    else
         Batcher.Render();
#    endif

FB->Unbind();

FB->Render();


            m_Shader.Enable();
#if 1
            for(auto &Block : Chunk)
            {
                Block->Render();
            }
#else
            Batcher.Render();
#endif





            // Print(Camera1.Position.x << Camera1.Position.y << Camera1.Position.z );
            // Print(Camera1.Rotation.x << " : " << Camera1.Rotation.y << ": " << Camera1.Rotation.z); 
            // Print(MainWin.FPS);

            SYNC();
      }

//glDeleteFramebuffersEXT(1, &frameBuffer);
}