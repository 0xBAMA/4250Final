#version 450 core

in vec3 position;
in vec4 color;
in vec3 normal;
in vec3 texcoord;

out vec4 fcolor;

uniform sampler3D tex;


#define NUM_STEPS 1000

#define MIN_DISTANCE 0.0
#define MAX_DISTANCE 1000.0

uniform float t;




uniform vec2 rotation;
uniform vec3 location;




// hit() code adapted from:
//
//    Amy Williams, Steve Barrus, R. Keith Morley, and Peter Shirley
//    "An Efficient and Robust Ray-Box Intersection Algorithm"
//    Journal of graphics tools, 10(1):49-54, 2005



double t0 = MIN_DISTANCE;
double t1 = MAX_DISTANCE;

double tmin, tmax; //global scope, set in hit() to tell min and max parameters


vec3 gorg = vec3(0);
vec3 gdir = vec3(0);



bool hit(vec3 ray_org, vec3 dir)
{
  //the bounding box is from 000 to 111
  // vec3 min = vec3(-1,-1,-1);
  vec3 min = vec3(0,0,0);
  vec3 max = vec3(1,1,1);

  int sign[3];

  vec3 inv_direction = vec3(1/dir.x, 1/dir.y, 1/dir.z);

	sign[0] = (inv_direction[0] < 0)?1:0;
  sign[1] = (inv_direction[1] < 0)?1:0;
	sign[2] = (inv_direction[2] < 0)?1:0;

  vec3 bbox[2] = {min,max};

  tmin = (bbox[sign[0]][0] - ray_org[0]) * inv_direction[0];
  tmax = (bbox[1-sign[0]][0] - ray_org[0]) * inv_direction[0];

  double tymin = (bbox[sign[1]][1] - ray_org[1]) * inv_direction[1];
  double tymax = (bbox[1-sign[1]][1] - ray_org[1]) * inv_direction[1];

  if ( (tmin > tymax) || (tymin > tmax) )
    return false;
  if (tymin > tmin)
    tmin = tymin;
  if (tymax < tmax)
    tmax = tymax;

  double tzmin = (bbox[sign[2]][2] - ray_org[2]) * inv_direction[2];
  double tzmax = (bbox[1-sign[2]][2] - ray_org[2]) * inv_direction[2];

  if ( (tmin > tzmax) || (tzmin > tmax) )
    return false;
  if (tzmin > tmin)
    tmin = tzmin;
  if (tzmax < tmax)
    tmax = tzmax;
  return ( (tmin < t1) && (tmax > t0) );

  return true;


}


vec4 get_color_for_pixel()
{
  // return vec4(tmax-tmin,0,1,1);

  float current_t = float(tmax); //start at the farthest point into the texture
  vec4 t_color = vec4(0);

  vec4 new_read, old_read;
  old_read = new_read = texture(tex,gorg+current_t*gdir);


  for(int i = 0; i < NUM_STEPS; i++)
  {
    if(current_t>tmin)
    {
      current_t -= 0.001;

      old_read = new_read;
      new_read = texture(tex,gorg+current_t*gdir);
      // new_read = texture(tex,gorg+current_t*gdir+vec3(sin(0.1*t),cos(t),0));

      t_color = mix(old_read,new_read,new_read.a);
    }
  }

  return t_color;
}



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


  // rotation =





  fcolor = color;
  fcolor = vec4(0.396,0.3,0.17,1.0);

gorg = position+vec3(cos(t),sin(t),sin(0.3*t));
// gdir = (rotation * vec4(normal,0.0)).xyz;
gdir = normalize(vec3(normal.xy*1.3,normal.z));

  if(hit(gorg,gdir))
    fcolor = get_color_for_pixel();  //this assumes tmin, tmax defined
  else
    discard;

  // fcolor.xyz *= 0.2/gl_FragCoord.z;


}
