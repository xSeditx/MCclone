#version 110
varying vec3 normal;
varying vec3 vertex_to_light_vector;

uniform sampler2D tex;

void main()
{

//   gl_Position = gl_Position * .5 + .5
    vec4 color =  texture2D(tex,gl_TexCoord[0].st);

    const vec4 AmbiantColor      = vec4(.1,0.0,0.0,1.0);
    const vec4 DiffuseColorColor = vec4(1.0,0.0,0.0,1.0);

    vec3 normalized_normal = normalize(normal) * .5 + .5;
    vec3 normalized_vertex_to_light_vector = normalize(vertex_to_light_vector);

    float DiffuseTerm = clamp(dot(normal, vertex_to_light_vector), 0.0, 1.0);

	gl_FragColor = color; // * DiffuseTerm;
}