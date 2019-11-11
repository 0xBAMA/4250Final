#version 450 core
// #version 330

in vec3 vPosition;
in vec3 vTexCoord;
in vec3 vNormal;
in vec4 vColor;

// out vec4 color;

void main()
{
  gl_Position = vec4(vPosition, 1.0);
  // color = vColor;
}
