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
#include"SkyBox.h"

std::vector<Block*> Chunk;

Shader *ShadowShader;
Texture *BlockTexture,
        *StoneTexture, 
        *ShadowTexture;


//Texture *SkyBox;
SkyBox *Sky;

Camera Camera1;
bool View = false;

/// I also explictly handled this before in the main loop for debug reasons, I have a tiny persistant error with the 
//keyboard and mouse  I have yet to fix so the callback leads to delayed response right now.
void Keydown(GLushort Keycode, GLushort ScanCode, GLushort Modifier)
{
// --------------------- Handle Input ---------------------------------------------
        if(SCREEN->KEY_BOARD.Key == GLFW_KEY_SPACE)
        {
             View = !View;
             if (View == true)    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE );
             if (View == false)   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL );
             Sleep(200);
        }
         
        if(SCREEN->KEY_BOARD.Key == GLFW_KEY_RIGHT)
        {
        //    Camera1.MoveRight(0.2f);
            SCREEN->Camera.StrifeRight(0.02f); // New Matrix Camera
        } 
        if(SCREEN->KEY_BOARD.Key == GLFW_KEY_LEFT)
        {
         //   Camera1.MoveLeft(0.2f);
            SCREEN->Camera.StrifeLeft(0.02f); // New Matrix Camera
        }
        if(SCREEN->KEY_BOARD.Key == GLFW_KEY_DOWN)
        { 
         //   Camera1.MoveForward(0.2f);
             SCREEN->Camera.MoveBack(0.02f); // New Matrix Camera
        }
        if(SCREEN->KEY_BOARD.Key == GLFW_KEY_UP) 
        {
           //  Camera1.MoveBack(0.2f);
             SCREEN->Camera.MoveForward(0.02f); // New Matrix Camera
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
      
        Shader BasicShader( "basic.vert", "basic.frag");
        Shader CubeMap( "CubeMap.vert", "CubeMap.frag");
        Shader ShadowShader ("Shadow.vert", "Shadow.frag");


        BlockTexture  = new Texture("Kait.bmp");
        StoneTexture  = new Texture("Stone.bmp");
        ShadowTexture = new Texture();


       // SkyBox        = new Texture("Sky2.bmp");
        Sky = new SkyBox(CubeMap);
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
// Matrix Implementation for the Main Camera in the Window class
         MainWin.Camera =   Cam(Vec3(10,10,0),
                                Vec3(-180,-180,0.0f));

         Chunk.reserve(CHUNK_SIZE*CHUNK_SIZE);
         int ZIndex = 0;


         for_loop(YIndex, CHUNK_SIZE)
         {
             for_loop(XIndex, CHUNK_SIZE)
             {
                  Block *B = new Block(Vec3(XIndex * 2.001 - (CHUNK_SIZE / 2), ZIndex * 2.001f, YIndex * 2.001 - (CHUNK_SIZE / 2)), MetaData(1, Stone));
                  Batcher.Submit(B);
                  Chunk.emplace_back(B);
             }
         }

         for_loop(YIndex, CHUNK_SIZE)
         {
             Block *B = new Block(Vec3(rand()%60, (rand()%5) * 2.001f, rand()%60), MetaData(1, Stone));
             Batcher.Submit(B);
             Chunk.emplace_back(B);
         }


         Batcher.Build();

//     Sky *SkyBoxCube = new Sky(SkyBox);   



//     glEnable(GL_CULL_FACE); 
//     glCullFace(GL_BACK);
       
       
float Brightness = .7;
#if 1
      LightSource Light(BasicShader,
                        Vec4(10,7,10,0),
                        Vec3(Brightness,Brightness,Brightness),
                        Vec3(Brightness,Brightness,Brightness),
                        Vec3(Brightness,Brightness,Brightness));
#else
      LightSource Light(BasicShader,
                        Vec4(10,7,10,0),
                        Brightness,
                        Brightness,
                        Brightness);
 
#endif


        FrameBuffer *FB = new FrameBuffer(BasicShader, 640,480);

        Vec3 COL(1.0,0.0,0.0);
        BasicShader.AttachUniform("Color", Uniformtype::Vector3, (Vec3*)&COL);


        GLfloat FF_MODELVIEW[16], FF_PROJECTION[16];
        glGetFloatv(GL_PROJECTION_MATRIX,  &FF_PROJECTION[0]) ;
        Matrix Projection;

        Projection[0][0] = FF_PROJECTION[0];
        Projection[0][1] = FF_PROJECTION[1];
        Projection[0][2] = FF_PROJECTION[2];
        Projection[0][3] = FF_PROJECTION[3];

        Projection[1][0] = FF_PROJECTION[4];
        Projection[1][1] = FF_PROJECTION[5];
        Projection[1][2] = FF_PROJECTION[6];
        Projection[1][3] = FF_PROJECTION[7];

        Projection[2][0] = FF_PROJECTION[8];
        Projection[2][1] = FF_PROJECTION[9];
        Projection[2][2] = FF_PROJECTION[10];
        Projection[2][3] = FF_PROJECTION[11];

        Projection[3][0] = FF_PROJECTION[12];
        Projection[3][1] = FF_PROJECTION[13];
        Projection[3][2] = FF_PROJECTION[14];
        Projection[3][3] = FF_PROJECTION[15];


        while(GAME_LOOP())
        {
          CLS();

           Angle++; if(Angle > 360)Angle = 0;
       
           if(SCREEN->KEY_BOARD.Key == GLFW_KEY_RIGHT) { Camera1.MoveRight(.1);   } 
           if(SCREEN->KEY_BOARD.Key == GLFW_KEY_LEFT)  { Camera1.MoveLeft(.1);    }
           if(SCREEN->KEY_BOARD.Key == GLFW_KEY_DOWN)  { Camera1.MoveForward(.1); }
           if(SCREEN->KEY_BOARD.Key == GLFW_KEY_UP)    { Camera1.MoveBack(.1);    }
       
           Camera1.Rotate((-(SCREEN->MOUSE.X - OLDMX)), (SCREEN->MOUSE.Y - OLDMY) ) ;
//         MainWin.Camera.Rotate(-(SCREEN->MOUSE.X - OLDMX) / 4, (SCREEN->MOUSE.Y - OLDMY) / 4 );
// MainWin.Camera.Rotate(-(SCREEN->MOUSE.X - OLDMX), (SCREEN->MOUSE.Y - OLDMY));
           OLDMX = SCREEN->MOUSE.X; // MOUSE.MouseMove.X only works when the callback is being activated
           OLDMY = SCREEN->MOUSE.Y; // Must gather the true mousemovement here in this function 
           Camera1.Update();             // <---- CAMERA                 
           MainWin.Camera.Update();

           Light.SetPosition(Vec3(std::cos(RADIANS(Angle)) * 20,0,std::sin(RADIANS(Angle)) * 20), Vec3(0, Camera1.Rotation.y,0));


BasicShader.Enable();
#if 0
            for(auto &Block : Chunk)
            {
                 Block.Render();
            }
#else
        Matrix ModelView = glm::mat4(1.0f);
        BasicShader.SetUniformMat4("ProjectionMatrix", MainWin.Camera.GetViewProjection());//Camera1.ViewProjectionMatrix);
        BasicShader.SetUniformMat4("ModelMatrix", ModelView);//Camera1.ViewProjectionMatrix);
        Batcher.Render();
#endif
BasicShader.Disable();

  //Print(Camera1.Rotation.x << " : " << Camera1.Rotation.y << ": " << Camera1.Rotation.z); 
  //Print(MainWin.FPS);                                                                                                                                                    
        SYNC();


    }


    Light.Delete();
    ShadowShader.Delete();
    BasicShader.Delete();
    CubeMap.Delete();

    delete( BlockTexture);
    delete( StoneTexture);
    delete( ShadowTexture);
    
}





    
// Print(Camera1.Position.x << Camera1.Position.y << Camera1.Position.z );

// Light.SetPosition(Vec3(0,0,0),Vec3(0,0,0));