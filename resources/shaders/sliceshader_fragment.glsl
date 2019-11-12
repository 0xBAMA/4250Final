#version 450 core

in vec4 color;
in vec3 normal;
in vec3 texcoord;

out vec4 fcolor;

uniform sampler3D tex;

uniform float t;


void main()
{
  // fcolor = color+vec4(normal,1.0)+vec4(texcoord,1.0);
  //
  // fcolor /= 3;


  fcolor = texture(tex, texcoord+vec3(0,0,sin(t)))+color+vec4(normal,1.0);
}
