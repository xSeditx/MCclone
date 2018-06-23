//#define GLEW_STATIC
//#include <GL/glew.h>

#include"Window.h"
#include"Camera.h"
#include"Core.h"
#include"Texture.h"
#include"Renderer.h"
#include"Shader.h"
#include"Lights.h"
#include<ctime>


std::vector<Block*> Chunk;

Shader *ShadowShader;
Texture *BlockTexture,
        *StoneTexture, 
        *ShadowTexture;


Texture *SkyBox;


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
        SCREEN->MOUSE.X = 0; SCREEN->MOUSE.Y = 0; // Have no idea why if this is not Initialized (AGAIN) to zero it returns
                                                // #IND throwing all my Rendering off since it reads the Mouse position to position the Camera
                                                // Only if mouse is not in borders of window during load though
      
        BlockTexture  = new Texture("Kait.bmp");
        StoneTexture  = new Texture("Stone.bmp");
        ShadowTexture = new Texture();
        SkyBox        = new Texture("Sky.bmp");


//-----------------------------------------------------------------------
  const GLubyte *extensions = glGetString( GL_EXTENSIONS );
  Print(extensions);
  Print( "OpenGL Version: "  ; Print(glGetString(GL_VERSION)));
  Print( "Renderer: "        ; Print(    glGetString(GL_RENDERER)));
  Print( "Current Context: " ; Print(wglGetCurrentContext()));
//-- Just Information Scope --------------------------------------------
       
       
         BatchRender Batcher(BlockTexture), 
                     Batch2(StoneTexture);
               
         Camera1.Position = Vec3(0,0,0);
         Camera1.Rotation = Vec3(-180,-180,0);
         Chunk.reserve(CHUNK_SIZE*CHUNK_SIZE);
         int ZIndex = 0;

           Shader m_Shader("basic.vert", 
                         "basic.frag");

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
                 Batch2.Submit(B);
                 Chunk.emplace_back(*&B);
             }
         }
         
         Batcher.Build();
         Batch2.Build();
           Sky *SkyBoxCube = new Sky(SkyBox);   
//     glEnable(GL_CULL_FACE); 
//     glCullFace(GL_BACK);
       
       
        float Brightness = .5;
      
       

       
  //   
  //  ShadowShader = new Shader("Shadow.vert", 
  //                           "Shadow.frag");
  //
         LightSource Light(&m_Shader,
                           Vec4(10,7,10,0),
                           Vec3(Brightness,Brightness,Brightness),
                           Vec3(Brightness,Brightness,Brightness),
                           Vec3(Brightness,Brightness,Brightness));
       
      
//        m_Shader.Disable();
//        ShadowShader->Disable();  // Just making sure everything is off at the start
      
        FrameBuffer *FB = new FrameBuffer(&m_Shader, 640,480);
                     FB->PositionQuad(Vec3(10, 5.5,10));
 //       FB->Unbind();
 
   
        while(GAME_LOOP())
        {
          CLS();
          SkyBoxCube->Render(Camera1.Rotation);
           Angle++; if(Angle > 360)Angle = 0;
       
           if(SCREEN->KEY_BOARD.Key == GLFW_KEY_RIGHT) { Camera1.MoveRight(.1);   } 
           if(SCREEN->KEY_BOARD.Key == GLFW_KEY_LEFT)  { Camera1.MoveLeft(.1);    }
           if(SCREEN->KEY_BOARD.Key == GLFW_KEY_DOWN)  { Camera1.MoveForward(.1); }
           if(SCREEN->KEY_BOARD.Key == GLFW_KEY_UP)    { Camera1.MoveBack(.1);    }
       
           Camera1.Rotate((-(SCREEN->MOUSE.X - OLDMX)) , (SCREEN->MOUSE.Y - OLDMY) ) ;
           OLDMX = SCREEN->MOUSE.X; // MOUSE.MouseMove.X only works when the callback is being activated
           OLDMY = SCREEN->MOUSE.Y; // Must gather the true mousemovement here in this function 
           Camera1.Update();             // <---- CAMERA                 

           Light.SetPosition(Vec3(std::cos(RADIANS(Angle)) * 20,0,std::sin(RADIANS(Angle)) * 20), Vec3(0, Camera1.Rotation.y,0));
   



//FB->Bind();
//#if 0
//        for(auto &Block : Chunk)
//        {
//            Block->Render();
//        }
//#else
//        Batcher.Render();
//        Batch2.Render();
//#endif
//FB->Unbind();
//FB->Render();   
//

m_Shader.Enable();
      //      m_Shader.SetUniformMat4("MVP", Camera1.ModelViewProjectionMatrix);

// Light.Shadow->Render();

#if 0
            for(auto &Block : Chunk)
            {
               // for_loop(Index, Block->Vertices->ElementCount)
               // {
               //    Block->Vertices->Data[Index] = Block->Vertices->Data[Index] + 
               //             Vec3(RANDOM(.2) - .1, RANDOM(.2) - .1,RANDOM(.2) - .1); 
               // }
               // Block->Vertices->Rebuild();
                Block->Render();
            }
#else
            Batcher.Render();
            Batch2.Render();
#endif
m_Shader.Disable();

  // Print(Camera1.Rotation.x << " : " << Camera1.Rotation.y << ": " << Camera1.Rotation.z); 

          Light.Render();
 // Print(MainWin.FPS);
          SYNC();
    }


      //  delete(FB);
       //elete(&m_Shader);
   //     delete(ShadowShader);
        delete(BlockTexture);
        delete( StoneTexture);
        delete(  ShadowTexture);
    //    delete(ShadowShader);
}





    
// Print(Camera1.Position.x << Camera1.Position.y << Camera1.Position.z );

// Light.SetPosition(Vec3(0,0,0),Vec3(0,0,0));