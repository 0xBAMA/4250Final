#version 450 core

in vec3 vPosition;
in vec3 vTexCoord;
in vec3 vNormal;
in vec4 vColor;

out vec4 color;
out vec3 normal;
out vec3 texcoord;

uniform float t;

uniform mat4 view;
uniform mat4 proj;



//thanks to Neil Mendoza via http://www.neilmendoza.com/glsl-rotation-about-an-arbitrary-axis/
mat4 rotationMatrix(vec3 axis, float angle)
{
    axis = normalize(axis);
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;

    return mat4(oc * axis.x * axis.x + c,           oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,  0.0,
                oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,           oc * axis.y * axis.z - axis.x * s,  0.0,
                oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c,           0.0,
                0.0,                                0.0,                                0.0,                                1.0);
}


void main()
{

  vec4 vPosition_local = rotationMatrix(vec3(0,0.3,1),0.1*t)*rotationMatrix(vec3(0.1,1,0),t)*vec4(vPosition,1.0);

  gl_Position = proj * view * vPosition_local;
  color = vColor;
  normal = vNormal;
  texcoord = vTexCoord;

}
