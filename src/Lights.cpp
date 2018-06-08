#include"Lights.h"
#include "gtc/matrix_transform.hpp"
#include "Texture.h"


// VERY BASIC LIGHTING SYSTEM I PLAN ON EXTENDED AS I WORK ON THE SHADOW MAKER
 int LightSource::NumberOfLights;
extern Texture *ShadowTexture;
//----------------------- ----------------------------------
 LightSource::LightSource(Vec4 pos, RGBf alight, RGBf dlight, RGBf slight)
            : LightNumber(NumberOfLights++),
              ShadowBufferName(0)
{       
     GLfloat a[] = {alight.r,alight.g,alight.b,1};
     GLfloat d[] = {dlight.r,dlight.g,dlight.b,1};
     GLfloat s[] = {slight.r,slight.g,slight.b,1};
     GLfloat p[] = {pos.x,pos.y,pos.z,pos.w};
      glEnable(GL_LIGHTING);  
      glEnable(GL_LIGHT0 + LightNumber);

      glLightf(GL_LIGHT0+LightNumber, GL_POSITION, *p);
          
      glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
      
      glLightfv(GL_LIGHT0+LightNumber, GL_AMBIENT,a);
      glLightfv(GL_LIGHT0+LightNumber, GL_DIFFUSE,d);
      glLightfv(GL_LIGHT0+LightNumber, GL_SPECULAR,s);
    

    // SetPosition(pos, pos);
   
}

 void LightSource::SetAmbient(RGBAf color)
{
    glLightfv(GL_LIGHT0+LightNumber, GL_AMBIENT, &color[0]);
}
 void LightSource::SetSpecular(RGBAf color)
{
    glLightfv(GL_LIGHT0+LightNumber, GL_SPECULAR,&color[0]);
}
 void LightSource::SetDiffuse(RGBAf color)
{
    glLightfv(GL_LIGHT0+LightNumber, GL_DIFFUSE,&color[0]);
}
 void LightSource::SetPosition(Vec3 position, Vec3 direction)
{
    glLightfv(GL_LIGHT0 + LightNumber, GL_POSITION,&position[0]);
}











bool LightSource::CreateShadowMap()
{
     // The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
 //     glGenRenderbuffersEXT(1, uint *renderbuffers);
     glGenFramebuffersEXT(1, &ShadowBufferName);
     glBindFramebufferEXT(GL_FRAMEBUFFER, ShadowBufferName);

     // Depth texture. Slower than a depth buffer, but you can sample it later in your shader

     glGenTextures(1, &ShadowTexture->ID);

     glBindTexture(GL_TEXTURE_2D, ShadowTexture->ID);
     glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT16, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);

     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
     
    // ATTACHES THE DEPTHS BUFFER TO THE TEXTURE SINCE WE DONT NEED THE COLOR THE DEPTH INFO IS RENDERED TO THE TEXTURE
     glFramebufferTexture2DEXT(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, ShadowTexture->ID, 0);
     glDrawBuffer(GL_NONE); // No color buffer is drawn to.
     glReadBuffer(GL_NONE);// Not in original tutorial
     // Always check that our framebuffer is ok
     if(glCheckFramebufferStatusEXT(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
         glBindFramebufferEXT(GL_FRAMEBUFFER,0);
     return false;
}


void LightSource::CreateMatrices()
{
     glm::vec3 lightInvDir = glm::vec3(0.5f,2,2);
 
     // Compute the MVP matrix from the light's point of view
     glm::mat4 depthProjectionMatrix = glm::ortho<float>(-10,10,-10,10,-10,20);
     glm::mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(0,0,0), glm::vec3(0,1,0));
     glm::mat4 depthModelMatrix = glm::mat4(1.0);
     glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;
    
     // Send our transformation to the currently bound shader,
     // in the "MVP" uniform
     glUniformMatrix4fv(1, 1, GL_FALSE, &depthMVP[0][0]);
glm::mat4 biasMatrix(
0.5, 0.0, 0.0, 0.0,
0.0, 0.5, 0.0, 0.0,
0.0, 0.0, 0.5, 0.0,
0.5, 0.5, 0.5, 1.0
);
glm::mat4 depthBiasMVP = biasMatrix*depthMVP;

}

///https://www.khronos.org/opengl/wiki/Framebuffer_Object_Extension_Examples




void setTextureMatrix(void)
{
	static double modelView[16];
	static double projection[16];
	
	// Moving from unit cube [-1,1] to [0,1]  
	const GLdouble bias[16] = {	
		                        0.5, 0.0, 0.0, 0.0, 
		                        0.0, 0.5, 0.0, 0.0,
		                        0.0, 0.0, 0.5, 0.0,
	                            0.5, 0.5, 0.5, 1.0
                              };
	
	// Grab modelview and transformation matrices
	glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	
	glMatrixMode(GL_TEXTURE);
	glActiveTextureARB(GL_TEXTURE7);
	
	glLoadIdentity();	
	glLoadMatrixd(bias);
	
	// concatating all matrices into one.
	glMultMatrixd (projection);
	glMultMatrixd (modelView);
	
	// Go back to normal matrix mode
	glMatrixMode(GL_MODELVIEW);
}			
	//http://ogldev.atspace.co.uk/www/tutorial23/tutorial23.html