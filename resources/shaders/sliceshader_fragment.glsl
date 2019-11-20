#version 450 core

in vec4 color;
in vec3 normal;
in vec3 texcoord;

out vec4 fcolor;

uniform sampler3D tex;

uniform float t;



float scale = 0.4;    //makes the texture larger
// float scale = 3.0;    //makes the texture smaller - makes it loop a bunch of times

void main()
{

  if(gl_FrontFacing == true)
  {
    fcolor = texture(tex, scale*texcoord+vec3(0.5*sin(t),0.5+2*sin(t),sin(t)));
  }
  else
  {
    discard;
  }
}
