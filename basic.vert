#version 120

void main()
{
	vec3 normal, lightDir;
	vec4 diffuse, ambient, globalAmbient;
	float NdotL;

	normal = normalize(gl_NormalMatrix * gl_Normal);
	lightDir = normalize(vec3(gl_LightSource[0].position));
	NdotL = max(dot(normal, lightDir), 0.0);
	diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;
	/* Compute the ambient and globalAmbient terms */

	ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;
	globalAmbient = gl_LightModel.ambient * gl_FrontMaterial.ambient;
	gl_FrontColor =  NdotL * diffuse + globalAmbient + ambient;

	gl_Position = ftransform();
}





















//varying vec3 N;
//varying vec3 V;
//
//void main() 
//{
//    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
//
//   V = vec3(gl_ModelViewMatrix * gl_Vertex);       
//   N = normalize(gl_NormalMatrix * gl_Normal);
//
// //   gl_TexCoord[0] = gl_MultiTexCoord0;   
//	gl_Position =  gl_ModelViewProjectionMatrix * gl_Vertex;
//}