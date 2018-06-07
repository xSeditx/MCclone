#version 110 
//    
//    // Input vertex data, different for all executions of this shader. layout(location = 0) in vec3 vertexPosition_modelspace;
//
//attribute  vec3 vertexPosition_modelspace;
//
//
//// Values that stay constant for the whole mesh.
//uniform mat4 depthMVP;
//    
//void main(){
//     gl_Position =  depthMVP * vec4(vertexPosition_modelspace,1);
//} 


// Used for shadow lookup
varying vec4 ShadowCoord;

void main()
{
	ShadowCoord= gl_TextureMatrix[7] * gl_Vertex;
  
	gl_Position = ftransform();

	gl_FrontColor = gl_Color;
}

