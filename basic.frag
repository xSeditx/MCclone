#version 120



void main()
{
	gl_FragColor = gl_Color;
}





//uniform sampler2D texture;
//varying vec3 N;
//varying vec3 V;
//
//void main()
//{
//    vec4 texelColor0 = texture2D(texture, gl_TexCoord[0].xy);
// 
//  vec3 Ligg = normalize(gl_LightSource[0].position.xyz - V);   
//
//   vec4 Idiff = gl_FrontLightProduct[0].diffuse * max(dot(N,Ligg), 0.0);  
//   Idiff = clamp(Idiff, 0.0, 1.0); 
//
//	gl_FragColor =  texelColor0 + Idiff;
//}
//
//
//
