#version 450 core

in vec4 color;
in vec3 normal;
in vec3 texcoord;

out vec4 fcolor;

uniform sampler3D tex;

uniform float t;


void main()
{

  if(gl_FrontFacing == true)
  {
    fcolor = texture(tex, texcoord+vec3(0.5*sin(t),0.5+2*sin(t),sin(t)));
  }
  else
  {
    discard;
  }
}
