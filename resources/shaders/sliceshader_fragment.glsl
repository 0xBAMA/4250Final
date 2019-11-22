#version 450 core

in vec4 color;
in vec3 normal;
in vec3 texcoord;

out vec4 fcolor;

uniform sampler3D tex;






uniform vec2 rotation;
uniform vec3 location;


void main()
{
  // the ray origin will be determined by the location of the viewer,
  // specified in the value of location, and for each pixel a displacement
  // will be figured out using the texture coordinate

  // the ray direction will be determined by using the value of direction,
  // potentially displaced by up and right, to do something like perspective
  // projection - another thing to consider is you might scale the contribution
  // of left and right based on the squared distance of the pixel's xy value
  // from the center, i.e. modeling fisheye effects.








  // fcolor = vec4(1,0.3,0,1);
  fcolor = color;


  // fcolor.xyz *= 0.2/gl_FragCoord.z;


}
