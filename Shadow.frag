#version 110 
//
////out vec4 FragColor;
////in vec2 TexCoords;
//
//
//uniform sampler2D depthMap;
//
//void main()
//{             
//    float depthValue = texture(depthMap, gl_TexCoord);
//    gl_FragColor = vec4(vec3(depthValue), 1.0);
//}  
//


uniform sampler2D ShadowMap;

varying vec4 ShadowCoord;

void main()
{	
	vec4 shadowCoordinateWdivide = ShadowCoord / ShadowCoord.w ;
	
	// Used to lower moiré pattern and self-shadowing
	shadowCoordinateWdivide.z += 0.0005;
	
	
	float distanceFromLight = texture2D(ShadowMap,shadowCoordinateWdivide.st).z;
	
	
 	float shadow = 1.0;
 	if (ShadowCoord.w > 0.0)
 		shadow = distanceFromLight < shadowCoordinateWdivide.z ? 0.5 : 1.0 ;
  	
	
	gl_FragColor =	 shadow * gl_Color;
  
}