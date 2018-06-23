#version 110 

uniform sampler2D ShadowMap;
varying vec4 ShadowCoord;

void main()
{	

	vec4 shadowCoordinateWdivide = (ShadowCoord / ShadowCoord.w ) * .5 +  .5;
	
	// Used to lower moiré pattern and self-shadowing
	shadowCoordinateWdivide.z += 0.0005;
	
	float distanceFromLight = texture2D(ShadowMap,shadowCoordinateWdivide.st).z;
	
 	float shadow = 1.0;
 	if (ShadowCoord.w > 0.0)
 		shadow = distanceFromLight < shadowCoordinateWdivide.z ? 0.5 : 1.0 ;
	
    gl_FragDepth = 1.0;//shadow;
	//gl_FragColor = vec4(1.0,1.0,1.0,1.0);
}