
#version 110 
 
varying vec4 ShadowCoord;

void main()
{

	ShadowCoord =  vec4(1.0,1.0,1.0,1.0) ; //gl_TextureMatrix[0] * gl_Vertex;
	gl_Position = ftransform();
    gl_FrontColor = gl_Color;
}

