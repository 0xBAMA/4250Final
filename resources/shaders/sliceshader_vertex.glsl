#version 450 core

in vec3 vPosition;
in vec3 vTexCoord;
in vec3 vNormal;
in vec4 vColor;

out vec4 color;
out vec3 normal;
out vec3 texcoord;

void main()
{
  gl_Position = vec4(vPosition, 1.0);
  color = vColor;
  normal = vNormal;
  texcoord = vTexCoord;
}
